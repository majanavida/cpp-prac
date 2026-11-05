#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <typeinfo>
#include <type_traits>

template <typename T>
class DynamicArray {
private:
    T* data_;
    int size_;

    static void validateValue(const T& value) {
        if constexpr (std::is_integral_v<T>) {
            if (value < -100 || value > 100) {
                throw std::invalid_argument("Value must be in the range [-100, 100]");
            }
        }
    }

    void validateIndex(int index) const {
        if (index < 0 || index >= size_) {
            throw std::out_of_range("Array index is out of range");
        }
    }

public:
    class ElementReference {
    private:
        DynamicArray& array_;
        int index_;

    public:
        ElementReference(DynamicArray& array, int index) : array_(array), index_(index) {}

        operator T() const {
            return array_.get(index_);
        }

        ElementReference& operator=(const T& value) {
            array_.set(index_, value);
            return *this;
        }
    };

    explicit DynamicArray(int size) : data_(nullptr), size_(size) {
        if (size < 0) {
            throw std::invalid_argument("Array size cannot be negative");
        }
        if (size_ > 0) {
            data_ = new T[size_]{};
        }
    }

    DynamicArray(const DynamicArray& other) : data_(nullptr), size_(other.size_) {
        if (size_ > 0) {
            data_ = new T[size_];
            for (int i = 0; i < size_; ++i) {
                data_[i] = other.data_[i];
            }
        }
    }

    DynamicArray& operator=(const DynamicArray& other) = delete;

    ~DynamicArray() {
        delete[] data_;
    }

    void set(int index, const T& value) {
        validateIndex(index);
        validateValue(value);
        data_[index] = value;
    }

    T get(int index) const {
        validateIndex(index);
        return data_[index];
    }

    int size() const {
        return size_;
    }

    ElementReference operator[](int index) {
        validateIndex(index);
        return ElementReference(*this, index);
    }

    const T& operator[](int index) const {
        validateIndex(index);
        return data_[index];
    }

    bool operator==(const DynamicArray& other) const {
        if (size_ != other.size_) {
            return false;
        }
        for (int i = 0; i < size_; ++i) {
            if (data_[i] != other.data_[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const DynamicArray& other) const {
        return !(*this == other);
    }

    DynamicArray& operator+=(const DynamicArray& other) {
        for (int i = 0; i < size_; ++i) {
            const T otherValue = i < other.size_ ? other.data_[i] : T{};
            const T result = data_[i] + otherValue;
            validateValue(result);
            data_[i] = result;
        }
        return *this;
    }

    DynamicArray& operator-=(const DynamicArray& other) {
        for (int i = 0; i < size_; ++i) {
            const T otherValue = i < other.size_ ? other.data_[i] : T{};
            const T result = data_[i] - otherValue;
            validateValue(result);
            data_[i] = result;
        }
        return *this;
    }

    DynamicArray& operator+=(const T& value) {
        for (int i = 0; i < size_; ++i) {
            const T result = data_[i] + value;
            validateValue(result);
            data_[i] = result;
        }
        return *this;
    }

    DynamicArray& operator-=(const T& value) {
        for (int i = 0; i < size_; ++i) {
            const T result = data_[i] - value;
            validateValue(result);
            data_[i] = result;
        }
        return *this;
    }

    T* begin() {
        return data_;
    }

    T* end() {
        return size_ == 0 ? data_ : data_ + size_;
    }

    const T* begin() const {
        return data_;
    }

    const T* end() const {
        return size_ == 0 ? data_ : data_ + size_;
    }

    void append(const T& value) {
        validateValue(value);
        T* expanded = new T[size_ + 1];
        for (int i = 0; i < size_; ++i) {
            expanded[i] = data_[i];
        }
        expanded[size_] = value;
        delete[] data_;
        data_ = expanded;
        ++size_;
    }

    void add(const DynamicArray& other) {
        *this += other;
    }

    void subtract(const DynamicArray& other) {
        *this -= other;
    }

    double distance(const DynamicArray& other) const {
        if constexpr (!std::is_arithmetic_v<T>) {
            throw std::bad_typeid();
        } else {
            if (size_ != other.size_) {
                throw std::invalid_argument("Arrays must have the same size");
            }
            double sum = 0.0;
            for (int i = 0; i < size_; ++i) {
                const double difference = static_cast<double>(data_[i]) -
                                          static_cast<double>(other.data_[i]);
                sum += difference * difference;
            }
            return std::sqrt(sum);
        }
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& output, const DynamicArray<T>& array) {
    output << "{";
    for (int i = 0; i < array.size(); ++i) {
        if (i > 0) {
            output << ", ";
        }
        output << array.get(i);
    }
    output << "}";
    return output;
}

#endif
