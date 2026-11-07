#include "DynamicArray.h"

#include <iostream>
#include <exception>

int main() {
    try {
        // создаём массив, записываем и читаем значения
        DynamicArray arrayA(3);
        arrayA.set(0, 10);
        arrayA.set(1, 20);
        arrayA.set(2, 30);
        std::cout << "arrayA: ";
        arrayA.print();
        std::cout << "arrayA[1] = " << arrayA.get(1) << "\n";

        // проверяем, что копия массива не меняет оригинал
        DynamicArray copiedArray(arrayA);
        copiedArray.set(0, -10);
        std::cout << "Copied array: ";
        copiedArray.print();
        std::cout << "Original array: ";
        arrayA.print();

        // добавляем элемент в конец массива
        arrayA.append(40);
        std::cout << "arrayA after append: ";
        arrayA.print();

        // складываем и вычитаем массивы разного размера
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
