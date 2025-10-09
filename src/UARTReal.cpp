#include "UARTReal.hpp"
#include <cstring>

UARTReal::UARTReal(const std::string& port, int baudrate) {
    serial_fd = open(port.c_str(), O_RDWR | O_NOCTTY);
    if (serial_fd < 0) {
        perror("Erro ao abrir porta serial");
        throw std::runtime_error("Erro ao abrir porta serial: " + port);
    }

    struct termios tty{};
    if (tcgetattr(serial_fd, &tty) != 0) {
        perror("tcgetattr");
        close(serial_fd);
        throw std::runtime_error("Erro ao obter atributos da UART");
    }

    cfmakeraw(&tty); // garante modo raw (sem eco, canônico, etc.)

    // ⚙️ Mapeia o baudrate numérico para a constante certa
    speed_t speed;
    switch (baudrate) {
    case 9600:
        speed = B9600;
        break;
    case 19200:
        speed = B19200;
        break;
    case 38400:
        speed = B38400;
        break;
    case 57600:
        speed = B57600;
        break;
    case 115200:
        speed = B115200;
        break;
    default:
        std::cerr << "[UARTReal] Baudrate não suportado: " << baudrate
                  << ", usando 115200" << std::endl;
        speed = B115200;
        break;
    }

    cfsetospeed(&tty, speed);
    cfsetispeed(&tty, speed);

    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tty.c_cflag &= ~CRTSCTS;
    tty.c_cflag |= (CREAD | CLOCAL);

    // modo bloqueante (para getline ou leitura contínua)
    fcntl(serial_fd, F_SETFL, 0);

    if (tcsetattr(serial_fd, TCSANOW, &tty) != 0) {
        perror("tcsetattr");
        close(serial_fd);
        throw std::runtime_error("Erro ao configurar UART");
    }

    std::cout << "[UARTReal] Porta " << port << " aberta a "
              << baudrate << " baud com sucesso." << std::endl;
}

UARTReal::~UARTReal() {
    if (serial_fd >= 0) close(serial_fd);
}

void UARTReal::write(const std::string& data) {
    if (serial_fd < 0) return;

    std::string fixed = data;
    // Substitui \n por \r\n
    for (size_t i = 0; i < fixed.size(); ++i) {
        if (fixed[i] == '\n' && (i == 0 || fixed[i - 1] != '\r')) {
            fixed.insert(i, "\r");
            ++i; // pula o caractere recém-inserido
        }
    }

    ssize_t bytes = ::write(serial_fd, fixed.c_str(), fixed.size());
    if (bytes < 0) {
        perror("Erro no write()");
    } else {
        tcdrain(serial_fd);
    }
}

std::string UARTReal::readLine() {
    if (serial_fd < 0) return "";

    std::string line;
    char ch;
    ssize_t n;

    while (true) {
        n = ::read(serial_fd, &ch, 1);
        if (n > 0) {
            if (ch == 0x7F || ch == '\b') {
                if (!line.empty()) {
                    line.pop_back();          // remove do buffer
                    const char* bs = "\b \b"; // apaga visualmente
                    ::write(serial_fd, bs, 3);
                }
                continue;
            }

            if (ch == '\n' || ch == '\r') {
                const char* rn = "\r\n";
                ::write(serial_fd, rn, 2);
                break;
            } else {
                ::write(serial_fd, &ch, 1);
            }
            line += ch;
        } else if (n < 0) {
            perror("Erro no read()");
            break;
        } else {
            // n == 0 → fim de leitura
            usleep(1000);
        }
    }

    return line;
}
