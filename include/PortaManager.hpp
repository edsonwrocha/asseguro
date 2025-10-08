#pragma once
#include "EventoManager.hpp"
#include "Porta.hpp"
#include "Usuario.hpp"
#include <vector>

class PortaManager {
  private:
    std::vector<std::unique_ptr<Porta>> portas;
    EventoManager& eventoManager;

  public:
    PortaManager(EventoManager& eventoManager);

    void adicionarPorta(int pin, const std::string& nome);
    bool abrirPorta(std::string& nome, int id);
    bool fecharPorta(int id);
};
