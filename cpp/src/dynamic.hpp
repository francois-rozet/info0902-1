#ifndef DYNAMIC_H
#define DYNAMIC_H

#include "lcs.hpp"

#include <array>
#include <memory>

/***** Header *****/

/**
 * Computes, using dynamic programming, a longest common contiguous subsequence of X and Y.
 */
template <typename T>
triple dynamic_search(const std::vector<T>& X, const std::vector<T>& Y);

/***** Template implementation *****/

template <typename T>
triple dynamic_search(const std::vector<T>& X, const std::vector<T>& Y) {
    size_t N = X.size() + 1, M = Y.size() + 1;
    std::unique_ptr<size_t[]> C = std::make_unique<size_t[]>(N * M);

    size_t l = 0, i_end, j_end;

    for (size_t i = 0; i < N; i++)
        for (size_t j = 0, k = i * M; j < M; j++, k++)
            if (i != 0 and j != 0 and X[i - 1] == Y[j - 1]) {
                C[k] = C[k - M - 1] + 1;

                if (C[k] > l) {
                    l = C[k];
                    i_end = i - 1;
                    j_end = j - 1;
                }
            } else
                C[k] = 0;

    if (l != 0)
        return std::make_tuple(l, i_end - l + 1, j_end - l + 1);

    return std::make_tuple(0, 0, 0);
}

#endif
