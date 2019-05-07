cmake_minimum_required(VERSION 3.13)
project(Gladiators-GBP-Server)

set(CMAKE_CXX_STANDARD 14)

add_executable(Gladiators-GBP-Server main.cpp Gladiador.h Gladiador.cpp FabricaGladiadores.cpp FabricaGladiadores.h)

find_package(PkgConfig REQUIRED)
pkg_check_modules(JSON-C json-c)
link_libraries(${JSON-C_LIBRARIES})
target_link_libraries(Gladiators-GBP-Server ${JSON-C_LIBRARIES})