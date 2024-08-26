//
// Created by srefa on 5/24/2024.
//

#include "KeyIterator.h"
#include "SortedMultiMap.h"

KeyIterator::KeyIterator(const SortedMultiMap &d) : map(d) {
    first();
}

void KeyIterator::first(){
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


void KeyIterator::next() {
    if (this->valid() == true) {
        if (current->next != nullptr) { // verifica sa nu fie urmatorul nullptr
            //current = current->next;
            SortedMultiMap::Node* aux = current;
            while(aux->next->data.first == aux->data.first && aux->next != nullptr){
                aux = aux->next;
            }
            current = aux->next;
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


bool KeyIterator::valid() const{
    return pos < map.capacity_table && current != nullptr;
}

TElem KeyIterator::getCurrent() const{
    if(this->valid() == true){
        return current->data;
    }
    else{
        throw exception();
    }
}