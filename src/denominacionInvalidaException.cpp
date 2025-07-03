#include "denominacionInvalidaException.h"

DenominacionInvalidaException::DenominacionInvalidaException(const std::string& msg)
    : ExcepcionBase("Denominación inválida: " + msg) {}