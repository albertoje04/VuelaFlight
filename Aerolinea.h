//
// Created by alber on 09/12/2023.
//

#ifndef PRACTICA_6_EEDD_AEROLINEA_H
#define PRACTICA_6_EEDD_AEROLINEA_H

#include <vector>
#include <list>
#include "Aeropuerto.h"
#include "Vuelo.h"
#include <deque>
#include <map>

class Ruta;

class Aerolinea {
private:
    unsigned int id = 0;
    std::string icao = "";
    std::string nombre = "";
    std::string pais = "";
    bool activo = false;
    std::deque<Ruta*> aeroroutes;
    std::multimap<std::string,Vuelo> flights;
public:
    Aerolinea();
    Aerolinea(unsigned int id, const std::string& icao, const std::string& nombre,
              const std::string& pais, bool activo);
    Aerolinea(const Aerolinea& copy);
    Aerolinea& operator=(const Aerolinea& other);
    unsigned int getId() const;

    void setId(unsigned int id);

    const std::string &getIcao() const;

    void setIcao(const std::string &icao);

    const std::string &getNombre() const;

    void setNombre(const std::string &nombre);

    const std::string &getPais() const;

    void setPais(const std::string &pais);

    bool isActivo() const;

    void setActivo(bool activo);

    std::vector<Aeropuerto*> getAeropuertosOrig();
    std::list<Ruta*> getRutasAeropuertos (const std::string& iataAeropuerto);
    void linkAerolRuta (Ruta *linkRuta);

    Vuelo* addVuelo (Vuelo& v);
    std::vector<Vuelo*> getVuelos (const std::string& find_Numfl);
    std::vector<Vuelo*> getVuelos (const Fecha &inicio, const Fecha &final);

    //Metodo auxiliar para obtener los vuelos y usarlos en buscaAeropuertosAerolinea
    std::deque<Vuelo*> getFlightsAerolinea();

    void bajaAeropuerto (const std::string& iataAp);


    bool operator<(const Aerolinea& comp);
    bool operator>(const Aerolinea& comp);
    bool operator==(const Aerolinea& comp);
};


#endif //PRACTICA_6_EEDD_AEROLINEA_H
