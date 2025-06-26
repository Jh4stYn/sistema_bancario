#pragma once
#include <string>

class Banco {
public:
    std::string id;
    std::string nombre;
    std::string codigoBCR;

    Banco(std::string id, std::string nombre, std::string codigoBCR);
};