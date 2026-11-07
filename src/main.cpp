#include "DynamicArray.h"

#include <cstddef>
#include <exception>
#include <iostream>
#include <limits>
#include <new>
#include <stdexcept>
#include <string>

int main() {
    try {
        // часть 1: создаём массив, записываем и читаем значения
        DynamicArray<int> arrayA(3);
        arrayA.set(0, 10);
        arrayA.set(1, 20);
        arrayA.set(2, 30);
        std::cout << "arrayA: " << arrayA << '\n';
        std::cout << "arrayA[1] = " << arrayA.get(1) << '\n';

        // часть 1: проверяем, что изменения копии не затрагивают исходный массив
        DynamicArray<int> copiedArray(arrayA);
        copiedArray.set(0, -10);
        std::cout << "Copied array: " << copiedArray << '\n';
        std::cout << "Original array: " << arrayA << '\n';

        // часть 1: добавляем элемент в конец массива
        arrayA.append(40);
        std::cout << "arrayA after append: " << arrayA << '\n';

        // часть 1: складываем и вычитаем массивы разного размера
        DynamicArray<int> arrayB(2);
        arrayB.set(0, 1);
        arrayB.set(1, 2);
        arrayA.add(arrayB);
        std::cout << "arrayA after add(arrayB): " << arrayA << '\n';
        arrayA.subtract(arrayB);
        std::cout << "arrayA after subtract(arrayB): " << arrayA << '\n';

        // часть 2: проверяем обработку индекса за границами массива
        try {
            arrayA.get(arrayA.size());
        } catch (const std::out_of_range& error) {
            std::cout << "Caught std::out_of_range: " << error.what() << '\n';
        }

        // часть 2: проверяем обработку значения вне допустимого диапазона
        try {
            arrayA.set(0, 101);
        } catch (const std::invalid_argument& error) {
            std::cout << "Caught std::invalid_argument: " << error.what() << '\n';
        }

        // часть 2: проверяем обработку ошибки выделения памяти
        try {
            volatile std::size_t tooManyElements =
                std::numeric_limits<std::size_t>::max() / sizeof(int) + 1;
            int* impossibleArray = new int[tooManyElements];
            delete[] impossibleArray;
        } catch (const std::bad_alloc& error) {
            std::cout << "Caught std::bad_alloc: " << error.what() << '\n';
        }

        // часть 3: выводим числовые массивы и находим расстояние между ними
        DynamicArray<int> numbersA(3);
        numbersA.set(0, 1);
        numbersA.set(1, 2);
        numbersA.set(2, 3);

        DynamicArray<int> numbersB(3);
        numbersB.set(0, 4);
        numbersB.set(1, 5);
        numbersB.set(2, 6);

        std::cout << "numbersA: " << numbersA << '\n';
        std::cout << "numbersB: " << numbersB << '\n';
        std::cout << "Distance: " << numbersA.distance(numbersB) << '\n';

        // часть 3: для массивов разного размера расстояние не вычисляется
        try {
            std::cout << numbersA.distance(arrayB) << '\n';
        } catch (const std::invalid_argument& error) {
            std::cout << "Caught std::invalid_argument: " << error.what() << '\n';
        }

        // часть 3: проверяем шаблонный массив для строк и ошибку расстояния
        DynamicArray<std::string> words(2);
        words.set(0, "hello");
        words.set(1, "world");
        std::cout << "Words: " << words << '\n';
        try {
            std::cout << words.distance(words) << '\n';
        } catch (const std::bad_typeid&) {
            std::cout << "Distance is only defined for numeric arrays.\n";
        }
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }

    return 0;
}
