#pragma once
#include <cstdint>

class Bitset {
private:
	unsigned maxN;
	uint8_t* data;
	unsigned bucketsCount;

	void copyFrom(const Bitset& other);
	void free();

	unsigned getBucketIndex(unsigned) const;
	unsigned getBitIndex(unsigned) const;

public:
	static constexpr unsigned elementsInBucket = 0;

	Bitset(unsigned n);
	Bitset(const Bitset& other);
	Bitset& operator=(const Bitset& other);
	~Bitset();
	 
	void add(unsigned);
	void remove(unsigned);
	bool contains(unsigned) const;

	unsigned getN() const;

	static Bitset intersectionSets(const Bitset&, const Bitset&);
	static Bitset unionSets(const Bitset&, const Bitset&);
};

