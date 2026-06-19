#pragma once
#include <vector>
#include "IncompatibleDimensionsException.h"
#include "InvalidMatrixIndexException.h"

template <typename T>
class Matrix {
private:
	size_t m;
	size_t n;

	std::vector<std::vector<T>> data;

public:
	Matrix(size_t m, size_t n);

	size_t getM() const;
	size_t getN() const;

	//friend Matrix<T> operator+(const Matrix& lhs, const Matrix& rhs);
	//friend Matrix<T> operator*(const Matrix& lhs, const Matrix& rhs);

	std::vector<T>& operator[](int index);
	const std::vector<T>& operator[](int index) const;
};

template<typename T>
Matrix<T>::Matrix(size_t m, size_t n) : m(m), n(n)
{
	data.resize(m);
	
	for (size_t i = 0; i < m; i++)
	{
		data[i].resize(n);
	}
}

template<typename T>
size_t Matrix<T>::getM() const
{
	return m;
}

template<typename T>
size_t Matrix<T>::getN() const
{
	return n;
}

template<typename T>
Matrix<T> operator+(const Matrix<T>& lhs, const Matrix<T>& rhs)
{
	size_t lhsM = lhs.getM();
	size_t lhsN = lhs.getN();
	size_t rhsM = rhs.getM();
	size_t rhsN = rhs.getN();

	if (lhsM != rhsM || lhsN != rhsN) {
		throw IncompatibleDimensionsException("Dimensions are not compatible.");
	}

	Matrix<T> res(lhsM, lhsN);

	for (size_t i = 0; i < lhsM; i++)
	{
		for (size_t j = 0; j < lhsN; j++)
		{
			res[i][j] = lhs[i][j] + rhs[i][j];
		}
	}

	return res;
}

template<typename T>
Matrix<T> operator*(const Matrix<T>& lhs, const Matrix<T>& rhs)
{
	size_t lhsM = lhs.getM();
	size_t lhsN = lhs.getN();
	size_t rhsM = rhs.getM();
	size_t rhsN = rhs.getN();

	if (lhsN != rhsM) {
		throw IncompatibleDimensionsException("Dimensions are not compatible.");
	}

	Matrix<T> res(lhsM, rhsN);

	for (size_t i = 0; i < lhsM; i++)
	{
		for (size_t j = 0; j < rhsN; j++)
		{
			for (size_t k = 0; k < lhsN; k++)
			{
				res[i][j] += lhs[i][k] * rhs[k][j];
			}
		}
	}

	return res;
}

template<typename T>
std::vector<T>& Matrix<T>::operator[](int index)
{
	if (index < 0 || index >= m) {
		throw InvalidMatrixIndexException("Invalid index.");
	}

	return data[index];
}

template<typename T>
const std::vector<T>& Matrix<T>::operator[](int index) const
{
	if (index < 0 || index >= m) {
		throw InvalidMatrixIndexException("Invalid index.");
	}

	return data[index];
}
