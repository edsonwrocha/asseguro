#pragma once
#include <ctime>
#include <sstream>
#include <string>

enum class TipoEvento {
    ABERTURA_PORTA_1,
    ABERTURA_PORTA_2,
    CRIACAO_USUARIO
};

class Evento {
  private:
    std::time_t timestamp;
    std::string usuario;
    TipoEvento tipo;

  public:
    Evento();
    Evento(const std::string& u, TipoEvento t);

    std::string getUsuario() const;
    TipoEvento getTipo() const;
    std::time_t getTimestamp() const;

    std::string toCSV() const;
    std::string toJSON() const;
    static Evento fromCSV(const std::string& linha);
};
