/**
 * @file Studentas.h
 * @brief Studentas klasės ir pagalbinių funkcijų deklaracijos.
 */

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Zmogus.h"

/**
 * @brief Studentą aprašanti klasė, paveldinti Zmogus.
 *
 * Laiko pažymių sąrašą ir egzamino balą, leidžia skaičiuoti galutinį balą
 * pagal vidurkio ar medianos strategiją.
 */
class Studentas : public Zmogus {
private:
    /// Namų darbų pažymiai.
    std::vector<double> nd_;
    /// Egzamino balas.
    double egzaminas_;

public:
    // Rule of Three

    /**
     * @brief Numatytoji konstruktorius. Sukuria studentą su 0 egzamino balu.
     */
    Studentas();

    /**
     * @brief Kopijavimo konstruktorius.
     * @param other Kitas Studentas objektas.
     */
    Studentas(const Studentas& other);

    /**
     * @brief Priskyrimo operatorius.
     * @param other Kitas Studentas objektas.
     * @return Nuoroda į šį objektą.
     */
    Studentas& operator=(const Studentas& other);

    /// Destruktorius.
    ~Studentas();

    /**
     * @brief Konstruktorius, skaitantis studento duomenis iš srauto.
     * @param is Įvesties srautas.
     */
    explicit Studentas(std::istream& is);

    // Paveldėti getteriai iš Zmogus

    /// @copydoc Zmogus::vardas()
    const std::string& vardas() const override { return vardas_; }

    /// @copydoc Zmogus::pavarde()
    const std::string& pavarde() const override { return pavarde_; }

    /**
     * @brief Spausdina trumpą informaciją apie studentą.
     */
    void info() const override {
        std::cout << "Studentas: " << vardas_ << " " << pavarde_ << std::endl;
    }

    /**
     * @brief Grąžina nuorodą į namų darbų pažymių vektorių.
     * @return Konstanta nuoroda į pažymių vektorių.
     */
    const std::vector<double>& nd() const;

    /**
     * @brief Grąžina egzamino balą.
     * @return Egzamino balas.
     */
    double egzaminas() const;

    /**
     * @brief Nustato studento vardą.
     * @param v Naujas vardas.
     */
    void setVardas(const std::string& v);

    /**
     * @brief Nustato studento pavardę.
     * @param p Nauja pavardė.
     */
    void setPavarde(const std::string& p);

    /**
     * @brief Nustato namų darbų pažymius.
     * @param nd Nauji pažymiai.
     */
    void setNd(const std::vector<double>& nd);

    /**
     * @brief Nustato egzamino balą.
     * @param egz Naujas egzamino balas.
     */
    void setEgzaminas(double egz);

    /**
     * @brief Apskaičiuoja pažymių vidurkį.
     * @param paz Pažymių vektorius.
     * @return Vidurkis.
     */
    static double vidurkis(const std::vector<double>& paz);

    /**
     * @brief Apskaičiuoja pažymių medianą.
     * @param paz Pažymių vektorius.
     * @return Mediana.
     */
    static double mediana(const std::vector<double>& paz);

    /**
     * @brief Apskaičiuoja galutinį balą pagal pasirinktą strategiją.
     *
     * @param strategy Funkcija, kuri iš pažymių vektoriaus grąžina vieną reikšmę
     * (vidurkį, medianą ir pan.). Jei nepateikta, naudojama mediana.
     *
     * @return Galutinis balas.
     */
    double galBalas(
        double (*strategy)(const std::vector<double>&) = Studentas::mediana
    ) const;

    /**
     * @brief Nuskaito studento duomenis iš srauto.
     *
     * Funkcija palaiko tiek nuskaitymą iš failo (vienos eilutės formatas),
     * tiek interaktyvią įvestį iš std::cin.
     *
     * @param is Įvesties srautas.
     * @return Nuoroda į tą patį srautą.
     */
    std::istream& readStudent(std::istream& is);

    /**
     * @brief Įvesties operatorius studentui nuskaityti.
     */
    friend std::istream& operator>>(std::istream& in, Studentas& s);

    /**
     * @brief Išvesties operatorius studento duomenims atspausdinti.
     */
    friend std::ostream& operator<<(std::ostream& out, const Studentas& s);
};

/**
 * @brief Struktūra, kurioje saugomos dvi studentų grupės:
 * kietiakiai ir vargsiukai.
 */
struct StudentGroups {
    /// Studentai, kurių galutinis balas pakankamas.
    std::vector<Studentas> kietiakiai;
    /// Studentai, kurių galutinis balas per žemas.
    std::vector<Studentas> vargsiukai;
};

/**
 * @brief Palygina studentus pagal vardą (a–z).
 */
bool compare(const Studentas& a, const Studentas& b);

/**
 * @brief Palygina studentus pagal pavardę (a–z).
 */
bool comparePagalPavarde(const Studentas& a, const Studentas& b);

/**
 * @brief Palygina studentus pagal egzamino balą (nuo mažiausio).
 */
bool comparePagalEgza(const Studentas& a, const Studentas& b);
