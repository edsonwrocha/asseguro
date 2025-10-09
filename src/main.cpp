#include "Asseguro.hpp"
#include "Config.hpp"
#include "CurlHTTPCliente.hpp"
#include "UARTReal.hpp"
#include <iostream>

int main() {
    try {
        Config config("asseguro.conf");
        CurlHttpCliente http;
        UARTReal uart(config.getString("UART", "device"), config.getInt("UART", "baud"));
        Asseguro asseguro(config, http);
        asseguro.startMenu(uart);

    } catch (const std::exception& e) {
        std::cerr << "[ERRO] Falha ao iniciar aplicação: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
