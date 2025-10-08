#include "PortaManager.hpp"
#include <iostream>

PortaManager::PortaManager(EventoManager& eventoManager) : eventoManager(eventoManager) {}

void PortaManager::adicionarPorta(const Porta& porta) {
    portas.push_back(porta);
    std::cout << "[PortaManager] Porta '" << porta.getNome() << "' adicionada.\n";
}

bool PortaManager::abrirPorta(std::string& nome, int id) {
    if (id < 0 || id >= (int)portas.size()) {
        std::cerr << "[PortaManager] ID inválido.\n";
        return false;
    }

    portas[id].abrir();
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

    portas[id].fechar();
    return true;
}
