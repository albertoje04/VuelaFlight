//
// Created by alber on 09/12/2023.
//

#ifndef PRACTICA_6_EEDD_RUTA_H
#define PRACTICA_6_EEDD_RUTA_H

#include "Vuelo.h"
#include "Aerolinea.h"

class Ruta {
private:
    std::string aerolinea = "";
    Aeropuerto* origin = nullptr;
    Aeropuerto* destiny = nullptr;
    Aerolinea* company = nullptr;
    std::list<Vuelo*> flightRoutes;
public:
    Ruta () : flightRoutes() { }

    Ruta(const std::string& _alinea, Aeropuerto* o, Aeropuerto* d, Aerolinea* c);

    Ruta(const Ruta& copy);

    Ruta& operator=(const Ruta& other);

    const std::string &getAerolinea() const;

    void setAerolinea(const std::string &aerolinea);

    void setOrigin(Aeropuerto* source);
    Aeropuerto* getOrigin() const;

    void setDestiny (Aeropuerto* dest);
    Aeropuerto* getDestiny() const;

    void setCompany(Aerolinea* _comp);
    Aerolinea* getCompany() const;

    bool addVuelo(Vuelo *v);
    int getNumVuelos() const;

    std::list<Vuelo*> getVuelos();
};


#endif //PRACTICA_6_EEDD_RUTA_H
