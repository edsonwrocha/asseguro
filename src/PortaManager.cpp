#include "PortaManager.hpp"
#include <iostream>

PortaManager::PortaManager(EventoManager& eventoManager) : eventoManager(eventoManager) {}

void PortaManager::adicionarPorta(int pin, const std::string& nome) {
    portas.push_back(std::make_unique<Porta>(pin, nome));

    std::cout << "[PortaManager] Porta '" << nome << "' adicionada.\n";
}

bool PortaManager::abrirPorta(int id, const std::string& nome) {
    if (id < 0 || id >= (int)portas.size()) {
        std::cerr << "[PortaManager] ID inválido.\n";
        return false;
    }

    std::string pacoteModbus = "000000";
    Evento e(id + 1, "abrir", pacoteModbus, nome);
    eventoManager.registrarEvento(e);
    portas[id]->abrir();
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    fecharPorta(id, nome);
    return true;
}

bool PortaManager::fecharPorta(int id, const std::string& nome) {
    if (id < 0 || id >= (int)portas.size()) {
        std::cerr << "[PortaManager] ID inválido.\n";
        return false;
    }

    portas[id]->fechar();

    std::string pacoteModbus = "000000";
    Evento e(id + 1, "fechar", pacoteModbus, nome);
    eventoManager.registrarEvento(e);

    return true;
}
