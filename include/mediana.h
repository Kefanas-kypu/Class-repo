#pragma once

#include <algorithm>
#include <numeric>
#include <vector>

inline double skaiciuotiVidurki(const std::vector<double>& paz) {
    if (paz.empty()) return 0.0;
    double suma = std::accumulate(paz.begin(), paz.end(), 0.0);
    return suma / paz.size();
}

inline double skaiciuotiMediana(std::vector<double> paz) {
    if (paz.empty()) return 0.0;
    std::sort(paz.begin(), paz.end());
    std::size_t vidurys = paz.size() / 2;
    if (paz.size() % 2 == 0)
        return (paz[vidurys - 1] + paz[vidurys]) / 2.0;
    return paz[vidurys];
}
