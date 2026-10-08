#include "DynamicArray.h"

#include <iostream>
#include <stdexcept>

void DynamicArray::validateValue(int value) {
    if (value < -100 || value > 100) {
        throw std::out_of_range("Value must be in the range [-100, 100]");
    }
}

void DynamicArray::validateIndex(int index) const {
    if (index < 0 || index >= size_) {
        throw std::out_of_range("Array index is out of range");
    }
}

DynamicArray::DynamicArray(int size) : data_(nullptr), size_(size) {
    if (size < 0) {
        throw std::invalid_argument("Array size cannot be negative");
    }

    if (size_ > 0) {
        data_ = new int[size_]{};
    }
}

DynamicArray::DynamicArray(const DynamicArray& other)
    : data_(nullptr), size_(other.size_) {
    if (size_ > 0) {
        data_ = new int[size_];
        for (int i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }
}

DynamicArray::~DynamicArray() {
    delete[] data_;
}

void DynamicArray::set(int index, int value) {
    validateIndex(index);
    validateValue(value);
    data_[index] = value;
}

int DynamicArray::get(int index) const {
    validateIndex(index);
    return data_[index];
}

int DynamicArray::size() const {
    return size_;
}

void DynamicArray::print() const {
    std::cout << "{";
    for (int i = 0; i < size_; ++i) {
        if (i > 0) {
            std::cout << ", ";
        }
        std::cout << data_[i];
    }
    std::cout << "}\n";
}

void DynamicArray::append(int value) {
    validateValue(value);

    int* expanded = new int[size_ + 1];
    for (int i = 0; i < size_; ++i) {
        expanded[i] = data_[i];
    }
    expanded[size_] = value;

    delete[] data_;
    data_ = expanded;
    ++size_;
}

void DynamicArray::add(const DynamicArray& other) {
    for (int i = 0; i < size_; ++i) {
        const int otherValue = i < other.size_ ? other.data_[i] : 0;
        data_[i] += otherValue;
    }
}

void DynamicArray::subtract(const DynamicArray& other) {
    for (int i = 0; i < size_; ++i) {
        const int otherValue = i < other.size_ ? other.data_[i] : 0;
        data_[i] -= otherValue;
    }
}
