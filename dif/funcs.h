#pragma once

#include<iostream>
#include<array>
#include<eigen-3.4.0\Eigen\Dense>

 
template<typename RealType, unsigned int N>
struct DerivativeCoef {
	RealType centralCoef;
	std::array<RealType, N> otherCoeffs;
};

template<typename RealType, unsigned int N>
DerivativeCoef<RealType, N>
calcDerivativeCoef(const std::array<RealType, N>& points) noexcept {
	Eigen::Matrix<RealType, N + 1, N + 1> A;

	for (unsigned int i = 0; i <= N; i++) {
		A(0, i) = 1;
	}

	for (unsigned int i = 1; i <= N; i++) {
		A(i, 0) = 0;
		for (unsigned int j = 1; j <= N; j++) {
			A(i, j) = A(i - 1, j) * points[j - 1];
		}
	}

	Eigen::Matrix<RealType, N + 1, 1> b = Eigen::Matrix<RealType, N + 1, 1>::Zero();
	b(1) = 1;

	Eigen::Vector<RealType, N + 1> c = A.colPivHouseholderQr().solve(b);

	RealType centralCoef = c(0);

	std::array<RealType, N> coefs;
	for (unsigned int i = 0; i < N; i++) {
		coefs[i] = c(i + 1);
	}

	return DerivativeCoef<RealType, N>{ centralCoef, coefs};
}

template<typename RealType, unsigned int N>
RealType d_e(const RealType x0, const RealType h, const std::array<RealType, N>& points) {
	DerivativeCoef<double, N> coefs = calcDerivativeCoef<RealType, N>(points);

	RealType de_x0 = coefs.centralCoef * exp(x0) / h;
	for (unsigned int i = 0; i < N; i++) {
		de_x0 += coefs.otherCoeffs[i] * exp(x0 + points[i] * h) / h;
	}

	return de_x0;
}
