#include "Vector.h"


bool Vector::compare(void *a, size_t a_size, void *b, size_t b_size) {
    return a_size == b_size ? !memcmp(a, b, a_size) : 0;
}

size_t Vector::vsize() {
    return current;
}

int Vector::push_back(void *elem, size_t elemSize) {
    if (elemSize == 0) {
        return 1;
    }
    if (current == capacity) {
        Node *temp = new Node[2 * capacity];
        for (int i = 0; i < capacity; i++) {
            temp[i] = array[i];
        }
        delete[] array;
        capacity *= 2;
        array = temp;
    }
    array[current].elem = new(_memory.allocMem(sizeof(char) * elemSize)) char;
    memcpy(array[current].elem, elem, elemSize);
    array[current].elem_size = elemSize;
    current++;
    return 0;
}

void Vector::pop_back() {
    if (current) {
        if (array[current - 1].elem_size) {
            delete[] (char *) (array[current].elem);
            array[current - 1].elem_size;
            current--;
        }
    }
}

void *Vector::front(size_t &size) {
    size = array[0].elem_size;
    return array[0].elem;
}

void *Vector::back(size_t &size) {
    size = array[current - 1].elem_size;
    return array[current - 1].elem;
}

void *Vector::at(size_t i, size_t &size) {
    if (i < current) {
        size = array[i].elem_size;
        return array[i].elem;
    } else {
        return NULL;
    }
}

int Vector::insert(Iterator *iter, void *elem, size_t elemSize) {
    Vector::Vector_Iterator *tmp = dynamic_cast < Vector::Vector_Iterator *> (iter);
    if (tmp == NULL) {
        return 1;
    } else {
        delete[] (char *) (tmp->node->elem);
        tmp->node->elem_size = elemSize;
        memcpy(tmp->node->elem, elem, elemSize);
        return 0;
    }
}

Vector::Iterator *Vector::newIterator() {// создаем итератор
    if (current) {
        return new Vector_Iterator(array, this, 0);
    } else {
        return NULL;
    }
}

void Vector::remove(Iterator *iter) {// удаляем ноду на которую указывает итератор
    Vector::Vector_Iterator *tmp = dynamic_cast < Vector::Vector_Iterator *> (iter);
    Node *x = tmp->node;
    if (tmp->hasNext()) {
        tmp->goToNext();
    } else {
        tmp = NULL;
    }
    delete[] (char *) (x->elem);
    x->elem_size = 0;

}

Vector::Iterator *Vector::find(void *elem, size_t size) {//----------------
    return NULL;
}

void Vector::clear() {// очищаем вектор
    for (size_t i = 0; i < current; i++) {
        delete[] (char *) (array[i].elem);
        array[i].elem_size = 0;
    }
    current = 0;
}

int Vector::size() {
    return (int) current; // возвращаем размер вектора
}

size_t Vector::max_bytes() {
    return _memory.maxBytes();  // возвращаем maxbytes см. MemoryManager
}

bool Vector::empty() {
    return !current; // возвращает пустой вектор или нет
}

// функции внизу описаны в Cotainer.h

void *Vector::Vector_Iterator::getElement(size_t &size) {
    size = node->elem_size;
    return node->elem; // возвратит NULL если элемент удален
}

bool Vector::Vector_Iterator::hasNext() {
    if (id < this_vector->current - 1) { // если не последний элемент возвращаем true, иначе false
        return true;
    } else {
        return false;
    }
}

void Vector::Vector_Iterator::goToNext() {
    node = &(this_vector->array[++id]);
}

bool Vector::Vector_Iterator::equals(Iterator *right) {// проверка на равенство Node
    return dynamic_cast < Vector::Vector_Iterator *> (right)->node == this->node;
}

