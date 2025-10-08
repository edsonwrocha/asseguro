#pragma once
#include "UARTInterface.hpp"
#include <fcntl.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include <termios.h>
#include <unistd.h>

class UARTReal : public UARTInterface {
  private:
    int serial_fd;

  public:
    explicit UARTReal(const std::string& port = "/dev/ttyS0", int baudrate = B115200);
    ~UARTReal() override;

    void write(const std::string& data) override;
    std::string readLine() override;
};
