#pragma once

#include "Vec.hpp"
#include "Mat.hpp"

#include <algorithm>

namespace numa {

	class GaussElimSolver {
	public:
		// Functions invoked by the user.
	private:
		// Hide helper functions.
	};

	template<typename T, int M, int N>
	Vec<T, N> SolveAxb(const Mat<T, M, N>& A, const Vec<T, M>& b) {
		Vec<T, N> x{};
		int minDim = std::min(M, N);
		// 1. Forward elimination.
		for (int i = 0; i < minDim; i++) {
			// Recall, that the indexing scheme is '[col][row]'.
			if (A[i][i])
		}
		// 2. Back substitution.
		return x;
	}

}