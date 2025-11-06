#include "Funkcijos.h"
#include <iomanip>
#include <random>
#include <chrono>

double skaiciuotiVidurki(const std::vector<int>& paz) {
    if (paz.empty()) return 0.0;
    double suma = 0;
    for (int p : paz) suma += p;
    return suma / paz.size();
}

void spausdintiStudentus(const std::vector<Studentas>& studentai) {
    std::cout << std::left << std::setw(15) << "Vardas"
              << std::setw(15) << "Pavarde"
              << std::setw(15) << "Galutinis (Med.)" << std::endl;
    std::cout << std::string(45, '-') << std::endl;

    for (const auto& s : studentai) {
        std::cout << std::left << std::setw(15) << s.vardas()
                  << std::setw(15) << s.pavarde()
                  << std::setw(15) << std::fixed << std::setprecision(2) << s.galutinis()
                  << std::endl;
    }
}

void rusiavimas(std::vector<Studentas>& studentai) {
    std::sort(studentai.begin(), studentai.end(),
              [](const Studentas& a, const Studentas& b) {
                  return a.vardas() < b.vardas();
              });
}

StudentGroups suskirstytiStudentus(const std::vector<Studentas>& studentai) {
    StudentGroups grupes;
    for (const auto& s : studentai) {
        if (s.galutinis() >= 5.0)
            grupes.kietiakiai.push_back(s);
        else
            grupes.vargsiukai.push_back(s);
    }
    return grupes;
}

void generuotiFaila(const std::string& failoPavadinimas, int kiek) {
    std::ofstream out(failoPavadinimas);
    if (!out) {
        std::cerr << "Nepavyko sukurti failo!" << std::endl;
        return;
    }

    out << "Vardas Pavarde ND1 ND2 ND3 ND4 ND5 Egzaminas\n";

    std::mt19937 mt(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> dist(1, 10);

    for (int i = 0; i < kiek; i++) {
        out << "Vardas" << i + 1 << " Pavarde" << i + 1 << " ";
        for (int j = 0; j < 5; j++)
            out << dist(mt) << " ";
        out << dist(mt) << "\n";
    }

    std::cout << "Sugeneruotas failas: " << failoPavadinimas << std::endl;
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

    while (true) {
        Studentas s;
        if (!s.readStudent(in)) break;
        studentai.push_back(s);
    }

    return studentai;
}

void isvestiRezultatus(const std::vector<Studentas>& studentai, const std::string& failoPavadinimas) {
    std::ofstream out(failoPavadinimas);
    if (!out) {
        std::cerr << "Nepavyko sukurti failo: " << failoPavadinimas << std::endl;
        return;
    }

    out << std::left << std::setw(15) << "Vardas"
        << std::setw(15) << "Pavarde"
        << std::setw(15) << "Galutinis (Med.)" << std::endl;
    out << std::string(45, '-') << std::endl;

    for (const auto& s : studentai) {
        out << std::left << std::setw(15) << s.vardas()
            << std::setw(15) << s.pavarde()
            << std::setw(15) << std::fixed << std::setprecision(2) << s.galutinis()
            << std::endl;
    }
}

void testavimas(const std::string& failas) {
    auto studentai = nuskaitytiIsFailo(failas);
    rusiavimas(studentai);
    spausdintiStudentus(studentai);
}
