#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <chrono>

#include "Studentas.h"

void spausdintiStudentus(const std::vector<Studentas>& studentai);
void rusiavimas(std::vector<Studentas>& studentai);
StudentGroups suskirstytiStudentus(const std::vector<Studentas>& studentai);

void generuotiFaila(int nd_count, long long kiek);
std::vector<Studentas> nuskaitytiIsFailo(const std::string& failoPavadinimas);

void isvestiRezultatus(const std::vector<Studentas>& studentai, const std::string& failoPavadinimas);

void testavimas();
