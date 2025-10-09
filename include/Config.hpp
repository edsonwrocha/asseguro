#pragma once
#include <map>
#include <string>

class Config {
  public:
    Config(const std::string& arquivo);
    void createDefault(const std::string& arquivo);
    std::string getString(const std::string& secao, const std::string& chave, const std::string& padrao = "") const;
    int getInt(const std::string& secao, const std::string& chave, int padrao = 0) const;

  private:
    std::map<std::string, std::string> dados;
    static std::string trim(const std::string& str);
};
