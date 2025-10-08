#pragma once
#include "EventoManager.hpp"
#include "Usuario.hpp"
#include <string>
#include <vector>

class UsuarioManager {
  private:
    std::vector<Usuario> usuarios;
    std::string caminhoArquivo;
    EventoManager& eventoManager;

  public:
    explicit UsuarioManager(const std::string& arquivo, EventoManager& eventoManager);

    void carregarDoCSV();
    void salvarNoCSV();

    void adicionarUsuario(const Usuario& usuario);

    std::vector<Usuario> listarUsuarios() const;

    bool validarLogin(const std::string& nome, const std::string& senha) const;
    bool validarLoginAdmin(const std::string& nome, const std::string& senha) const;


    Usuario getUsuarioPorSenha(const std::string& senha) const;
};
