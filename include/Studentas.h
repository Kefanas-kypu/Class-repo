#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "mediana.h"
class Studentas {
private:
    std::string vardas_;
    std::string pavarde_;
    std::vector<int> paz_;
    int egzaminas_;
    double gal_rezultatas_;
    double mediana_;

public:
    Studentas() : egzaminas_(0), gal_rezultatas_(0.0), mediana_(0.0) {}
    Studentas(std::istream& is) { readStudent(is); }

    inline std::string vardas() const { return vardas_; }
    inline std::string pavarde() const { return pavarde_; }
    inline std::vector<int> paz() const { return paz_; }
    inline int egzaminas() const { return egzaminas_; }
    inline double galutinis() const { return gal_rezultatas_; }

    double galBalas(double (*skaiciavimas)(std::vector<int>) = mediana) const;
    std::istream& readStudent(std::istream& is);

    void setVardas(const std::string& vardas) { vardas_ = vardas; }
    void setPavarde(const std::string& pavarde) { pavarde_ = pavarde; }
    void setPaz(const std::vector<int>& paz) { paz_ = paz; }
    void setEgzaminas(int egz) { egzaminas_ = egz; }
    void setGalutinis(double gal) { gal_rezultatas_ = gal; }
};

bool compare(const Studentas& a, const Studentas& b);
bool comparePagalPavarde(const Studentas& a, const Studentas& b);
bool comparePagalEgza(const Studentas& a, const Studentas& b);

struct StudentGroups {
    std::vector<Studentas> kietiakiai;
    std::vector<Studentas> vargsiukai;
};
