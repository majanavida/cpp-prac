#include "DynamicArray.h"

#include <iostream>
#include <exception>

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
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << "\n";
        return 1;
    }

    return 0;
}
