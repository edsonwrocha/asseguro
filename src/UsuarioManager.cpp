#include "UsuarioManager.hpp"
#include <algorithm>
#include <fstream>

UsuarioManager::UsuarioManager(const std::string& arquivo, EventoManager& eventoManager)
    : caminhoArquivo(arquivo), eventoManager(eventoManager) {
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
    Evento e(usuario.getNome(), TipoEvento::CRIACAO_USUARIO);
    eventoManager.registrarEvento(e);
}

std::vector<Usuario> UsuarioManager::listarUsuarios() const {
    return usuarios;
}

bool UsuarioManager::validarLogin(const std::string& nome, const std::string& senha) const {
    return std::any_of(usuarios.begin(), usuarios.end(),
                       [&](const Usuario& u) {
                           return u.getNome() == nome && u.getSenha() == senha;
                       });
}

bool UsuarioManager::validarLoginAdmin(const std::string& nome, const std::string& senha) const {
    return std::any_of(usuarios.begin(), usuarios.end(),
                       [&](const Usuario& u) {
                           return u.getNome() == nome && u.getSenha() == senha && u.isAdmin();
                       });
}

Usuario UsuarioManager::getUsuarioPorSenha(const std::string& senha) const {
    auto it = std::find_if(usuarios.begin(), usuarios.end(),
                           [&](const Usuario& u) { return u.getSenha() == senha; });
    if (it != usuarios.end()) return *it;
    return Usuario();
}
