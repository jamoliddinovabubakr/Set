#pragma once

#include "Set.h"

#include <vector>
#include <algorithm>

// Структура элемента множества.
struct Cell {
    void *data;
    size_t size;
};

// Тестирующий класс для контейнера Set - Множество.
class SetTest {
private:

    Set *set;

    // Функция сравнения для сортировки.
    static bool comp(Cell first, Cell second);


public:

    // Конструктор.
    explicit SetTest(Set *set) : set(set) {};

    // Тестирует insert() и find().
    // Добавляет 1'000'000 элементов с помощью insert()
    // и проверяет их фактическое наличие с помощью find().
    // В случае успеха возвращает 0, в случае неудачи - 1.
    // В случае неудачи выводит номер элемента, вызвашего ошибку.
    int insert_find_test(int count);

    // Тестирует remove() и find().
    // Удаляет все нечетные элементы с помощью remove()
    // и проверяет наличие четных и отсутствие нечетных с помощью find().
    // В случае успеха возвращает 0, в случае неудачи - 1.
    // В случае неудачи выводит номер элемента, вызвашего ошибку.
    int remove_find_test(int count);
};

