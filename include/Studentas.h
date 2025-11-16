#pragma once

#include <iostream>
#include <string>
#include <vector>

class Studentas {
private:
    std::string vardas_;
    std::string pavarde_;
    std::vector<double> nd_;
    double egzaminas_;

public:
    // ============================
    //        RULE OF THREE
    // ============================

    Studentas();                                      // Default konstruktorius
    Studentas(const Studentas& other);                // Copy konstruktorius
    Studentas& operator=(const Studentas& other);     // Copy operatorius
    ~Studentas();                                     // Destruktorius

    // Papildomas konstruktorius skaitymui
    explicit Studentas(std::istream& is);

    // Get'eriai
    const std::string& vardas() const;
    const std::string& pavarde() const;
    const std::vector<double>& nd() const;
    double egzaminas() const;

    // Set'eriai
    void setVardas(const std::string& v);
    void setPavarde(const std::string& p);
    void setNd(const std::vector<double>& nd);
    void setEgzaminas(double egz);

    // Strategijos
    static double vidurkis(const std::vector<double>& paz);
    static double mediana(const std::vector<double>& paz);

    double galBalas(
        double (*strategy)(const std::vector<double>&) = Studentas::mediana
    ) const;

    // Skaitymas iš stream'o
    std::istream& readStudent(std::istream& is);

    // Operatoriai
    friend std::istream& operator>>(std::istream& in, Studentas& s);
    friend std::ostream& operator<<(std::ostream& out, const Studentas& s);
};

// Grupės struktūra
struct StudentGroups {
    std::vector<Studentas> kietiakiai;
    std::vector<Studentas> vargsiukai;
};

// Lyginimo funkcijos
bool compare(const Studentas& a, const Studentas& b);
bool comparePagalPavarde(const Studentas& a, const Studentas& b);
bool comparePagalEgza(const Studentas& a, const Studentas& b);
