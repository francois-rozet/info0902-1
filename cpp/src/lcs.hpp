#ifndef LCS_H
#define LCS_H

#include <tuple>
#include <vector>

typedef std::tuple<size_t, size_t, size_t> triple;

/**
 * States if the subsequences of length l starting in X[i] and Y[j] are equivalent.
 */
template <typename T>
bool isCommon(const std::vector<T>& X, const std::vector<T>& Y, size_t l, size_t i, size_t j) {
	size_t k;

	for (k = 0; k < l and X[i + k] == Y[j + k]; k++);

	if (k == l)
		return true;
	return false;
}

#endif
