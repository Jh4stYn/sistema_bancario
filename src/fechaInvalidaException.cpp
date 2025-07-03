#include "FechaInvalidaException.h"

FechaInvalidaException::FechaInvalidaException(const std::string& msg)
    : ExcepcionBase("Fecha inválida: " + msg) {}