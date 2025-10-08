#include "PortaManager.hpp"
#include <iostream>

PortaManager::PortaManager(EventoManager& eventoManager) : eventoManager(eventoManager) {}

void PortaManager::adicionarPorta(int pin, const std::string& nome) {
    portas.push_back(std::make_unique<Porta>(pin, nome));

    std::cout << "[PortaManager] Porta '" << nome << "' adicionada.\n";
}

bool PortaManager::abrirPorta(std::string& nome, int id) {
    if (id < 0 || id >= (int)portas.size()) {
        std::cerr << "[PortaManager] ID inválido.\n";
        return false;
    }

    portas[id]->abrirComTimeout(5000);
    Evento e;
    if (id == 0) {
        e = Evento(nome, TipoEvento::ABERTURA_PORTA_1);
    } else if (id == 1) {
        e = Evento(nome, TipoEvento::ABERTURA_PORTA_2);
    }
    eventoManager.registrarEvento(e);
    return true;
}

bool PortaManager::fecharPorta(int id) {
    if (id < 0 || id >= (int)portas.size()) {
        std::cerr << "[PortaManager] ID inválido.\n";
        return false;
    }

    portas[id]->fechar();
    return true;
}
