#ifndef OSCILL_VECTOR_H
#define OSCILL_VECTOR_H

#include <deque>
#include <stdexcept>
#include <vector>
#include "Oscill.h"

class OscillVector {
private:
    std::deque<Oscill> data;
    void verifyIntegrity() const;

public:
    OscillVector() = default;
    explicit OscillVector(const std::vector<Oscill>& input);
    void initialize(const std::vector<Oscill>& input);
    void push_back(const Oscill& oscill);
    Oscill& at(size_t index);
    const Oscill& at(size_t index) const;
    void modify(size_t index, const Oscill& oscill);
    size_t size() const;
    void clear();

    using iterator = std::deque<Oscill>::iterator;
    using const_iterator = std::deque<Oscill>::const_iterator;
    iterator begin() { return data.begin(); }
    iterator end() { return data.end(); }
    const_iterator begin() const { return data.begin(); }
    const_iterator end() const { return data.end(); }
};

#endif // OSCILL_VECTOR_H
