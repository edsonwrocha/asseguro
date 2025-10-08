#include "EventoManager.hpp"
#include <cstdint>
#include <iostream>

EventoManager::EventoManager(const std::string& arquivo, HttpCliente& http, std::string url) : caminhoArquivo(arquivo), http(http), url(url) {
    carregarDoCSV();
}

void EventoManager::carregarDoCSV() {
    eventos.clear();
    std::ifstream file(caminhoArquivo);
    if (!file.is_open()) return;

    std::string linha;
    while (std::getline(file, linha)) {
        if (!linha.empty())
            eventos.push_back(Evento::fromCSV(linha));
    }
    file.close();
}

void EventoManager::salvarNoCSV() {
    std::ofstream file(caminhoArquivo, std::ios::trunc);
    for (const auto& e : eventos)
        file << e.toCSV() << "\n";
    file.close();
}

void EventoManager::registrarEvento(const Evento& e) {
    eventos.push_back(e);
    salvarNoCSV();

    std::string json = e.toJSON();
    std::cout << json << std::endl;
    std::cout << http.post(url + "/api/evento", json) << std::endl;
    // enviarEventoModbus(e);
}

std::vector<Evento> EventoManager::listarEventos() const {
    return eventos;
}

void EventoManager::enviarEventoModbus(const Evento& e) {
    uint8_t address = 0x01;
    uint16_t reg = 0;
    uint8_t value = 0;

    switch (e.getTipo()) {
    case TipoEvento::ABERTURA_PORTA_1:
        reg = 0x34;
        value = 0xFF; // aberto
        break;
    case TipoEvento::ABERTURA_PORTA_2:
        reg = 0x35;
        value = 0xFF; // aberto
        break;
    default:
        return; // só enviamos eventos de abertura de portas
    }

    // Aqui você colocaria a chamada à sua biblioteca Modbus RTU
    // Exemplo pseudocódigo:
    // modbus_write_register(address, reg, value);

    std::cout << "Enviando Modbus: addr=" << int(address) << " reg=" << reg
              << " value=" << int(value) << "\n";
}
