#include "../include/sistema_bancario.h"
#include "../include/funciones_aux.h"
#include "../include/excepciones.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <cstdlib>
#include <cmath>
#include <stdexcept>
#include <cctype>

using namespace std;

// ================== MÉTODOS PRIVADOS ==================

void SistemaBancario::validarFecha(const string& fecha) {
    if (fecha.length() != 10 || 
        fecha[4] != '-' || fecha[7] != '-' ||
        !all_of(fecha.begin(), fecha.begin()+4, ::isdigit) ||
        !all_of(fecha.begin()+5, fecha.begin()+7, ::isdigit) ||
        !all_of(fecha.begin()+8, fecha.end(), ::isdigit)) {
        throw FechaInvalidaException("Formato de fecha inválido. Use AAAA-MM-DD");
    }

    int mes = stoi(fecha.substr(5, 2));
    int dia = stoi(fecha.substr(8, 2));
    
    if (mes < 1 || mes > 12) throw FechaInvalidaException("Mes inválido");
    if (dia < 1 || dia > 31) throw FechaInvalidaException("Día inválido");
}

void SistemaBancario::validarDenominaciones(const map<int, int>& denom, double monto) {
    double total = 0;
    for (const auto& d : denom) {
        if (d.first <= 0 || d.second <= 0) {
            throw DenominacionInvalidaException("Denominaciones deben ser positivas");
        }
        total += d.first * d.second;
    }

    if (fabs(total - monto) > 0.01) {
        throw DenominacionInvalidaException("Las denominaciones no coinciden con el monto");
    }
}

double SistemaBancario::calcularMontoDenominaciones(const map<int, int>& denom) {
    double total = 0;
    for (const auto& d : denom) {
        total += d.first * d.second;
    }
    return total;
}

bool SistemaBancario::compararDenominaciones(const pair<int, int>& a, const pair<int, int>& b) {
    return a.first > b.first;
}

void SistemaBancario::actualizarSaldos(Transaccion* trans) {
    for (auto& saldo : saldosBCR) {
        if (saldo->fecha == trans->fecha && saldo->moneda == trans->moneda) {
            if (trans->esIngreso) {
                saldo->ingresos += trans->monto;
            } else {
                saldo->egresos += trans->monto;
            }
            saldo->saldoFinal = saldo->saldoInicial + saldo->ingresos - saldo->egresos;
            return;
        }
    }

    // Si no existe, crear nuevo saldo
    double saldoInicial = 0;
    for (auto it = saldosBCR.rbegin(); it != saldosBCR.rend(); ++it) {
        if ((*it)->moneda == trans->moneda) {
            saldoInicial = (*it)->saldoFinal;
            break;
        }
    }

    SaldoBCR* nuevoSaldo = new SaldoBCR(trans->fecha, trans->moneda, saldoInicial);
    saldosBCR.push_back(nuevoSaldo);
    actualizarSaldos(trans);
}

// ================== DESTRUCTOR ==================

SistemaBancario::~SistemaBancario() {
    for (auto& t : transacciones) delete t;
    for (auto& s : saldosBCR) delete s;
}

// ================== MÉTODOS PÚBLICOS ==================

void SistemaBancario::agregarBanco(Banco* banco) { bancos.push_back(banco); }
void SistemaBancario::agregarTransportista(Transportista* trans) { transportistas.push_back(trans); }
void SistemaBancario::agregarPlaza(Plaza* plaza) { plazas.push_back(plaza); }
void SistemaBancario::agregarSaldoBCR(SaldoBCR* saldo) { saldosBCR.push_back(saldo); }

void SistemaBancario::registrarTransaccion(Transaccion* trans) {
    try {
        validarFecha(trans->fecha);
        validarDenominaciones(trans->denominaciones, trans->monto);
        
        if (trans->monto <= 0) {
            throw ValorInvalidoException("El monto debe ser positivo");
        }

        transacciones.push_back(trans);
        actualizarSaldos(trans);
    } catch (const exception& e) {
        cerr << "\nError al registrar transacción: " << e.what() << endl;
        delete trans;
        throw;
    }
}

void SistemaBancario::generarReporteDiario(string fecha) {
    try {
        system("cls");
        validarFecha(fecha);
        cout << fixed << setprecision(2);
        
        cout << "\n=== REPORTE DIARIO (" << fecha << ") ===" << endl;
        cout << "-----------------------------------------------------------------" << endl;
        cout << left << setw(16) << "OPERACION" << setw(12) << "TIPO" 
             << setw(10) << "MONEDA" << setw(16) << "TRANSPORTISTA" 
             << setw(12) << "MONTO" << setw(8) << "FLUJO" << "DENOMINACIONES" << endl;
        cout << "-----------------------------------------------------------------" << endl;
        
        bool hayTransacciones = false;
        for (auto& trans : transacciones) {
            if (trans->fecha == fecha) {
                hayTransacciones = true;
                vector<pair<int, int>> denomOrdenadas(
                    trans->denominaciones.begin(), 
                    trans->denominaciones.end()
                );
                sort(denomOrdenadas.begin(), denomOrdenadas.end(), compararDenominaciones);

                cout << left << setw(16) << trans->idOperacion 
                     << setw(12) << getTipoOperacionStr(trans->tipo)
                     << setw(10) << getMonedaStr(trans->moneda)
                     << setw(16) << trans->transportista->nombre
                     << setw(12) << trans->monto
                     << setw(8) << (trans->esIngreso ? "INGRESO" : "EGRESO");
                
                for (auto& denom : denomOrdenadas) {
                    cout << denom.first << "x" << denom.second << " ";
                }
                cout << endl;
            }
        }

        if (!hayTransacciones) {
            cout << "No hay transacciones registradas para esta fecha." << endl;
        }

        // Mostrar saldos BCR
        cout << "\nSALDOS BCR:" << endl;
        cout << "----------------------------------------" << endl;
        bool haySaldos = false;
        for (auto& saldo : saldosBCR) {
            if (saldo->fecha == fecha) {
                haySaldos = true;
                cout << "Moneda: " << left << setw(8) << getMonedaStr(saldo->moneda)
                     << " | Saldo Inicial: " << setw(12) << saldo->saldoInicial
                     << " | Egresos: " << setw(10) << saldo->egresos
                     << " | Ingresos: " << setw(10) << saldo->ingresos
                     << " | Saldo Final: " << setw(12) << saldo->saldoFinal << endl;
            }
        }

        if (!haySaldos) {
            cout << "No hay saldos registrados para esta fecha." << endl;
        }
    } catch (const exception& e) {
        cerr << "\nError al generar reporte: " << e.what() << endl;
    }
}

void SistemaBancario::agregarOperacionManual() {
    try {
        system("cls");
        string fecha;
        cout << "Ingrese fecha de la operacion (AAAA-MM-DD): ";
        getline(cin, fecha);
        validarFecha(fecha);

        cout << "\nTipos de operacion:" << endl;
        cout << "1. DEPOSITO (Ingreso)\n2. RETIRO (Egreso)\n3. TRASLADO (Egreso)\n4. CANJE (Egreso)\n5. PAGO (Egreso)" << endl;
        
        int tipoOp;
        cout << "Seleccione el tipo (1-5): ";
        if (!(cin >> tipoOp) || tipoOp < 1 || tipoOp > 5) {
            throw ValorInvalidoException("Tipo de operación inválido");
        }
        
        bool esIngreso = (tipoOp == 1);

        cout << "\nMonedas disponibles:" << endl;
        cout << "1. SOLES\n2. DOLARES\n3. EUROS\n4. BONOS\n5. JOYAS" << endl;
        
        int monedaOp;
        cout << "Seleccione la moneda (1-5): ";
        if (!(cin >> monedaOp) || monedaOp < 1 || monedaOp > 5) {
            throw ValorInvalidoException("Moneda inválida");
        }

        cout << "\nTransportistas:" << endl;
        for(size_t i = 0; i < transportistas.size(); ++i) {
            cout << i+1 << ". " << transportistas[i]->nombre << endl;
        }
        
        int transportistaOp;
        cout << "Seleccione transportista (1-" << transportistas.size() << "): ";
        if (!(cin >> transportistaOp) || transportistaOp < 1 || transportistaOp > static_cast<int>(transportistas.size())) {
            throw ValorInvalidoException("Transportista inválido");
        }

        cout << "\nPlazas:" << endl;
        for(size_t i = 0; i < plazas.size(); ++i) {
            cout << i+1 << ". " << plazas[i]->nombre << endl;
        }
        
        int plazaOp;
        cout << "Seleccione plaza (1-" << plazas.size() << "): ";
        if (!(cin >> plazaOp) || plazaOp < 1 || plazaOp > static_cast<int>(plazas.size())) {
            throw ValorInvalidoException("Plaza inválida");
        }

        cout << "\nBancos:" << endl;
        for(size_t i = 0; i < bancos.size(); ++i) {
            cout << i+1 << ". " << bancos[i]->nombre << endl;
        }
        
        int bancoOrigenOp, bancoDestinoOp;
        cout << "Seleccione banco origen (1-" << bancos.size() << "): ";
        if (!(cin >> bancoOrigenOp) || bancoOrigenOp < 1 || bancoOrigenOp > static_cast<int>(bancos.size())) {
            throw ValorInvalidoException("Banco origen inválido");
        }
        
        cout << "Banco destino (0 si no aplica): ";
        if (!(cin >> bancoDestinoOp) || bancoDestinoOp < 0 || bancoDestinoOp > static_cast<int>(bancos.size())) {
            throw ValorInvalidoException("Banco destino inválido");
        }

        double monto;
        cout << "Monto: ";
        if (!(cin >> monto) || monto <= 0) {
            throw ValorInvalidoException("Monto debe ser positivo");
        }

        // Crear denominaciones
        map<int, int> denominaciones;
        int denom, cant;
        cout << "\nIngrese denominaciones (ej: 200 50):\n(0 0 para terminar)" << endl;
        while(true) {
            cout << "Denominacion cantidad: ";
            if (!(cin >> denom >> cant)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw ValorInvalidoException("Entrada inválida para denominaciones");
            }
            
            if (denom == 0 && cant == 0) break;
            if (denom <= 0 || cant <= 0) {
                throw DenominacionInvalidaException("Denominaciones deben ser positivas");
            }
            denominaciones[denom] = cant;
        }

        // Validar denominaciones
        validarDenominaciones(denominaciones, monto);

        // Crear transacción
        string id = "OPE-" + fecha.substr(2, 2) + fecha.substr(5, 2) + fecha.substr(8, 2) + "-" + to_string(transacciones.size() + 1);
        
        Transaccion* nuevaTrans = new Transaccion(
            id, fecha, 
            static_cast<TipoOperacion>(tipoOp - 1),
            static_cast<Moneda>(monedaOp - 1),
            transportistas[transportistaOp - 1],
            plazas[plazaOp - 1],
            bancos[bancoOrigenOp - 1],
            (bancoDestinoOp > 0) ? bancos[bancoDestinoOp - 1] : nullptr,
            monto, denominaciones, esIngreso
        );

        registrarTransaccion(nuevaTrans);
        cout << "\nOperación registrada exitosamente!" << endl;
        
    } catch (const exception& e) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "\nError: " << e.what() << endl;
        cerr << "La operación no fue registrada. Intente nuevamente." << endl;
    }
    
    cout << "Presione Enter para continuar...";
    cin.ignore();
    cin.ignore();
}

void SistemaBancario::mostrarMenu() {
    int opcion;
    do {
        try {
            system("cls");
            cout << "\n=== SISTEMA BANCARIO ===" << endl;
            cout << "1. Mostrar reporte inicial (26/06/2024)" << endl;
            cout << "2. Agregar nueva operación" << endl;
            cout << "3. Generar reporte por fecha" << endl;
            cout << "4. Salir" << endl;
            cout << "Seleccione una opción: ";
            
            if (!(cin >> opcion)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw ValorInvalidoException("Entrada inválida");
            }
            cin.ignore();

            switch(opcion) {
                case 1:
                    generarReporteDiario("2024-06-26");
                    cout << "\nPresione Enter para continuar...";
                    cin.ignore();
                    break;
                case 2:
                    agregarOperacionManual();
                    break;
                case 3: {
                    string fecha;
                    cout << "Ingrese fecha (AAAA-MM-DD): ";
                    getline(cin, fecha);
                    try {
                        validarFecha(fecha);
                        generarReporteDiario(fecha);
                    } catch (const exception& e) {
                        cerr << "\nError: " << e.what() << endl;
                    }
                    cout << "\nPresione Enter para continuar...";
                    cin.ignore();
                    break;
                }
                case 4:
                    cout << "Saliendo del sistema..." << endl;
                    break;
                default:
                    cout << "Opción no válida." << endl;
            }
        } catch (const exception& e) {
            cerr << "\nError en el menú: " << e.what() << endl;
            cout << "Presione Enter para continuar...";
            cin.ignore();
            cin.ignore();
        }
    } while(opcion != 4);
}