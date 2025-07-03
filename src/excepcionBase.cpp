#include "excepcionBase.h"

ExcepcionBase::ExcepcionBase(const std::string& msg) : mensaje(msg) {}

const char* ExcepcionBase::what() const noexcept {
    return mensaje.c_str();
}