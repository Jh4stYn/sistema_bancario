#ifndef MANEJADOR_EXCEPCIONES_H
#define MANEJADOR_EXCEPCIONES_H

#include <iostream>
#include <exception>

class ManejadorExcepciones {
public:
    static void mostrarError(const std::exception& e);
};

#endif