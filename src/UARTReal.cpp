#include "UARTReal.hpp"
#include <cstring>

UARTReal::UARTReal(const std::string& port, int baudrate) {
    serial_fd = open(port.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
    if (serial_fd < 0) {
        perror("Erro ao abrir porta serial");
        throw std::runtime_error("Erro ao abrir porta serial: " + port);
    }

    struct termios tty;
    if (tcgetattr(serial_fd, &tty) != 0) {
        perror("tcgetattr");
        close(serial_fd);
        throw std::runtime_error("Erro ao obter atributos da UART");
    }

    // Mesma configuração do seu código base
    cfsetospeed(&tty, baudrate);
    cfsetispeed(&tty, baudrate);

    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tty.c_cflag &= ~CRTSCTS;
    tty.c_cflag |= (CREAD | CLOCAL);

    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    tty.c_oflag &= ~OPOST;

    // ⚠️ IMPORTANTE: o read() precisa ser bloqueante para se comportar como getline()
    fcntl(serial_fd, F_SETFL, 0);

    if (tcsetattr(serial_fd, TCSANOW, &tty) != 0) {
        perror("tcsetattr");
        close(serial_fd);
        throw std::runtime_error("Erro ao configurar UART");
    }

    std::cout << "[UARTReal] Porta " << port << " aberta com sucesso." << std::endl;
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
            if (ch == '\r') continue;

            if (ch == 0x7F || ch == '\b') {
                if (!line.empty()) {
                    line.pop_back();          // remove do buffer
                    const char* bs = "\b \b"; // apaga visualmente
                    ::write(serial_fd, bs, 3);
                }
                continue;
            }

            if (ch == '\n') {
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
