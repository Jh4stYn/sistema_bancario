#ifndef SALDO_INSUFICIENTE_EXCEPTION_H
#define SALDO_INSUFICIENTE_EXCEPTION_H

#include "ExcepcionBase.h"

class SaldoInsuficienteException : public ExcepcionBase {
private:
    float saldoActual;
    float montoSolicitado;
public:
    SaldoInsuficienteException(float saldo, float monto);
    float getSaldoActual() const;
    float getMontoSolicitado() const;
};

#endif