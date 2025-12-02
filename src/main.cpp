/**
 * @file main.cpp
 * @brief Pagrindinė programos įėjimo funkcija – naudotojo meniu ir programos valdymas.
 */

#include "Funkcijos.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <list>
#include <chrono>
#include <limits>

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(0)));

    vector<Studentas> grupe;
    string fail;
    int pasirinkimas;

    do {
        cout << "\nKa norite atlikti?" << endl;
        cout << "1. Ivesti nauja studenta" << endl;
        cout << "2. Atspausdinti rezultatus" << endl;
        cout << "3. Iseiti" << endl;
        cout << "4. Nuskaityti studentus is failo" << endl;
        cout << "5. Sugeneruoti atsitiktinius studentu failus" << endl;
        cout << "6. Padalinti studentus i grupes ir issaugoti i failus" << endl;
        cout << "7. Testuoti veikima su ivairaus dydzio failais" << endl;
        cout << "Pasirinkite veiksma: ";

        if (!(cin >> pasirinkimas)) {
            cout << "Neteisinga ivestis, bandykite dar karta." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (pasirinkimas) {

        case 1: {
            Studentas s;
            s.readStudent(cin);
            grupe.push_back(s);
            cout << "Studentas pridetas sekmingai!" << endl;
            cout << "Objekto adresas: " << &s << std::endl;
            break;
        }

        case 2: {
            if (grupe.empty()) {
                cout << "Nera studentu duomenu!" << endl;
                break;
            }
            rusiavimas(grupe);
            spausdintiStudentus(grupe);
            break;
        }

        case 3:
            cout << "Programa baigta." << endl;
            break;

        case 4: {
            cout << "Iveskite failo pavadinima: ";
            cin >> fail;
            grupe = nuskaitytiIsFailo(fail);
            break;
        }

        case 5: {
            string failoPav;
            int kiek, nd;
            cout << "Kiek studentu generuoti? ";
            cin >> kiek;
            cout << "Iveskite, kiek studentas turi pazymiu: ";
            cin >> nd;
            generuotiFaila(nd, kiek);
            break;
        }

        case 6: {
            std::cout << "Iveskite failo pavadinima, kuri norite dalinti: ";
            std::cin >> fail;

            std::vector<Studentas> grupe;
            grupe = nuskaitytiIsFailo(fail);

            if (grupe.empty()) {
                std::cout << "Nera studentu faile arba nepavyko nuskaityti." << std::endl;
                break;
            }

            int rusiavimas;
            std::cout << "Pagal ka rusiuoti studentus? (1 - pagal varda, 0 - pagal galutini bala): ";
            std::cin >> rusiavimas;

            auto start_rusiavimas = std::chrono::high_resolution_clock::now();

            StudentGroups groups = suskirstytiStudentus(grupe);

            if (rusiavimas == 1) {
                std::sort(groups.kietiakiai.begin(), groups.kietiakiai.end(),
                    [](const Studentas& a, const Studentas& b) {
                        return a.vardas() < b.vardas();
                    }
                );
                std::sort(groups.vargsiukai.begin(), groups.vargsiukai.end(),
                    [](const Studentas& a, const Studentas& b) {
                        return a.vardas() < b.vardas();
                    }
                );
            } else {
                std::sort(groups.kietiakiai.begin(), groups.kietiakiai.end(),
                    [](const Studentas& a, const Studentas& b) {
                        return a.galBalas(Studentas::vidurkis) > b.galBalas(Studentas::vidurkis);
                    }
                );
                std::sort(groups.vargsiukai.begin(), groups.vargsiukai.end(),
                    [](const Studentas& a, const Studentas& b) {
                        return a.galBalas(Studentas::vidurkis) > b.galBalas(Studentas::vidurkis);
                    }
                );
            }

            auto end_rusiavimas = std::chrono::high_resolution_clock::now();
            double laikas_rusiavimas = std::chrono::duration<double>(end_rusiavimas - start_rusiavimas).count();

            size_t pos1 = fail.find_last_of('_');
            size_t pos2 = fail.find_last_of('.');
            std::string number = (pos1 != std::string::npos && pos2 != std::string::npos && pos2 > pos1)
                                ? fail.substr(pos1 + 1, pos2 - pos1 - 1)
                                : "output";

            auto start_irasymas = std::chrono::high_resolution_clock::now();

            isvestiRezultatus(groups.kietiakiai, "kietiakiai_" + number + ".txt");
            isvestiRezultatus(groups.vargsiukai, "vargsiukai_" + number + ".txt");

            auto end_irasymas = std::chrono::high_resolution_clock::now();
            double laikas_irasymas = std::chrono::duration<double>(end_irasymas - start_irasymas).count();

            std::cout << "Studentai issaugoti i kietiakiai_" << number
                     << ".txt ir vargsiukai_" << number << ".txt" << std::endl;

            std::cout << std::fixed << std::setprecision(3);
            std::cout << "Rusiavimo laikas: " << laikas_rusiavimas << " s" << std::endl;
            std::cout << "Irasymo i faila laikas: " << laikas_irasymas << " s" << std::endl;
            break;
        }

        case 7: {
            cout << "Vykdomas testavimas..." << endl;
            testavimas();
            break;
        }

        default:
            cout << "Tokio pasirinkimo nera!" << endl;
            break;
        }

    } while (pasirinkimas != 3);

    return 0;
}
