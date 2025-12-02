/**
 * @file Zmogus.h
 * @brief Aprašo abstrakčią bazinę klasę Zmogus, kurią paveldi Studentas.
 */

#pragma once

#include <string>
#include <iostream>

/**
 * @brief Abstrakti žmogaus klasė su vardu ir pavarde.
 *
 * Ši klasė naudojama kaip bazinė klase kitoms konkrečioms esybėms (pvz., Studentas).
 */
class Zmogus {
protected:
    std::string vardas_;
    std::string pavarde_;

public:
    Zmogus() = default;

    /**
     * @brief Konstruktorius su parametrais.
     * @param vardas Žmogaus vardas.
     * @param pavarde Žmogaus pavarde.
     */
    Zmogus(const std::string& vardas, const std::string& pavarde)
        : vardas_(vardas), pavarde_(pavarde) {}

    Zmogus(const Zmogus&) = default;
    Zmogus& operator=(const Zmogus&) = default;

    virtual ~Zmogus() = default;

    /**
     * @brief Grąžina žmogaus vardą.
     * @return Vardo konstanta nuoroda.
     */
    virtual const std::string& vardas() const = 0;

    /**
     * @brief Grąžina žmogaus pavardę.
     * @return Pavardės konstanta nuoroda.
     */
    virtual const std::string& pavarde() const = 0;

    /**
     * @brief Spausdina informaciją apie objektą.
     */
    virtual void info() const = 0;
};
