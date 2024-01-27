//
// Created by alber on 09/12/2023.
//

#ifndef PRACTICA_6_EEDD_VUELAFLIGHT_H
#define PRACTICA_6_EEDD_VUELAFLIGHT_H


#include <fstream>
#include <string>
#include <sstream>
#include "Ruta.h"
#include <map>
#include "Aerolinea.h"
#include "MallaRegular.h"
#include <unordered_map>
#include <string>
#include <set>

class VuelaFlight {
private:
    std::multimap<std::string,Ruta> routesOrig;
    std::multimap<std::string,Ruta*> routesDest;
    std::unordered_map<std::string,Aeropuerto> airportsID;
    MallaRegular<Aeropuerto*> airportsUTM;
    std::map<std::string,Aerolinea> airlines;

    //atributos para guardar las dimensiones de la malla para cargarla despues
    float Xmx = -1000, Ymx = -1000, Xmn = 1000, Ymn = 1000;

    void cargarVuelos(const std::string& achVuelos);
    void rellenaMalla();
public:
    VuelaFlight(const std::string& ach_Aeropuertos, const std::string& ach_Rutas,
                const std::string& ach_Aerolineas, const std::string& ach_Vuelos);
    VuelaFlight(const VuelaFlight& copy);
    ~VuelaFlight();

    Ruta buscarRutasOriDes(const std::string& iataOri, const std::string& iataDest);

    std::list<Ruta*> buscarRutasOrigen (const std::string& iataOrig);

    std::vector<Aeropuerto*> buscarAeropuertoPais (const std::string& iso);

    void addNuevaRuta(const std::string &iataOrig, const std::string& iataDest, const std::string& aLinea);

    void addNuevoAeropuerto (const std::string& id,const std::string& iata,const std::string &tipo,const std::string& nombre,
                             const UTM& posicion, const std::string& continente, const std::string& iso_pais);

    void addNuevaAerolinea(unsigned int _id, const std::string& _icao, const std::string& _nombre,
                           const std::string& _pais, bool active);

    Aerolinea* buscarAerolinea(const std::string& _icao);

    std::vector<Aerolinea*> buscaAerolineasActivas();

    std::vector<Aerolinea*> getAerolineasPais(const std::string& idPais);

    bool registrarVuelo(const std::string& fNum, const std::string& iataOri, const std::string& iataDes,
                        const std::string& _pln, const std::string& d_meteo, Fecha f);

    std::vector<Vuelo*> buscaVuelos (const std::string& numberFl);

    std::vector<Vuelo*> vuelosOperadosPor (const std::string& icAerol, Fecha& fOperacion);

    std::set<std::string> buscaVuelosDestAerop (const std::string& iso_paisOri, const std::string& iataDest);

    std::set<Aeropuerto*> buscaAeropuertosAerolinea(const std::string& ic_Aero);

    Aeropuerto* buscarAeropuerto(const std::string& iataAp);

    unsigned int getNumAeropuertos() const;

    std::vector<Aeropuerto*> getAeropuertos();

    void eliminarAeropuerto(const std::string& iataAp);

    void eliminarAeropuertosInactivos();

    void mostrarEstadoTabla();

    void datosMalla(); //< Método auxiliar para visualizar si se han cargado los datos correctamente

    std::vector<Aeropuerto*> buscarApRadio(const UTM& pos, float radioKm);

    std::vector<Aeropuerto*> apMasSalidas(const UTM& pos, float radioKm);

    //Método auxiliar para comprobar el número de vuelos de un aeropuerto dado
    unsigned int getNumVuelosSalidaAp (const std::string& iata);
};


#endif //PRACTICA_6_EEDD_VUELAFLIGHT_H
