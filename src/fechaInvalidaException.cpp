#include "fechaInvalidaException.h"

FechaInvalidaException::FechaInvalidaException(const std::string& msg)
    : ExcepcionBase("Fecha inválida: " + msg) {}

// =======================
// ValorInvalidoException.h
// =======================
#ifndef VALOR_INVALIDO_EXCEPTION_H
#define VALOR_INVALIDO_EXCEPTION_H

#include "ExcepcionBase.h"

class ValorInvalidoException : public ExcepcionBase {
public:
    explicit ValorInvalidoException(const std::string& msg);
};

#endif