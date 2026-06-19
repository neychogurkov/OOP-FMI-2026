#pragma once
#include "Point.h"
#include "Transformation.h"

class Rotation : public Transformation
{
	int degrees;

public:
	Rotation(int degrees);

	Point transform(const Point& point) const override;

	std::unique_ptr<Transformation> clone() const override;
};

