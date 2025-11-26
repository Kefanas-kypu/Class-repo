#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Zmogus.h"

class Studentas : public Zmogus {
private:
    std::vector<double> nd_;
    double egzaminas_;

public:
    Studentas();
    Studentas(const Studentas& other);
    Studentas& operator=(const Studentas& other);
    ~Studentas();

    explicit Studentas(std::istream& is);

    // Override iš Žmogus
    std::string vardas() const override { return vardas_; }
    std::string pavarde() const override { return pavarde_; }
    void info() const override {
        std::cout << "Studentas: " << vardas_ << " " << pavarde_ << std::endl;
    }

    const std::vector<double>& nd() const;
    double egzaminas() const;

    void setVardas(const std::string& v);
    void setPavarde(const std::string& p);
    void setNd(const std::vector<double>& nd);
    void setEgzaminas(double egz);

    static double vidurkis(const std::vector<double>& paz);
    static double mediana(const std::vector<double>& paz);

    double galBalas(
        double (*strategy)(const std::vector<double>&) = Studentas::mediana
    ) const;

    std::istream& readStudent(std::istream& is);

    friend std::istream& operator>>(std::istream& in, Studentas& s);
    friend std::ostream& operator<<(std::ostream& out, const Studentas& s);
};

struct StudentGroups {
    std::vector<Studentas> kietiakiai;
    std::vector<Studentas> vargsiukai;
};

bool compare(const Studentas& a, const Studentas& b);
bool comparePagalPavarde(const Studentas& a, const Studentas& b);
bool comparePagalEgza(const Studentas& a, const Studentas& b);
