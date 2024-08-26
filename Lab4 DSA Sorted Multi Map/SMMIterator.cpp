#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
    first();
}

void SMMIterator::first(){
    this->pos = 0;
    while(pos < map.capacity_table && map.lista_noduri[pos] == nullptr){
        pos++;
    }
    if(pos < map.capacity_table){
        current = map.lista_noduri[pos];
    }
    else{
        current = nullptr;
    }
}

/*
 * Best case: T(1)
 * Average Case: T(n)
 * Worst Case: T(n)
 * */
void SMMIterator::next() {
    if (this->valid() == true) {
        if (current->next != nullptr) { // verifica sa nu fie urmatorul nullptr
            current = current->next;
        } else {
            // Avansăm la următoarea poziție care conține un nod
            this->pos++;
            while (pos < map.capacity_table && map.lista_noduri[pos] == nullptr) {
                pos++;
            }
            if (pos < map.capacity_table) {
                current = map.lista_noduri[pos];
            } else {
                current = nullptr;
            }
        }
    }
    else{
        throw exception();
    }
}

bool SMMIterator::valid() const{
    return pos < map.capacity_table && current != nullptr;
}

TElem SMMIterator::getCurrent() const{
	if(this->valid() == true){
         return current->data;
    }
    else{
        throw exception();
    }
}


/*
void SMMIterator::next() {
    if (this->valid()) {
        if (current->next != nullptr) {
            current = current->next;
        } else {
            // Avansăm la următoarea poziție care conține un nod
            this->pos++;
            while (pos < map.capacity_table && map.lista_noduri[pos] == nullptr) {
                pos++;
            }
            if (pos < map.capacity_table) {
                current = map.lista_noduri[pos];
            } else {
                current = nullptr;
            }
        }
    } else {
        throw std::exception();
    }
}
*/
/*
void SMMIterator::next(){
    if(this->current->next != nullptr){
        current = current->next;
    } else{
        this->pos++;
        while(pos < map.capacity_table && map.lista_noduri[pos] == nullptr){
            pos++;
        }
        if(pos < map.capacity_table){
            current = map.lista_noduri[pos];
        }
        else {
            current = nullptr;
        }
    }
}
*/





