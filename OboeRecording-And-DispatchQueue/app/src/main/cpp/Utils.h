//
// Created by remy on 26/4/20.
//

#ifndef UTILS_H
#define UTILS_H

#include <logging_macros.h>
#include <cmath>
#include <vector>
#include <array>
#include "macros.h"

class Utils {

public:
    static std::shared_ptr<std::vector<double>> generateNormalizedHammingWindow();

    static std::shared_ptr<std::vector<double>> extractSample(const std::array<float, __NUM_SAMPLES__> &);

    static std::shared_ptr<std::vector<double>> windowedTheSignal(
            const std::shared_ptr<std::vector<double>> &,
            const std::shared_ptr<std::vector<double>> &);

    static bool isPower2(int n);

    static const char *writeInString(const std::shared_ptr<std::vector<double>> &);
    static const char *writeInString(const std::array<float, __NUM_SAMPLES__> &);

};

#endif //UTILS_H