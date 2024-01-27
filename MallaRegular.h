//
// Created by alber on 09/12/2023.
//

#ifndef PRACTICA_6_EEDD_MALLAREGULAR_H
#define PRACTICA_6_EEDD_MALLAREGULAR_H

#include <list>
#include <vector>
#include <cmath>

template<typename T>
class MallaRegular;

template<typename T>
class Caja {
    std::list<T> dots;
public:
    friend class MallaRegular<T>;
    Caja(): dots() { }
    void insert (const T& elemIns) { dots.push_back(elemIns); }

    T* find (const T& elemBq){
        typename std::list<T>::iterator bq = dots.begin();
        while (bq != dots.end()){
            if (*bq == elemBq)
                return &(*bq);
        }
        return nullptr;
    }
    bool erase (const T& elemDel){
        typename std::list<T>::iterator del = dots.begin();
        while (del != dots.end()) {
            if (*del == elemDel){
                dots.erase(del);
                return true;
            }
        }
        return false;
    }
};

template<typename T>
class MallaRegular{
private:

    float xMin, yMin, xMax, yMax;
    float sizeCajaX, sizeCajaY;
    unsigned int size = 0;
    int nDiv; //También podríamos calcular las divisiones de la matriz con matrix.size()
    unsigned int maxElem = 0;

    std::vector<std::vector<Caja<T> > >  matrix;

    Caja<T> *obtenerCasilla(float posX, float posY);
    float distanceFrom (float longi1, float lat1, float longi2, float lat2);

public:
    MallaRegular();
    MallaRegular(float _XMin, float _YMin, float _XMax, float _YMax, int
    _nDiv);
    MallaRegular(const MallaRegular<T>& copy);

    unsigned int getSize() const { return size; }

    void insert (float x, float y, const T& elemIns);
    T* find (float x, float y, const T& elemBq);
    bool erase (float x, float y, const T& elemDel);

    std::vector<T> buscarRadio (float x,float y, float radio);
    unsigned int maxElemCelda();
    float promedioElemCelda();

};

/**
 * @brief Constructor por defecto de la malla
 */
template<typename T>
MallaRegular<T>::MallaRegular() {

}

/**
 * @brief Constructor parametrizado de la MallaRegular
 * @param[in] XMin Longitud minima
 * @param[in] YMin Latitud minima
 * @param[in] XMax Longitud maxima
 * @param[in] YMax Latitud maxima
 * @param[in] _nDiv Número de divisiones (dimensiones) de la malla
 */
template<typename T>
MallaRegular<T>::MallaRegular(float _XMin, float _YMin, float _XMax, float _YMax, int
_nDiv):
    xMin(_XMin),xMax(_XMax), yMin(_YMin), yMax(_YMax), nDiv(_nDiv), size(0) {
    sizeCajaX = (xMax - xMin) / _nDiv;
    sizeCajaY = (yMax - yMin) / _nDiv;
    matrix.insert(matrix.begin(),_nDiv,std::vector<Caja<T> > (_nDiv));
}

/**
 * @brief Constructor copia de la MallaRegular
 * @param[in] copy Objeto copiado de tipo MallaRegular
 */
template<typename T>
MallaRegular<T>::MallaRegular(const MallaRegular<T>& copy): xMax(copy.xMax),xMin(copy.xMin),
    yMax(copy.yMax),yMin(copy.yMin), nDiv(copy.nDiv),matrix(copy.matrix), size(copy.size) {

}

/**
 * @brief Funcion para obtener una casilla dadas sus coordenadas
 * @param[in] posX Posición x (longitud)
 * @param[in] posY Posición y (latitud)
 * @return Devuelve un puntero la casilla (Caja)
 */
template<typename T>
Caja<T> *MallaRegular<T>::obtenerCasilla(float posX, float posY) {
    int x = (posX - xMin) / sizeCajaX;
    int y = (posY - yMin) / sizeCajaY;
    return &(matrix[x][y]);
}

/**
 * @brief Función que calcula la distancia en km entre dos puntos de la tierra
 * @param[in] longi1 Longitud del primer punto
 * @param[in] lat1 Latitud del primer punto
 * @param[in] longi2 Longitud del segundo punto
 * @param[in] lat2 Latitud del segundo punto
 * @return Devuelve la distancia (float) entre los dos puntos
 */
template<typename T>
float MallaRegular<T>::distanceFrom(float longi1, float lat1, float longi2, float lat2) {
    float tierra = 6378.0;

    float incrLat = (lat2 - lat1)*(M_PI/180);
    float incrLongi = (longi2 - longi1)*(M_PI/180);

    float a = pow(sin(incrLat/2),2) +
            (cos(lat1*(M_PI/180)) * cos(lat2*(M_PI/180)) * pow(sin(incrLongi/2),2));
    float c = 2 * atan2(sqrt(a), sqrt(1-a));

    float d = tierra * c;

    return d;
}

/**
 * @brief Función para insertar un elemento en la malla
 * @param[in] x Coordenada x (longitud)
 * @param[in] y Coordenada y (latitud)
 * @param[in] elemIns Elemento a insertar
 */
template<typename T>
void MallaRegular<T>::insert(float x, float y,const T &elemIns) {
    if (x <= xMax && x >= xMin && y <= yMax && y >= yMin) {
        Caja<T> *box = obtenerCasilla(x, y);
        box->insert(elemIns);
        size++;

        if (box->dots.size() > maxElem)
            maxElem = box->dots.size();
    }
}

/**
 * @brief Function que busca y devuelve un elemento de la malla
 * @param[in] x Coordenada x (longitud)
 * @param[in] y Coordenada y (latitud)
 * @param[in] elemBq Elemento a buscar
 * @return Devuelve un puntero al elemento encontrado (o nullptr)
 */
template<typename T>
T* MallaRegular<T>::find(float x, float y, const T &elemBq) {
    Caja<T>* box = obtenerCasilla(x,y);
    return box->find(elemBq);
}

/**
 * @brief Funcion para eliminar un elemento de la malla
 * @param[in] x Coordenada x (longitud)
 * @param[in] y Coordenada y (latitud)
 * @param[in] elemDel Elemento a borrar
 * @return Devuelve un bool indicando si se pudo borrar o no (si se encontró o no)
 */
template<typename T>
bool MallaRegular<T>::erase(float x, float y, const T &elemDel) {
    Caja<T>* box = obtenerCasilla(x,y);
    return box->erase(elemDel);
    size--;
}

/**
 * @brief Función que busca todos los elementos de la malla en un radio dado desde un punto dado
 * @param[in] x Coordenada x (longitud)
 * @param[in] y Coordenada y (latitud)
 * @param[in] radio Radio de búsqueda
 * @return Devuelve un vector de objetos de tipo T con los elementos que están dentro del radio
 */
template<typename T>
std::vector<T> MallaRegular<T>::buscarRadio(float x, float y, float radio) {
    std::vector<T> retApRadio;

    float lMin = x - (radio/111.1), lMax = x + (radio/111.1);
    float latMin = y - (radio/111.1), latMax = y + (radio/111.1);

    for (float i=lMin; i <= lMax ; i+=sizeCajaX){
        for (float j=latMin; j <= latMax; j+=sizeCajaY){
            if (j <= yMax && i <= xMax && j >= yMin && i >= xMin){
                Caja<T>* c = obtenerCasilla(i,j);
                if(c->dots.size() != 0) {
                    typename std::list<T>::iterator box = c->dots.begin();
                    while (box != c->dots.end()) {
                        float distance = distanceFrom(x, y, (*box)->getX(), (*box)->getY());
                        if (distance <= radio)
                            retApRadio.push_back((*box));
                        box++;
                    }
                }
            }
        }
    }

    return retApRadio;
}

/**
 * @brief Funcion que devuelve el máximo de elementos en una celda
 * @return Devuelve el numero maximo de elementos entre todas las celdas de la malla
 */
template<typename T>
unsigned int MallaRegular<T>::maxElemCelda() {
    return maxElem;
}

/**
 * @brief Funcion que devuelve la media aritmética de elementos de todas las celdas
 * @return Devuelve un float, que es el promedio de elementos
 */
template<typename T>
float MallaRegular<T>::promedioElemCelda() {
    return (float)size / (nDiv*nDiv);
}

#endif //PRACTICA_6_EEDD_MALLAREGULAR_H
