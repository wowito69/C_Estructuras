cmake_minimum_required(VERSION 3.26)
project(estructuras_de_datos C)

set(CMAKE_C_STANDARD 11)

add_executable(arbol arbol_binario/arbol_binario.c)
add_executable(lista_simple lista_enlace_simple/lista_enlace_simple.c)
add_executable(grafo Grafo_estructura/Grafo.c)