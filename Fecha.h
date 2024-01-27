//
// Created by alber on 09/12/2023.
//

#ifndef PRACTICA_6_EEDD_FECHA_H
#define PRACTICA_6_EEDD_FECHA_H

/**
@author Antonio J. Rueda
*/

#include <string>

/** @brief Excepci�n que representa fechas incorrectas */
class ErrorFechaIncorrecta {};

/** @brief Clases sencilla para representar fechas y horas */
class Fecha {
    /** Fecha y hora */
    unsigned dia, mes, anio, hora, min;
    /** Dias por mes */
    static const unsigned diasMes[12];

    /** Comprobaci�n de validez de una fecha */
    void comprobarFecha(unsigned aDia, unsigned aMes, unsigned aAnio, unsigned aHora, unsigned aMin) const;
    /** Funci�n auxiliar de conversi�n desde estructura de tiempo tm de time.h */
    void leerTiempo(const tm &t);
    /** Funci�n	auxiliar de conversi�n a estructura de tiempo tm de time.h */
    void escribirTiempo(tm &t);

public:
    /** Crea una fecha con la hora actual */
    Fecha();
    /** Crea una fecha concreta. Devuelve una excepci�n ErrorFechaIncorrecta si la fecha introducida no es correcta */
    Fecha(unsigned aDia, unsigned aMes, unsigned aAnio, unsigned aHora = 0, unsigned aMin = 0);
    /** Constructor copia */
    Fecha(const Fecha &f) :
            dia(f.dia), mes(f.mes), anio(f.anio), hora(f.hora), min(f.min) {}

    /** Asignar un nuevo d�a */
    void asignarDia(unsigned aDia, unsigned aMes, unsigned aAnio);
    /** Asignar una nueva hora */
    void asignarHora(unsigned aHora, unsigned aMin);

    /** Obtener hora */
    unsigned verHora() const { return hora; }
    /** Obtener minutos */
    unsigned verMin() const { return min; }
    /** Obtener dia */
    unsigned verDia() const { return dia; }
    /** Obtener mes */
    unsigned verMes() const { return mes; }
    /** Obtener a�o */
    unsigned verAnio() const { return anio; }

    /** Obtener una cadena con el d�a */
    std::string cadenaDia() const;
    /** Obtener una cadena con la hora */
    std::string cadenaHora() const;
    /** Obtener una cadena con d�a y hora */
    std::string cadena() const {
        return cadenaDia() + " " + cadenaHora();
    }

    /** Indica si las dos fechas tienen el mismo d�a */
    bool mismoDia(const Fecha &f) const {
        return dia == f.dia && mes == f.mes && anio == f.anio;
    }
    /** Comparar fechas */
    bool operator<(const Fecha &f) const;
    /** Asignar fechas */
    Fecha &operator=(const Fecha &f);

    /** A�adir un n�mero de minutos indicado */
    void anadirMin(int numMin);
    /** A�adir un n�mero de horas indicado*/
    void anadirHoras(int numHoras);
    /** A�adir un n�mero de d�as indicado */
    void anadirDias(int numDias);
    /** A�adir un n�mero de meses indicado */
    void anadirMeses(int numMeses);
    /** A�adir un n�mero de a�os indicado */
    void anadirAnios(int numAnios);

    ~Fecha();
};

/** Serializaci�n de fechas: salida */
std::ostream &operator<<(std::ostream &os, const Fecha &f);


#endif //PRACTICA_6_EEDD_FECHA_H
