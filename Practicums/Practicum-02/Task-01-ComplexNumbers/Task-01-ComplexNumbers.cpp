#include <iostream>

struct ComplexNumber {
	double real;
	double imaginary;
};

ComplexNumber sumComplexNumbers(const ComplexNumber& num1, const ComplexNumber& num2) {
	double real = num1.real + num2.real;
	double imaginary = num1.imaginary + num2.imaginary;

	return { real, imaginary };
}

ComplexNumber multiplyComplexNumbers(const ComplexNumber& num1, const ComplexNumber& num2) {
	double real = num1.real * num2.real - num1.imaginary * num2.imaginary;
	double imaginary = num1.real * num2.imaginary + num1.imaginary * num2.real;

	return { real, imaginary };
}

void printComplexNumber(const ComplexNumber& num) {
	std::cout << num.real << " ";

	if (num.imaginary > 0) {
		std::cout << "+ " << num.imaginary;
	}
	else {
		std::cout << "- " << -num.imaginary;
	}

	std::cout << "i" << std::endl;
}

int main() {
	ComplexNumber num1 = { 4, -2 };
	ComplexNumber num2 = { -3, 5 };

	ComplexNumber sum = sumComplexNumbers(num1, num2);
	ComplexNumber product = multiplyComplexNumbers(num1, num2);

	std::cout << "First number: ";
	printComplexNumber(num1);

	std::cout << "Second number: ";
	printComplexNumber(num2);

	std::cout << "Sum: ";
	printComplexNumber(sum);

	std::cout << "Product: ";
	printComplexNumber(product);
}