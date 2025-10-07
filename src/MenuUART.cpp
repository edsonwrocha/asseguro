#include "MenuUART.hpp"

MenuUART::MenuUART(UARTInterface& uartInterface)
    : uart(uartInterface), running(true) {}

std::string MenuUART::getMenuOptionText(MenuOption option) {
    switch (option) {
    case MenuOption::CREATE_USER:
        return "Cadastrar novo usuario";
    case MenuOption::LIST_USERS:
        return "Listar usuarios";
    case MenuOption::LIST_EVENTS:
        return "Listar eventos";
    case MenuOption::OPEN_DOOR_1:
        return "Liberar Porta 1";
    case MenuOption::OPEN_DOOR_2:
        return "Liberar Porta 2";
    default:
        return "";
    }
}

MenuOption MenuUART::parseOption(const std::string& input) {
    if (input == "1") return MenuOption::CREATE_USER;
    if (input == "2") return MenuOption::LIST_USERS;
    if (input == "3") return MenuOption::LIST_EVENTS;
    if (input == "4") return MenuOption::OPEN_DOOR_1;
    if (input == "5") return MenuOption::OPEN_DOOR_2;
    return MenuOption::INVALID;
}

void MenuUART::show() {
    uart.write("\x1B[2J\x1B[H"); // limpa tela

    uart.write("=== Asseguro ===\n");
    uart.write("designed by Edson W. Rocha\n");
    uart.write("version 1.0.0 2025(c)\n\n");

    uart.write("=== MENU PRINCIPAL ===\n");

    for (int i = 1; i <= 5; ++i) {
        MenuOption opt = static_cast<MenuOption>(i);
        uart.write("[" + std::to_string(i) + "] " + getMenuOptionText(opt) + "\n");
    }

    uart.write("> ");
}

void MenuUART::handleInput(const std::string& input) {
    MenuOption option = parseOption(input);

    switch (option) {
    case MenuOption::CREATE_USER: {
        uart.write("Digite o nome: ");
        std::string nome;
        nome = uart.readLine();

        uart.write("Digite a senha: ");
        std::string senha;
        senha = uart.readLine();

        uart.write("Tipo [1] Admin, [0] Regular: ");
        std::string tipoStr = uart.readLine();
        bool isAdmin = (tipoStr == "1");

        uart.write("Usuário criado com sucesso!\n");
        uart.write("Pressione Enter para voltar ao menu: ");
        uart.readLine();
        break;
    }
    case MenuOption::LIST_USERS:
        uart.write("Listando usuários...\n");
        break;

    case MenuOption::LIST_EVENTS:
        uart.write("Listando eventos...\n");
        break;

    case MenuOption::OPEN_DOOR_1:
        uart.write("Porta 1 liberada!\n");
        break;

    case MenuOption::OPEN_DOOR_2:
        uart.write("Porta 2 liberada!\n");
        break;

    default:
        uart.write("Opção inválida!\n");
        break;
    }
}

void MenuUART::run() {
    while (running) {
        show();
        std::string input = uart.readLine();
        handleInput(input);
    }
}
