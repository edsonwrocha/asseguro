#include "PortaManager.hpp"
#include <iostream>

PortaManager::PortaManager() {}

void PortaManager::adicionarPorta(const Porta& porta) {
    portas.push_back(porta);
    std::cout << "[PortaManager] Porta '" << porta.getNome() << "' adicionada.\n";
}

bool PortaManager::abrirPorta(int id) {
    if (id < 0 || id >= (int)portas.size()) {
        std::cerr << "[PortaManager] ID inválido.\n";
        return false;
    }

    portas[id].abrir();
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
