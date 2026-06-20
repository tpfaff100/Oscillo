#include "OscillVector.h"

OscillVector::OscillVector(size_t initialCapacity) {
    data.reserve(initialCapacity);
}

void OscillVector::reserve(size_t capacity) {
    data.reserve(capacity);
}

void OscillVector::verifyIntegrity() const {
    for (const auto& oscill : data) {
        if (!oscill.isValid()) { // Assumes Oscill has isValid()
            throw std::runtime_error("Integrity check failed for Oscill object");
        }
    }
}

// Add an Oscill object with validation
void OscillVector::push_back(const Oscill& oscill) {
    if (!oscill.isValid()) {
        throw std::invalid_argument("Cannot add invalid Oscill object");
    }
    data.push_back(oscill);
    verifyIntegrity(); // Optional: Verify entire vector
}

// Access an element with bounds checking
Oscill& OscillVector::at(size_t index) {
    if (index >= data.size()) {
        throw std::out_of_range("Index out of bounds");
    }
    return data.at(index); // Uses vector's bounds-checked access
}

const Oscill& OscillVector::at(size_t index) const {
    if (index >= data.size()) {
        throw std::out_of_range("Index out of bounds");
    }
    return data.at(index);
}

// Modify an element with validation
void OscillVector::modify(size_t index, const Oscill& oscill) {
    if (!oscill.isValid()) {
        throw std::invalid_argument("Cannot assign invalid Oscill object");
    }
    if (index >= data.size()) {
        throw std::out_of_range("Index out of bounds");
    }
    data[index] = oscill;
    verifyIntegrity(); // Optional: Verify entire vector
}

// Other useful methods
size_t OscillVector::size() const {
    return data.size();
}

void OscillVector::clear() {
    data.clear();
}

