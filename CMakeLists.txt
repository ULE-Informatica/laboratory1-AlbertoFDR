cmake_minimum_required(VERSION 3.10)

# Especificamos que el proyecto es en C, cogiendo el compilador de C por defecto del sistema.
project(Entrega_DPS C)

# Especificamos el standard con el que compilar
set(CMAKE_C_STANDARD 11)
#set(CMAKE_C_STANDARD 99)

# Especificamos las opciones con las que compilar
add_compile_options(-Wall -Wextra -pedantic -Werror)

# Añadimos el ejecutable
add_executable(executable fixedExampleStrings.c)

