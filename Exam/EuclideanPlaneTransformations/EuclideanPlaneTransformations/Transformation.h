#pragma once
#include "Point.h"
#include <memory>

class Transformation
{
public:
	virtual ~Transformation() = default;

	virtual Point transform(const Point&) const = 0;

	virtual std::unique_ptr<Transformation> clone() const = 0;
};

