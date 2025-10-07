#pragma once
#include "Usuario.hpp"
#include <string>
#include <vector>

class UsuarioManager {
  private:
    std::vector<Usuario> usuarios;
    std::string caminhoArquivo;

  public:
    explicit UsuarioManager(const std::string& arquivo);

    void carregarDoCSV();
    void salvarNoCSV();

    void adicionarUsuario(const Usuario& usuario);

    std::vector<Usuario> listarUsuarios() const;

    bool validarSenhaUsuario(const std::string& senha) const;
    bool validarSenhaAdmin(const std::string& senha) const;

    Usuario getUsuarioPorSenha(const std::string& senha) const;
};
