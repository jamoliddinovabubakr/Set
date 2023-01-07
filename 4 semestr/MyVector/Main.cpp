#include <iostream>
#include "Mem.h"
#include "Vector.h"

int main() {
    Mem mem(100);
    Vector vector1(mem);
    int z = 123, t = 234, r = 345, y = 457;
    size_t zs = sizeof(z);
    vector1.push_back(&z, zs);
    vector1.push_back(&y, zs);
    vector1.push_back(&r, zs);
    vector1.push_back(&t, zs);
    void *p;
    p = vector1.back(zs);
    int *c = (int *) p;
    cout << *c << " ";
    vector1.pop_back();
    p = vector1.back(zs);
    c = (int *) p;
    cout << *c << "\n";
    Mem mem2(1);
    Vector vector2(mem2);
    for (int i = 0; i < 1000000; i++) {
        // char a[16]="VectorContainer";
        int y = i + 10;
        void *ap = &y;
        // cout<<(sizeof a);
        vector2.push_back(ap, sizeof y);
    }
    for (int i = 0; i < 10; i++) {
        size_t tmp_size;
        void *tmp = vector2.back(tmp_size);
        vector2.pop_back();
        // cout<<tmp_size<<" ";
        int *num = (int *) tmp;
        // cout<<(*num)<<" ";
        // char *begin=(char*)tmp;
        // for (size_t j=0;j<tmp_size;j++){
        // cout<<*(begin+j);
        // }
    }
    Vector::Vector_Iterator *tmp = (Vector::Vector_Iterator *) vector2.newIterator();
    while (tmp->hasNext()) {
        if (tmp->id % 2 == 1) {
            vector2.remove(tmp);
        } else {
            tmp->goToNext();
        }

    }
    // cout<<"\n";
    Vector::Vector_Iterator *tmp1 = (Vector::Vector_Iterator *) vector2.newIterator();
    while (tmp1->hasNext()) {
        if (tmp1->node->elem_size) {
            if (t % 2 == 1) {
                cout << "Incorrect\n";
                return 0;
            }
//       cout<<*((int*)(tmp1->node->elem))<<" ";
        }
        tmp1->goToNext();
    }
    cout << "Correct\n";
    // for (int i=0;i<10;i++){
    //   size_t tmp_size;
    //   void *tmp=vector2.back(tmp_size);
    //   vector2.pop_back();
    //   cout<<tmp_size<<" ";
    //   int *num=(int*)tmp;
    //   cout<<(*num)<<" ";
    //   // char *begin=(char*)tmp;
    //   // for (size_t j=0;j<tmp_size;j++){
    //     // cout<<*(begin+j);
    //   // }
    // }
    return 0;
}