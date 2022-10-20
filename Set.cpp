#include "Set.h"

Set::Set(MemoryManager &mem) : AbstractSet(mem) {
    for (auto &i: arr) {
        i = nullptr;
    }
}

Set::~Set() {
    clear();
}

Set::SetIterator::SetIterator(Set *mySet, size_t myIndex, List::ListIterator *iter) {
    set = mySet;
    index = myIndex;
    listIter = iter;
}

Set::SetIterator::~SetIterator() {
    delete listIter;
}

// Возврашает явно указатель на элемент, на который указывает итератор в данный момент.
// Неявно возвращает размер данных.
// Если итератор показывает за пределы контейнера (например, удален последний элемент), возвращает NULL.
void *Set::SetIterator::getElement(size_t &size) {
//    cout << "listIter: " << listIter << '\n';
    if (listIter == nullptr) {
        size = 0;
        return nullptr;
    }
    void *elem = listIter->getElement(size);
//    cout << "elem: " << elem << '\n';
    return elem;
}

//bool Set::SetIterator::hasNext() {
//    cout << "listIter->hasNext(): " << listIter->hasNext() << '\n';
//    if (listIter->hasNext()) {
//        return true;
//    }
//
//    for (size_t i = index + 1; i < set->size(); i++) {
//        if (set->arr[i] != nullptr && !set->arr[i]->empty()) {
//            return true;
//        }
//    }
//
//    return false;
//}
bool Set::SetIterator::hasNext() {
    if (listIter->hasNext())
        return true;
    else
        for (size_t i = index + 1; i < set->size(); ++i)
            if (!(set->arr[i]->empty()))
                return true;

    return false;
}


void Set::SetIterator::goToNext() {
//    cout << "listIter->hasNext(): " << listIter->hasNext() << '\n';
    if (listIter->hasNext()) {
        listIter->goToNext();
    }

    for (size_t i = index + 1; i < set->size(); i++) {
        if (set->arr[i] != nullptr && !set->arr[i]->empty()) {
            index = i;
            listIter = dynamic_cast<List::ListIterator *> (set->arr[i]->newIterator());
        }
    }
}

bool Set::SetIterator::equals(Container::Iterator *right) {
//    cout << "listIter: " << listIter << endl;
//    cout << "right: " << right << endl;
    if (listIter == nullptr || right == nullptr) {
        return false;
    }
//    cout << "listIter->equals(right): " << listIter->equals(right) << endl;
    return listIter->equals(right);
}

// Попробовать эту функцию для сварнения двух итератора
// Возвращает true, если текущий итератор равен заданному, иначе false.
//bool Set::SetIterator::equals(Iterator *right) {
//    return (listIter == dynamic_cast<List::Iterator *>(right));
//}

// Попробовать поставить хеш Сарвара
size_t Set::hash_function(void *elem, size_t size) {
    auto b = static_cast<char *>(elem);
    size_t h = ((size_t) b[0] & 0xFFu);

    for (int i = 1; i < size; i++) {
        h |= ((size_t) b[i] & 0xFFu) << (i * 8u);
    }

    return h % CAPACITY;
}

int Set::size() {
    return sizeOfSet;
}

size_t Set::max_bytes() {
    return _memory.maxBytes();
}

Container::Iterator *Set::find(void *elem, size_t elemSize) {
    size_t index = hash_function(elem, elemSize);
//    cout << "index: " << index << '\n';
    List *list = arr[index];
//    cout << "list: " << list << '\n';
//    cout << "empty(): " << list->empty() << '\n';
    if (list == nullptr || list->empty()) //didn't exist
    {
//        cout << "if: 1" << '\n';
        return nullptr;
    }

    Container::Iterator *listIter = list->find(elem, elemSize);
//    cout << "listIter: " << listIter << '\n';
    if (listIter == nullptr) //no matches
    {
        return nullptr;
    }
    auto a = new SetIterator(this, index, dynamic_cast<List::ListIterator *>(listIter));
//    cout << "a: " << a << '\n';
    return a;
}

Set::SetIterator *Set::newIterator() {
    auto tmp = new SetIterator(this, 0, nullptr);
//    cout << "tmp: " << tmp << '\n';
    return tmp;
}

void Set::remove(Container::Iterator *iter) {
//    cout << "iter: " << iter << endl;
    if (iter == nullptr) {
        return;
    }

    auto setIter = dynamic_cast<SetIterator *>(iter);
    List *list = arr[setIter->index];
//    cout << "list: " << list << endl;
    if (list == nullptr || list->empty()) //didn't exist
    {
        return;
    }

    list->remove(setIter->listIter);
    sizeOfSet--;

    if (setIter->hasNext())
        setIter->goToNext();
    else {
        delete setIter->listIter;
        setIter->listIter = nullptr;
        setIter->index = CAPACITY;
    }
}

void Set::clear() {
    for (auto &i: arr) {
        if (i != nullptr) {
            /* delete arr[i];
             arr[i] = nullptr;*/
            i->clear();
        }
    }
    sizeOfSet = 0;
}

bool Set::empty() {
    return size() == 0;
}

/*
Container::Iterator* Set::begin()
{
    for (size_t i = 0; i < sizeOfSet; i++)
    {
        if (arr[i] == nullptr && !arr[i]->empty())
        {
            return new SetIterator(this, i, (List::ListIterator*)(arr[i]->begin()));
        }
    }

    return nullptr;
}

Container::Iterator* Set::end()
{
    for (size_t i = sizeOfSet; i >= 0; i--)
    {
        if (arr[i] == nullptr && !arr[i]->empty())
        {
            return new SetIterator(this, i, (List::ListIterator*)(arr[i]->end()));
        }
    }

    return nullptr;
}
*/


// Добавление элемента в позицию, на которую указывает итератор iter.
// В случае успешного добавления функция возвращает значение 0, в случае неудачи 1.
int Set::insert(void *elem, size_t elemSize) {
    size_t index = hash_function(elem, elemSize);
//    cout << "index: " << index << '\n';
    if (arr[index] == nullptr) //for the first elem of the list
    {
        arr[index] = new List(_memory); // чуть не понятно зачем это делать
    }
//    cout << "arr[index] = " << arr[index] << '\n';
//    List *list = arr[index];
//    cout << "list = " << list << '\n';
    Container::Iterator *iter = arr[index]->find(elem, elemSize);
//    Container::Iterator *iter = list->find(elem, elemSize);
//    cout << "iter: " << iter << '\n';
    if (iter == nullptr) {
        if (arr[index]->push_front(elem, elemSize) != 0) return 2;
        //        if (list->push_front(elem, elemSize) != 0) // из push_front всегда возвращается 0 // Шухрат сказал что в какое то случае возмоно пуш фронт не равно 0
//          return 2; //sth is wrong with push_front

        sizeOfSet++;
//        cout << "sizeofSet: " << sizeOfSet << '\n';
        delete iter;
        return 0; //inserted
    }

    return 1; //not unique
}