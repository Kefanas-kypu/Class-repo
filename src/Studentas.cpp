#include "Studentas.h"
#include "mediana.h"
#include <sstream>
#include <limits>
#include <iostream>
#include <algorithm>

// --- Rule of Three ---

Studentas::Studentas() : egzaminas_(0.0) {}

Studentas::Studentas(const Studentas& other)
    : Zmogus(other) 
{
    nd_ = other.nd_;
    egzaminas_ = other.egzaminas_;
}

Studentas& Studentas::operator=(const Studentas& other) {
    if (this != &other) {
        Zmogus::operator=(other); 
        nd_ = other.nd_;
        egzaminas_ = other.egzaminas_;
    }
    return *this;
}

Studentas::~Studentas() {}

// --- Papildomi konstruktoriai ---
Studentas::Studentas(std::istream& is) : egzaminas_(0.0) {
    readStudent(is);
}

// --- Getteriai ---
const std::vector<double>& Studentas::nd() const { return nd_; }
double Studentas::egzaminas() const { return egzaminas_; }

// --- Setteriai ---
void Studentas::setVardas(const std::string& v) { vardas_ = v; }
void Studentas::setPavarde(const std::string& p) { pavarde_ = p; }
void Studentas::setNd(const std::vector<double>& nd) { nd_ = nd; }
void Studentas::setEgzaminas(double egz) { egzaminas_ = egz; }

// --- Strategijos ---
double Studentas::vidurkis(const std::vector<double>& paz) {
    return skaiciuotiVidurki(paz);
}

double Studentas::mediana(const std::vector<double>& paz) {
    return skaiciuotiMediana(paz);
}

double Studentas::galBalas(
    double (*strategy)(const std::vector<double>&)) const {

    if (!strategy) strategy = Studentas::mediana;
    double ndRez = nd_.empty() ? 0.0 : strategy(nd_);
    return 0.4 * ndRez + 0.6 * egzaminas_;
}

// --- Skaitymas ---
std::istream& Studentas::readStudent(std::istream& is) {
    nd_.clear();
    egzaminas_ = 0.0;

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

    std::cout << "Iveskite studento duomenis\n";

    std::cout << "Studento vardas: ";
    is >> vardas_;

    std::cout << "Studento pavarde: ";
    is >> pavarde_;

    int generuoti = 0;
    std::cout << "Generuoti pazymius atsitiktinai? (1 - taip, 0 - ne): ";
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
    std::cout << "Ar zinote pazymiu kieki? (1 - taip, 0 - ne): ";
    is >> zinauKiek;

    if (zinauKiek == 1) {
        int kiek;
        std::cout << "Kiek pazymiu turi studentas? ";
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
        std::cout << "Veskite pazymius (iveskite 0, jei norite baigti):\n";
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

// --- Operatoriai ---
std::istream& operator>>(std::istream& in, Studentas& s) {
    return s.readStudent(in);
}

std::ostream& operator<<(std::ostream& out, const Studentas& s) {
    out << s.vardas() << " " << s.pavarde() << " ND: ";
    for (double v : s.nd_) out << v << " ";
    out << "Egz: " << s.egzaminas()
        << " Galutinis: " << s.galBalas();
    return out;
}

// --- Lyginimai ---
bool compare(const Studentas& a, const Studentas& b) {
    return a.vardas() < b.vardas();
}

bool comparePagalPavarde(const Studentas& a, const Studentas& b) {
    return a.pavarde() < b.pavarde();
}

bool comparePagalEgza(const Studentas& a, const Studentas& b) {
    return a.egzaminas() < b.egzaminas();
}
