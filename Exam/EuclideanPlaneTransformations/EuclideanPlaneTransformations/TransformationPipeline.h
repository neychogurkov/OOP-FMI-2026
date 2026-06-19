#pragma once
#include <vector>
#include "Transformation.h"
#include <memory>

class TransformationPipeline
{
	std::vector<std::unique_ptr<Transformation>> transformations;
	
	void copyFrom(const TransformationPipeline& other);

public:
	TransformationPipeline() = default;

	TransformationPipeline(const TransformationPipeline& other);
	TransformationPipeline& operator=(const TransformationPipeline& other);
	
	TransformationPipeline(TransformationPipeline&&) = default;
	TransformationPipeline& operator=(TransformationPipeline&&) = default;
	
	~TransformationPipeline() = default;

	void add(const Transformation& transformation);
	void remove(int index);
	Point applyTransformations(const Point& point) const;
	
	Transformation& operator[](int index);
	const Transformation& operator[](int index) const;

	size_t size() const;
};

