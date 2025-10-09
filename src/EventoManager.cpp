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
        if (!linha.empty()) {
            try {
                eventos.push_back(Evento::fromCSV(linha));
            } catch (const std::exception& ex) {
                std::cerr << "Erro ao ler linha do CSV: " << ex.what() << "\n";
            }
        }
    }
    file.close();
}

void EventoManager::salvarNoCSV() {
    std::ofstream file(caminhoArquivo, std::ios::trunc);
    if (!file.is_open()) {
        std::cerr << "Não foi possível abrir o arquivo para salvar eventos\n";
        return;
    }

    for (const auto& e : eventos) {
        file << e.toCSV() << "\n";
    }
    file.close();
}

void EventoManager::registrarEvento(const Evento& e) {
    eventos.push_back(e);
    salvarNoCSV();

    std::string json = e.toJSON();
    std::cout << json << std::endl;
    std::cout << http.post(url + "/api/evento", json) << std::endl;
}

std::vector<Evento> EventoManager::listarEventos() const {
    return eventos;
}
