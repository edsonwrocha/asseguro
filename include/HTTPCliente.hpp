#pragma once
#include <string>

class HttpCliente {
  public:
    virtual ~HttpCliente() = default;

    virtual std::string get(const std::string& url) = 0;
    virtual std::string post(const std::string& url, const std::string& body) = 0;
};
