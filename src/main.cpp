#include "DynamicArray.h"

#include <cstddef>
#include <iostream>
#include <exception>
#include <limits>
#include <new>
#include <stdexcept>

int main() {
    try {
        // Задание 1: создание массива, установка и получение элемента.
        DynamicArray arrayA(3);
        arrayA.set(0, 10);
        arrayA.set(1, 20);
        arrayA.set(2, 30);
        std::cout << "arrayA: ";
        arrayA.print();
        std::cout << "arrayA[1] = " << arrayA.get(1) << "\n";

        // Задание 2: независимая копия массива.
        DynamicArray copiedArray(arrayA);
        copiedArray.set(0, -10);
        std::cout << "Copied array: ";
        copiedArray.print();
        std::cout << "Original array: ";
        arrayA.print();

        // Задание 3: добавление элемента в конец.
        arrayA.append(40);
        std::cout << "arrayA after append: ";
        arrayA.print();

        // Задание 4: недостающие элементы второго массива считаются нулями.
        DynamicArray arrayB(2);
        arrayB.set(0, 1);
        arrayB.set(1, 2);
        arrayA.add(arrayB);
        std::cout << "arrayA after add(arrayB): ";
        arrayA.print();
        arrayA.subtract(arrayB);
        std::cout << "arrayA after subtract(arrayB): ";
        arrayA.print();

        // Проверка выхода индекса за границы массива.
        try {
            arrayA.get(arrayA.size());
        } catch (const std::out_of_range& error) {
            std::cout << "Caught std::out_of_range: " << error.what() << "\n";
        }

        // Проверка значения вне диапазона [-100, 100].
        try {
            arrayA.set(0, 101);
        } catch (const std::invalid_argument& error) {
            std::cout << "Caught std::invalid_argument: " << error.what() << "\n";
        }

        // Запрос невозможного размера массива гарантированно вызывает
        // std::bad_array_new_length, производный от std::bad_alloc.
        try {
            volatile std::size_t tooManyElements =
                std::numeric_limits<std::size_t>::max() / sizeof(int) + 1;
            int* impossibleArray = new int[tooManyElements];
            delete[] impossibleArray;
        } catch (const std::bad_alloc& error) {
            std::cout << "Caught std::bad_alloc: " << error.what() << "\n";
        }
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << "\n";
        return 1;
    }

    return 0;
}
