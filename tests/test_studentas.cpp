/**
 * @file test_studentas.cpp
 * @brief Pagrindiniai unit testai Studentas ir suskirstytiStudentus funkcijoms.
 */

#include <vector>
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "Studentas.h"
#include "Funkcijos.h"

using Catch::Approx;

TEST_CASE("Studento galutinis balas skaiciuojamas pagal vidurki", "[Studentas]") {
    Studentas s;
    s.setVardas("Jonas");
    s.setPavarde("Jonaitis");
    s.setNd({10.0, 8.0, 6.0});
    s.setEgzaminas(9.0);

    double expected_nd_avg = Studentas::vidurkis({10.0, 8.0, 6.0});
    double expected = 0.4 * expected_nd_avg + 0.6 * 9.0;

    REQUIRE(s.galBalas(Studentas::vidurkis) == Approx(expected));
}

TEST_CASE("Studentai teisingai suskirstomi i kietiakius ir vargsiukus", "[suskirstytiStudentus]") {
    Studentas geras;
    geras.setVardas("Geras");
    geras.setPavarde("Studentas");
    geras.setNd({8.0, 9.0, 10.0});
    geras.setEgzaminas(9.0);

    Studentas blogas;
    blogas.setVardas("Blogas");
    blogas.setPavarde("Studentas");
    blogas.setNd({2.0, 3.0, 4.0});
    blogas.setEgzaminas(3.0);

    std::vector<Studentas> grupe = {geras, blogas};

    StudentGroups groups = suskirstytiStudentus(grupe);

    REQUIRE(groups.kietiakiai.size() == 1);
    REQUIRE(groups.vargsiukai.size() == 1);
    REQUIRE(groups.kietiakiai[0].vardas() == "Geras");
    REQUIRE(groups.vargsiukai[0].vardas() == "Blogas");
}
