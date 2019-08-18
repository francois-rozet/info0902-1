#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#define REQUIRES(...) typename std::enable_if<(__VA_ARGS__), int>::type = 0

#include "lcs.hpp"

#include <cassert>
#include <cmath>
#include <unordered_map>

/***** Header *****/

/**
 * Computes, using an hash table, a longest common contiguous subsequence of X and Y.
 */
template<class T, REQUIRES(std::is_integral<T>())>
triple hash_table_search(const std::vector<T>& X, const std::vector<T>& Y, int base);

/**
 * Computes, using an hash table, a common contiguous subsequence of length l of X and Y.
 */
template<class T, REQUIRES(std::is_integral<T>())>
triple hash_table_aux(const std::vector<T>& X, const std::vector<T>& Y, int base, size_t l);

/**
 * Encodes a subsequence of a sequence.
 */
template<class T, REQUIRES(std::is_integral<T>())>
uintmax_t encode(const std::vector<T>& X, size_t i, int base, size_t l);

/***** Template implementation *****/

template<class T, REQUIRES(std::is_integral<T>())>
triple hash_table_search(const std::vector<T>& X, const std::vector<T>& Y, int base) {
    triple t, temp;

    size_t p = 1, r = X.size() > Y.size() ? X.size() : Y.size(), q;

    while (p <= r) {
        q = (p + r) / 2;

        temp = hash_table_aux<T>(X, Y, base, q);

        if (std::get<0>(temp) == 0)
            r = q - 1;
        else {
            t = temp;
            p = q + 1;
        }
    }

    return t;
}

template<class T, REQUIRES(std::is_integral<T>())>
triple hash_table_aux(const std::vector<T>& X, const std::vector<T>& Y, int base, size_t l) {
    assert(X.size() >= l);
    assert(Y.size() >= l);

    std::unordered_map<uintmax_t, size_t> H(X.size() - l + 1);

    uintmax_t p = pow(base, l - 1);

    uintmax_t f = encode<T>(X, 0, base, l);
    H[f] = 0;
    for (size_t i = 1; i < X.size() - l + 1; i++) {
        f = (f - X[i - 1] * p) * base + X[i + l - 1];
        H[f] = i;
    }

    f = encode<T>(Y, 0, base, l);
    if (H.count(f) > 0)
        return std::make_tuple(l, H[f], 0);
    for (size_t j = 1; j < Y.size() - l + 1; j++) {
        f = (f - Y[j - 1] * p) * base + Y[j + l - 1];
        if (H.count(f) > 0)
            return std::make_tuple(l, H[f], j);
    }

    return std::make_tuple(0, 0, 0);
}

template<class T, REQUIRES(std::is_integral<T>())>
uintmax_t encode(const std::vector<T>& X, size_t i, int base, size_t l) {
    assert(X.size() >= i + l);

    uintmax_t f = 0;

    for (size_t j = 0; j < l; j++)
        f = f * base + X[i + j];

    return f;
}

#endif
