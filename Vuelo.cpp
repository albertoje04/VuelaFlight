//
// Created by alber on 09/12/2023.
//

#include "Vuelo.h"

Vuelo::Vuelo(): fecha() {}

Vuelo::Vuelo(const std::string &fnum, const std::string &avion, const std::string dat_met,
             Fecha _f, Aerolinea *lAero, Aeropuerto* ori, Aeropuerto* dest):
        flight_num(fnum), plane(avion), datos_meteo(dat_met), fecha(_f), linkAero(lAero),
        apOrigin(ori), apDestiny(dest)
{ }

Vuelo::Vuelo(const Vuelo &copy): flight_num(copy.flight_num), plane(copy.plane), datos_meteo(copy.datos_meteo),
                                 fecha(copy.fecha), linkAero(copy.linkAero), apOrigin(copy.apOrigin), apDestiny(copy.apDestiny)
{ }

Vuelo& Vuelo::operator=(const Vuelo &other) {
    if (this!=&other){
        flight_num = other.flight_num;
        plane = other.plane;
        datos_meteo = other.datos_meteo;
        fecha = other.fecha;
        linkAero = other.linkAero;
        apDestiny = other.apDestiny;
        apOrigin = other.apOrigin;
    }
    return *this;
}

Aeropuerto *Vuelo::getApOrigin() {
    return apOrigin;
}

void Vuelo::setApOrigin(Aeropuerto *apOrigin) {
    Vuelo::apOrigin = apOrigin;
}

Aeropuerto *Vuelo::getApDestiny() {
    return apDestiny;
}

void Vuelo::setApDestiny(Aeropuerto *apDestiny) {
    Vuelo::apDestiny = apDestiny;
}

const std::string &Vuelo::getFlightNum() const {
    return flight_num;
}

void Vuelo::setFlightNum(const std::string &flightNum) {
    flight_num = flightNum;
}

const std::string &Vuelo::getPlane() const {
    return plane;
}

void Vuelo::setPlane(const std::string &plane) {
    Vuelo::plane = plane;
}

const std::string &Vuelo::getDatosMeteo() const {
    return datos_meteo;
}

void Vuelo::setDatosMeteo(const std::string &datosMeteo) {
    datos_meteo = datosMeteo;
}

const Fecha &Vuelo::getFecha() const {
    return fecha;
}

void Vuelo::setFecha(const Fecha &fecha) {
    Vuelo::fecha = fecha;
}

Aerolinea *Vuelo::getLinkAero(){
    return linkAero;
}

void Vuelo::setLinkAero(Aerolinea *lnkAero) {
    Vuelo::linkAero = lnkAero;
}
