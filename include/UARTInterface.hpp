#pragma once
#include <string>

class UARTInterface {
  public:
    virtual ~UARTInterface() = default;

    virtual void write(const std::string& data) = 0;
    virtual std::string readLine() = 0;
};

class UARTSimulada : public UARTInterface {
  public:
    void write(const std::string& data) override;
    std::string readLine() override;
};
