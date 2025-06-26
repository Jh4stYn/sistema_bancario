#pragma once
#include <string>

class Plaza {
public:
    std::string id;
    std::string nombre;
    std::string ciudad;

    Plaza(std::string id, std::string nombre, std::string ciudad);
};