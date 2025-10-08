#pragma once
#include "Evento.hpp"
#include <algorithm>
#include <fstream>
#include <vector>

class EventoManager {
  private:
    std::vector<Evento> eventos;
    std::string caminhoArquivo;

    void salvarNoCSV();

  public:
    EventoManager(const std::string& arquivo);

    void carregarDoCSV();
    void registrarEvento(const Evento& e);

    std::vector<Evento> listarEventos() const;

    // Função para enviar evento via Modbus RTU
    void enviarEventoModbus(const Evento& e);
};
