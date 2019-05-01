cmake_minimum_required(VERSION 3.13)
project(Gladiators-GBP-Server)

set(CMAKE_CXX_STANDARD 14)

add_executable(Gladiators-GBP-Server main.cpp Gladiador.h Gladiador.cpp FabricaGladiadores.cpp FabricaGladiadores.h)