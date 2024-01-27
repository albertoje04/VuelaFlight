//
// Created by alber on 09/12/2023.
//

#include <algorithm>
#include <cmath>
#include "VuelaFlight.h"
#include <queue>

/**
 * @brief Constructor parametrizado de la clase VuelaFlight
 * @param[in] ach_Aeropuertos Fichero con la información de los aeropuertos
 * @param[in] ach_Rutas Fichero con la información de las rutas
 * @param[in] ach_Aerolineas Fichero con la información de las aerolineas
 * @param[in] ach_Vuelos Fichero con la información de los vuelos
 */
VuelaFlight::VuelaFlight(const std::string& ach_Aeropuertos, const std::string& ach_Rutas,
                         const std::string& ach_Aerolineas, const std::string& ach_Vuelos):
        routesOrig(), routesDest(), airportsID(), airlines(),airportsUTM() {
    std::ifstream is;
    std::stringstream columnas;
    std::string fila;

    std::string id = "";
    std::string ident = "";
    std::string tipo = "";
    std::string nombre = "";
    std::string latitud_str = "";
    std::string longitud_str = "";
    std::string continente = "";
    std::string iso_pais = "";

    float latitud, longitud;

    clock_t t_ini = clock();

    is.open(ach_Aeropuertos); //carpeta de proyecto
    if (is.good()) {
        std::getline(is,fila);
        while (getline(is, fila)) {

            //¿Se ha leído una nueva fila?
            if (fila != "") {

                columnas.str(fila);

                //formato de fila: id;ident;tipo;nombre;latitud;longitud;continente;iso_pais

                getline(columnas, id, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, ident, ';');
                getline(columnas, tipo, ';');
                getline(columnas, nombre, ';');
                getline(columnas, latitud_str, ';');
                getline(columnas, longitud_str, ';');
                getline(columnas, continente, ';');
                getline(columnas, iso_pais, ';');

                //  Transformamos la latitud y longitud a float
                latitud = std::stof(latitud_str);
                longitud = std::stof(longitud_str);

                if (latitud > Ymx)
                    Ymx = latitud;
                if (latitud < Ymn)
                    Ymn = latitud;
                if (longitud > Xmx)
                    Xmx = longitud;
                if (longitud < Xmn)
                    Xmn = longitud;

                fila = "";
                columnas.clear();

                UTM uAux(longitud, latitud);

                addNuevoAeropuerto(id, ident, tipo, nombre, uAux, continente, iso_pais);
            }
        }
        is.close();
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }

    std::string _id = "";
    std::string _icao = "";
    std::string _nombre = "";
    std::string _pais = "";
    std::string active = "";

    is.open(ach_Aerolineas); //carpeta de proyecto
    if (is.good()) {
        std::getline(is,fila);
        while (getline(is, fila)) {

            //¿Se ha leído una nueva fila?
            if (fila != "") {

                columnas.str(fila);

                //formato de fila: id;ident;tipo;nombre;latitud;longitud;continente;iso_pais

                getline(columnas, _id, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, _icao, ';');
                getline(columnas, _nombre, ';');
                getline(columnas, _pais, ';');
                getline(columnas, active, ';');

                unsigned int idEnt = std::stoi(_id);
                bool _act;

                if (active == "Y")
                    _act = true;
                else
                    _act = false;

                fila = "";
                columnas.clear();

                addNuevaAerolinea(idEnt,_icao,_nombre,_pais,_act);
            }
        }
        is.close();
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }

    std::string aLinea = "";
    std::string iataOrig = "";
    std::string iataDest = "";

    is.open(ach_Rutas); //carpeta de proyecto
    if (is.good()) {
        std::getline(is,fila);
        while (getline(is, fila)) {

            //¿Se ha leído una nueva fila?
            if (fila != "") {

                columnas.str(fila);

                //formato de fila: id;ident;tipo;nombre;latitud;longitud;continente;iso_pais

                getline(columnas, aLinea, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, iataOrig, ';');
                getline(columnas, iataDest, ';');

                fila = "";
                columnas.clear();

                addNuevaRuta(iataOrig, iataDest, aLinea);
            }
        }

        is.close();
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }

    cargarVuelos(ach_Vuelos);

    rellenaMalla();

    std::cout << "Tiempo lectura de VuelaFlight: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
}

/**
 * @brief Constructor de copia de la clase VuelaFlight
 * @param[in] copy Objeto de la clase VuelaFlight del que copiaremos los datos pertinentes al objeto "this"
 */
VuelaFlight::VuelaFlight(const VuelaFlight &copy): airportsID(copy.airportsID), routesOrig(copy.routesOrig),
                routesDest(copy.routesDest), airlines(copy.airlines),airportsUTM(copy.airportsUTM) {

}

/**
 * @brief Destructor de la clase VuelaFlight
 * @post Se llamarán automáticamente a los destructores correspondiente de las clases VDinamico y ListaEnlazada para borrar rutas y aeropuertos
 */
VuelaFlight::~VuelaFlight() {

}

/**
 * @brief Funcion que busca una ruta entre dos aeropuertos por su código iata
 * @param[in] iataOri Código iata (string) del aeropuerto de origen
 * @param[in] iataDest Código iata (string) del aeropuerto de destino
 * @return Devuelve una ruta cuyos aeropuertos de origen y destino coinciden con los códigos dados
 * @throw std::runtime_error En caso de que no se encuentre ninguna ruta coincidente
 */
Ruta VuelaFlight::buscarRutasOriDes(const std::string& iataOri, const std::string& iataDest) {
    std::multimap<std::string,Ruta*>::iterator i = routesDest.find(iataDest);
    while (i != routesDest.end() && i->first == iataDest){
        if (i->second->getOrigin()->getIata() == iataOri)
            return *(i->second);
        i++;
    }

    throw std::runtime_error("No se ha encontrado la ruta deseada: " + iataOri + " - " + iataDest + "\n");
}

/**
 * @brief Funcion que devuelve una lista enlazada de punteros a rutas con todas las que salen de un aeropuerto de origen dado
 * @param[in] iataOrig Código iata (string) del aeropuerto origen
 * @return Devuelve una lista enlazada de punteros a rutas
 */
std::list<Ruta*> VuelaFlight::buscarRutasOrigen(const std::string& iataOrig) {
    std::list<Ruta*> toRet;
    std::multimap<std::string,Ruta>::iterator it = routesOrig.find(iataOrig);
    while (it->first == iataOrig && it != routesOrig.end()){
        toRet.push_back(&(it->second));
        ++it;
    }

    return toRet;
}

/**
 * @brief Funcion que busca todos los aeropuertos de un país dado (iso)
 * @param[in] iso Código del país (string) que queremos encontrar
 * @return Devuelve un vector dinámico de punteros a aeropuertos
 */
std::vector<Aeropuerto*> VuelaFlight::buscarAeropuertoPais(const std::string& iso) {
    std::vector<Aeropuerto*> retIsoAp;
    for (auto i=airportsID.begin(); i != airportsID.end();++i){
        if (i->second.getIsoPais() == iso)
            retIsoAp.push_back(&(i->second));
    }

    return retIsoAp;
}

/**
 * @brief Funcion que añade una nueva ruta a la lista de rutas de VuelaFlight (routes)
 * @param[in] iataOrig Código iata (string) del aeropuerto de origen
 * @param[in] iataDest Código iata (string) del aeropuerto de destino
 * @param[in] aLinea Nombre de la aerolínea (string) para la nueva ruta
 * @post Primero se buscarán los aeropuertos para añadirlos junto con la aerolínea y crear una nueva ruta
 * @post Se buscará la aerolinea. Si se encuentra, se añadirá a la ruta para insertarla.
 * @post También se añadirá esta ruta a la serie de rutas de la aerolinea a la que pertenece (la que hemos creado)
 */
void VuelaFlight::addNuevaRuta(const std::string& iataOrig, const std::string &iataDest, const std::string& aLinea) {
    std::unordered_map<std::string,Aeropuerto>::iterator ori = airportsID.find(iataOrig);

    std::unordered_map<std::string,Aeropuerto>::iterator dest = airportsID.find(iataDest);

    std::map<std::string,Aerolinea>::iterator air = airlines.find(aLinea);

    if (ori != airportsID.end() && dest != airportsID.end()  && air != airlines.end()) {
        Ruta inserta(aLinea, &ori->second, &dest->second, &air->second);
        Ruta *r = &routesOrig.insert(std::make_pair(iataOrig,inserta))->second;
        routesDest.insert(std::make_pair(iataDest,r));

        air->second.linkAerolRuta(r);
    } else{
        throw std::invalid_argument("Error : Ruta no insertada, algunos de los datos no es correcto");
    }
}

/**
 * @brief Funcion que añade un nuevo aeropuerto a un objeto de VuelaFlight
 * @param[in] id Id del aeropuerto
 * @param[in] ident Identificador del aeropuerto
 * @param[in] tipo Tipo de aeropuerto
 * @param[in] nombre Nombre del aeropuerto
 * @param[in] posicion Posicion geográfica del aeropuerto (en formato UTM)
 * @param[in] continente Continenete en el que se encuentra
 * @param[in] iso_pais Código iso del país perteneciente
 */
void VuelaFlight::addNuevoAeropuerto(const std::string &id, const std::string &iata,const std::string &tipo,
                                     const std::string &nombre, const UTM &posicion, const std::string &continente,
                                     const std::string &iso_pais) {
    Aeropuerto insAero(id, iata, tipo,nombre, posicion, continente, iso_pais);

    airportsID.insert(std::make_pair(iata,insAero));
}

/**
 * @brief Funcion para añadir una nueva Aerolinea a un objeto de VuelaFlight
 * @param[in] _id Identificador de la aerolinea
 * @param[in] _icao Código icao para la aerolinea
 * @param[in] _nombre Nombre de la aerolinea
 * @param[in] _pais País donde trabaja la aerolinea
 * @param[in] active Atributo que indica si la aerolinea esta activa o no
 */
void VuelaFlight::addNuevaAerolinea(unsigned int _id, const std::string &_icao, const std::string &_nombre,
                                    const std::string &_pais, bool active) {
    Aerolinea insAerLinea(_id,_icao,_nombre,_pais,active);

    airlines.insert(std::make_pair(_icao, insAerLinea));
}

/**
 * @brief Funcion que busca una Aerolinea dado su código icao
 * @param[in] _icao Código icao para buscar la Aerolinea
 * @return Devuelve un puntero a la Aerolinea o nullptr si no lo ha encontrado
 */
Aerolinea* VuelaFlight::buscarAerolinea(const std::string &_icao) {
    auto i = airlines.find(_icao);
    if (i != airlines.end())
        return &(i->second);
    return nullptr;
}

/**
 * @brief Funcion que busca todas las aerolineas activas de un objeto de VuelaFlight
 * @return Devuelve un vector de punteros a Aerolineas (las que están activas)
 */
std::vector<Aerolinea *> VuelaFlight::buscaAerolineasActivas() {
    std::vector<Aerolinea*> retAerolin;
    std::map<std::string,Aerolinea>::iterator rec;

    for (rec = airlines.begin(); rec != airlines.end(); ++rec){
        if (rec->second.isActivo())
            retAerolin.push_back(&(rec->second));
    }

    return retAerolin;
}

/**
 * @brief Funcion que devuelve las aerolineas de un pais dado
 * @param[in] idPais Código del país solicitado
 * @return Devuelve un vector de puntero a Aerolineas con la información deseada
 */
std::vector<Aerolinea *> VuelaFlight::getAerolineasPais(const std::string &idPais) {
    std::vector<Aerolinea*> retAerolineas;
    std::map<std::string,Aerolinea>::iterator i;

    for (i = airlines.begin() ; i != airlines.end(); ++i){
        if (i->second.getPais() == idPais)
            retAerolineas.push_back(&(i->second));
    }

    return retAerolineas;
}

/**
 * @brief Método que registra un vuelo en su correspondiente aerolínea
 * @param[in] fNum Número identificador de vuelo
 * @param[in] iataOri Código iata del aeropuerto origen
 * @param[in] iataDes Código iata del aeropuerto destino
 * @param[in] _pln Modelo de avión
 * @param[in] d_meteo Datos meteorológicos de ese vuelo
 * @param[in] f Fecha del vuelo
 * @return Devuelve un bool indicando si se realizó la inserción o no
 */
bool VuelaFlight::registrarVuelo(const std::string &fNum, const std::string &iataOri, const std::string &iataDes,
                                 const std::string &_pln, const std::string &d_meteo, Fecha f) {
    std::string comprueba = fNum.substr(0,3);
    std::map<std::string,Aerolinea>::iterator check = airlines.lower_bound(comprueba);

    std::unordered_map<std::string,Aeropuerto>::iterator ori = airportsID.find(iataOri);

    std::unordered_map<std::string,Aeropuerto>::iterator des = airportsID.find(iataDes);

    if (check != airlines.end() && des != airportsID.end() && ori != airportsID.end()
        && check->second.getIcao() == comprueba){

        Vuelo insVuelo(fNum, _pln, d_meteo, f, &check->second, &(ori->second), &(des->second));
        check->second.addVuelo(insVuelo);
        return true;
    }
    return false;
}

/**
 * @brief Método que carga todos los vuelos dado un fichero con información
 * @param[in] achVuelos Fichero que contiene la información de los vuelos
 */
void VuelaFlight::cargarVuelos(const std::string &achVuelos) {

    std::ifstream is;
    std::stringstream columnas;
    std::string fila;

    std::string fNum = "";
    std::string iataOri = "";
    std::string iataDest = "";
    std::string plane = "";
    std::string datosMeteo = "";
    std::string fecha = "";

    is.open(achVuelos); //carpeta de proyecto
    if (is.good()) {
        std::getline(is,fila);
        while (getline(is, fila)) {

            //¿Se ha leído una nueva fila?
            if (fila != "") {

                columnas.str(fila);

                getline(columnas, fNum, ';');
                getline(columnas, iataOri, ';');
                getline(columnas, iataDest, ';');
                getline(columnas, plane, ';');
                getline(columnas, datosMeteo, ';');
                getline(columnas, fecha, ';');


                fila = "";
                columnas.clear();

                //Pasamos la fecha a formato Fecha
                unsigned int _dia = std::stoi(fecha.substr(0,2));
                unsigned int _mes = std::stoi(fecha.substr(3,2));
                unsigned int _anio = std::stoi(fecha.substr(6,4));

                Fecha fAux (_dia,_mes,_anio);

                registrarVuelo(fNum,iataOri,iataDest,plane,datosMeteo,fAux);
            }
        }
        is.close();
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }
}

/**
 * @brief Función que busca todos los vuelos dado su flight number
 * @param[in] numberFl Número identificador de un vuelo
 * @return Devuelve un vector de punteros de Vuelos con todos los vuelos identificados
 */
std::vector<Vuelo *> VuelaFlight::buscaVuelos(const std::string &numberFl) {
    std::string auxIcao = numberFl.substr(0, 3);
    std::map<std::string,Aerolinea>::iterator air = airlines.lower_bound(auxIcao);
    std::vector<Vuelo*> retVuelosNumFl;
    if (air != airlines.end() && air->second.getIcao() == auxIcao){
        retVuelosNumFl = air->second.getVuelos(numberFl);
    }

    return retVuelosNumFl;
}

/**
 * @brief Función que devuelve los vuelos operados por una aerolinea e una fecha concreta
 * @param[in] icAerol Icao de la aerolinea
 * @param[in] fOperacion Fecha de la operación/vuelo
 * @return Devuelve un vector de punteros a Vuelos con la información deseada
 */
std::vector<Vuelo *> VuelaFlight::vuelosOperadosPor(const std::string &icAerol, Fecha &fOperacion) {
    std::map<std::string,Aerolinea>::iterator itBusca = airlines.lower_bound(icAerol);
    std::vector<Vuelo*> retVuelosFecha;
    if (itBusca != airlines.end() && itBusca->second.getIcao() == icAerol){
        retVuelosFecha = itBusca->second.getVuelos(fOperacion, fOperacion);
    }

    return retVuelosFecha;
}

/**
 * @brief Función que busca los vuelos que viene de un pais dado (origen) y va hacia (destino) un Aeropuerto con un iata dado
 * @param[in] iso_paisOri Código iso del pais de origen
 * @param[in] iataDest Código iata del Aeropuerto de destino
 * @return Devuelve un set de string con los flight number (únicos) deseados
 */
std::set<std::string> VuelaFlight::buscaVuelosDestAerop(const std::string &iso_paisOri, const std::string &iataDest) {
    std::multimap<std::string,Ruta>::iterator rut = routesOrig.begin();
    std::set<std::string> retSet;
    while (rut != routesOrig.end()){
        if (rut->second.getOrigin()->getIsoPais() == iso_paisOri){
            std::list<Vuelo*> vuelosRuta = rut->second.getVuelos();
            std::list<Vuelo*>::iterator itVuelos;
            for (itVuelos = vuelosRuta.begin(); itVuelos != vuelosRuta.end(); ++itVuelos){
                if ((*itVuelos)->getApDestiny()->getIata() == iataDest){
                    retSet.insert((*itVuelos)->getFlightNum());
                }
            }
        }
        rut++;
    }

    return retSet;
}

/**
 * @brief @brief Funcion que busca todos los Aeropuertos en los que opera una aerolinea
 * @param[in] ic_Aero Código icao de la aerolinea
 * @return Devuelve un set con todos los Aeropuertos (punteros a Aeropuertos)
 */
std::set<Aeropuerto *> VuelaFlight::buscaAeropuertosAerolinea(const std::string &ic_Aero) {
    std::set<Aeropuerto*> retSet;
    std::map<std::string,Aerolinea>::iterator aLine = airlines.lower_bound(ic_Aero);
    if (aLine != airlines.end() && aLine->second.getIcao() == ic_Aero){
        std::deque<Vuelo*> flightsAerol = aLine->second.getFlightsAerolinea();
        for (auto & i : flightsAerol){
            retSet.insert(i->getApOrigin());
            retSet.insert(i->getApDestiny());
        }
    }

    return retSet;
}

/**
 * @brief Funcion que busca un Aeropuerto en una tabla hash dado su código iata
 * @param[in] iataAp Código iata identificador del aeropuerto
 * @return Devuelve un puntero al aeropuerto o nullptr si no lo encontró
 */
Aeropuerto *VuelaFlight::buscarAeropuerto(const std::string &iataAp) {
    std::unordered_map<std::string,Aeropuerto>::iterator ori = airportsID.find(iataAp);
    if (ori != airportsID.end())
        return &(ori->second);
    return nullptr;
}

/**
 * @brief Funcion que devuelve el numero de aeropuertos de la tabla hash
 * @return Devuelve el numero de aeropuertos actual
 */
unsigned int VuelaFlight::getNumAeropuertos() const {
    return airportsID.size();
}

/**
 * @brief Funcion que elimina un aeropuerto dado su iata (y toda la informacion relacionada con él)
 * @param[in] iataAp Código iata del aeropuerto a borrar
 */
void VuelaFlight::eliminarAeropuerto(const std::string &iataAp) {
    std::map<std::string,Aerolinea>::iterator airl = airlines.begin();
    do{
        if (airl != airlines.end()){
            airl->second.bajaAeropuerto(iataAp);
        }
        airl++;
    } while (airl != airlines.end());

    std::multimap<std::string,Ruta*>::iterator rDes = routesDest.find(iataAp);
    while (rDes != routesDest.end() && rDes->second->getDestiny()->getIata() == iataAp){
        routesDest.erase(rDes);
        rDes++;
    }

    std::multimap<std::string,Ruta>::iterator rOri = routesOrig.find(iataAp);
    while (rOri != routesOrig.end() && rOri->second.getOrigin()->getIata() == iataAp){
        routesOrig.erase(rOri);
        rOri++;
    }

    if (! airportsID.erase(iataAp))
        throw std::invalid_argument("El iata " + iataAp + " no "
                                                          "ha sido encontrado y no se podrá borrar el aeropuerto");
}

/**
 * @brief Funcion que elimina todos los aeropuertos inactivos
 * @note Los aeropuertos estarán inactivos si no hay niguna ruta que tenga dicho aeropuerto(iata)
 * @note No se eliminará la información relacionada puesto que previamente hemos visto que no hay NINGUNA ruta asociada al aeropuerto
 */
void VuelaFlight::eliminarAeropuertosInactivos() {
    std::vector<Aeropuerto*> allAp = getAeropuertos();
    for (int i=0;i<allAp.size();++i) {
        std::multimap<std::string, Ruta>::iterator itOrig = routesOrig.find(allAp[i]->getIata());
        if (itOrig == routesOrig.end()){
            std::multimap<std::string, Ruta*>::iterator itDest = routesDest.find(allAp[i]->getIata());
            if (itDest == routesDest.end()){
                airportsID.erase(allAp[i]->getIata());
            }
        }
    }
}

/**
 * @brief Funcion que muestra el estado actual de la tabla hash
 */
void VuelaFlight::mostrarEstadoTabla() {
    std::cout << "***** DATOS TABLA HASH *****" << std::endl;
    std::cout << "Factor de carga : " << airportsID.load_factor() << std::endl
              << "Elementos en la tabla : " << airportsID.size() << std::endl;
}

/**
 * @brief Funcion que devuelve todos los aeropuertos registrados en la aplicación
 * @return Devuelve un vector de punteros a Aeropuertos
 */
std::vector<Aeropuerto*> VuelaFlight::getAeropuertos() {
    std::unordered_map<std::string,Aeropuerto>::iterator it = airportsID.begin();
    std::vector<Aeropuerto*> retAp;
    while (it != airportsID.end()){
        retAp.push_back(&it->second);
        it++;
    }

    return retAp;
}

/**
 * @brief Función que carga los datos de los Aeropuertos en la MallaRegular (airportsUTM)
 */
void VuelaFlight::rellenaMalla() {
    //Hacemos ceil y floor para que cuando llegue a las coordenadas maximas y minimas no se salga de la malla
    airportsUTM = MallaRegular<Aeropuerto*> (std::floor(Xmn),std::floor(Ymn),
                                            std::ceil(Xmx),std::ceil(Ymx),77);
    std::unordered_map<std::string,Aeropuerto>::iterator map = airportsID.begin();
    while (map != airportsID.end()){
        airportsUTM.insert(map->second.getX(),map->second.getY(),&map->second);
        map++;
    }
}

/**
 * @brief Funcion que busca todos los aeropuertos en un radio dado
 * @param[in] pos Posición UTM (x,y) desde la que se buscará
 * @param[in] radioKm Radio de búsqueda
 * @return Devuelve un vector de punteros a Aeropuertos
 */
std::vector<Aeropuerto *> VuelaFlight::buscarApRadio(const UTM &pos, float radioKm) {
    std::vector<Aeropuerto*> apRadio = airportsUTM.buscarRadio(pos.getLongitud(),pos.getLatitud(),radioKm);
    return apRadio;
}

/**
 * @brief Función que devuelve los 5 aeropuertos con más vuelos de salida dado un radio
 * @param[in] pos Posición inicial
 * @param[in] radioKm Radio de búsqueda
 * @return Devuelve un vector de punteros a Aeropuertos
 */
std::vector<Aeropuerto *> VuelaFlight::apMasSalidas(const UTM &pos, float radioKm) {
    std::vector<Aeropuerto*> apRadio = buscarApRadio(pos,radioKm);

    class Mas {
    public:
        bool operator()( const std::pair<int,Aeropuerto*>& a, const std::pair<int,Aeropuerto*>& b){
            if (a.first < b.first)
                return true;
            return false;
        }
    };

    std::priority_queue<std::pair<int,Aeropuerto*>,std::deque<std::pair<int,Aeropuerto*> >,Mas > queue;

    for (int i=0;i<apRadio.size();++i){
        unsigned vuelos = getNumVuelosSalidaAp(apRadio[i]->getIata());
        queue.push(std::make_pair(vuelos,apRadio[i]));
    }

    std::vector<Aeropuerto*> masAp5;

    for (int i=0;i<5;++i){
        masAp5.push_back(queue.top().second);
        queue.pop();
    }

    return masAp5;
}

/**
 * @brief Funcion que devuelve el número de vuelos de salida dado su iata
 * @param[in] iata Código iata para la búsqueda
 * @return Devuelve el número de vuelos de salida de un aeropuerto
 */
unsigned int VuelaFlight::getNumVuelosSalidaAp(const std::string &iata) {
    std::multimap<std::string,Ruta>::iterator rut = routesOrig.find(iata);
    unsigned int numVuelos = 0;

    while (rut != routesOrig.end() && rut->first == iata){
        numVuelos += rut->second.getNumVuelos();
        rut++;
    }

    return numVuelos;
}

/**
 * @brief Funcion que muestra por pantalla los datos de rendimiento de la MallaRegular
 */
void VuelaFlight::datosMalla() {
    std::cout << "***** DATOS DE LA MALLA *****" << std::endl;
    std::cout << "Tamano : " << airportsUTM.getSize() << std::endl;
    std::cout << "Promedio de elementos por casilla: " << airportsUTM.promedioElemCelda() << std::endl;
    std::cout << "Maximo de elementos en una casilla: " << airportsUTM.maxElemCelda() << std::endl;
}