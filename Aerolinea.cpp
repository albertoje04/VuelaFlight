//
// Created by alber on 09/12/2023.
//

#include "Aerolinea.h"
#include "Ruta.h"

/**
 * @brief Constructor parametrizado de Aerolinea
 */
Aerolinea::Aerolinea(): aeroroutes(), flights() {}

/**
 * @brief Constructor copia de Aerolinea
 * @param[in] copy Objeto que queremos copiar
 */
Aerolinea::Aerolinea(const Aerolinea &copy): id (copy.id), icao(copy.icao), nombre(copy.nombre),
                                             pais(copy.pais), activo(copy.activo), aeroroutes(copy.aeroroutes), flights(copy.flights)
{ }

/**
 * @brief Constructor parametrizado de Aerolinea
 * @param[in] id Identificador de la aerolinea (unsigned int)
 * @param[in] icao Código icao de la aerolinea (string)
 * @param[in] nombre Nombre de la propia aerolinea (string)
 * @param[in] pais Pais donde opera la aerolinea (string)
 * @param[in] activo Parámetro que indica si la aerolinea esta activa o no (bool)
 */
Aerolinea::Aerolinea(unsigned int id, const std::string& icao, const std::string& nombre, const std::string& pais,
                     bool activo) : id (id), icao(icao), nombre(nombre), pais(pais), activo(activo)

{ }

Aerolinea& Aerolinea::operator=(const Aerolinea &other) {
    if (this != &other){
        id = other.id;
        icao = other.icao;
        nombre = other.nombre;
        pais = other.pais;
        activo = other.activo;
        aeroroutes = other.aeroroutes;
        flights = other.flights;
    }
    return *this;
}


unsigned int Aerolinea::getId() const {
    return id;
}

void Aerolinea::setId(unsigned int id) {
    Aerolinea::id = id;
}

const std::string &Aerolinea::getIcao() const {
    return icao;
}

void Aerolinea::setIcao(const std::string &icao) {
    Aerolinea::icao = icao;
}

const std::string &Aerolinea::getNombre() const {
    return nombre;
}

void Aerolinea::setNombre(const std::string &nombre) {
    Aerolinea::nombre = nombre;
}

const std::string &Aerolinea::getPais() const {
    return pais;
}

void Aerolinea::setPais(const std::string &pais) {
    Aerolinea::pais = pais;
}

bool Aerolinea::isActivo() const {
    return activo;
}

void Aerolinea::setActivo(bool activo) {
    Aerolinea::activo = activo;
}

/**
 * @brief Funcion que devuelve un vector con todos los aeropuertos donde opera la aerolinea
 * @return Devuelve un vector dinámico de punteros a Aeropuertos donde opera la aerolinea
 */
std::vector<Aeropuerto *> Aerolinea::getAeropuertosOrig() {
    std::vector<Aeropuerto*> toRet;
    bool enc;

    for (int i=0;i<aeroroutes.size();++i){
        enc = false;
        Aeropuerto* ins = aeroroutes[i]->getOrigin();
        int j=0;
        while (j<toRet.size() && !enc){
            if (ins == toRet[j])
                enc = true;
            j++;
        }
        if (!enc)
            toRet.push_back(ins);
    }

    return toRet;
}

/**
 * @brief Funcion que devuelve una lista de rutas cuyos aeropuertos (origen y/o destino)
 * coinciden con el código iata pasado como parámetro
 * @param[in] iataAeropuerto  Código iata del Aeropuerto que se va a buscar
 * @return Devuelve una ListaEnlazada de punteros a Rutas con las rutas que cumplan las condiciones
 */
std::list<Ruta *> Aerolinea::getRutasAeropuertos(const std::string &iataAeropuerto) {
    std::list<Ruta*> toRet;
    for (int i=0;i<aeroroutes.size();++i){
        if (aeroroutes[i]->getOrigin()->getIata() == iataAeropuerto ||
            aeroroutes[i]->getDestiny()->getIata() == iataAeropuerto){
            toRet.push_back(aeroroutes[i]);
        }
    }

    return toRet;
}

/**
 * @brief Funcion que enlaza una Aerolinea con una ruta
 * @param[in] linkRuta Ruta que se añadirá a las ya existentes de una Aerolinea
 */
void Aerolinea::linkAerolRuta(Ruta *linkRuta) {
    aeroroutes.push_back(linkRuta);
}

/**
 * @brief Funcion que añade un vuelo al multimapa de Vuelos (flights)
 * @param[in] v Vuelo que se va a añadir
 * @return Devuelve el vuelo insertado
 */
Vuelo *Aerolinea::addVuelo(Vuelo &v) {
    if (v.getApDestiny() && v.getApOrigin() && v.getLinkAero()->getIcao() == this->icao){
        std::pair<std::string,Vuelo> insPair (v.getFlightNum(),v);
        flights.insert(insPair);
        std::multimap<std::string,Vuelo>::iterator itBusca = flights.find(v.getFlightNum());
        if (itBusca != flights.end()){
            Vuelo* vRet = &(itBusca->second);
            //Añadimos a la ruta
            bool found = false;
            std::deque<Ruta*>::iterator route = aeroroutes.begin();
            while (route != aeroroutes.end() && !found){
                if ((*route)->getOrigin() == v.getApOrigin() &&
                    (*route)->getDestiny() == v.getApDestiny() &&
                    (*route)->getCompany()->getIcao() == v.getLinkAero()->getIcao()){
                    found = true;
                    (*route)->addVuelo(vRet);
                }
                route++;
            }
            return vRet;
        }
    }
    return nullptr;
}

/**
 * @brief Funcion que devuelve todos los vuelos de una aerolinea dado su flight number
 * @param[in] find_Numfl Número identificador de un vuelo
 * @return Devuelve un vector de punteros a Vuelos del flight number dado
 */
std::vector<Vuelo*> Aerolinea::getVuelos(const std::string &find_Numfl) {
    std::multimap<std::string,Vuelo>::iterator tree = flights.find(find_Numfl);
    std::vector<Vuelo*> retVuelos;

    for (tree = tree; tree != flights.end(); ++tree){
        if (tree->second.getFlightNum() == find_Numfl)
            retVuelos.push_back(&(tree->second));
    }

    return retVuelos;
}

/**
 * @brief Funcion que devuelve todos los vuelos entre dos fechas dadas
 * @param[in] inicio Fecha de inicio
 * @param[in] final Fecha límite
 * @return Devuelve un vector de punteros a Vuelos que se encuentran entre las fechas dadas
 */
std::vector<Vuelo *> Aerolinea::getVuelos(const Fecha &inicio, const Fecha &final) {
    std::multimap<std::string,Vuelo>::iterator f = flights.begin();
    std::vector<Vuelo*> retVuelos;
    while (f != flights.end()){
        if (!(inicio < f->second.getFecha()) && (f->second.getFecha().mismoDia(final) || final < f->second.getFecha()))
            retVuelos.push_back(&(f->second));
        f++;
    }

    return retVuelos;
}

bool Aerolinea::operator<(const Aerolinea &comp) {
    if (this->getIcao()<comp.getIcao())
        return true;
    return false;
}

bool Aerolinea::operator>(const Aerolinea &comp) {
    if (this->getIcao() > comp.getIcao())
        return true;
    return false;
}

bool Aerolinea::operator==(const Aerolinea &comp) {
    if (this->getIcao() == comp.getIcao())
        return true;
    return false;
}

/**
 * @brief Funcion que devuelve todos los vuelos de una aerolínea (flights)
 * @return Devuelve un deque (vector mejorado) con todos los vuelos de una aerolínea
 * @note Este método está destinado a auxiliar a otro método diseñado en VuelaFlight (buscaAeropuertosAerolinea)
 */
std::deque<Vuelo*> Aerolinea::getFlightsAerolinea() {
    std::multimap<std::string,Vuelo>::iterator i;
    std::deque<Vuelo*> retFlights;
    for (i = flights.begin(); i != flights.end(); ++i){
        retFlights.push_back(&(i->second));
    }

    return retFlights;
}

void Aerolinea::bajaAeropuerto(const std::string &iataAp) {
    std::multimap<std::string,Vuelo>::iterator itVuelos = flights.begin();
    for (;itVuelos != flights.end();++itVuelos){
        if (itVuelos->second.getApDestiny()->getIata() == iataAp ||
            itVuelos->second.getApOrigin()->getIata() == iataAp)
            flights.erase(itVuelos);
    }

    std::deque<Ruta*>::iterator rut;
    for (rut = aeroroutes.begin(); rut != aeroroutes.end(); rut++) {
        if ((*rut)->getOrigin()->getIata() == iataAp ||
            (*rut)->getDestiny()->getIata() == iataAp)
            aeroroutes.erase(rut);
    }
}
