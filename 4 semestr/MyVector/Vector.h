#include "VectorAbstract.h"

class Vector: public AbstractVector
{
private:
	struct Node{  //элемент вектора(нода)
		void *elem; // сам элемент(строка, число, массив и т.д.)
		size_t elem_size;// размер самого элемента
	};
	Node *array; //указатель на ноду(в дальнейшем по нему создадим массив)
	size_t capacity,current;// вместимость, размер текущего вектора
public:
	class Vector_Iterator: public Container::Iterator
	{
	public:
		Node *node;// указатель на ноду
		Vector *this_vector;// указатель на сам вектор
		size_t id;// индекс ноды на которую указывает итератор
		Vector_Iterator(Node *cur, Vector *new_vector, size_t new_id){
			node = cur;
			this_vector = new_vector;
			id = new_id;
		}
		void* getElement(size_t &size);
		bool hasNext();
		void goToNext();
		bool equals(Iterator *right);
		~Vector_Iterator();
	};
	Vector(MemoryManager &mem): AbstractVector(mem) {
		array = new Node[1];
		capacity = 1;
		current = 0;
	}

    ~Vector() {
    	delete [] array;
    }

    bool compare(void *a,size_t a_size,void *b,size_t b_size) ;

    size_t vsize() ;

    int push_back(void *elem, size_t elemSize);

    void pop_back();

    void* front(size_t &size);

    void* back(size_t &size);

    void* at(size_t i, size_t &size);

    int insert(Iterator *iter, void *elem, size_t elemSize);

    int size() ;

    size_t max_bytes() ;
    
    Iterator* find(void *elem, size_t size) ;

    Iterator* newIterator() ;

    void remove(Iterator *iter) ;

    void clear() ;

    bool empty() ;
};