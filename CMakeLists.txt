cmake_minimum_required(VERSION 3.10)
project(SistemaBancario)

# Configuración básica
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Directorios de origen
set(SOURCE_DIR src)
set(INCLUDE_DIR include)

# Archivos fuente
file(GLOB_RECURSE SOURCES 
    "${SOURCE_DIR}/*.cpp"
    "${SOURCE_DIR}/entidades/*.cpp"
)

# Archivos de cabecera
file(GLOB_RECURSE HEADERS 
    "${INCLUDE_DIR}/*.h"
    "${INCLUDE_DIR}/entidades/*.h"
)

# Configurar el ejecutable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Incluir directorios
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${INCLUDE_DIR}
)

# Opciones para Windows
if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()