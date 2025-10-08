#pragma once
#include "Porta.hpp"
#include "Usuario.hpp"
#include <vector>

class PortaManager {
  private:
    std::vector<Porta> portas;

  public:
    PortaManager();

    void adicionarPorta(const Porta& porta);
    bool abrirPorta(int id);
    bool fecharPorta(int id);
};
