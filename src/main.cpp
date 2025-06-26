#include "../include/sistema_bancario.h"
#include "../include/entidades/banco.h"
#include "../include/entidades/transportista.h"
#include "../include/entidades/plaza.h"
#include "../include/entidades/transaccion.h"
#include "../include/entidades/saldo_bcr.h"
#include <iostream>

using namespace std;

int main() {
    try {
        system("chcp 65001 > nul"); // Configurar consola para UTF-8
        system("cls");

        // ================== CONFIGURACIÓN INICIAL ==================
        Banco bcp("BCP", "Banco de Crédito", "002");
        Banco bbva("BBVA", "BBVA Perú", "001");
        Banco interbank("INT", "Interbank", "003");

        Transportista prosegur("PRO", "Prosegur", "20123456789");
        Transportista hermes("HER", "Hermes", "20234567890");
        Transportista brinks("BRI", "Brinks", "20345678901");

        Plaza lima("LIM", "Lima Centro", "Lima");
        Plaza arequipa("ARE", "Arequipa", "Arequipa");
        Plaza cusco("CUS", "Cusco", "Cusco");

        SistemaBancario sistema;
        sistema.agregarBanco(&bcp);
        sistema.agregarBanco(&bbva);
        sistema.agregarBanco(&interbank);
        sistema.agregarTransportista(&prosegur);
        sistema.agregarTransportista(&hermes);
        sistema.agregarTransportista(&brinks);
        sistema.agregarPlaza(&lima);
        sistema.agregarPlaza(&arequipa);
        sistema.agregarPlaza(&cusco);

        // ================== SALDOS INICIALES ==================
        sistema.agregarSaldoBCR(new SaldoBCR("2024-06-26", Moneda::PEN, 1000000.00));
        sistema.agregarSaldoBCR(new SaldoBCR("2024-06-27", Moneda::PEN, 1200000.00));
        sistema.agregarSaldoBCR(new SaldoBCR("2024-06-26", Moneda::USD, 500000.00));
        sistema.agregarSaldoBCR(new SaldoBCR("2024-06-27", Moneda::USD, 600000.00));

        // ================== OPERACIONES INICIALES ==================
        // Deposito en PEN
        sistema.registrarTransaccion(new Transaccion(
            "OPE-240626-001", "2024-06-26", TipoOperacion::DEPOSITO, Moneda::PEN,
            &prosegur, &lima, &bbva, nullptr, 25000.00, {{200, 100}, {50, 100}}, true));

        // Traslado en PEN
        sistema.registrarTransaccion(new Transaccion(
            "OPE-240626-002", "2024-06-26", TipoOperacion::TRASLADO, Moneda::PEN,
            &hermes, &arequipa, &bcp, &interbank, 18000.00, {{100, 150}, {50, 60}}, false));

        // Retiro en USD
        sistema.registrarTransaccion(new Transaccion(
            "OPE-240626-003", "2024-06-26", TipoOperacion::RETIRO, Moneda::USD,
            &brinks, &cusco, &interbank, nullptr, 5000.00, {{100, 50}}, false));

        // Canje en PEN
        sistema.registrarTransaccion(new Transaccion(
            "OPE-240626-004", "2024-06-26", TipoOperacion::CANJE, Moneda::PEN,
            &prosegur, &lima, &bbva, &bcp, 12000.00, {{100, 120}}, false));

        // Pago en USD
        sistema.registrarTransaccion(new Transaccion(
            "OPE-240626-005", "2024-06-26", TipoOperacion::PAGO, Moneda::USD,
            &hermes, &arequipa, &interbank, nullptr, 3000.00, {{100, 30}}, false));

        // ================== MENÚ PRINCIPAL ==================
        sistema.mostrarMenu();

    } catch (const exception& e) {
        cerr << "\nError crítico en el sistema: " << e.what() << endl;
        return 1;
    } catch (...) {
        cerr << "\nError desconocido en el sistema" << endl;
        return 2;
    }

    return 0;
}