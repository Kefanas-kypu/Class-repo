#include "Studentas.h"
#include "mediana.h"
#include <sstream>
#include <limits>
#include <iostream>
#include <algorithm>

// =========================
//   RULE OF THREE
// =========================

Studentas::Studentas() : egzaminas_(0.0) {}

Studentas::Studentas(const Studentas& other)
    : vardas_(other.vardas_),
      pavarde_(other.pavarde_),
      nd_(other.nd_),
      egzaminas_(other.egzaminas_) {}

Studentas& Studentas::operator=(const Studentas& other) {
    if (this != &other) {
        vardas_ = other.vardas_;
        pavarde_ = other.pavarde_;
        nd_ = other.nd_;
        egzaminas_ = other.egzaminas_;
    }
    return *this;
}

Studentas::~Studentas() {}

// =========================
//   PAPILDOMAS KONSTR.
// =========================

Studentas::Studentas(std::istream& is) : egzaminas_(0.0) {
    readStudent(is);
}

// =========================
//   GET'eriai
// =========================

const std::string& Studentas::vardas() const { return vardas_; }
const std::string& Studentas::pavarde() const { return pavarde_; }
const std::vector<double>& Studentas::nd() const { return nd_; }
double Studentas::egzaminas() const { return egzaminas_; }

// =========================
//        SET'eriai
// =========================

void Studentas::setVardas(const std::string& v) { vardas_ = v; }
void Studentas::setPavarde(const std::string& p) { pavarde_ = p; }
void Studentas::setNd(const std::vector<double>& nd) { nd_ = nd; }
void Studentas::setEgzaminas(double egz) { egzaminas_ = egz; }

// =========================
//        STRATEGIJOS
// =========================

double Studentas::vidurkis(const std::vector<double>& paz) {
    return skaiciuotiVidurki(paz);
}

double Studentas::mediana(const std::vector<double>& paz) {
    return skaiciuotiMediana(paz);
}

double Studentas::galBalas(double (*strategy)(const std::vector<double>&)) const {
    if (!strategy) strategy = Studentas::mediana;
    double ndRez = nd_.empty() ? 0.0 : strategy(nd_);
    return 0.4 * ndRez + 0.6 * egzaminas_;
}

// =========================
//     NUSKAITYMAS
// =========================

std::istream& Studentas::readStudent(std::istream& is) {
    nd_.clear();
    egzaminas_ = 0.0;

    // === Jei skaitoma iš failo ===
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

    // === Interaktyvus skaitymas iš vartotojo ===
    std::cout << "Iveskite studento duomenis\n";

    std::cout << "Studento vardas: ";
    is >> vardas_;

    std::cout << "Studento pavarde: ";
    is >> pavarde_;

    int generuoti = 0;
    std::cout << "Ar pazymius generuoti atsitiktinai? (1 - taip, 0 - ne): ";
    while (!(is >> generuoti) || (generuoti != 0 && generuoti != 1)) {
        std::cout << "Iveskite 1 arba 0: ";
        is.clear();
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    if (generuoti == 1) {
        int kiek = rand() % 10 + 1;
        nd_.reserve(kiek);

        for (int i = 0; i < kiek; i++)
            nd_.push_back(rand() % 10 + 1);

        egzaminas_ = rand() % 10 + 1;
        return is;
    }

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

    std::cout << "Egzaminas: ";
    while (!(is >> egzaminas_) || egzaminas_ < 0 || egzaminas_ > 10) {
        std::cout << "Iveskite 0–10: ";
        is.clear();
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return is;
}

// =========================
//     LYGĮNIMO FUNKCIJOS
// =========================

bool compare(const Studentas& a, const Studentas& b) {
    return a.vardas() < b.vardas();
}

bool comparePagalPavarde(const Studentas& a, const Studentas& b) {
    return a.pavarde() < b.pavarde();
}

bool comparePagalEgza(const Studentas& a, const Studentas& b) {
    return a.egzaminas() < b.egzaminas();
}
