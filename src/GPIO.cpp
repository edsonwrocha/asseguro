#include "GPIO.hpp"

GPIO::GPIO(int pin, GPIODirection direction)
    : pin(pin), direction(direction), state(false), chip("/dev/gpiochip0") {
    try {
        // 1. Configura line_settings
        gpiod::line_settings settings;
        if (direction == GPIODirection::OUTPUT)
            settings.set_direction(gpiod::line::direction::OUTPUT)
                .set_output_value(gpiod::line::value::INACTIVE);
        else
            settings.set_direction(gpiod::line::direction::INPUT);

        // 2. Configura line_config
        gpiod::line_config config;
        config.add_line_settings(pin, settings);

        // 3. Configura request_config
        gpiod::request_config req_cfg;
        req_cfg.set_consumer("GPIO_class");

        // 4. Cria request_builder **a partir do chip**
        auto req_builder = chip.prepare_request(); // retorna temporário
        req_builder.set_request_config(req_cfg);
        req_builder.set_line_config(config);

        // 5. Executa o request e armazena em optional
        line_req = req_builder.do_request();

        std::cout << "[GPIO] Pin " << pin << " inicializado como "
                  << (direction == GPIODirection::OUTPUT ? "SAÍDA" : "ENTRADA") << "\n";

    } catch (const std::exception& e) {
        std::cerr << "[GPIO] Erro ao inicializar o pin " << pin << ": " << e.what() << "\n";
    }
}

GPIO::~GPIO() {
    try {
        if (line_req.has_value())
            line_req->release();
    } catch (...) {
        // Ignora erros na liberação
    }
}

void GPIO::write(bool value) {
    if (direction == GPIODirection::OUTPUT) {
        try {
            if (line_req.has_value())
                line_req->set_value(pin, value ? gpiod::line::value::ACTIVE : gpiod::line::value::INACTIVE);
            state = value;
            std::cout << "[GPIO] Pin " << pin << " setado para " << (value ? "HIGH" : "LOW") << "\n";
        } catch (const std::exception& e) {
            std::cerr << "[GPIO] Erro ao escrever no pin " << pin << ": " << e.what() << "\n";
        }
    } else {
        std::cerr << "[GPIO] Tentativa de escrita em pino configurado como ENTRADA!\n";
    }
}

bool GPIO::read() {
    if (direction == GPIODirection::INPUT) {
        try {
            if (line_req.has_value())
                return line_req->get_value(pin) == gpiod::line::value::ACTIVE;
        } catch (const std::exception& e) {
            std::cerr << "[GPIO] Erro ao ler pin " << pin << ": " << e.what() << "\n";
        }
        return false;
    }
    return state;
}

int GPIO::getPin() const { return pin; }
