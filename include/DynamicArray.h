#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

class DynamicArray {
private:
    int* data_;
    int size_;

    static void validateValue(int value);
    void validateIndex(int index) const;

public:
    explicit DynamicArray(int size);
    DynamicArray(const DynamicArray& other);
    DynamicArray& operator=(const DynamicArray& other) = delete;
    ~DynamicArray();

    void set(int index, int value);
    int get(int index) const;
    int size() const;
    void print() const;
    void append(int value);
    void add(const DynamicArray& other);
    void subtract(const DynamicArray& other);
};

#endif
