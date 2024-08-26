#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <iostream>
using namespace std;
#include <exception>

// θ(n)
SortedIteratedList::SortedIteratedList(Relation r) {
    this->capacity = 50;
    this->length = 0;
    this->head = -1;
    this->tail = -1;
    this->firstEmpty = 0;
    this->r = r;
    this->elements = new DLLANode[this->capacity];

    for(int index = 0; index < this->capacity - 1; ++index) {
        this->elements[index].previous = index - 1;
        this->elements[index].next = index + 1;
        this->elements[index].info = NULL_TCOMP;
    }

//    this->elements[this->capacity - 1].next = -1;
    this->elements[this->capacity - 1].next = -1;// The last element in the array does not have a next element
    this->elements[this->capacity - 1].previous = this->capacity - 2;// Update the pointer to the previous element of the last element in the array
    this->elements[this->capacity - 1].info = NULL_TCOMP;
}

// θ(1)
int SortedIteratedList::size() const {
    return this->length;
}

// θ(1)
bool SortedIteratedList::isEmpty() const {
    return length == 0;
}

// θ(1)
ListIterator SortedIteratedList::first() const {
    ListIterator iterator = ListIterator(*this);
    return iterator;
}

// θ(1)
TComp SortedIteratedList::getElement(ListIterator poz) const {
    return poz.getCurrent();
}

// θ(1)
TComp SortedIteratedList::allocate() {
    TComp newIndex = this->firstEmpty;
    if(newIndex != -1) {
        this->firstEmpty = this->elements[this->firstEmpty].next;
        if(this->firstEmpty != -1) {
            this->elements[this->firstEmpty].previous = -1;
        }


        this->elements[newIndex].next = -1;
        this->elements[newIndex].previous = -1;
    }

    return newIndex;
}

// θ(1)
void SortedIteratedList::deallocate(int position) {
//    if(position == this->head) {
//        this->head = this->elements[this->head].next;
//    }
//
//    if(position == this->tail) {
//        this->tail = this->elements[this->tail].previous;
//    }
//
//    this->elements[position].next = this->firstEmpty;
//    this->elements[position].previous = -1;
//
//    if(this->firstEmpty != -1) {
//        this->elements[this->firstEmpty].previous = position;
//    }
//
//    this->firstEmpty = position;
    elements[position].next = firstEmpty;
    elements[position].previous = -1;
    if(firstEmpty != -1){
        elements[firstEmpty].previous = position;
    }
    firstEmpty = position;

}

//
void SortedIteratedList::resize() {
    int newCapacity=capacity * 2;
    auto newArray=new DLLANode[newCapacity];

    for (int index=0;index<capacity;index++)
    {
        newArray[index].info=elements[index].info;
        newArray[index].next=elements[index].next;
    }

    for (int index=capacity;index<newCapacity;index++)
        newArray[index].next=index+1;
    newArray[newCapacity-1].next=-1;
    firstEmpty=capacity;

    delete[] elements;

    elements = newArray;
    capacity = newCapacity;
}


//// θ(1)
//TComp SortedIteratedList::remove(ListIterator& poz) {
//    TComp oldValue = poz.getCurrent();
//    int position = poz.index;
//    poz.next();
//    deallocate(position);
//    this->length--;
//    return oldValue;
//}

//TComp SortedIteratedList::remove(ListIterator& poz) {
//    TComp oldValue = poz.getCurrent();
//    int position = poz.index;
//    poz.next(); // Mutăm iteratorul la următorul element înainte de a elimina elementul curent
//
//    if (position == this->head) {
//        this->head = this->elements[position].next;
//    }
//
//    if (position == this->tail) {
//        this->tail = this->elements[position].previous;
//    }
//
//    int previousIndex = this->elements[position].previous;
//    int nextIndex = this->elements[position].next;
//
//    if (previousIndex != -1) {
//        this->elements[previousIndex].next = nextIndex;
//    }
//
//    if (nextIndex != -1) {
//        this->elements[nextIndex].previous = previousIndex;
//    }
//
//    deallocate(position);
//    this->length--;
//
//    return oldValue;
//}

TComp SortedIteratedList::remove(ListIterator& poz) {
    TComp oldValue = poz.getCurrent();
    int position = poz.index;
    poz.next(); // Mutăm iteratorul la următorul element înainte de a elimina elementul curent

    if (position == this->head) {
        this->head = this->elements[position].next;
        if (this->head != -1) {
            this->elements[this->head].previous = -1;
        }
    } else if (position == this->tail) {
        this->tail = this->elements[position].previous;
        if (this->tail != -1) {
            this->elements[this->tail].next = -1;
        }
    } else {
        int previousIndex = this->elements[position].previous;
        int nextIndex = this->elements[position].next;
        this->elements[previousIndex].next = nextIndex;
        this->elements[nextIndex].previous = previousIndex;
    }

    deallocate(position);
    this->length--;

    return oldValue;
}




//ListIterator SortedIteratedList::search(TComp e) const {
//    ListIterator iterator = ListIterator(*this);
//
//    try {
//        while(iterator.getCurrent() != e) {
//            try {
//                iterator.next();
//            }
//            catch (std::exception &e){
//                return iterator;
//            }
//        }
//    }
//    catch (std::exception &e) {
//        return iterator;
//    }
//
//
//    return iterator;
//}
ListIterator SortedIteratedList::search(TComp e) const {
    ListIterator iterator = ListIterator(*this);

    while (iterator.valid()) {
        if (iterator.getCurrent() == e) {
            return iterator;
        }
        iterator.next();
    }

    // Dacă elementul nu este găsit, returnăm un iterator invalid
    return iterator;
}

void SortedIteratedList::add(TComp e) {
    if (this->capacity == this->size())
        resize();

    this->length++;

    if (this->head == -1) { // Lista este goală e bine
        this->head = allocate();
        this->tail = this->head;
        this->elements[this->head].info = e;
        return;
    }

    if (r(e, this->elements[this->head].info)) { // Adăugare înainte de head

        TComp newIndex = allocate();
        this->elements[newIndex].info = e;
        elements[newIndex].previous = -1;
        elements[newIndex].next = head;
        elements[head].previous = newIndex;
        head = newIndex;

        return;
    }

    if (r(this->elements[this->tail].info, e)) { // Adăugare după tail
        TComp newIndex = allocate();
        this->elements[newIndex].info = e;
        this->elements[newIndex].next = -1;

        this->elements[newIndex].previous = this->tail;
        this->elements[this->tail].next = newIndex;
        this->tail = newIndex;
        return;
    }

    TComp currentIndex = this->head;
    TComp aux = currentIndex;
    while (r(this->elements[currentIndex].info, e)) { // Cautare pozitie de inserare
        aux = currentIndex;
        currentIndex = this->elements[currentIndex].next;
    }
//    cout<<"currentIndex: "<<currentIndex<<'\n';
    TComp position = allocate();
    this->elements[position].info = e;

    if (currentIndex != -1) {
        elements[position].next = currentIndex;
        elements[position].previous = aux;
        elements[aux].next = position;
        elements[currentIndex].previous = position;
    }
}



// θ(1)
SortedIteratedList::~SortedIteratedList() {
    delete[] this->elements;
}

void SortedIteratedList::afis() {
 //   int currentIndex = head;
//    while (currentIndex != -1) { // Cautare pozitie de inserare
//        cout<<'('<<elements[currentIndex].previous<<','<<elements[currentIndex].info<< ','<<elements[currentIndex].next<< ')'<< ' ';
//        currentIndex = this->elements[currentIndex].next;
//    }
    for(int currentIndex = 0; currentIndex<length; currentIndex++) { // Cautare pozitie de inserare
        cout<<'('<<elements[currentIndex].previous<<','<<elements[currentIndex].info<< ','<<elements[currentIndex].next<< ')'<< ' ';
    }
    cout<<'\n';
}
