#include <iostream>
#include "VuelaFlight.h"

/**
 * @author Alberto Jiménez Expósito - aje00009@red.ujaen.es
 * @date 14/12/23
 */

//Tenemos que tener la siguiente función para calcular el ap más cercano a Jaén en km
float main_distanceFrom(float longi1, float lat1, float longi2, float lat2) {
    float tierra = 6378.0;

    float incrLat = (lat2 - lat1)*(M_PI/180);
    float incrLongi = (longi2 - longi1)*(M_PI/180);

    float a = pow(sin(incrLat/2),2) +
              (cos(lat1*(M_PI/180)) * cos(lat2*(M_PI/180)) * pow(sin(incrLongi/2),2));
    float c = 2 * atan2(sqrt(a), sqrt(1-a));

    float d = tierra * c;

    return d;
}

int main() {
    //1
    VuelaFlight app("../aeropuertos_v3.csv","../rutas_v1.csv",
                  "../aerolineas_v1.csv","../infovuelos_v1.csv");
    app.datosMalla();

    //2
    std::cout << "============================================================" << std::endl;
    std::cout << "***** AEROPUERTOS A 300KM A JAEN *****" << std::endl;
    UTM jaen (-3.7902800,37.7692200);
    std::vector<Aeropuerto*> apJaen = app.buscarApRadio(jaen,300);

    if (apJaen.size() > 0) {
        Aeropuerto *masCercano;
        float menorDist = main_distanceFrom(jaen.getLongitud(),jaen.getLatitud(),
                                           apJaen[0]->getX(),apJaen[0]->getY());
        for (int i = 0; i < apJaen.size(); ++i) {
            std::cout << apJaen[i]->getId() << " - " <<
                      apJaen[i]->getIata() << " - " << apJaen[i]->getNombre() <<
                      " - " << apJaen[i]->getTipo() << apJaen[i]->getContinente() << apJaen[i]->getIsoPais()
                      << " (" << apJaen[i]->getX() << "," << apJaen[i]->getY() << ")" << std::endl;

            float distJaen = main_distanceFrom(jaen.getLongitud(),jaen.getLatitud(),
                                               apJaen[i]->getX(),apJaen[i]->getY());

            if (distJaen < menorDist){
                menorDist = distJaen;
                masCercano = apJaen[i];
            }
        }

        std::cout << "Se han encontrado " << apJaen.size() << " aeropuertos a 300km de Jaen" << std::endl;

        std::cout << "El aeropuerto más cercano es: " <<
        masCercano->getNombre()  << " a " << menorDist << " km" << std::endl;
    }

    std::cout << "============================================================" << std::endl;

    //3
    std::cout << "***** LOS 5 AEROPUERTOS CON MAS VUELOS A 800KM DE MADRID *****" << std::endl;

    UTM m(-3.689976,40.427285);
    std::vector<Aeropuerto*> madrid800km = app.apMasSalidas(m,800);
    std::vector<Aeropuerto*>::iterator mad = madrid800km.begin();
    while (mad != madrid800km.end()){
        std::cout << (*mad)->getId() << " - " << (*mad)->getIata() << " - " <<
        (*mad)->getNombre() << " - " << (*mad)->getTipo() << " - " <<
        (*mad)->getContinente() << " - " << (*mad)->getIsoPais() << " -----> " <<
        app.getNumVuelosSalidaAp((*mad)->getIata()) << " vuelos" << std::endl;
        mad++;
    }


    std::cout << "============================================================" << std::endl;

    //4
    std::cout << "***** ? VENECIA O LONDRES, QUIEN TIENE MAS AEROPUERTOS ? *****" << std::endl;

    UTM l(-0.282894,51.489659), v(12.227650,45.484189); //Coordenadas tomadas desde la página web
    std::vector<Aeropuerto*> apLondon = app.buscarApRadio(l,400);
    std::vector<Aeropuerto*> apVenezia = app.buscarApRadio(v,400);

    if (apLondon.size() > apVenezia.size())
        std::cout << "Londres(" << apLondon.size() <<
        " aeropuertos) tiene mas aeropuertos que Venecia(" << apVenezia.size() << " aeropuertos)" << std::endl;
    else {
        if (apVenezia.size() > apLondon.size())
            std::cout << "Venecia(" << apVenezia.size() <<
                      "aeropuertos) tiene mas aeropuertos que Londres(" << apLondon.size() << " aeropuertos)"
                      << std::endl;
        else
            std::cout << "Venecia y Londres tienen la"
                         " misma cantidad de aeropuertos(" << apVenezia.size() << ")" << std::endl;
    }

    std::cout << "============================================================" << std::endl;
}
