//
// Created by alber on 09/12/2023.
//

#ifndef PRACTICA_6_EEDD_UTM_H
#define PRACTICA_6_EEDD_UTM_H

class UTM {
private:
    float latitud;
    float longitud;
public:
    UTM();
    UTM(float longi, float lati);
    UTM(const UTM& orig);

    const float getLatitud () const;
    const float getLongitud () const;
};


#endif //PRACTICA_6_EEDD_UTM_H
