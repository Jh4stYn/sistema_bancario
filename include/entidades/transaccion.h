#pragma once
#include "enumeraciones.h"
#include <string>
#include <map>

class Transportista;
class Plaza;
class Banco;

class Transaccion {
public:
    std::string idOperacion;
    std::string fecha;
    TipoOperacion tipo;
    Moneda moneda;
    Transportista* transportista;
    Plaza* plaza;
    Banco* bancoOrigen;
    Banco* bancoDestino;
    double monto;
    std::map<int, int> denominaciones;
    bool esIngreso;

    Transaccion(std::string id, std::string fecha, TipoOperacion tipo, Moneda moneda, 
                Transportista* transportista, Plaza* plaza, 
                Banco* origen, Banco* destino, double monto, 
                std::map<int, int> denom, bool ingreso);
};