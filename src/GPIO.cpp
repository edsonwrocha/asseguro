#include "GPIO.hpp"
#include <iostream>

GPIO::GPIO(int pin, GPIODirection direction)
    : pin(pin), direction(direction), state(false) {
    std::cout << "[GPIO] Pin " << pin << " inicializado como "
              << (direction == GPIODirection::OUTPUT ? "SAÍDA" : "ENTRADA") << "\n";
}

void GPIO::write(bool value) {
    if (direction == GPIODirection::OUTPUT) {
        state = value;
        std::cout << "[GPIO] Pin " << pin << " setado para " << (value ? "HIGH" : "LOW") << "\n";
    } else {
        std::cerr << "[GPIO] Tentativa de escrita em pino configurado como ENTRADA!\n";
    }
}

bool GPIO::read() const {
    return state;
}
