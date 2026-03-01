#include <iostream>

struct Triangle {
	double a;
	double b;
	double c;

	double calculatePerimeter() const {
		return a + b + c;
	}

	double calculateArea() const {
		double s = calculatePerimeter() / 2;
		return sqrt(s * (s - a) * (s - b) * (s - c));
	}

	const char* getTriangleType() const {
		if (a == b && a == c) {
			return "equilateral";
		}
		else if (a != b && a != c && b != c) {
			return "scalene";
		}
		else {
			return "isosceles";
		}
	}
};

bool isValidTriangle(double a, double b, double c) {
	return (a + b > c) && (a + c > b) && (b + c > a);
}

Triangle inputTriangle() {
	double a, b, c;

	while (true) {
		std::cout << "Enter a: ";
		std::cin >> a;
		std::cout << "Enter b: ";
		std::cin >> b;
		std::cout << "Enter c: ";
		std::cin >> c;

		if (isValidTriangle(a, b, c)) {
			break;
		}

		std::cout << "Invalid triangle! Please enter again." << std::endl;
	}

	return { a, b, c };
}

void printTriangle(const Triangle& triangle) {
	std::cout << "The triangle with sides a = " << triangle.a
			  << ", b = " << triangle.b
			  << ", c = " << triangle.c
			  << " is " << triangle.getTriangleType()
			  << " and has P = " << triangle.calculatePerimeter()
			  << " and S = " << triangle.calculateArea()
			  << std::endl;
}

int main() {
	Triangle triangle = inputTriangle();
	printTriangle(triangle);
}