#include "TransformationPipeline.h"
#include "TransformationException.h"

void TransformationPipeline::copyFrom(const TransformationPipeline& other) {
	for (const auto& t : other.transformations) {
		transformations.push_back(t->clone());
	}
}

TransformationPipeline::TransformationPipeline(const TransformationPipeline& other) {
	copyFrom(other);
}

TransformationPipeline& TransformationPipeline::operator=(const TransformationPipeline& other) {
	if (this != &other) {
		transformations.clear();
		transformations.reserve(other.transformations.size());
		copyFrom(other);
	}

	return *this;
}

void TransformationPipeline::add(const Transformation& transformation) {
	transformations.push_back(transformation.clone());
}

void TransformationPipeline::remove(int index)
{
	if (index < 0 || index >= transformations.size()) {
		throw TransformationException("Invalid index.");
	}

	transformations.erase(transformations.begin() + index);
}

Point TransformationPipeline::applyTransformations(const Point& point) const
{
	Point res(point);

	for (const auto& t : transformations) {
		res = t->transform(res);
	}

	return res;
}

Transformation& TransformationPipeline::operator[](int index) {
	if (index < 0 || index >= transformations.size()) {
		throw TransformationException("Invalid index.");
	}

	return *transformations[index];
}

const Transformation& TransformationPipeline::operator[](int index) const {
	if (index < 0 || index >= transformations.size()) {
		throw TransformationException("Invalid index.");
	}

	return *transformations[index];
}

size_t TransformationPipeline::size() const {
	return transformations.size();
}
