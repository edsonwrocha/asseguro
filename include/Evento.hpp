#pragma once
#include <ctime>
#include <sstream>
#include <string>

enum class TipoEvento {
    ABERTURA_PORTA,
    CRIACAO_USUARIO
};

class Evento {
  private:
    std::time_t timestamp;
    TipoEvento tipo;

    std::string usuario;
    std::string tipoUsuario;

    int porta;
    std::string acao;
    std::string modbus;

  public:
    Evento();
    Evento(const std::string& usuario, const std::string& nivel, std::time_t ts = std::time(nullptr));
    Evento(int p, const std::string& a, const std::string& pacoteModbus, const std::string& usuario, std::time_t ts = std::time(nullptr));
    std::string getUsuario() const;
    TipoEvento getTipo() const;
    std::time_t getTimestamp() const;
    int getPorta() const;
    std::string getAcao() const;
    std::string getModbus() const;

    std::string toCSV() const;
    std::string toJSON() const;
    static Evento fromCSV(const std::string& linha);
};
