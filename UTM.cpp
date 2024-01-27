//
// Created by alber on 09/12/2023.
//

#include "UTM.h"

UTM::UTM(): longitud(0.0), latitud(0.0) {

}

UTM::UTM(float longi, float lati): latitud(lati), longitud(longi) {

}

UTM::UTM(const UTM &orig): latitud(orig.latitud), longitud(orig.longitud) {

}

const float UTM::getLatitud() const {
    return latitud;
}

const float UTM::getLongitud() const {
    return longitud;
}
