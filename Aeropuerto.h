//
// Created by alber on 09/12/2023.
//

#ifndef PRACTICA_6_EEDD_AEROPUERTO_H
#define PRACTICA_6_EEDD_AEROPUERTO_H


#include <iostream>
#include <string>
#include "UTM.h"

class Aeropuerto {
private:
    std::string id = "";
    std::string iata = "";
    std::string tipo = "";
    std::string nombre = "";
    UTM posicion;
    std::string continente = "";
    std::string iso_pais = "";
public:
    Aeropuerto();

    Aeropuerto(const std::string& id,const std::string& ident,std::string tipo,const std::string& nombre, const UTM& posicion,
               const std::string continente, const std::string& iso_pais);

    Aeropuerto(const Aeropuerto& orig);

    const std::string &getId() const;

    void setId(const std::string &id);

    const std::string &getIata() const;

    void setIata(const std::string &_iata);

    const std::string &getTipo() const;

    void setTipo(const std::string &tipo);

    const std::string &getNombre() const;

    void setNombre(const std::string &nombre);

    const std::string &getContinente() const;

    void setContinente(const std::string &continente);

    const std::string &getIsoPais() const;

    void setIsoPais(const std::string &isoPais);

    const float getY () const;
    const float getX () const;

    void setUTM (UTM u);

    bool operator==(const Aeropuerto& comp);
    bool operator<(const Aeropuerto& comp);
};


#endif //PRACTICA_6_EEDD_AEROPUERTO_H
