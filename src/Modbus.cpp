#include "Modbus.hpp"

// Função para calcular CRC16 MODBUS RTU
uint16_t Modbus::crc16(const std::vector<uint8_t>& data) {
    uint16_t crc = 0xFFFF;
    for (uint8_t b : data) {
        crc ^= b;
        for (int i = 0; i < 8; i++) {
            if (crc & 0x0001)
                crc = (crc >> 1) ^ 0xA001;
            else
                crc = crc >> 1;
        }
    }
    return crc;
}

Modbus::Modbus(uint8_t addr, Porta reg, Estado val)
    : address(addr), func(0x06), regAddr(reg), value(val) {}

std::string Modbus::modbusToStr() {
    std::vector<uint8_t> frame;

    frame.push_back(address);                               // Address
    frame.push_back(func);                                  // Função
    frame.push_back(static_cast<uint16_t>(regAddr) >> 8);   // Endereço High
    frame.push_back(static_cast<uint16_t>(regAddr) & 0xFF); // Endereço Low
    frame.push_back(static_cast<uint16_t>(value) >> 8);     // Valor High
    frame.push_back(static_cast<uint16_t>(value) & 0xFF);   // Valor Low

    uint16_t crc = crc16(frame);
    frame.push_back(crc & 0xFF); // CRC Low
    frame.push_back(crc >> 8);   // CRC High

    // Converter para string hexadecimal

    std::stringstream ss;
    ss << std::hex << std::uppercase << std::setfill('0');
    for (uint8_t b : frame) {
        ss << std::setw(2) << (int)b;
    }
    return ss.str();
}
