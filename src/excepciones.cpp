#include "../include/excepciones.h"

OperacionInvalidaException::OperacionInvalidaException(const std::string& msg) 
    : std::runtime_error(msg) {}

ValorInvalidoException::ValorInvalidoException(const std::string& msg) 
    : std::runtime_error(msg) {}

FechaInvalidaException::FechaInvalidaException(const std::string& msg) 
    : std::runtime_error(msg) {}

DenominacionInvalidaException::DenominacionInvalidaException(const std::string& msg) 
    : std::runtime_error(msg) {}