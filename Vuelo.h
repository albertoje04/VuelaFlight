//
// Created by alber on 09/12/2023.
//

#ifndef PRACTICA_6_EEDD_VUELO_H
#define PRACTICA_6_EEDD_VUELO_H

#include "Fecha.h"
#include "Aeropuerto.h"

class Aerolinea;

class Vuelo {
private:
    std::string flight_num = "";
    std::string plane = "";
    std::string datos_meteo = "";
    Fecha fecha;
    Aerolinea* linkAero = nullptr;
    Aeropuerto* apOrigin = nullptr;
    Aeropuerto* apDestiny = nullptr;
public:
    Vuelo();
    Vuelo(const std::string& fnum, const std::string& avion, const std::string dat_met, Fecha _f,
          Aerolinea* lAero = nullptr, Aeropuerto* ori = nullptr, Aeropuerto* dest = nullptr);
    Vuelo(const Vuelo& copy);
    Vuelo& operator=(const Vuelo& other);

    const std::string &getFlightNum() const;

    void setFlightNum(const std::string &flightNum);

    const std::string &getPlane() const;

    void setPlane(const std::string &plane);

    const std::string &getDatosMeteo() const;

    void setDatosMeteo(const std::string &datosMeteo);

    const Fecha &getFecha() const;

    void setFecha(const Fecha &fecha);

    Aerolinea *getLinkAero();

    void setLinkAero(Aerolinea *lnkAero);

    Aeropuerto *getApOrigin();

    void setApOrigin(Aeropuerto *apOrigin);

    Aeropuerto *getApDestiny();

    void setApDestiny(Aeropuerto *apDestiny);

};


#endif //PRACTICA_6_EEDD_VUELO_H
