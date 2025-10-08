#pragma once
#include "EventoManager.hpp"
#include "Porta.hpp"
#include "Usuario.hpp"
#include <vector>

class PortaManager {
  private:
    std::vector<Porta> portas;
    EventoManager& eventoManager;

  public:
    PortaManager(EventoManager& eventoManager);

    void adicionarPorta(const Porta& porta);
    bool abrirPorta(std::string& nome, int id);
    bool fecharPorta(int id);
};
