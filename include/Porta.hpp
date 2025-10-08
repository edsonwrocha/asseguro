#pragma once
#include "GPIO.hpp"
#include <string>

class Porta : public GPIO {
  private:
    std::string nome;

  public:
    Porta(int pin, const std::string& nome);

    void abrir();
    void fechar();
    bool estaAberta() const;

    const std::string& getNome() const { return nome; }
};
