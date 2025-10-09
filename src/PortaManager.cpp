#include "PortaManager.hpp"
#include "Modbus.hpp"
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

    Modbus::Porta portaEnum;
    switch (id) {
    case 0:
        portaEnum = Modbus::Porta::PORTA1;
        break;
    case 1:
        portaEnum = Modbus::Porta::PORTA2;
        break;
    default:
        std::cerr << "[PortaManager] ID inválido.\n";
        return false;
    }

    Modbus comando1(1, portaEnum, Modbus::Estado::ABERTO);

    std::string pacoteModbus = comando1.modbusToStr();
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

    Modbus::Porta portaEnum;
    switch (id) {
    case 0:
        portaEnum = Modbus::Porta::PORTA1;
        break;
    case 1:
        portaEnum = Modbus::Porta::PORTA2;
        break;
    default:
        std::cerr << "[PortaManager] ID inválido.\n";
        return false;
    }

    Modbus comando1(1, portaEnum, Modbus::Estado::FECHADO);

    std::string pacoteModbus = comando1.modbusToStr();
    Evento e(id + 1, "fechar", pacoteModbus, nome);
    eventoManager.registrarEvento(e);

    return true;
}
