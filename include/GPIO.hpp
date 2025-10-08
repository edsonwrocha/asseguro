#pragma once
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

  public:
    GPIO(int pin, GPIODirection direction);
    virtual ~GPIO() = default;

    virtual void write(bool value);
    virtual bool read() const;
    int getPin() const;
};
