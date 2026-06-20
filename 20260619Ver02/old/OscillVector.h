#ifndef OSCILL_VECTOR_H
#define OSCILL_VECTOR_H

#include <vector>
#include <stdexcept>
#include "Oscill.h" // Include the Oscill class definition

class OscillVector {
private:
    std::vector<Oscill> data;
    void verifyIntegrity() const;

public:
	explicit OscillVector(size_t initialCapacity);
	void reserve(size_t capacity);
	
	void push_back(const Oscill& oscill);
	Oscill& at(size_t index);
	const Oscill& at(size_t index) const;
	void modify(size_t index, const Oscill& oscill);
	size_t size() const;
	void clear();

	    // Iterator support
	using iterator = std::vector<Oscill>::iterator;
	using const_iterator = std::vector<Oscill>::const_iterator;
	iterator begin() { return data.begin(); }
	iterator end() { return data.end(); }
	const_iterator begin() const { return data.begin(); }
	const_iterator end() const { return data.end(); }
};

#endif // OSCILL_VECTOR_H
