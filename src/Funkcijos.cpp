#include "Funkcijos.h"

#include <chrono>
#include <iomanip>
#include <random>
#include <sstream>
#include <chrono>

using std::vector;

void spausdintiStudentus(const std::vector<Studentas>& studentai) {
    std::cout << std::left << std::setw(15) << "Vardas"
              << std::setw(15) << "Pavarde"
              << std::setw(20) << "Galutinis (Med.)"
              << std::setw(20) << "Galutinis (Vid.)" << std::endl;

    std::cout << std::string(70, '-') << std::endl;

    for (const auto& s : studentai) {
        std::cout << std::left << std::setw(15) << s.vardas()
                  << std::setw(15) << s.pavarde()
                  << std::setw(20) << std::fixed << std::setprecision(2) << s.galBalas(Studentas::mediana)
                  << std::setw(20) << std::fixed << std::setprecision(2) << s.galBalas(Studentas::vidurkis)
                  << std::endl;
    }
}

void rusiavimas(std::vector<Studentas>& studentai) {
    std::sort(studentai.begin(), studentai.end(), comparePagalPavarde);
}

StudentGroups suskirstytiStudentus(const std::vector<Studentas>& studentai) {
    StudentGroups grupes;

    for (const auto& s : studentai) {
        if (s.galBalas(Studentas::vidurkis) >= 5.0)
            grupes.kietiakiai.push_back(s);
        else
            grupes.vargsiukai.push_back(s);
    }

    return grupes;
}

void generuotiFaila(int nd_count, long long kiek) {
    std::ofstream fout("studentai_" + std::to_string(kiek) + ".txt");
    if (!fout) {
        std::cout << "Nepavyko sukurti failo\n";
        return;
    }

    fout << "Vardas Pavarde";
    for (int i = 1; i <= nd_count; ++i) 
        fout << " ND" << i;
    fout << " Egzaminas\n";

    std::mt19937 mt(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> dist(1, 10);

    for (long long i = 1; i <= kiek; ++i) {
        fout << "Vardas" << i << " Pavarde" << i;
        for (int j = 0; j < nd_count; ++j) 
            fout << " " << dist(mt);
        fout << " " << dist(mt) << "\n";
    }

    fout.close();
    std::cout << "Sugeneruotas failas studentai_" << kiek << ".txt su " << kiek << " studentais ir " << nd_count << " ND.\n";
}

std::vector<Studentas> nuskaitytiIsFailo(const std::string& failoPavadinimas) {
    std::ifstream in(failoPavadinimas);
    std::vector<Studentas> studentai;

    if (!in) {
        std::cerr << "Nepavyko atidaryti failo!" << std::endl;
        return studentai;
    }

    std::string header;
    std::getline(in, header);

    std::string eilute;
    while (std::getline(in, eilute)) {
        if (eilute.empty()) continue;

        std::istringstream eilutesSrautas(eilute);
        Studentas s(eilutesSrautas);

        if (!eilutesSrautas.fail()) {
            studentai.push_back(s);
        }
    }

    return studentai;
}

void isvestiRezultatus(const std::vector<Studentas>& studentai,
                       const std::string& failoPavadinimas) 
{
    std::ofstream out(failoPavadinimas);
    if (!out) {
        std::cerr << "Nepavyko sukurti failo: " << failoPavadinimas << std::endl;
        return;
    }

    out << std::left << std::setw(15) << "Vardas"
        << std::setw(15) << "Pavarde"
        << std::setw(20) << "Galutinis (Med.)"
        << std::setw(20) << "Galutinis (Vid.)" << std::endl;

    out << std::string(70, '-') << std::endl;

    for (const auto& s : studentai) {
        out << std::left << std::setw(15) << s.vardas()
            << std::setw(15) << s.pavarde()
            << std::setw(20) << std::fixed << std::setprecision(2) 
            << s.galBalas(Studentas::mediana)
            << std::setw(20) << std::fixed << std::setprecision(2) 
            << s.galBalas(Studentas::vidurkis)
            << std::endl;
    }

    out.close();
}

void testavimas() {
    std::vector<long long> sizes = {100000, 1000000};
    std::cout << std::fixed << std::setprecision(3);

    for (auto n : sizes) {
        std::cout << "\n--- Testuojama su failu studentai_" << n << ".txt ---\n";
        std::string fail_name = "studentai_" + std::to_string(n) + ".txt";
        std::vector<Studentas> test_grupe;

        auto start_nuskaitymas = std::chrono::high_resolution_clock::now();
        test_grupe = nuskaitytiIsFailo(fail_name);
        auto end_nuskaitymas = std::chrono::high_resolution_clock::now();
        double laikas_nuskaitymas = std::chrono::duration<double>(end_nuskaitymas - start_nuskaitymas).count();

        if (test_grupe.empty()) {
            std::cout << "Failas " << fail_name << " tuščias arba nepavyko nuskaityti.\n";
            continue;
        }

        auto start_rikiavimas = std::chrono::high_resolution_clock::now();
        std::sort(test_grupe.begin(), test_grupe.end(),
            [](const Studentas& a, const Studentas& b) {
                return a.galBalas(Studentas::vidurkis) < b.galBalas(Studentas::vidurkis);
            }
        );
        auto end_rikiavimas = std::chrono::high_resolution_clock::now();
        double laikas_rikiavimas = std::chrono::duration<double>(end_rikiavimas - start_rikiavimas).count();

        auto start_padalijimas = std::chrono::high_resolution_clock::now();
        StudentGroups groups = suskirstytiStudentus(test_grupe);
        auto end_padalijimas = std::chrono::high_resolution_clock::now();
        double laikas_padalijimas = std::chrono::duration<double>(end_padalijimas - start_padalijimas).count();

        auto start_irasymas = std::chrono::high_resolution_clock::now();
        isvestiRezultatus(groups.kietiakiai, "kietiakiai_" + std::to_string(n) + ".txt");
        isvestiRezultatus(groups.vargsiukai, "vargsiukai_" + std::to_string(n) + ".txt");
        auto end_irasymas = std::chrono::high_resolution_clock::now();
        double laikas_irasymas = std::chrono::duration<double>(end_irasymas - start_irasymas).count();

        double laikas_total = laikas_nuskaitymas + laikas_rikiavimas + laikas_padalijimas + laikas_irasymas;

        std::cout << "Failo nuskaitymo laikas: " << laikas_nuskaitymas << " s\n";
        std::cout << "Rikiavimo laikas: " << laikas_rikiavimas << " s\n";
        std::cout << "Padalijimo i vargsiukus ir kietakius laikas: " << laikas_padalijimas << " s\n";
        std::cout << "Irasymo laikas i failus laikas: " << laikas_irasymas << " s\n";
        std::cout << "Bendras laikas: " << laikas_total << " s\n";
    }
}
