#include <iostream>
#include "Matrix.hpp"
#include "TransformationPipeline.h"
#include "Translation.h"
#include "Rotation.h"
#include "TransformationException.h"

int main()
{
	Matrix<double> m1(2, 2), m2(2, 2);
	m1[0][0] = 1; m1[0][1] = 2;
	m1[1][0] = 3; m1[1][1] = 4;
	m2[0][0] = 5; m2[0][1] = 6;
	m2[1][0] = 7; m2[1][1] = 8;

	Matrix<double> sum = m1 + m2;
	Matrix<double> prod = m1 * m2;
	
	std::cout << "m1[0][0]=" << m1[0][0] << "\n";
	std::cout << "m1[0][1]=" << m1[0][1] << "\n";
	std::cout << "m1[1][0]=" << m1[1][0] << "\n";
	std::cout << "m1[1][1]=" << m1[1][1] << "\n";

	std::cout << "m2[0][0]=" << m2[0][0] << "\n";
	std::cout << "m2[0][1]=" << m2[0][1] << "\n";
	std::cout << "m2[1][0]=" << m2[1][0] << "\n";
	std::cout << "m2[1][1]=" << m2[1][1] << "\n";


	std::cout << "sum[0][0]=" << sum[0][0] << "\n";
	std::cout << "sum[0][1]=" << sum[0][1] << "\n";
	std::cout << "sum[1][0]=" << sum[1][0] << "\n";
	std::cout << "sum[1][1]=" << sum[1][1] << "\n";
	
	std::cout << "prod[0][0]=" << prod[0][0] << "\n";
	std::cout << "prod[0][1]=" << prod[0][1] << "\n";
	std::cout << "prod[1][0]=" << prod[1][0] << "\n";
	std::cout << "prod[1][1]=" << prod[1][1] << "\n";

	TransformationPipeline pipeline;
	pipeline.add(Translation(1.0, 2.0));
	pipeline.add(Rotation(90));

	Point p(1.0, 0.0);
	Point result = pipeline.applyTransformations(p);

	std::cout << "After translation and rotation: (" << result.getX() << ", " << result.getY() << ")\n";

	std::cout << "Number of transformations: " << pipeline.size() << "\n";

	TransformationPipeline copy = pipeline;

	copy.add(Rotation(45));
	std::cout << "Original: " << pipeline.size() << ", copy: " << copy.size() << "\n";

	pipeline.remove(0);

	Point afterRemove = pipeline.applyTransformations(p);

	std::cout << "After remove(0): (" << afterRemove.getX() << ", " << afterRemove.getY() << ")\n";

	try {
		Matrix<double> bad1(2, 2), bad2(3, 3);
		Matrix<double> bad = bad1 + bad2;
	}
	catch (const IncompatibleDimensionsException& e) {
		std::cout << "Caught: " << e.what() << "\n";
	}

	try {
		pipeline.remove(99);
	}
	catch (const TransformationException& e) {
		std::cout << "Caught: " << e.what() << "\n";
	}

	return 0;
}