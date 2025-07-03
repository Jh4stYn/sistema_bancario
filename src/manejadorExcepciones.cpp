#include "manejadorExcepciones.h"

void ManejadorExcepciones::mostrarError(const std::exception& e) {
    std::cerr << "\n[ERROR]: " << e.what() << std::endl;
}
