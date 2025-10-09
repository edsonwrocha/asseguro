#include "Porta.hpp"
#include <iostream>

Porta::Porta(int pin, const std::string& nome)
    : GPIO(pin, GPIODirection::OUTPUT), nome(nome) {
    fechar();
}

void Porta::abrir() {
    write(false);
    std::cout << "[Porta] " << nome << " foi ABERTA.\n";
}

void Porta::abrirComTimeout(int timeout_ms) {
    // Abre a porta
    write(false);
    std::cout << "[Porta] " << nome << " foi ABERTA.\n";

    // Aguarda pelo timeout
    std::this_thread::sleep_for(std::chrono::milliseconds(timeout_ms));

    // Fecha a porta após o timeout
    write(true);
    std::cout << "[Porta] " << nome << " foi FECHADA após " << timeout_ms << " ms.\n";
}

void Porta::fechar() {
    write(true);
    std::cout << "[Porta] " << nome << " foi FECHADA.\n";
}

bool Porta::estaAberta() {
    return read();
}
