#ifndef SETDI_SET_H
#define SETDI_SET_H

#include "SetAbstract.h"
#include "List.h"
#include "MemoryManager.h"
#include "Mem.h"

const size_t CAPACITY = 100000;
//#define CAPACITY 1000000

class Set : public AbstractSet {

    List *arr[CAPACITY];
    int sizeOfSet = 0;

public:

    Set(MemoryManager &mem);

    ~Set();

    class SetIterator : public Container::Iterator {
    public:
        Set *set;
        size_t index;
        List::ListIterator *listIter;

        SetIterator(Set *mySet, size_t myIndex, List::ListIterator *iter);

        ~SetIterator();

        void *getElement(size_t &size) override;

        bool hasNext() override;

        void goToNext() override;

        bool equals(Iterator *right) override;
    };

    size_t hash_function(void *elem, size_t size);

    int size() override;

    size_t max_bytes() override;

    Container::Iterator *find(void *elem, size_t size) override;

    SetIterator * newIterator() override;
    // Container::Iterator* begin() override;
    // Container::Iterator* end() override;

    void remove(Iterator *iter) override;

    void clear() override;

    bool empty() override;

    int insert(void *elem, size_t size) override;
};


#endif //SETDI_SET_H