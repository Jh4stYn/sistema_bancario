#include "../include/funciones_aux.h"
#include "../include/enumeraciones.h"

std::string getTipoOperacionStr(TipoOperacion tipo) {
    switch(tipo) {
        case TipoOperacion::RETIRO: return "RETIRO";
        case TipoOperacion::DEPOSITO: return "DEPOSITO";
        case TipoOperacion::TRASLADO: return "TRASLADO";
        case TipoOperacion::CANJE: return "CANJE";
        case TipoOperacion::PAGO: return "PAGO";
        default: return "DESCONOCIDO";
    }
}

std::string getMonedaStr(Moneda moneda) {
    switch(moneda) {
        case Moneda::PEN: return "SOLES";
        case Moneda::USD: return "DOLARES";
        case Moneda::EUR: return "EUROS";
        case Moneda::BONOS: return "BONOS";
        case Moneda::JOYAS: return "JOYAS";
        default: return "DESCONOCIDO";
    }
}