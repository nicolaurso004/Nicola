cmake_minimum_required(VERSION 3.10)
project(Esercitazione2)

# Impostazioni richieste dal prof per attivare i warning e l'errore sui VLA
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")

# Istruzioni per creare i due programmi
add_executable(es1 es1.cpp)
add_executable(es2 es2.cpp)