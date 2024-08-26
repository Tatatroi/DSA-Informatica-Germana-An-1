#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <exception>

using namespace std;

// θ(1)
ListIterator::ListIterator(const SortedIteratedList& list) : list(list){
    this->index = this->list.head;
}

// θ(1)
void ListIterator::first(){
    this->index = this->list.head;
}

// θ(1)
void ListIterator::next(){
    if(this->valid()) {
        this->index = this->list.elements[this->index].next;
        return ;
    }

    throw exception();
}

// θ(1)
bool ListIterator::valid() const{
    if(this->index != -1)
        return true;

    return false;
}

// θ(1)
TComp ListIterator::getCurrent() const{
    if(this->valid()) {
        return this->list.elements[this->index].info;
    }

    throw exception();
}
