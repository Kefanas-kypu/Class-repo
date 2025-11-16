#pragma once

#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

#include "mediana.h"

class Studentas {
private:
    std::string vardas_;
    std::string pavarde_;
    std::vector<double> nd_;   // namų darbų pažymiai
    double egzaminas_;         // egzamino pažymys

public:
    // === KONSTRUKTORIAI ===

    // Numatytoji reikšmė
    Studentas() : egzaminas_(0.0) {}

    // Konstruktorius, kuris iš karto skaito studentą iš įvesties srauto
    explicit Studentas(std::istream& is) : egzaminas_(0.0) {
        readStudent(is);
    }

    // Pilnai realizuotas destruktorius
    ~Studentas() = default;

    // === GET'eriai ===
    const std::string& vardas() const { return vardas_; }
    const std::string& pavarde() const { return pavarde_; }
    const std::vector<double>& nd() const { return nd_; }
    double egzaminas() const { return egzaminas_; }

    // Statinės strategijų funkcijos
    static double vidurkis(const std::vector<double>& paz);
    static double mediana(const std::vector<double>& paz);

    // Galutinio balo skaičiavimas (0.4 * ND + 0.6 * egz.)
    double galBalas(
        double (*skaiciavimas)(const std::vector<double>&) = Studentas::mediana
    ) const;

    // Nuskaitymas iš srauto (cin arba failo)
    std::istream& readStudent(std::istream& is);

    // SET'eriai
    void setVardas(const std::string& vardas) { vardas_ = vardas; }
    void setPavarde(const std::string& pavarde) { pavarde_ = pavarde; }
    void setNd(const std::vector<double>& nd) { nd_ = nd; }
    void setEgzaminas(double egz) { egzaminas_ = egz; }
};

// Grupės struktūra
struct StudentGroups {
    std::vector<Studentas> kietiakiai;
    std::vector<Studentas> vargsiukai;
};

// Palyginimo funkcijos
bool compare(const Studentas& a, const Studentas& b);
bool comparePagalPavarde(const Studentas& a, const Studentas& b);
bool comparePagalEgza(const Studentas& a, const Studentas& b);

// =======================
//     IMPLEMENTACIJOS
// =======================

inline double Studentas::galBalas(
    double (*skaiciavimas)(const std::vector<double>&)
) const {
    auto strategija = skaiciavimas ? skaiciavimas : Studentas::mediana;
    double ndRezultatas = nd_.empty() ? 0.0 : strategija(nd_);
    return 0.4 * ndRezultatas + 0.6 * egzaminas_;
}

// =========================
//     STUDENTO NUSKAITYMAS
// =========================
inline std::istream& Studentas::readStudent(std::istream& is) {
    nd_.clear();
    egzaminas_ = 0.0;

    // === 1) Jei skaitoma iš failo ===
    if (&is != &std::cin) {
        if (!(is >> vardas_ >> pavarde_)) {
            is.setstate(std::ios::failbit);
            return is;
        }

        std::string likusi;
        std::getline(is, likusi);
        std::istringstream ss(likusi);
        double x;

        while (ss >> x) nd_.push_back(x);

        if (nd_.empty()) {
            is.setstate(std::ios::failbit);
            return is;
        }

        egzaminas_ = nd_.back();
        nd_.pop_back();
        return is;
    }

    // === 2) Jei skaitoma iš vartotojo (cin) ===

    std::cout << "Iveskite studento duomenis\n";

    std::cout << "Vardas: ";
    is >> vardas_;

    std::cout << "Pavarde: ";
    is >> pavarde_;

    int generuoti = 0;
    std::cout << "Ar pazymius generuoti atsitiktinai? (1 - taip, 0 - ne): ";
    while (!(is >> generuoti) || (generuoti != 0 && generuoti != 1)) {
        std::cout << "Iveskite 1 arba 0: ";
        is.clear();
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    if (generuoti == 1) {
        // === Auto generacija ===
        int kiek = rand() % 10 + 1;
        nd_.reserve(kiek);

        for (int i = 0; i < kiek; i++) {
            nd_.push_back(rand() % 10 + 1);
        }

        egzaminas_ = rand() % 10 + 1;
        return is;
    }

    // === Rankinis įvedimas ===
    int zinauKiek = 0;
    std::cout << "Ar zinote, kiek pazymiu turi studentas? (1 - taip, 0 - ne): ";
    while (!(is >> zinauKiek) || (zinauKiek != 0 && zinauKiek != 1)) {
        std::cout << "Iveskite 1 arba 0: ";
        is.clear();
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    if (zinauKiek == 1) {
        int kiek;
        std::cout << "Kiek pazymiu? ";
        while (!(is >> kiek) || kiek < 0) {
            std::cout << "Iveskite teigiama skaiciu: ";
            is.clear();
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        nd_.reserve(kiek);

        for (int i = 0; i < kiek; i++) {
            double paz;
            std::cout << i + 1 << ": ";
            while (!(is >> paz) || paz < 0 || paz > 10) {
                std::cout << "Iveskite 0–10: ";
                is.clear();
                is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            nd_.push_back(paz);
        }
    }
    else {
        double paz = -1;
        std::cout << "Veskite pazymius (0 - baigti):\n";
        while (true) {
            std::cout << "Pazymys: ";
            while (!(is >> paz) || paz < 0 || paz > 10) {
                std::cout << "Iveskite 0–10: ";
                is.clear();
                is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            if (paz == 0) break;
            nd_.push_back(paz);
        }
    }

    // Egzaminas
    std::cout << "Egzamino pazymys: ";
    while (!(is >> egzaminas_) || egzaminas_ < 0 || egzaminas_ > 10) {
        std::cout << "Iveskite 0–10: ";
        is.clear();
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return is;
}

// Strategijos
inline double Studentas::vidurkis(const std::vector<double>& paz) {
    return skaiciuotiVidurki(paz);
}

inline double Studentas::mediana(const std::vector<double>& paz) {
    return skaiciuotiMediana(paz);
}

// Palyginimai
inline bool compare(const Studentas& a, const Studentas& b) {
    return a.vardas() < b.vardas();
}

inline bool comparePagalPavarde(const Studentas& a, const Studentas& b) {
    return a.pavarde() < b.pavarde();
}

inline bool comparePagalEgza(const Studentas& a, const Studentas& b) {
    return a.egzaminas() < b.egzaminas();
}
