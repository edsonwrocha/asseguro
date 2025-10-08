#include "Porta.hpp"
#include <iostream>

Porta::Porta(int pin, const std::string& nome)
    : GPIO(pin, GPIODirection::OUTPUT), nome(nome) {}

void Porta::abrir() {
    write(true);
    std::cout << "[Porta] " << nome << " foi ABERTA.\n";
}

void Porta::fechar() {
    write(false);
    std::cout << "[Porta] " << nome << " foi FECHADA.\n";
}

bool Porta::estaAberta() const {
    return read();
}
