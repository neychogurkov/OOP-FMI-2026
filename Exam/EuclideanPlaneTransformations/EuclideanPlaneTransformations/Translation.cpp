#include "Translation.h"
#include "Matrix.hpp"

Translation::Translation(double v1, double v2) : v1(v1), v2(v2) {
}

Point Translation::transform(const Point& point) const {
	Matrix<double> m1(2, 1), m2(2, 1);
	m1[0][0] = point.getX();
	m1[1][0] = point.getY();

	m2[0][0] = v1;
	m2[1][0] = v2;

	Matrix<double> m3 = m1 + m2;

	return Point(m3[0][0], m3[1][0]);
}

std::unique_ptr<Transformation> Translation::clone() const {
	return std::make_unique<Translation>(*this);
}
