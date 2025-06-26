#pragma once
#include "enumeraciones.h"
#include <string>

class SaldoBCR {
public:
    std::string fecha;
    Moneda moneda;
    double saldoInicial;
    double egresos;
    double ingresos;
    double saldoFinal;

    SaldoBCR(std::string fecha, Moneda moneda, double inicial);
    void actualizarSaldo(double egreso, double ingreso);
};