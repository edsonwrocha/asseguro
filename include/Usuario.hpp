#pragma once
#include <string>

enum class TipoUsuario {
    REGULAR,
    ADMIN
};

class Usuario {
  private:
    std::string nome;
    std::string senha;
    TipoUsuario tipo;

  public:
    Usuario() = default;

    Usuario(const std::string& n, const std::string& s, TipoUsuario t);

    const std::string& getNome() const;
    const std::string& getSenha() const;
    TipoUsuario getTipo() const;

    bool isAdmin() const;

    std::string toCSV() const;
    static Usuario fromCSV(const std::string& linha);
};
