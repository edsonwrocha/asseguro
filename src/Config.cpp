#include "Config.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

Config::Config(const std::string& arquivo) {
    std::ifstream f(arquivo);

    if (!f.is_open()) {
        std::cerr << "[INFO] Arquivo de configuração não encontrado. Criando padrão em " << arquivo << std::endl;
        createDefault(arquivo);
        f.open(arquivo);
        if (!f.is_open()) throw std::runtime_error("Não foi possível criar o arquivo padrão " + arquivo);
    }

    std::string linha;
    std::string secao;

    while (std::getline(f, linha)) {
        linha = trim(linha);
        if (linha.empty() || linha[0] == '#') continue;

        if (linha.front() == '[' && linha.back() == ']') {
            secao = linha.substr(1, linha.size() - 2);
            continue;
        }

        auto eq = linha.find('=');
        if (eq == std::string::npos) continue;

        std::string chave = trim(linha.substr(0, eq));
        std::string valor = trim(linha.substr(eq + 1));

        dados[secao + "." + chave] = valor;
    }
}

void Config::createDefault(const std::string& arquivo) {
    std::ofstream f(arquivo);
    f << "[UART]\n";
    f << "device=/dev/serial0\n";
    f << "baud=115200\n\n";
    f << "[HTTP]\n";
    f << "server_url=192.168.1.8:8080\n\n";
    f << "[Files]\n";
    f << "evento_file=eventos.txt\n";
    f << "usuario_file=usuarios.txt\n\n";
    f << "[Portas]\n";
    f << "P1=17\n";
    f << "P2=27\n";
    f.close();
}

std::string Config::getString(const std::string& secao, const std::string& chave, const std::string& padrao) const {
    auto it = dados.find(secao + "." + chave);
    return it != dados.end() ? it->second : padrao;
}

int Config::getInt(const std::string& secao, const std::string& chave, int padrao) const {
    auto s = getString(secao, chave);
    return s.empty() ? padrao : std::stoi(s);
}

std::string Config::trim(const std::string& str) {
    const char* ws = " \t\n\r";
    size_t start = str.find_first_not_of(ws);
    size_t end = str.find_last_not_of(ws);
    return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
}
