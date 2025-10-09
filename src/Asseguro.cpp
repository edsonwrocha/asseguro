#include "Asseguro.hpp"

Asseguro::Asseguro(const Config& config, CurlHttpCliente& http)
    : eventoManager(config.getString("Files", "evento_file"), http, config.getString("HTTP", "server_url")),
      usuarioManager(config.getString("Files", "usuario_file"), eventoManager),
      portaManager(eventoManager) {
    for (const auto& p : {"P1", "P2"}) {
        portaManager.adicionarPorta(config.getInt("Portas", p), p);
    }
}

void Asseguro::startMenu(UARTInterface& uart) {
    MenuUART menu(uart, usuarioManager, portaManager, eventoManager);
    menu.run();
}
