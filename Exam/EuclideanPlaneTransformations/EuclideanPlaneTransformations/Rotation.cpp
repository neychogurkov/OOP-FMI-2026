#include "Rotation.h"
#include "Matrix.hpp"
#include <cmath>
#include <numbers>

Rotation::Rotation(int degrees) : degrees(degrees)
{
}

Point Rotation::transform(const Point& point) const
{
	double rad = degrees * std::numbers::pi / 180.0;

	Matrix<double> m1(2, 2), m2(2, 1);
	m1[0][0] = std::cos(rad);
	m1[0][1] = -std::sin(rad);
	m1[1][0] = std::sin(rad);
	m1[1][1] = std::cos(rad);

	m2[0][0] = point.getX();
	m2[1][0] = point.getY();

	Matrix<double> m3 = m1 * m2;

	return Point(m3[0][0], m3[1][0]);
}

std::unique_ptr<Transformation> Rotation::clone() const {
	return std::make_unique<Rotation>(*this);
}
