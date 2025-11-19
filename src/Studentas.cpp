#include "Studentas.h"
#include "mediana.h"
#include <sstream>
#include <limits>
#include <iostream>
#include <algorithm>

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

Studentas::Studentas(std::istream& is) : egzaminas_(0.0) {
    readStudent(is);
}
// GET'ERIAI

const std::string& Studentas::vardas() const { return vardas_; }
const std::string& Studentas::pavarde() const { return pavarde_; }
const std::vector<double>& Studentas::nd() const { return nd_; }
double Studentas::egzaminas() const { return egzaminas_; }

// SET'ERIAI

void Studentas::setVardas(const std::string& v) { vardas_ = v; }
void Studentas::setPavarde(const std::string& p) { pavarde_ = p; }
void Studentas::setNd(const std::vector<double>& nd) { nd_ = nd; }
void Studentas::setEgzaminas(double egz) { egzaminas_ = egz; }

// STRATEGIJOS

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

// STUDENTO NUSKAITYMAS

std::istream& Studentas::readStudent(std::istream& is) {
    nd_.clear();
    egzaminas_ = 0.0;

    // ==== Skaitymas iš failo ====
    if (&is != &std::cin) {
        if (!(is >> vardas_ >> pavarde_)) {
            is.setstate(std::ios::failbit);
            return is;
        }

        std::string line;
        std::getline(is, line);
        std::istringstream ss(line);

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

    // ==== Interaktyvus vartotojo skaitymas ====

    std::cout << "Iveskite studento duomenis\n";

    std::cout << "Vardas: ";
    is >> vardas_;

    std::cout << "Pavarde: ";
    is >> pavarde_;

    int generuoti = 0;
    std::cout << "Generuoti pazymius atsitiktinai? (1/0): ";
    is >> generuoti;

    if (generuoti == 1) {
        int kiek = rand() % 10 + 1;
        nd_.reserve(kiek);
        for (int i = 0; i < kiek; i++)
            nd_.push_back(rand() % 10 + 1);
        egzaminas_ = rand() % 10 + 1;
        return is;
    }

    int zinauKiek = 0;
    std::cout << "Ar zinote pazymiu kieki? (1/0): ";
    is >> zinauKiek;

    if (zinauKiek == 1) {
        int kiek;
        std::cout << "Kiek pazymiu? ";
        is >> kiek;

        nd_.reserve(kiek);

        for (int i = 0; i < kiek; i++) {
            double paz;
            std::cout << i + 1 << ": ";
            is >> paz;
            nd_.push_back(paz);
        }
    } else {
        double paz;
        std::cout << "Veskite pazymius (0 baigti):\n";
        while (true) {
            std::cout << "Pazymys: ";
            is >> paz;
            if (paz == 0) break;
            nd_.push_back(paz);
        }
    }

    std::cout << "Egzaminas: ";
    is >> egzaminas_;

    return is;
}

// OPERATORIAI

std::istream& operator>>(std::istream& in, Studentas& s) {
    return s.readStudent(in);
}

std::ostream& operator<<(std::ostream& out, const Studentas& s) {
    out << s.vardas_ << " " << s.pavarde_ << " ND: ";
    for (double v : s.nd_) out << v << " ";
    out << "Egz: " << s.egzaminas_
        << " Galutinis: " << s.galBalas();
    return out;
}

// LYGINIMO FUNKCIJOS

bool compare(const Studentas& a, const Studentas& b) {
    return a.vardas() < b.vardas();
}

bool comparePagalPavarde(const Studentas& a, const Studentas& b) {
    return a.pavarde() < b.pavarde();
}

bool comparePagalEgza(const Studentas& a, const Studentas& b) {
    return a.egzaminas() < b.egzaminas();
}
