#include "Evento.hpp"

Evento::Evento() {}

Evento::Evento(const std::string& u, TipoEvento t)
    : usuario(u), tipo(t) {
    timestamp = std::time(nullptr);
}

std::string Evento::getUsuario() const { return usuario; }
TipoEvento Evento::getTipo() const { return tipo; }
std::time_t Evento::getTimestamp() const { return timestamp; }

std::string Evento::toCSV() const {
    std::stringstream ss;
    ss << timestamp << "," << usuario << "," << static_cast<int>(tipo);
    return ss.str();
}

std::string Evento::toJSON() const {
    std::stringstream ss;
    ss << "{";

    ss << "\"timestamp\":" << timestamp << ",";

    if (tipo == TipoEvento::ABERTURA_PORTA_1) {
        ss << "\"tipo\":\"ABERTURA_PORTA\",";
        ss << "\"data\":\"";
        // for (auto b : modbusData) {
        //  ss << std::hex << (int)b << " "; // converte bytes para hex
        //}
        ss << "\"";
    } else if (tipo == TipoEvento::CRIACAO_USUARIO) {
        ss << "\"tipo\":\"CRIACAO_USUARIO\",";
        ss << "\"nome\":\"" << usuario << "\"";
    }

    ss << "}";
    return ss.str();
}

Evento Evento::fromCSV(const std::string& linha) {
    size_t pos1 = linha.find(',');
    size_t pos2 = linha.find(',', pos1 + 1);
    size_t pos3 = linha.find(',', pos2 + 1);

    std::time_t ts = std::stol(linha.substr(0, pos1));
    std::string u = linha.substr(pos1 + 1, pos2 - pos1 - 1);
    TipoEvento t = static_cast<TipoEvento>(std::stoi(linha.substr(pos2 + 1, pos3 - pos2 - 1)));
    std::string d = linha.substr(pos3 + 1);

    Evento e;
    e = Evento(u, t);
    e.timestamp = ts; // mantemos o timestamp original
    return e;
}
