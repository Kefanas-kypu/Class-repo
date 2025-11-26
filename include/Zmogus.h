#pragma once

#include <string>
#include <iostream>

class Zmogus {
protected:
    std::string vardas_;
    std::string pavarde_;

public:
    Zmogus() = default;

    Zmogus(const std::string& vardas, const std::string& pavarde)
        : vardas_(vardas), pavarde_(pavarde) {}

    Zmogus(const Zmogus&) = default;
    Zmogus& operator=(const Zmogus&) = default;

    virtual ~Zmogus() = default;

    virtual const std::string& vardas() const = 0;
    virtual const std::string& pavarde() const = 0;

    virtual void info() const = 0;
};
