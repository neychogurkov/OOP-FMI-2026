#pragma once
#include "Transformation.h"

class Translation : public Transformation
{
	double v1;
	double v2;

public:
	Translation(double v1, double v2);

	Point transform(const Point& point) const override;

	std::unique_ptr<Transformation> clone() const override;
};

