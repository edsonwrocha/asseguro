#include "Usuario.hpp"

Usuario::Usuario(const std::string& n, const std::string& s, TipoUsuario t)
    : nome(n), senha(s), tipo(t) {}

const std::string& Usuario::getNome() const { return nome; }
const std::string& Usuario::getSenha() const { return senha; }
TipoUsuario Usuario::getTipo() const { return tipo; }

bool Usuario::isAdmin() const { return tipo == TipoUsuario::ADMIN; }

// Serialização para CSV
std::string Usuario::toCSV() const {
    return nome + "," + senha + "," + (isAdmin() ? "1" : "0");
}

// Desserialização de CSV
Usuario Usuario::fromCSV(const std::string& linha) {
    size_t pos1 = linha.find(',');
    size_t pos2 = linha.rfind(',');

    std::string n = linha.substr(0, pos1);
    std::string p = linha.substr(pos1 + 1, pos2 - pos1 - 1);
    TipoUsuario t = (linha.substr(pos2 + 1) == "1") ? TipoUsuario::ADMIN : TipoUsuario::REGULAR;

    return Usuario(n, p, t);
}
