#include "DynamicArray.h"

#include <cstddef>
#include <iostream>
#include <exception>
#include <limits>
#include <new>
#include <stdexcept>

int main() {
    try {
        // часть 1: создаём массив, записываем и читаем значения
        DynamicArray arrayA(3);
        arrayA.set(0, 10);
        arrayA.set(1, 20);
        arrayA.set(2, 30);
        std::cout << "arrayA: ";
        arrayA.print();
        std::cout << "arrayA[1] = " << arrayA.get(1) << "\n";

        // часть 1: проверяем, что изменения копии не затрагивают исходный массив
        DynamicArray copiedArray(arrayA);
        copiedArray.set(0, -10);
        std::cout << "Copied array: ";
        copiedArray.print();
        std::cout << "Original array: ";
        arrayA.print();

        // часть 1: добавляем элемент в конец массива
        arrayA.append(40);
        std::cout << "arrayA after append: ";
        arrayA.print();

        // часть 1: складываем и вычитаем массивы разного размера
        DynamicArray arrayB(2);
        arrayB.set(0, 1);
        arrayB.set(1, 2);
        arrayA.add(arrayB);
        std::cout << "arrayA after add(arrayB): ";
        arrayA.print();
        arrayA.subtract(arrayB);
        std::cout << "arrayA after subtract(arrayB): ";
        arrayA.print();

        // часть 2: проверяем обработку индекса за границами массива
        try {
            arrayA.get(arrayA.size());
        } catch (const std::out_of_range& error) {
            std::cout << "Caught std::out_of_range: " << error.what() << "\n";
        }

        // часть 2: проверяем обработку значения вне допустимого диапазона
        try {
            arrayA.set(0, 101);
        } catch (const std::invalid_argument& error) {
            std::cout << "Caught std::invalid_argument: " << error.what() << "\n";
        }

        // часть 2: проверяем обработку ошибки выделения памяти
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
