#pragma once
#include "Config.hpp"
#include "CurlHTTPCliente.hpp"
#include "EventoManager.hpp"
#include "MenuUART.hpp"
#include "PortaManager.hpp"
#include "UARTInterface.hpp"
#include "UsuarioManager.hpp"

class Asseguro {
  public:
    Asseguro(const Config& config, CurlHttpCliente& http);
    void startMenu(UARTInterface& uart);

  private:
    EventoManager eventoManager;
    UsuarioManager usuarioManager;
    PortaManager portaManager;
};
