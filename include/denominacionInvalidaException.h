#ifndef DENOMINACION_INVALIDA_EXCEPTION_H
#define DENOMINACION_INVALIDA_EXCEPTION_H

#include "ExcepcionBase.h"

class DenominacionInvalidaException : public ExcepcionBase {
public:
    explicit DenominacionInvalidaException(const std::string& msg);
};

#endif