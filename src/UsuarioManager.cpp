#include "UsuarioManager.hpp"
#include <algorithm>
#include <fstream>

UsuarioManager::UsuarioManager(const std::string& arquivo)
    : caminhoArquivo(arquivo) {
    carregarDoCSV();
}

void UsuarioManager::carregarDoCSV() {
    usuarios.clear();
    std::ifstream file(caminhoArquivo);
    if (!file.is_open()) return;

    std::string linha;
    while (std::getline(file, linha)) {
        if (!linha.empty())
            usuarios.push_back(Usuario::fromCSV(linha));
    }
    file.close();
}

void UsuarioManager::salvarNoCSV() {
    std::ofstream file(caminhoArquivo, std::ios::trunc);
    for (const auto& u : usuarios) {
        file << u.toCSV() << "\n";
    }
    file.close();
}

void UsuarioManager::adicionarUsuario(const Usuario& usuario) {
    usuarios.push_back(usuario);
    salvarNoCSV(); // salva imediatamente
}

std::vector<Usuario> UsuarioManager::listarUsuarios() const {
    return usuarios;
}

bool UsuarioManager::validarSenhaUsuario(const std::string& senha) const {
    return std::any_of(usuarios.begin(), usuarios.end(),
                       [&](const Usuario& u) { return u.getSenha() == senha; });
}

bool UsuarioManager::validarSenhaAdmin(const std::string& senha) const {
    return std::any_of(usuarios.begin(), usuarios.end(),
                       [&](const Usuario& u) { return u.getSenha() == senha && u.isAdmin(); });
}

Usuario UsuarioManager::getUsuarioPorSenha(const std::string& senha) const {
    auto it = std::find_if(usuarios.begin(), usuarios.end(),
                           [&](const Usuario& u) { return u.getSenha() == senha; });
    if (it != usuarios.end()) return *it;
    return Usuario();
}
