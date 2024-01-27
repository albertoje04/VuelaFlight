//
// Created by alber on 09/12/2023.
//

#include "Aeropuerto.h"

const std::string &Aeropuerto::getId() const {
    return id;
}

void Aeropuerto::setId(const std::string &id) {
    Aeropuerto::id = id;
}

const std::string &Aeropuerto::getIata() const {
    return iata;
}

void Aeropuerto::setIata(const std::string &_iata) {
    Aeropuerto::iata = _iata;
}

const std::string &Aeropuerto::getTipo() const {
    return tipo;
}

void Aeropuerto::setTipo(const std::string &tipo) {
    Aeropuerto::tipo = tipo;
}

const std::string &Aeropuerto::getNombre() const {
    return nombre;
}

void Aeropuerto::setNombre(const std::string &nombre) {
    Aeropuerto::nombre = nombre;
}

const std::string &Aeropuerto::getContinente() const {
    return continente;
}

void Aeropuerto::setContinente(const std::string &continente) {
    Aeropuerto::continente = continente;
}

const std::string &Aeropuerto::getIsoPais() const {
    return iso_pais;
}

void Aeropuerto::setIsoPais(const std::string &isoPais) {
    iso_pais = isoPais;
}

const float Aeropuerto::getY() const {
    return posicion.getLatitud();
}

const float Aeropuerto::getX() const {
    return posicion.getLongitud();
}

void Aeropuerto::setUTM(UTM u) {
    posicion = u;
}

Aeropuerto::Aeropuerto() : posicion(UTM()) {

}

Aeropuerto::Aeropuerto(const std::string &id, const std::string &ident, std::string tipo, const std::string &nombre,
                       const UTM &posicion, const std::string continente, const std::string &iso_pais):
        id(id), iata(ident), nombre(nombre), tipo(tipo), posicion(posicion),
        continente(continente), iso_pais(iso_pais)
{

}

Aeropuerto::Aeropuerto(const Aeropuerto &orig): id(orig.id), iata(orig.iata), tipo(orig.tipo), nombre(orig.nombre),
                                                posicion(orig.posicion), continente(orig.continente), iso_pais(orig.iso_pais) {

}

bool Aeropuerto::operator==(const Aeropuerto &comp) {
    if (iata == comp.iata)
        return true;
    return false;
}

bool Aeropuerto::operator<(const Aeropuerto &comp) {
    if (iata < comp.iata)
        return true;
    return false;
}
