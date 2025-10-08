#pragma once
#include <gpiod.hpp>
#include <iostream>
#include <optional>
#include <string>

enum class GPIODirection {
    INPUT,
    OUTPUT
};

class GPIO {
  protected:
    int pin;
    GPIODirection direction;
    bool state;

    // Componentes do libgpiod
    gpiod::chip chip;
    std::optional<gpiod::line_request> line_req;

  public:
    GPIO(int pin, GPIODirection direction);
    ~GPIO();
    void write(bool value);
    bool read();
    int getPin() const;
};
