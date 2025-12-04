/**
 * @file Skaiciavimai.h
 * @brief Deklaruoja funkcijas, eksportuojamas iš Skaiciavimai DLL.
 */

#pragma once

#ifdef _WIN32
    #ifdef SKAICIAVIMAI_EXPORTS
        /// Kai kompiliuojame DLL projektą
        #define SKAICIAVIMAI_API __declspec(dllexport)
    #else
        /// Kai naudojame DLL iš programos
        #define SKAICIAVIMAI_API __declspec(dllimport)
    #endif
#else
    /// Ne Windows platformose tiesiog tuščia
    #define SKAICIAVIMAI_API
#endif

/**
 * @brief Apskaičiuoja galutinį balą iš ND rezultato ir egzamino.
 *
 * Formulė:
 *      0.4 * ndRez + 0.6 * egzaminas
 *
 * Ši funkcija bus kompiliuojama į DLL ir kviečiama iš pagrindinės programos.
 *
 * @param ndRez Namų darbų įvertinimo rezultatas (vidurkis ar mediana).
 * @param egzaminas Egzamino balas.
 * @return Galutinis balas.
 */
SKAICIAVIMAI_API double skaiciuotiGalutiniBala(double ndRez, double egzaminas);
