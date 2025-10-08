#pragma once
#include "GPIO.hpp"
#include <chrono>
#include <string>
#include <thread>

class Porta : public GPIO {
  private:
    std::string nome;

  public:
    Porta(int pin, const std::string& nome);

    void abrir();
    void abrirComTimeout(int timeout_ms);
    void fechar();
    bool estaAberta();

    const std::string& getNome() const { return nome; }
};
