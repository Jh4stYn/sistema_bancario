#include "../include/entidades/saldo_bcr.h"

SaldoBCR::SaldoBCR(std::string fecha, Moneda moneda, double inicial)
    : fecha(fecha), moneda(moneda), saldoInicial(inicial),
      egresos(0), ingresos(0), saldoFinal(inicial) {}

void SaldoBCR::actualizarSaldo(double egreso, double ingreso) {
    egresos += egreso;
    ingresos += ingreso;
    saldoFinal = saldoInicial + ingresos - egresos;
}