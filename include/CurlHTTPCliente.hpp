#pragma once
#include "HTTPCliente.hpp"
#include <curl/curl.h>

class CurlHttpCliente : public HttpCliente {
  public:
    std::string get(const std::string& url) override;
    std::string post(const std::string& url, const std::string& body) override;
};
