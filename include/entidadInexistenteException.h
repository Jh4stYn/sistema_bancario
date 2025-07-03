#ifndef ENTIDAD_INEXISTENTE_EXCEPTION_H
#define ENTIDAD_INEXISTENTE_EXCEPTION_H

#include "ExcepcionBase.h"

class EntidadInexistenteException : public ExcepcionBase {
public:
    explicit EntidadInexistenteException(const std::string& entidad);
};

#endif