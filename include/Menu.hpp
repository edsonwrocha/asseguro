#pragma once
#include <string>

class Menu {
  public:
    virtual ~Menu() = default;
    virtual void show() = 0;
    virtual void handleInput(const std::string& input) = 0;
};
