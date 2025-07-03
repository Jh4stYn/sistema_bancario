#ifndef FECHA_INVALIDA_EXCEPTION_H
#define FECHA_INVALIDA_EXCEPTION_H

#include "excepcionBase.h"

class FechaInvalidaException : public ExcepcionBase {
public:
    explicit FechaInvalidaException(const std::string& msg);
};

#endif
