#include <iostream>
#include <cmath>

namespace Constants {
	const size_t MAX_COEFFS_COUNT = 20;
}

struct Polynomial {
	double coeffs[Constants::MAX_COEFFS_COUNT] = { 0.0 };
	size_t degree = 0;


	double calculateValue(double x) {
		double result = 0;

		for (size_t i = 0; i <= degree; i++) {
			result += coeffs[i] * pow(x, i);
		}

		return result;
	}

	void printPolynomial() {
		for (int i = degree; i >= 1; i--) {
			if (coeffs[i] == 0) {
				continue;
			}

			std::cout << coeffs[i] << "x^" << i << " + ";
		}

		std::cout << coeffs[0] << "x^0" << std::endl;
	}
};

Polynomial createPolynomial(const double* coeffs, size_t degree) {
	Polynomial polynomial{};

	if (degree >= Constants::MAX_COEFFS_COUNT || !coeffs) {
		std::cout << "Invalid input!";
		return polynomial;
	}

	polynomial.degree = degree;

	for (size_t i = 0; i <= degree; i++) {
		polynomial.coeffs[i] = coeffs[i];
	}

	return polynomial;
}

Polynomial sumPolynomials(const Polynomial& p1, const Polynomial& p2) {
	Polynomial result{};

	size_t minDegree;

	if (p1.degree < p2.degree) {
		minDegree = p1.degree;
		result.degree = p2.degree;
	}
	else {
		minDegree = p2.degree;
		result.degree = p1.degree;
	}

	for (size_t i = 0; i <= minDegree; i++) {
		result.coeffs[i] = p1.coeffs[i] + p2.coeffs[i];
	}

	for (size_t i = minDegree + 1; i <= p1.degree; i++) {
		result.coeffs[i] = p1.coeffs[i];
	}

	for (size_t i = minDegree + 1; i <= p2.degree; i++) {
		result.coeffs[i] = p2.coeffs[i];
	}

	return result;
}

Polynomial subtractPolynomials(const Polynomial& p1, const Polynomial& p2) {
	Polynomial result{};

	size_t minDegree;

	if (p1.degree < p2.degree) {
		minDegree = p1.degree;
		result.degree = p2.degree;
	}
	else {
		minDegree = p2.degree;
		result.degree = p1.degree;
	}

	for (size_t i = 0; i <= minDegree; i++) {
		result.coeffs[i] = p1.coeffs[i] - p2.coeffs[i];
	}

	for (size_t i = minDegree + 1; i <= p1.degree; i++) {
		result.coeffs[i] = p1.coeffs[i];
	}

	for (size_t i = minDegree + 1; i <= p2.degree; i++) {
		result.coeffs[i] = -p2.coeffs[i];
	}

	return result;
}

Polynomial multiplyPolynomials(const Polynomial& p1, const Polynomial& p2) {
	Polynomial result{};
	result.degree = p1.degree + p2.degree;

	if (result.degree >= Constants::MAX_COEFFS_COUNT) {
		std::cout << "Cannot multiply these two polynomials." << std::endl;
		return result;
	}

	for (size_t i = 0; i <= p1.degree; i++) {
		for (size_t j = 0; j <= p2.degree; j++) {
			result.coeffs[i + j] += p1.coeffs[i] * p2.coeffs[j];
		}
	}

	return result;
}

int main() {
	Polynomial p1 = { {-2, 6}, 1 };
	Polynomial p2 = { {4, -3.2, 3, 0}, 3 };
	p1.printPolynomial();
	p2.printPolynomial();
	Polynomial sum = sumPolynomials(p1, p2);
	sum.printPolynomial();
	Polynomial subtraction = subtractPolynomials(p1, p2);
	subtraction.printPolynomial();
	Polynomial product = multiplyPolynomials(p1, p2);
	product.printPolynomial();
}