#include "DynamicArray.h"

#include <iostream>
#include <string>
#include <utility>

void showByValue(DynamicArray<int> array) {
    std::cout << "Function received: " << array << '\n';
}

int main() {
    try {
        // часть 1: создаём массив и проверяем запись и чтение элементов
        DynamicArray<int> first(3);
        first.set(0, 1);
        first.set(1, 2);
        first.set(2, 3);
        std::cout << "First array: " << first << '\n';
        std::cout << "First element: " << first.get(0) << '\n';

        // часть 1: проверяем копирование, добавление и операции с массивами
        DynamicArray<int> copied(first);
        copied.set(0, 10);
        std::cout << "Copy: " << copied << '\n';
        first.append(4);
        std::cout << "After append: " << first << '\n';

        DynamicArray<int> shortArray(2);
        shortArray.set(0, 1);
        shortArray.set(1, 1);
        first.add(shortArray);
        std::cout << "After add: " << first << '\n';
        first.subtract(shortArray);
        std::cout << "After subtract: " << first << '\n';

        // часть 2: проверяем исключения для неверного индекса и значения
        try {
            first.get(first.size());
        } catch (const std::out_of_range& error) {
            std::cout << "Caught std::out_of_range: " << error.what() << '\n';
        }

        try {
            first.set(0, 101);
        } catch (const std::invalid_argument& error) {
            std::cout << "Caught std::invalid_argument: " << error.what() << '\n';
        }

        // часть 3: выводим числовые массивы и находим расстояние между ними
        DynamicArray<int> second(3);
        second.set(0, 4);
        second.set(1, 5);
        second.set(2, 6);
        std::cout << "Second array: " << second << '\n';
        std::cout << "Distance: " << second.distance(copied) << '\n';

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

        // часть 4: проверяем индексирование и сравнение массивов
        second[0] = 7;
        std::cout << "Changed first element: " << second.get(0) << '\n';
        std::cout << "Arrays are equal: " << (second == copied) << '\n';
        std::cout << "Arrays are different: " << (second != copied) << '\n';

        // часть 4: складываем и вычитаем массивы и число
        second += copied;
        second -= copied;
        second += 2;
        second -= 2;
        std::cout << "After arithmetic: " << second << '\n';

        // часть 4: меняем элементы в цикле по итераторам
        for (auto& value : second) {
            value += 1;
        }
        std::cout << "After loop: " << second << '\n';

        // часть 5: передаём массив по значению сначала копированием
        showByValue(second);
        std::cout << "Original after copy: " << second << '\n';

        // часть 5: передаём массив с перемещением и проверяем источник
        showByValue(std::move(second));
        std::cout << "Source size after move: " << second.size() << '\n';

        // часть 5: проверяем копирующее и перемещающее присваивание
        DynamicArray<int> assigned(1);
        assigned = copied;
        assigned = assigned;
        std::cout << "After copy assignment: " << assigned << '\n';

        DynamicArray<int> moved(0);
        moved = std::move(assigned);
        std::cout << "After move assignment: " << moved << '\n';
        std::cout << "Assigned source size: " << assigned.size() << '\n';
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }

    return 0;
}
