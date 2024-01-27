cmake_minimum_required(VERSION 3.26)
project(PRACTICA_6_EEDD)

set(CMAKE_CXX_STANDARD 17)

add_executable(PRACTICA_6_EEDD main.cpp
        Aerolinea.cpp
        Aerolinea.h
        Aeropuerto.cpp
        Aeropuerto.h
        Fecha.cpp
        Fecha.h
        Ruta.cpp
        Ruta.h
        UTM.cpp
        UTM.h
        VuelaFlight.cpp
        VuelaFlight.h
        Vuelo.cpp
        Vuelo.h
        MallaRegular.h
)
