#include "SortedSetIterator.h"
#include <exception>

using namespace std;

SortedSetIterator::SortedSetIterator(const SortedSet& m) : multime(m)
{
	//TODO - Implementation
    currentNode = m.head;
}

/*
 * Best:T(1)
 * Average:T(1)
 * Worst:T(1)
 * */
void SortedSetIterator::first() {
    this->currentNode = this->multime.head;
}

/*
 * Best:T(1)
 * Average:T(1)
 * Worst:T(1)
 * */
void SortedSetIterator::next() {
    if(this->valid() == true){
        this->currentNode = this->currentNode->next;
    }
    else throw std::exception();
}

/*
 * Best:T(1)
 * Average:T(1)
 * Worst:T(1)
 * */
TElem SortedSetIterator::getCurrent()
{
    if(this->currentNode == NULL){
        throw std::exception();
    }
    return this->currentNode->val;
}
/*
 * Best:T(1)
 * Average:T(1)
 * Worst:T(1)
 * */
bool SortedSetIterator::valid() const {
	if(this->currentNode == NULL){
        return false;
    }
    return true;
}

/*
 * Best:T(1)
 * Average:T(n)
 * Worst:T(n)
 * */

void SortedSetIterator::modificareElem(TComp newElem) {
    // caz 1 --> elementul newElem exista in alta parte a containerului
    if(multime.search(newElem) == true){
        if(getCurrent() != newElem) {
            throw std::exception();
        }
        else{// daca dorim sa modific elementul cu aceeasi valoare nu se intmpla nimic
            return;
        }
    }
    else{ // caz 2 --> elementul nu se afla in alta parte a listei
        delete currentNode;
        first();
        SortedSet::DLLNode* aux = currentNode;
        SortedSet::DLLNode* prev = NULL;
        while (multime.r(getCurrent(),newElem) == false && aux != NULL) {
            prev = aux;
            aux = aux->next;
        }
        SortedSet::DLLNode* newNode = new SortedSet::DLLNode;
        newNode->val = newElem;
        if(prev == NULL){ // cazul in care se adauga in fata
            newNode->next = aux;
            newNode->prev = NULL;
            aux->prev = newNode;
        }
        else if(aux == NULL){// cazul in care se adauga la sfarsit
            newNode->next = NULL;
            newNode->prev = prev;
            prev->next = newNode;
        }
        else{ // cazul in care adaugam oriunde altundeva
            prev->next = newNode;
            newNode->prev = prev;
            newNode->next = aux;
            aux->prev = newNode;
        }
    }
}

