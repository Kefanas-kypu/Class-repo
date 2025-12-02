/**
 * @file Funkcijos.h
 * @brief Pagalbinės funkcijos darbui su Studentas klase ir failais.
 */

#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <chrono>
#include "Studentas.h"

/**
 * @brief Atspausdina studentų lentelę į standartinį išvesties srautą.
 * @param studentai Studentų vektorius.
 */
void spausdintiStudentus(const std::vector<Studentas>& studentai);

/**
 * @brief Surūšiuoja studentus pagal pavardę.
 * @param studentai Studentų vektorius (modifikuojamas vietoje).
 */
void rusiavimas(std::vector<Studentas>& studentai);

/**
 * @brief Suskirsto studentus į kietiakius ir vargsiukus pagal galutinį balą.
 * @param studentai Pradinis studentų vektorius.
 * @return Struktūra su dviem grupėmis.
 */
StudentGroups suskirstytiStudentus(const std::vector<Studentas>& studentai);

/**
 * @brief Sugeneruoja atsitiktinių studentų failą.
 *
 * @param nd_count Kiek namų darbų pažymių turi kiekvienas studentas.
 * @param kiek Kiek studentų generuoti.
 */
void generuotiFaila(int nd_count, long long kiek);

/**
 * @brief Nuskaito studentus iš failo.
 *
 * @param failoPavadinimas Įvesties failo pavadinimas.
 * @return Nuskaitytų studentų vektorius (jei nepavyko – tuščias).
 */
std::vector<Studentas> nuskaitytiIsFailo(const std::string& failoPavadinimas);

/**
 * @brief Išveda studentų rezultatus į tekstinį failą.
 *
 * @param studentai Studentų vektorius.
 * @param failoPavadinimas Išvesties failo pavadinimas.
 */
void isvestiRezultatus(const std::vector<Studentas>& studentai, const std::string& failoPavadinimas);

/**
 * @brief Atlieka našumo testus su skirtingo dydžio failais.
 *
 * Spausdina nuskaitymo, rikiavimo, skirstymo ir išvedimo laikus.
 */
void testavimas();
