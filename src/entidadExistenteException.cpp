#include "entidadInexistenteException.h"

EntidadInexistenteException::EntidadInexistenteException(const std::string& entidad)
    : ExcepcionBase("Entidad inexistente: " + entidad) {}
