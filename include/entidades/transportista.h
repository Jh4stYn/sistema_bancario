#pragma once
#include <string>

class Transportista {
public:
    std::string id;
    std::string nombre;
    std::string ruc;

    Transportista(std::string id, std::string nombre, std::string ruc);
};