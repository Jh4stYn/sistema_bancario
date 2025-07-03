#include "valorInvalidoException.h"

ValorInvalidoException::ValorInvalidoException(const std::string& msg)
    : ExcepcionBase("Valor inválido: " + msg) {}

// =======================
// DenominacionInvalidaException.h
// =======================
#ifndef DENOMINACION_INVALIDA_EXCEPTION_H
#define DENOMINACION_INVALIDA_EXCEPTION_H

#include "ExcepcionBase.h"

class DenominacionInvalidaException : public ExcepcionBase {
public:
    explicit DenominacionInvalidaException(const std::string& msg);
};

#endif
