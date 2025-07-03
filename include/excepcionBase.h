#ifndef EXCEPCION_BASE_H
#define EXCEPCION_BASE_H

#include <exception>
#include <string>

class ExcepcionBase : public std::exception {
protected:
    std::string mensaje;
public:
    explicit ExcepcionBase(const std::string& msg);
    virtual const char* what() const noexcept override;
};

#endif