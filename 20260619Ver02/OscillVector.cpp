#include "OscillVector.h"

OscillVector::OscillVector(const std::vector<Oscill>& input) {
    for (const auto& oscill : input) {
        push_back(oscill);
    }
}

void OscillVector::initialize(const std::vector<Oscill>& input) {
    for (const auto& oscill : input) {
        push_back(oscill);
    }
}

void OscillVector::verifyIntegrity() const {
    for (const auto& oscill : data) {
        if (!oscill.isValid()) {
            throw std::runtime_error("Integrity check failed for Oscill object");
        }
    }
}

void OscillVector::push_back(const Oscill& oscill) {
    if (!oscill.isValid()) {
        throw std::invalid_argument("Cannot add invalid Oscill object");
    }
    data.push_back(oscill);
    verifyIntegrity();
}

Oscill& OscillVector::at(size_t index) {
    if (index >= data.size()) {
        throw std::out_of_range("Index out of bounds");
    }
    return data.at(index);
}

const Oscill& OscillVector::at(size_t index) const {
    if (index >= data.size()) {
        throw std::out_of_range("Index out of bounds");
    }
    return data.at(index);
}

void OscillVector::modify(size_t index, const Oscill& oscill) {
    if (!oscill.isValid()) {
        throw std::invalid_argument("Cannot assign invalid Oscill object");
    }
    if (index >= data.size()) {
        throw std::out_of_range("Index out of bounds");
    }
    data[index] = oscill;
    verifyIntegrity();
}

size_t OscillVector::size() const {
    return data.size();
}

void OscillVector::clear() {
    data.clear();
}
