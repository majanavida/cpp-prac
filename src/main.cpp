#include "DynamicArray.h"

#include <iostream>
#include <string>

int main() {
    try {
        // часть 1: создаём массив, записываем и читаем значения
        DynamicArray<int> first(3);
        first.set(0, 1);
        first.set(1, 2);
        first.set(2, 3);

        // часть 3: выводим массивы и находим расстояние между массивами одного размера
        DynamicArray<int> second(3);
        second.set(0, 4);
        second.set(1, 5);
        second.set(2, 6);

        std::cout << "First array: " << first << '\n';
        std::cout << "Second array: " << second << '\n';
        std::cout << "Distance: " << first.distance(second) << '\n';

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

        // часть 3: шаблонный массив можно создать и для строк
        DynamicArray<std::string> words(2);
        words.set(0, "hello");
        words.set(1, "world");
        std::cout << "Words: " << words << '\n';

        // для строк расстояние не определено, поэтому ловим std::bad_typeid
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
