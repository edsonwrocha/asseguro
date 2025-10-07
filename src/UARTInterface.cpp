#include "UARTInterface.hpp"
#include <iostream>

void UARTSimulada::write(const std::string& data) {
    std::cout << data;
}

std::string UARTSimulada::readLine() {
    std::string input;
    std::getline(std::cin, input);
    return input;
}
