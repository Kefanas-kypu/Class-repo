#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include "Studentas.h"

void spausdintiStudentus(const std::vector<Studentas>& studentai);
void rusiavimas(std::vector<Studentas>& studentai);
StudentGroups suskirstytiStudentus(const std::vector<Studentas>& studentai);

void generuotiFaila(const std::string& failoPavadinimas, int kiek);
std::vector<Studentas> nuskaitytiIsFailo(const std::string& failoPavadinimas);

double skaiciuotiVidurki(const std::vector<int>& paz);
void isvestiRezultatus(const std::vector<Studentas>& studentai, const std::string& failoPavadinimas);

void testavimas(const std::string& failas);
