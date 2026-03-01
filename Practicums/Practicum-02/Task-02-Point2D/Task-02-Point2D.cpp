#include <iostream>
#include <cmath>

struct Point {
	double x;
	double y;
};

Point inputPoint() {
	double x, y;
	std::cout << "Enter value for x: ";
	std::cin >> x;
	std::cout << "Enter value for y: ";
	std::cin >> y;

	return { x, y };
}

void printPoint(const Point& point) {
	std::cout << "(" << point.x << ", " << point.y << ")" << std::endl;
}

double getDistance(const Point& p1, const Point& p2) {
	return sqrt(pow(p2.x - p1.x, 2) + pow((p2.y - p1.y), 2));
}

int main() {
	Point point1 = inputPoint();
	Point point2 = inputPoint();
	printPoint(point1);
	printPoint(point2);
	std::cout << "Distance between points: " << getDistance(point1, point2);
}