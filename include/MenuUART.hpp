#pragma once
#include "Menu.hpp"
#include "PortaManager.hpp"
#include "UARTInterface.hpp"
#include "UsuarioManager.hpp"
#include <string>

enum class MenuOption {
    CREATE_USER = 1,
    LIST_USERS,
    LIST_EVENTS,
    OPEN_DOOR_1,
    OPEN_DOOR_2,
    INVALID
};

class MenuUART : public Menu {
  private:
    UARTInterface& uart;
    UsuarioManager& usuarioManager;
    PortaManager& portaManager;
    bool running;

  public:
    explicit MenuUART(UARTInterface& uartInterface, UsuarioManager& usuarioManager, PortaManager& portaManager);
    MenuOption parseOption(const std::string& input);
    std::string getMenuOptionText(MenuOption option);
    void show() override;
    void handleInput(const std::string& input) override;
    void run(); // loop principal do CLI
};
