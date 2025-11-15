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
    // Numatytoji reikšmė
    Studentas() : egzaminas_(0.0) {}

    // Konstruktorius, kuris iš karto skaito studentą iš įvesties srauto
    explicit Studentas(std::istream& is) : egzaminas_(0.0) {
        readStudent(is);
    }

    // GET'eriai
    const std::string& vardas() const { return vardas_; }
    const std::string& pavarde() const { return pavarde_; }
    const std::vector<double>& nd() const { return nd_; }
    double egzaminas() const { return egzaminas_; }

    // Statinės strategijų funkcijos
    static double vidurkis(const std::vector<double>& paz);
    static double mediana(const std::vector<double>& paz);

    // Galutinio balo skaičiavimas (0.4 * ND + 0.6 * egz.)
    // Numatytasis strategijos parametras – mediana
    double galBalas(
        double (*skaiciavimas)(const std::vector<double>&) = Studentas::mediana
    ) const;

    // Nuskaitymas iš srauto (arba iš cin, arba iš failo)
    std::istream& readStudent(std::istream& is);

    // SET'eriai (jeigu kada prireiktų)
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

// ====== INLINE IMPLEMENTACIJOS ======

inline double Studentas::galBalas(
    double (*skaiciavimas)(const std::vector<double>&)
) const {
    auto strategija = skaiciavimas ? skaiciavimas : Studentas::mediana;
    double ndRezultatas = nd_.empty() ? 0.0 : strategija(nd_);
    return 0.4 * ndRezultatas + 0.6 * egzaminas_;
}

inline std::istream& Studentas::readStudent(std::istream& is) {
    nd_.clear();
    egzaminas_ = 0.0;

    if (&is == &std::cin) {
        std::cout << "Iveskite varda: ";
        if (!(is >> vardas_)) return is;

        std::cout << "Iveskite pavarde: ";
        if (!(is >> pavarde_)) return is;

        std::size_t kiek = 0;
        std::cout << "Kiek namu darbu ivertinimu? ";
        while (!(is >> kiek)) {
            std::cout << "Neteisinga ivestis. Bandykite dar karta: ";
            is.clear();
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        nd_.reserve(kiek);
        for (std::size_t i = 0; i < kiek; ++i) {
            double pazymys;
            std::cout << "ND: " << i + 1 << ": ";
                        while (!(is >> pazymys) || pazymys < 0.0 || pazymys > 10.0) {
                std::cout << "Iveskite reiksme nuo 0 iki 10: ";
                is.clear();
                is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            nd_.push_back(pazymys);
        }

        std::cout << "Egzamino ivertinimas: ";
        while (!(is >> egzaminas_) || egzaminas_ < 0.0 || egzaminas_ > 10.0) {
            std::cout << "Iveskite reiksme nuo 0 iki 10: ";
            is.clear();
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else {
        // Skaitymas iš failo: "Vardas Pavarde nd1 nd2 ... ndN egz"
        if (!(is >> vardas_ >> pavarde_)) {
            is.setstate(std::ios::failbit);
            return is;
        }

        std::string likusiDalis;
        std::getline(is, likusiDalis);
        std::istringstream pazStream(likusiDalis);

        double pazymys;
        while (pazStream >> pazymys) {
            nd_.push_back(pazymys);
        }

        if (nd_.empty()) {
            is.setstate(std::ios::failbit);
            return is;
        }

        egzaminas_ = nd_.back();
        nd_.pop_back();
    }

    return is;
}

inline double Studentas::vidurkis(const std::vector<double>& paz) {
    return skaiciuotiVidurki(paz);
}

inline double Studentas::mediana(const std::vector<double>& paz) {
    return skaiciuotiMediana(paz);
}

inline bool compare(const Studentas& a, const Studentas& b) {
    return a.vardas() < b.vardas();
}

inline bool comparePagalPavarde(const Studentas& a, const Studentas& b) {
    return a.pavarde() < b.pavarde();
}

inline bool comparePagalEgza(const Studentas& a, const Studentas& b) {
    return a.egzaminas() < b.egzaminas();
}
