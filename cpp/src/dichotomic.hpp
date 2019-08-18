#ifndef DICHOTOMIC_H
#define DICHOTOMIC_H

#include "lcs.hpp"
#include "brute-force.hpp"

/***** Header *****/

/**
 * Computes, using dichotomic search, a longest common contiguous subsequence of X and Y.
 */
template <typename T>
triple dichotomic_search(const std::vector<T>& X, const std::vector<T>& Y);

/***** Template implementation *****/

template <typename T>
triple dichotomic_search(const std::vector<T>& X, const std::vector<T>& Y) {
    triple t, temp;

    size_t p = 1, r = X.size() < Y.size() ? X.size() : Y.size(), q;

    while (p <= r) {
        q = (p + r) / 2;

        temp = brute_force_aux<T>(X, Y, q);

        if (std::get<0>(temp) == 0)
            r = q - 1;
        else {
            t = temp;
            p = q + 1;
        }
    }

    return t;
}

#endif
