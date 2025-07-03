#include "ValorInvalidoException.h"

ValorInvalidoException::ValorInvalidoException(const std::string& msg)
    : ExcepcionBase("Valor inválido: " + msg) {}
