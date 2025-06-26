#pragma once
#include "entidades/banco.h"
#include "entidades/transportista.h"
#include "entidades/plaza.h"
#include "entidades/transaccion.h"
#include "entidades/saldo_bcr.h"
#include <vector>
#include <map>

class SistemaBancario {
private:
    std::vector<Banco*> bancos;
    std::vector<Transportista*> transportistas;
    std::vector<Plaza*> plazas;
    std::vector<Transaccion*> transacciones;
    std::vector<SaldoBCR*> saldosBCR;

    void validarFecha(const std::string& fecha);
    void validarDenominaciones(const std::map<int, int>& denom, double monto);
    double calcularMontoDenominaciones(const std::map<int, int>& denom);
    static bool compararDenominaciones(const std::pair<int, int>& a, const std::pair<int, int>& b);
    void actualizarSaldos(Transaccion* trans);

public:
    ~SistemaBancario();

    void agregarBanco(Banco* banco);
    void agregarTransportista(Transportista* trans);
    void agregarPlaza(Plaza* plaza);
    void agregarSaldoBCR(SaldoBCR* saldo);
    void registrarTransaccion(Transaccion* trans);
    void generarReporteDiario(std::string fecha);
    void agregarOperacionManual();
    void mostrarMenu();
};