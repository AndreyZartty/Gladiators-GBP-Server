cmake_minimum_required(VERSION 3.13)
project(Gladiators_GBP)

set(CMAKE_CXX_STANDARD 14)

add_executable(Gladiators_GBP main.cpp AStar.cpp AStar.h Node.cpp Node.h Vector2.cpp Vector2.h Gladiador.cpp Gladiador.h Torre.cpp Torre.h Cuadricula.cpp Cuadricula.h Juego.cpp Juego.h Backtracking.cpp Backtracking.h list.cpp list.h nodeG.cpp nodeG.h poblacion.cpp poblacion.h)

find_package(PkgConfig REQUIRED)
pkg_check_modules(JSON-C json-c)
link_libraries(${JSON-C_LIBRARIES})
target_link_libraries(Gladiators_GBP ${JSON-C_LIBRARIES})