/**
 * @file Skaiciavimai.cpp
 * @brief Skaiciavimai DLL funkcijų realizacija.
 */

#include "Skaiciavimai.h"

double skaiciuotiGalutiniBala(double ndRez, double egzaminas) {
    // Ta pati formulė, kurią iki šiol naudojai galBalas()
    return 0.4 * ndRez + 0.6 * egzaminas;
}
