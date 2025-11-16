#include "Studentas.h"
#include "mediana.h"

#include <algorithm>
#include <iomanip>
#include <sstream>
#include <limits>
#include <random>

// ============================
//       RULE OF THREE
// ============================

// 1. Default konstruktorius
Studentas::Studentas() : egzaminas_(0.0) {}

// 2. Copy konstruktorius
Studentas::Studentas(const Studentas& other)
    : vardas_(other.vardas_),
      pavarde_(other.pavarde_),
      nd_(other.nd_),
      egzaminas_(other.egzaminas_) {}

// 3. Copy priskyrimo operatorius
Studentas& Studentas::operator=(const Studentas& other) {
    if (this != &other) {
        vardas_ = other.vardas_;
        pavarde_ = other.pavarde_;
        nd_ = other.nd_;
        egzaminas_ = other.egzaminas_;
    }
    return *this;
}

// Destruktorius
Studentas::~Studentas() = default;


// ============================
//  Konstruktorius iš istream
// ============================

Studentas::Studentas(std::istream& is) : egzaminas_(0.0) {
    readStudent(is);
}


// ============================
//      GET'eriai
// ============================

const std::string& Studentas::vardas() const { return vardas_; }
const std::string& Studentas::pavarde() const { return pavarde_; }
const std::vector<double>& Studentas::nd() const { return nd_; }
double Studentas::egzaminas() const { return egzaminas_; }


// ============================
//       SET'eriai
// ============================

void Studentas::setVardas(const std::string& v) { vardas_ = v; }
void Studentas::setPavarde(const std::string& p) { pavarde_ = p; }
void Studentas::setNd(const std::vector<double>& nd) { nd_ = nd; }
void Studentas::setEgzaminas(double egz) { egzaminas_ = egz; }


// ============================
//       Strategijos
// ============================

double Studentas::vidurkis(const std::vector<double>& paz) {
    if (paz.empty()) return 0.0;
    return std::accumulate(paz.begin(), paz.end(), 0.0) / paz.size();
}

double Studentas::mediana(const std::vector<double>& paz) {
    return skaiciuotiMediana(paz);
}


// ============================
//   Galutinio balo formulė
// ============================

double Studentas::galBalas(
    double (*strategy)(const std::vector<double>&)
) const {
    auto strat = (strategy ? strategy : Studentas::mediana);
    double ndRez = nd_.empty() ? 0.0 : strat(nd_);
    return 0.4 * ndRez + 0.6 * egzaminas_;
}


// ============================
//      Skaitymas >> operatoriumi
// ============================

std::istream& Studentas::readStudent(std::istream& is) {
    nd_.clear();
    egzaminas_ = 0.0;

    // === Skaitymas iš failo (ne cin) ===
    if (&is != &std::cin) {
        if (!(is >> vardas_ >> pavarde_)) {
            is.setstate(std::ios::failbit);
            return is;
        }

        double x;
        while (is >> x) nd_.push_back(x);

        if (nd_.empty()) {
            is.setstate(std::ios::failbit);
            return is;
        }

        egzaminas_ = nd_.back();
        nd_.pop_back();

        return is;
    }

    // === Interaktyvus režimas ===
    std::cout << "Studento vardas: ";
    is >> vardas_;

    std::cout << "Studento pavarde: ";
    is >> pavarde_;

    int generuoti = 0;
    std::cout << "Generuoti pazymius atsitiktinai? (1 - taip, 0 - ne): ";
    is >> generuoti;

    if (generuoti == 1) {
        int kiek = rand() % 10 + 1;
        nd_.resize(kiek);
        for (double &x : nd_) x = rand() % 10 + 1;
        egzaminas_ = rand() % 10 + 1;
        return is;
    }

    // Rankinis įvedimas
    double paz;
    std::cout << "Veskite pazymius (0 - baigti):\n";

    while (true) {
        std::cout << "Pazymys: ";
        if (!(is >> paz) || paz < 0 || paz > 10) {
            std::cout << "Neteisinga ivestis. Kartokite.\n";
            is.clear();
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (paz == 0) break;
        nd_.push_back(paz);
    }

    std::cout << "Egzaminas: ";
    is >> egzaminas_;

    return is;
}


// ============================
//      Operatorius <<
// ============================

std::ostream& operator<<(std::ostream& out, const Studentas& s) {
    out << s.vardas_ << " " << s.pavarde_ << " | ND: ";

    for (double v : s.nd_) out << v << " ";

    out << "| Egz.: " << s.egzaminas_
        << " | Galutinis: " << std::fixed << std::setprecision(2)
        << s.galBalas();

    return out;
}


// ============================
//    Lyginimo funkcijos
// ============================

bool compare(const Studentas& a, const Studentas& b) {
    return a.vardas() < b.vardas();
}

bool comparePagalPavarde(const Studentas& a, const Studentas& b) {
    return a.pavarde() < b.pavarde();
}

bool comparePagalEgza(const Studentas& a, const Studentas& b) {
    return a.egzaminas() < b.egzaminas();
}
