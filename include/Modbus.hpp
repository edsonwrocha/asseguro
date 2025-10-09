#include <cstdint>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

class Modbus {
  public:
    enum class Porta : uint16_t {
        PORTA1 = 0x34,
        PORTA2 = 0x35
    };

    enum class Estado : uint16_t {
        FECHADO = 0x00,
        ABERTO = 0xFF
    };

  private:
    uint8_t address;
    uint8_t func;
    Porta regAddr;
    Estado value;

    uint16_t crc16(const std::vector<uint8_t>& data);

  public:
    Modbus(uint8_t addr, Porta reg, Estado val);
    std::string modbusToStr();
};
