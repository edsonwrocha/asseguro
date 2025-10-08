#pragma once
#include "Evento.hpp"
#include "HTTPCliente.hpp"
#include <algorithm>
#include <fstream>
#include <vector>

class EventoManager {
  private:
    HttpCliente& http;
    std::string url;
    std::vector<Evento> eventos;
    std::string caminhoArquivo;

    void salvarNoCSV();

  public:
    EventoManager(const std::string& arquivo, HttpCliente& http, std::string url);

    void carregarDoCSV();
    void registrarEvento(const Evento& e);

    std::vector<Evento> listarEventos() const;

    // Função para enviar evento via Modbus RTU
    void enviarEventoModbus(const Evento& e);
};
