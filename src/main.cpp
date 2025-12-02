/**
 * @file main.cpp
 * @brief Pagrindinė programos įėjimo funkcija – naudotojo meniu ir programos valdymas.
 */

#include "Funkcijos.h"

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <sstream>

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::vector<Studentas> grupe;
    std::string fail;
    int pasirinkimas = 0;

    do {
        std::cout << "\nKa norite atlikti?" << std::endl;
        std::cout << "1. Ivesti nauja studenta" << std::endl;
        std::cout << "2. Atspausdinti rezultatus" << std::endl;
        std::cout << "3. Iseiti" << std::endl;
        std::cout << "4. Nuskaityti studentus is failo" << std::endl;
        std::cout << "5. Sugeneruoti atsitiktinius studentu failus" << std::endl;
        std::cout << "6. Padalinti studentus i grupes ir issaugoti i failus" << std::endl;
        std::cout << "7. Testuoti veikima su ivairaus dydzio failais" << std::endl;
        std::cout << "Pasirinkite veiksma: ";

        if (!(std::cin >> pasirinkimas)) {
            std::cout << "Neteisinga ivestis, bandykite dar karta." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (pasirinkimas) {

        case 1: {
            Studentas s;
            s.readStudent(std::cin);
            grupe.push_back(s);
            std::cout << "Studentas pridetas sekmingai!" << std::endl;
            break;
        }

        case 2: {
            if (grupe.empty()) {
                std::cout << "Nera studentu duomenu!" << std::endl;
                break;
            }
            rusiavimas(grupe);
            spausdintiStudentus(grupe);
            break;
        }

        case 3:
            std::cout << "Programa baigta." << std::endl;
            break;

        case 4: {
            std::cout << "Iveskite failo pavadinima: ";
            std::cin >> fail;
            grupe = nuskaitytiIsFailo(fail);
            if (grupe.empty()) {
                std::cout << "Nepavyko nuskaityti studentu arba failas tuscias." << std::endl;
            }
            break;
        }

        case 5: {
            long long kiek = 0;
            int nd = 0;
            std::cout << "Kiek studentu generuoti? ";
            std::cin >> kiek;
            std::cout << "Kiek pazymiu turi kiekvienas studentas? ";
            std::cin >> nd;
            generuotiFaila(nd, kiek);
            break;
        }

        case 6: {
            std::cout << "Iveskite failo pavadinima, kuri norite dalinti: ";
            std::cin >> fail;

            std::vector<Studentas> failoGrupe = nuskaitytiIsFailo(fail);
            if (failoGrupe.empty()) {
                std::cout << "Nera studentu faile arba nepavyko nuskaityti." << std::endl;
                break;
            }

            int rusiavimoTipas = 0;
            std::cout << "Pagal ka rusiuoti studentus? "
                         "(1 - pagal varda, 0 - pagal galutini bala): ";
            std::cin >> rusiavimoTipas;

            auto start_rusiavimas = std::chrono::high_resolution_clock::now();

            StudentGroups groups = suskirstytiStudentus(failoGrupe);

            if (rusiavimoTipas == 1) {
                std::sort(groups.kietiakiai.begin(), groups.kietiakiai.end(),
                          [](const Studentas& a, const Studentas& b) {
                              return a.vardas() < b.vardas();
                          });
                std::sort(groups.vargsiukai.begin(), groups.vargsiukai.end(),
                          [](const Studentas& a, const Studentas& b) {
                              return a.vardas() < b.vardas();
                          });
            } else {
                std::sort(groups.kietiakiai.begin(), groups.kietiakiai.end(),
                          [](const Studentas& a, const Studentas& b) {
                              return a.galBalas(Studentas::vidurkis) >
                                     b.galBalas(Studentas::vidurkis);
                          });
                std::sort(groups.vargsiukai.begin(), groups.vargsiukai.end(),
                          [](const Studentas& a, const Studentas& b) {
                              return a.galBalas(Studentas::vidurkis) >
                                     b.galBalas(Studentas::vidurkis);
                          });
            }

            auto end_rusiavimas = std::chrono::high_resolution_clock::now();
            double laikas_rusiavimas =
                std::chrono::duration<double>(end_rusiavimas - start_rusiavimas)
                    .count();

            // bandome issiimti N is failo, pvz. studentai_100000.txt
            std::size_t pos1 = fail.find_last_of('_');
            std::size_t pos2 = fail.find_last_of('.');
            std::string number =
                (pos1 != std::string::npos && pos2 != std::string::npos &&
                 pos2 > pos1)
                    ? fail.substr(pos1 + 1, pos2 - pos1 - 1)
                    : "output";

            auto start_irasymas = std::chrono::high_resolution_clock::now();

            isvestiRezultatus(groups.kietiakiai,
                              "kietiakiai_" + number + ".txt");
            isvestiRezultatus(groups.vargsiukai,
                              "vargsiukai_" + number + ".txt");

            auto end_irasymas = std::chrono::high_resolution_clock::now();
            double laikas_irasymas =
                std::chrono::duration<double>(end_irasymas - start_irasymas)
                    .count();

            std::cout << "Studentai issaugoti i kietiakiai_" << number
                      << ".txt ir vargsiukai_" << number << ".txt" << std::endl;

            std::cout << std::fixed << std::setprecision(3);
            std::cout << "Rusiavimo laikas: " << laikas_rusiavimas << " s"
                      << std::endl;
            std::cout << "Irasymo i faila laikas: " << laikas_irasymas << " s"
                      << std::endl;
            break;
        }

        case 7: {
            std::cout << "Vykdomas testavimas..." << std::endl;
            testavimas();
            break;
        }

        default:
            std::cout << "Tokio pasirinkimo nera!" << std::endl;
            break;
        }

    } while (pasirinkimas != 3);

    return 0;
}
