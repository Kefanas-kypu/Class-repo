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
        cin >> pasirinkimas;

        switch (pasirinkimas) {

        case 1: {
            Studentas s;
            s.readStudent(cin);
            grupe.push_back(s);
            cout << "Studentas pridetas sekmingai!" << endl;
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

            auto start = chrono::high_resolution_clock::now();
            grupe = nuskaitytiIsFailo(fail);
            auto end = chrono::high_resolution_clock::now();

            double laikas = chrono::duration<double>(end - start).count();
            cout << "Duomenu nuskaitymas uztruko: " << laikas << " s" << endl;
            break;
        }

        case 5: {
            int kiek;
            cout << "Kiek studentu sugeneruoti? ";
            cin >> kiek;
            generuotiFaila("studentai_" + to_string(kiek) + ".txt", kiek);
            break;
        }

        case 6: {
            cout << "Iveskite failo pavadinima: ";
            cin >> fail;

            grupe = nuskaitytiIsFailo(fail);
            if (grupe.empty()) {
                cout << "Failas tuscias arba nepavyko nuskaityti." << endl;
                break;
            }

            auto start = chrono::high_resolution_clock::now();
            StudentGroups grupes = suskirstytiStudentus(grupe);
            auto end = chrono::high_resolution_clock::now();

            double laikas = chrono::duration<double>(end - start).count();

            isvestiRezultatus(grupes.kietiakiai, "kietiakiai.txt");
            isvestiRezultatus(grupes.vargsiukai, "vargsiukai.txt");

            cout << "Padalinta ir issaugota per: " << laikas << " s" << endl;
            break;
        }

        case 7: {
            vector<int> dydziai = {1000, 10000, 100000};
            for (int n : dydziai) {
                cout << "\n--- Testas su failu studentai_" << n << ".txt ---" << endl;
                generuotiFaila("studentai_" + to_string(n) + ".txt", n);
                testavimas("studentai_" + to_string(n) + ".txt");
            }
            break;
        }

        default:
            cout << "Neteisingas pasirinkimas!" << endl;
        }

    } while (pasirinkimas != 3);

    return 0;
}
