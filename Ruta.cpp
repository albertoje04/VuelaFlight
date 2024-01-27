//
// Created by alber on 09/12/2023.
//

#include "Ruta.h"

Ruta::Ruta(const std::string &_alinea, Aeropuerto *o, Aeropuerto *d, Aerolinea*c): aerolinea(_alinea),origin(o),destiny(d),
                                                                                   company(c), flightRoutes()
{ }

Ruta::Ruta(const Ruta &copy): aerolinea(copy.aerolinea), origin(copy.origin), destiny(copy.destiny),
                              company(copy.company), flightRoutes(copy.flightRoutes)

{ }

Ruta& Ruta::operator=(const Ruta &other) {
    if (this!=&other){
        aerolinea = other.aerolinea;
        origin = other.origin;
        destiny = other.destiny;
        company = other.company;
        flightRoutes = other.flightRoutes;
    }
    return *this;
}

const std::string &Ruta::getAerolinea() const {
    return aerolinea;
}

void Ruta::setAerolinea(const std::string &aerolinea) {
    Ruta::aerolinea = aerolinea;
}

void Ruta::setOrigin(Aeropuerto *source) {
    origin = source;
}

Aeropuerto* Ruta::getOrigin() const {
    return origin;
}

void Ruta::setDestiny(Aeropuerto *dest) {
    destiny = dest;
}

Aeropuerto* Ruta::getDestiny() const {
    return destiny;
}

void Ruta::setCompany(Aerolinea *_comp) {
    company = _comp;
}

Aerolinea* Ruta::getCompany() const {
    return company;
}

/**
 * @brief Método que añade un vuelo a su relación correspondiente de Vuelos (flightRoutes)
 * @param[in] v Vuelo que se añadirá a la lista de Vuelos
 * @return Devuelve un booleano indicando si se realizó la inserción o no
 */
bool Ruta::addVuelo(Vuelo *v) {
    if (v->getApDestiny() == this->destiny &&
        v->getApOrigin() == this->origin &&
        v->getLinkAero()->getIcao() == this->getCompany()->getIcao()){
        flightRoutes.push_back(v);
        return true;
    }

    return false;
}

/**
 * @brief Funcion que devuelve el numero de vuelos de una ruta
 * @return Devuelve un entero (tamaño de vuelos de una ruta)
 */
int Ruta::getNumVuelos() const {
    return flightRoutes.size();
}

/**
 * @brief Funcion que devuelve todos los vuelos de una ruta
 * @return Devuelve una lista de punteros a Vuelos
 */
std::list<Vuelo *> Ruta::getVuelos() {
    return flightRoutes;
}
