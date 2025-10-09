#include "MenuUART.hpp"
#include "PortaManager.hpp"
#include "Usuario.hpp"
#include "UsuarioManager.hpp"

MenuUART::MenuUART(UARTInterface& uartInterface, UsuarioManager& usuarioManager, PortaManager& portaManager, EventoManager& eventoManager)
    : uart(uartInterface), usuarioManager(usuarioManager), portaManager(portaManager), eventoManager(eventoManager), running(true) {}

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

        TipoUsuario tipo = (tipoStr == "1") ? TipoUsuario::ADMIN : TipoUsuario::REGULAR;
        Usuario novo(nome, senha, tipo);

        usuarioManager.adicionarUsuario(novo);

        uart.write("Usuário criado com sucesso!\n");
        uart.write("Pressione Enter para voltar ao menu: ");
        uart.readLine();
        break;
    }
    case MenuOption::LIST_USERS: {
        uart.write("Listando usuários...\n\n");

        // Cabeçalho
        uart.write("NOME                      | TIPO\n");
        uart.write("--------------------------|------\n");

        auto usuarios = usuarioManager.listarUsuarios();
        for (const auto& u : usuarios) {
            std::string nome = u.getNome();
            std::string tipo = (u.getTipo() == TipoUsuario::ADMIN ? "ADMIN" : "REGULAR");

            // Definindo largura fixa da coluna de nomes (25 caracteres)
            if (nome.length() < 25)
                nome += std::string(25 - nome.length(), ' '); // adiciona espaços à direita

            std::string linha = nome + " | " + tipo + "\n";
            uart.write(linha);
        }

        uart.write("\nPressione Enter para voltar ao menu: ");
        uart.readLine();
        break;
    }

    case MenuOption::LIST_EVENTS: {
        uart.write("Listando eventos em formato de tabela...\n\n");

        // Cabeçalho
        uart.write("TIMESTAMP            | TIPO_EVENTO        | USUARIO       | PORTA | ACAO       | MODBUS\n");
        uart.write("---------------------|--------------------|---------------|-------|------------|--------\n");

        auto eventos = eventoManager.listarEventos();
        for (const auto& e : eventos) {
            // Timestamp em ISO 8601
            std::time_t tims = e.getTimestamp();
            std::tm tm_val;
            gmtime_r(&tims, &tm_val); // versão thread-safe

            char buf[21]; // "YYYY-MM-DDTHH:MM:SSZ" + '\0'
            std::strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%SZ", &tm_val);
            std::string ts(buf);

            // Tipo de evento
            std::string tipo;
            if (e.getTipo() == TipoEvento::CRIACAO_USUARIO)
                tipo = "criar_usuario";
            else if (e.getTipo() == TipoEvento::ABERTURA_PORTA)
                tipo = "movimentacao_porta";
            else
                tipo = "outro_tipo";

            // Ajusta tamanho das colunas
            if (tipo.length() < 18) tipo += std::string(18 - tipo.length(), ' ');
            std::string usuario = e.getUsuario();
            if (usuario.length() < 13) usuario += std::string(13 - usuario.length(), ' ');

            // Campos adicionais (porta, ação, modbus)
            std::string porta = (e.getTipo() == TipoEvento::ABERTURA_PORTA) ? std::to_string(e.getPorta()) : "-";
            if (porta.length() < 5) porta += std::string(5 - porta.length(), ' ');

            std::string acao = (e.getTipo() == TipoEvento::ABERTURA_PORTA) ? e.getAcao() : "-";
            if (acao.length() < 10) acao += std::string(10 - acao.length(), ' ');

            std::string modbus = (e.getTipo() == TipoEvento::ABERTURA_PORTA) ? e.getModbus() : "-";
            if (modbus.length() < 6) modbus += std::string(6 - modbus.length(), ' ');

            // Linha completa
            std::string linha = ts + " | " + tipo + " | " + usuario + " | " + porta + " | " + acao + " | " + modbus + "\n";
            uart.write(linha);
        }

        uart.write("\nPressione Enter para voltar ao menu: ");
        uart.readLine();
        break;
    }
    case MenuOption::OPEN_DOOR_1: {
        uart.write("Digite o nome: ");
        std::string nome;
        nome = uart.readLine();

        uart.write("Digite a senha: ");
        std::string senha;
        senha = uart.readLine();

        if (usuarioManager.validarLoginAdmin(nome, senha)) {
            portaManager.abrirPorta(0, nome);
            uart.write("Porta 1 liberada!\n");
        } else {
            uart.write("Verifique credenciais, acesso liberado apenas para Admin!\n");
        }


        uart.write("\nPressione Enter para voltar ao menu: ");
        uart.readLine();
        break;
    }
    case MenuOption::OPEN_DOOR_2: {
        uart.write("Digite o nome: ");
        std::string nome;
        nome = uart.readLine();

        uart.write("Digite a senha: ");
        std::string senha;
        senha = uart.readLine();

        if (usuarioManager.validarLoginAdmin(nome, senha)) {
            portaManager.abrirPorta(1, nome);
            uart.write("Porta 2 liberada!\n");
        } else {
            uart.write("Verifique credenciais, acesso liberado apenas para Admin!\n");
        }


        uart.write("\nPressione Enter para voltar ao menu: ");
        uart.readLine();
        break;
    }

    default:
        uart.write("Opção inválida!\n");
        break;
    }
}

void MenuUART::run() {
    while (true) {
        std::cout << "porra";
        show();
        std::string input = uart.readLine();
        handleInput(input);
    }
}
