#include "../include/entidades/transaccion.h"

Transaccion::Transaccion(std::string id, std::string fecha, TipoOperacion tipo, Moneda moneda, 
                         Transportista* transportista, Plaza* plaza, 
                         Banco* origen, Banco* destino, double monto, 
                         std::map<int, int> denom, bool ingreso)
    : idOperacion(id), fecha(fecha), tipo(tipo), moneda(moneda),
      transportista(transportista), plaza(plaza),
      bancoOrigen(origen), bancoDestino(destino),
      monto(monto), denominaciones(denom), esIngreso(ingreso) {}