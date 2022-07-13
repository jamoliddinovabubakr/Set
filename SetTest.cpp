#include "Set.h"

int main() {
    Mem mm(0);
    Set set(mm);

    Set::SetIterator *set_iterator;
    int a1 = 5, a2 = 10, a3 = 7;
    cout << __LINE__ << " " << set.insert(&a1, sizeof(a1)) << '\n';
    cout << __LINE__ << " " << set.insert(&a2, sizeof(a2)) << '\n';
    cout << __LINE__ << " " << set.insert(&a3, sizeof(a3)) << '\n';
    cout << __LINE__ << " " << set.size() << '\n';
    set_iterator = set.newIterator();
    size_t tmp;
    cout << __LINE__ << " " << *(int*)set_iterator->getElement(tmp) << '\n';


    return 0;
}
/*
#include "SetTest.h"

// Функция сравнения для сортировки.
bool SetTest::comp(Cell first, Cell second) {
    return (*((int *) (first.data))) < (*((int *) (second.data)));
}

// Тестирует insert() и find().
// Добавляет 1'000'000 элементов с помощью insert()
// и проверяет их фактическое наличие с помощью find().
// В случае успеха возвращает 0, в случае неудачи - 1.
// В случае неудачи выводит номер элемента, вызвашего ошибку.
int SetTest::insert_find_test(int count) {
    Set::SetIterator *set_iterator;
    cout << "set_iterator: " << set_iterator << '\n';
//    cout << "&set_iterator: " << &set_iterator << '\n';
    void *data;
    size_t size;

    for (int i = 0; i < count; i++) {
        set->insert(&i, sizeof(i));

        set_iterator = dynamic_cast<Set::SetIterator *>(set->find(&i, sizeof(i)));
        cout << "set_iterator: " << set_iterator << '\n';
        if (set_iterator == nullptr) {
            cout << "Element " << i << " not found!" << endl;
            return 1;
        }

        data = set_iterator->getElement(size);
        cout << "data: " << data << '\n';
        if ((*((int *) data) != i) && (size != sizeof(i))) {
            cout << "Incorrect data or size of element " << i << "!" << endl;
            return 1;
        }
        delete set_iterator;
        cout << "\n\n\n";
    }

    Set::SetIterator *set_iter;
    int a1 = 5, a2 = 10, a3 = 7;
    set->insert(&a1, sizeof(a1));
    set->insert(&a2, sizeof(a2));
    set->insert(&a3, sizeof(a3));

    cout << __LINE__ << " " << set->size() << endl;

    size_t tmp;
    set_iter = dynamic_cast<Set::SetIterator *>(set->newIterator());
    cout << __LINE__ << " " << *(int*)set_iter->getElement(tmp) << '\n';
    return 0;
}

// Тестирует remove() и find().
// Удаляет все нечетные элементы с помощью remove()
// и проверяет наличие четных и отсутствие нечетных с помощью find().
// В случае успеха возвращает 0, в случае неудачи - 1.
// В случае неудачи выводит номер элемента, вызвашего ошибку.
int SetTest::remove_find_test(int count) {
    Set::SetIterator *set_iterator;

    vector<Cell> content;
    Cell temp;

    for (int i = 1; i < count; i += 2) {
        set_iterator = dynamic_cast<Set::SetIterator *>(set->find(&i, sizeof(i)));

        set->remove(set_iterator);

        set_iterator = dynamic_cast<Set::SetIterator *>(set->find(&i, sizeof(i)));

        if (set_iterator != nullptr) {
            cout << "Uneven element " << i << " found!" << endl;
            return 1;
        }

        delete set_iterator;
    }

    for (int i = 0; i < count; i++) {
        set_iterator = dynamic_cast<Set::SetIterator *>(set->find(&i, sizeof(i)));

        if (set_iterator != nullptr) {
            temp.data = set_iterator->getElement(temp.size);
            content.push_back(temp);
        }

        delete set_iterator;
    }

    sort(content.begin(), content.end(), comp);

    for (int i = 0; i < content.size(); i++)
        if (*((int *) (content[i].data)) != 2 * i) {
            cout << "Incorrect data of element " << i << "!" << endl;
            return 1;
        }

    return 0;
}
*/
