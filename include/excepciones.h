#pragma once
#include <stdexcept>
#include <string>

class OperacionInvalidaException : public std::runtime_error {
public:
    OperacionInvalidaException(const std::string& msg);
};

class ValorInvalidoException : public std::runtime_error {
public:
    ValorInvalidoException(const std::string& msg);
};

class FechaInvalidaException : public std::runtime_error {
public:
    FechaInvalidaException(const std::string& msg);
};

class DenominacionInvalidaException : public std::runtime_error {
public:
    DenominacionInvalidaException(const std::string& msg);
};