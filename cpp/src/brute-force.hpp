#ifndef BRUTE_FORCE_H
#define BRUTE_FORCE_H

#include "lcs.hpp"

#include <cassert>

/***** Header *****/

/**
 * Computes, using brute force, a longest common contiguous subsequence of X and Y.
 */
template <typename T>
triple brute_force_search(const std::vector<T>& X, const std::vector<T>& Y);

/**
 * Computes, using brute force, a common contiguous subsequence of length l of X and Y.
 */
template <typename T>
triple brute_force_aux(const std::vector<T>& X, const std::vector<T>& Y, size_t l);

/***** Template implementation *****/

template <typename T>
triple brute_force_search(const std::vector<T>& X, const std::vector<T>& Y) {
    triple t;

    size_t l = X.size() < Y.size() ? X.size() : Y.size();

    while (l > 0) {
        t = brute_force_aux<T>(X, Y, l);

        if (std::get<0>(t) > 0)
            return t;

        l--;
    }

    return t;
}

template <typename T>
triple brute_force_aux(const std::vector<T>& X, const std::vector<T>& Y, size_t l) {
    assert(X.size() >= l);
    assert(Y.size() >= l);

    for (size_t i = 0; i < X.size() - l + 1; i++)
        for (size_t j = 0; j < Y.size() - l + 1; j++) {
            size_t k;

            for (k = 0; k < l and X[i + k] == Y[j + k]; k++);

            if (k == l)
                return std::make_tuple(l, i, j);
        }

    return std::make_tuple(0, 0, 0);
}

#endif
