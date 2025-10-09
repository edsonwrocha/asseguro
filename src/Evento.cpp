#include "Evento.hpp"
#include <vector>

Evento::Evento() {}

// Construtor para criação de usuário
Evento::Evento(const std::string& usuario, const std::string& nivel, std::time_t ts)
    : usuario(usuario), tipoUsuario(nivel), tipo(TipoEvento::CRIACAO_USUARIO), timestamp(ts) {}

// Construtor para movimentação de porta
Evento::Evento(int p, const std::string& a, const std::string& pacoteModbus, const std::string& usuario, std::time_t ts)
    : porta(p), acao(a), modbus(pacoteModbus), tipo(TipoEvento::ABERTURA_PORTA), usuario(usuario), timestamp(ts) {}


std::string Evento::getUsuario() const { return usuario; }
TipoEvento Evento::getTipo() const { return tipo; }
std::time_t Evento::getTimestamp() const { return timestamp; }
int Evento::getPorta() const { return porta; }
std::string Evento::getAcao() const { return acao; }
std::string Evento::getModbus() const { return modbus; }


std::string Evento::toCSV() const {
    std::stringstream ss;

    ss << (tipo == TipoEvento::CRIACAO_USUARIO ? "CRIACAO_USUARIO" : "ABERTURA_PORTA") << ",";
    ss << timestamp << ",";

    if (tipo == TipoEvento::CRIACAO_USUARIO) {
        ss << usuario << "," << tipoUsuario << ",";
        ss << "," << "," << "," << ",";
    }
    // Campos de porta
    else if (tipo == TipoEvento::ABERTURA_PORTA) {
        ss << "," << ",";
        ss << usuario << ",";
        ss << porta << "," << acao << "," << modbus;
    }

    return ss.str();
}

std::string Evento::toJSON() const {
    std::stringstream ss;
    ss << "{";

    // timestamp em ISO 8601
    char buf[20];
    std::tm* ptm = std::gmtime(&timestamp);
    std::strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%SZ", ptm);
    ss << "\"timestamp\":\"" << buf << "\",";

    if (tipo == TipoEvento::CRIACAO_USUARIO) {
        ss << "\"tipo_evento\":\"criar_usuario\",";
        ss << "\"usuario\":{";
        ss << "\"nome\":\"" << usuario << "\",";
        ss << "\"tipo\":\"" << tipoUsuario << "\"";
        ss << "}";
    } else if (tipo == TipoEvento::ABERTURA_PORTA) {
        ss << "\"tipo_evento\":\"movimentacao_porta\",";
        ss << "\"usuario\":\"" << usuario << "\",";
        ss << "\"porta\":" << porta << ",";
        ss << "\"acao\":\"" << acao << "\",";
        ss << "\"modbus\":\"" << modbus << "\"";
    }

    ss << "}";
    return ss.str();
}

Evento Evento::fromCSV(const std::string& linha) {
    std::stringstream ss(linha);
    std::string item;
    std::vector<std::string> campos;

    while (std::getline(ss, item, ',')) {
        campos.push_back(item);
    }

    if (campos.size() != 8) {
        throw std::runtime_error("CSV inválido: deve ter 8 campos");
    }

    std::time_t ts = std::stoll(campos[1]);

    if (campos[0] == "CRIACAO_USUARIO") {
        Evento e(campos[2], campos[3], ts); // usuario, tipoUsuario
        return e;
    } else if (campos[0] == "ABERTURA_PORTA") {
        std::string usuarioPorta = campos[4];
        int p = std::stoi(campos[5]);
        std::string a = campos[6];
        std::string m = campos[7];
        Evento e(p, a, m, usuarioPorta, ts);
        return e;
    } else {
        throw std::runtime_error("Tipo de evento desconhecido no CSV");
    }
}
