#include "../include/excepciones/SaldoInsuficienteException.h"
#include <sstream>

SaldoInsuficienteException::SaldoInsuficienteException(float saldo, float monto)
    : ExcepcionBase("Saldo insuficiente: disponible " + std::to_string(saldo) + ", solicitado " + std::to_string(monto)), saldoActual(saldo), montoSolicitado(monto) {}

float SaldoInsuficienteException::getSaldoActual() const { return saldoActual; }
float SaldoInsuficienteException::getMontoSolicitado() const { return montoSolicitado; }
