#include "Bitset.h"
#include <algorithm>

void Bitset::copyFrom(const Bitset& other) {
	maxN = other.maxN;
	bucketsCount = other.bucketsCount;
	data = new uint8_t[bucketsCount];

	for (int i = 0; i < bucketsCount; i++) {
		data[i] = other.data[i];
	}
}

void Bitset::free() {
	delete[] data;
	data = nullptr;
	maxN = 0;
	bucketsCount = 0;
}

unsigned Bitset::getBucketIndex(unsigned n) const {
	return n / elementsInBucket;
}

unsigned Bitset::getBitIndex(unsigned n) const {
	return n % elementsInBucket;
}

Bitset::Bitset(unsigned n) {
	this->maxN = n;
	this->bucketsCount = this->maxN / elementsInBucket + 1;
	this->data = new uint8_t[bucketsCount];
}

Bitset::Bitset(const Bitset& other) {
	copyFrom(other);
}

Bitset& Bitset::operator=(const Bitset& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

Bitset::~Bitset() {
	free();
}

void Bitset::add(unsigned n) {
	if (n > maxN) {
		return;
	}

	unsigned bucketIndex = getBucketIndex(n);
	unsigned bitIndex = getBitIndex(n);

	uint8_t mask = 1 << bitIndex;

	data[bucketIndex] |= mask;
}

void Bitset::remove(unsigned n) {
	if (n > maxN) {
		return;
	}

	unsigned bucketIndex = getBucketIndex(n);
	unsigned bitIndex = getBitIndex(n);

	uint8_t mask = 1 << bitIndex;

	data[bucketIndex] &= (~mask);
}

bool Bitset::contains(unsigned n) const {
	if (n > maxN) {
		return;
	}

	unsigned bucketIndex = getBucketIndex(n);
	unsigned bitIndex = getBitIndex(n);

	uint8_t mask = 1 << bitIndex;

	return data[bucketIndex] & mask;
}

unsigned Bitset::getN() const {
	return maxN;
}

Bitset Bitset::intersectionSets(const Bitset& lhs, const Bitset& rhs) {
	Bitset res(std::min(lhs.getN(), rhs.getN()));

	for (int i = 0; i < res.bucketsCount; i++) {
		res.data[i] = lhs.data[i] & rhs.data[i];
	}

	return res;
}

Bitset Bitset::unionSets(const Bitset& lhs, const Bitset& rhs) {
	Bitset res(std::max(lhs.getN(), rhs.getN()));

	unsigned minBucketsCount = std::min(lhs.bucketsCount, rhs.bucketsCount);

	for (unsigned i = 0; i < minBucketsCount; i++) {
		res.data[i] = lhs.data[i] | rhs.data[i];
	}

	const Bitset& bigger = lhs.getN() > rhs.getN() ? lhs : rhs;

	for (unsigned i = minBucketsCount; i < bigger.bucketsCount; i++) {
		res.data[i] = bigger.data[i];
	}

	return res;
}
