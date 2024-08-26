#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

SortedMultiMap::SortedMultiMap(Relation r) {
    this->length_table = 0;
    this->capacity_table = 10;
    this->load_factor = (float)length_table/(float)capacity_table;
    this->lista_noduri = new Node*[this->capacity_table];
    for (int i = 0; i < this->capacity_table; i++)
        this->lista_noduri[i] = nullptr;
    this->r = r;
}


/*
 * Best case: T(1)
 * Average Case: T(n)
 * Worst Case: T(n)
 * */

void SortedMultiMap::rehash() {
    int oldCapacity = this->capacity_table;
    Node** oldTable = this->lista_noduri;

    // Dublăm capacitatea
    this->capacity_table *= 2;
    this->lista_noduri = new Node*[this->capacity_table];

    // Inițializăm noua listă de noduri cu nullptr
    for (int i = 0; i < this->capacity_table; ++i) {
        this->lista_noduri[i] = nullptr;
    }

    // Resetăm numărul de elemente deoarece funcția add îl va recalcula
    this->length_table = 0;

    // Adăugăm toate elementele vechi în noua listă folosind funcția add
    for (int i = 0; i < oldCapacity; ++i) {
        Node* aux = oldTable[i];
        while (aux != nullptr) {
            add(aux->data.first, aux->data.second);
            Node* toDelete = aux;
            aux = aux->next;
            delete toDelete;
        }
    }

    // Dezalocăm vechea listă de noduri
    delete[] oldTable;

    // Actualizăm load factor-ul
    this->load_factor = (float)this->length_table / (float)this->capacity_table;
}


/*
 * Best case: T(1)
 * Average Case: T(n)
 * Worst Case: T(n)
 * */
void SortedMultiMap::add(TKey c, TValue v) {
    // Verificăm load factor-ul și facem rehash dacă este necesar
    if (load_factor > 0.75) {
        rehash();
    }

    int value = hash(c);
    Node* aux = lista_noduri[value];

    // Creăm noul nod
    Node* newNode = new Node;
    pair<TKey, TValue> newPair;
    newPair.first = c;
    newPair.second = v;
    newNode->data = newPair;

    // Cazul când lista de noduri este goală sau trebuie inserat la început
    if (aux == nullptr || !r(c, aux->data.first)) {
        newNode->next = aux;
        lista_noduri[value] = newNode;
    } else {
        // Cazul când trebuie să inserăm în interiorul listei
        Node* prev = nullptr;
        while (aux != nullptr && r(c, aux->data.first)) {
            prev = aux;
            aux = aux->next;
        }

        if (aux != nullptr && r(c, aux->data.first)) {
            // Inserăm între două noduri
            prev->next = newNode;
            newNode->next = aux;
        } else if(prev->next == nullptr){
            // Inserăm la final
            prev->next = newNode;
            newNode->next = nullptr;
        }
    }

    length_table++;
    load_factor = (float)length_table / (float)capacity_table;
}

/*
 * Best case: T(1)
 * Average Case: T(1)
 * Worst Case: T(n)
 * */

vector<TValue> SortedMultiMap::search(TKey c) const {
    vector<TValue> rezult;
    int value = hash(c);
    Node *aux = lista_noduri[value];

    while (aux != nullptr) {
        if (aux->data.first == c) {
            // Continuăm să căutăm toate valorile asociate cheii c
            while (aux != nullptr && aux->data.first == c) {
                rezult.push_back(aux->data.second);
                aux = aux->next;
            }
            return rezult; // Odată ce am găsit toate valorile, returnăm rezultatul
        }
        aux = nullptr;
    }
    return rezult;
}

/*
 * Best case: T(1)
 * Average Case: T(1)
 * Worst Case: T(n)
 * */

bool SortedMultiMap::remove(TKey c, TValue v) {
    int value = hash(c);
    Node* head = lista_noduri[value];
    Node* prev = nullptr;

    // Parcurgem lista până găsim nodul cu cheia c și valoarea v
    while (head != nullptr) {
        if (head->data.first == c && head->data.second == v) {
            // Eliminăm nodul
            if (prev == nullptr) {
                lista_noduri[value] = head->next; // Nodul este primul din listă
            } else {
                prev->next = head->next; // Actualizăm pointerul nodului anterior
            }
            delete head;
            length_table--;
            return true; // Eliminare cu succes
        }
        prev = head;
        head = head->next;
    }

    return false; // Elementul nu a fost găsit
}

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

//KeyIterator SortedMultiMap::iterator2() const {
//    return KeyIterator(*this);
//}




int SortedMultiMap::size() const {
    return this->length_table;
}

bool SortedMultiMap::isEmpty() const {
    return this->length_table == 0;
}

int SortedMultiMap::hash(TKey key) const {
    if(key < 0){
        key = capacity_table + key % capacity_table;
    }
    return key % capacity_table;
}

SortedMultiMap::~SortedMultiMap() {
    for (int i = 0; i < capacity_table; ++i) {
        Node* aux = lista_noduri[i];
        while (aux != nullptr) {
            Node* toDelete = aux;
            aux = aux->next;
            delete toDelete;
        }
    }
    delete[] lista_noduri;
}

/*
 * Functia suplimentara:
 * iterator peste chei
 *
 * */

/*
void SortedMultiMap::add(TKey c, TValue v) {

    if(load_factor > 0.75){
        rehash();
    }
	int value = hash(c);
    Node* aux = lista_noduri[value];


    // 2 cazuri in care headul este null sau exista elemente
    if(aux == nullptr){
        Node* newNode = new Node;
        pair<TKey,TValue> newPair;
        newPair.first = c;
        newPair.second = v;
        newNode->data = newPair;
        newNode->next = nullptr;
        lista_noduri[value] = newNode;
    }
    else if(aux != nullptr){
        // se creeaza noul nod ce trebuie adaugat
        Node* newNode = new Node;
        pair<TKey,TValue> newPair;
        newPair.first = c;
        newPair.second = v;
        Node* head = lista_noduri[value];
        // 3 cazuri, adaugare la inceput, la sfarsit, intre elemente

        if(r(c,head->data.first) == false){
            newNode->next = head;
            lista_noduri[value] = newNode;
        }
        else{
            // 1 while cu care ne plimbam
            Node* aux = head;
            while(head != nullptr && r(c,head->data.first)){
                aux = head;
                head = head->next;
            }
            if(aux->next == nullptr){ // adaugare la final
                newNode->next = nullptr;
                aux->next = newNode;
            }
            else{
                aux->next = newNode;
                newNode->next = aux;
            }
        }
    }
    length_table++;
}
*/
/*
void SortedMultiMap::add(TKey c, TValue v) {
    // Verificăm load factor-ul și facem rehash dacă este necesar
    if (load_factor > 0.75) {
        rehash();
    }

    int value = hash(c);
    Node* aux = lista_noduri[value];

    // 2 cazuri: head-ul este null sau există elemente
    if (aux == nullptr) {
        Node* newNode = new Node;
        pair<TKey, TValue> newPair;
        newPair.first = c;
        newPair.second = v;
        newNode->data = newPair;
        newNode->next = nullptr;
        lista_noduri[value] = newNode;
    } else {
        // Se creează noul nod ce trebuie adăugat
        Node* newNode = new Node;
        pair<TKey, TValue> newPair;
        newPair.first = c;
        newPair.second = v;
        newNode->data = newPair;

        // Verificăm unde trebuie să fie adăugat nodul
        Node* head = lista_noduri[value];
        if (!r(c, head->data.first)) { // la inceput
            newNode->next = head;
            lista_noduri[value] = newNode;
        } else {
            Node* prev = nullptr;
            while (head != nullptr && r(c, head->data.first)) { // mergem la pozitia buna
                prev = head;
                head = head->next;
            }
            if(prev->next == nullptr){ // adaugare la final
                newNode->next = nullptr;
                prev->next = newNode;
            }
            else{
                prev->next = newNode;
                newNode->next = head;
            }
//            newNode->next = head;
//            if (prev != nullptr) {
//                prev->next = newNode;
//            }
        }
    }

    length_table++;
    load_factor = (float)length_table / (float)capacity_table;
}
*/
/*var2
void SortedMultiMap::add(TKey c, TValue v) {
    // Verificăm load factor-ul și facem rehash dacă este necesar
    if (load_factor > 0.75) {
        rehash();
    }

    int value = hash(c);
    Node* aux = lista_noduri[value];

    // Creăm noul nod
    Node* newNode = new Node;
    pair<TKey, TValue> newPair;
    newPair.first = c;
    newPair.second = v;
    newNode->data = newPair;

    // Cazul când lista de noduri este goală sau trebuie inserat la început
    if (aux == nullptr || !r(c, aux->data.first)) {
        newNode->next = aux;
        lista_noduri[value] = newNode;
    } else {
        // Cazul când trebuie să inserăm în interiorul listei
        Node* prev = nullptr;
        while (aux != nullptr && r(c, aux->data.first)) {
            prev = aux;
            aux = aux->next;
        }

        if (aux != nullptr && r(c, aux->data.first)) {
            // Inserăm între două noduri
            prev->next = newNode;
            newNode->next = aux;
        } else {
            // Inserăm la final
            prev->next = newNode;
            newNode->next = nullptr;
        }
    }

    length_table++;
    load_factor = (float)length_table / (float)capacity_table;
}
*/
/*
bool SortedMultiMap::remove(TKey c, TValue v) {
    vector<TValue> key_values = search(c);
    if(key_values.empty()){ // nu exista elemente de sters la cheia c
        return false;
    }
    int value = hash(c);
    Node* head = lista_noduri[value];
    Node* aux = head;

    while(head != nullptr && r(c,head->data.first)){
        if(c == head->data.first){
            if(v == head->data.second){ // stergem elementul
                if(aux == head){ // stergere inceput
                    lista_noduri[value] = head->next;
                    delete head;
                    head = aux->next;
                }
                else if(head->next == nullptr){ // stergere sfarsit
                    aux->next = nullptr;
                    delete head;
                }
                else{
                    aux->next = head->next;
                    delete head;
                }
            }
        }
        aux = head;
        head = head->next;
    }
    length_table--;

    return true;
}
*/
/*
vector<TValue> SortedMultiMap::search(TKey c) const {
	vector<TValue> rezult;
    cout<<"rezult.size:"<< rezult.size();
    int value = hash(c);
    Node* aux = lista_noduri[value];
    while(aux != nullptr){
        if(aux->data.first == c){
            while(aux != nullptr && aux->data.first == c){
                rezult.push_back(aux->data.second);
                cout<<"valoare cheie: "<< aux->data.second<<'\n';
                aux = aux->next;
            }
            return rezult;
        }
        aux = aux->next;
        if(aux != nullptr && r(c,aux->data.first) == false){
            return rezult;
        }
    }
}
*/
/*
void SortedMultiMap::rehash() {
    this->capacity_table *=2;
    this->load_factor = (float)length_table/(float)capacity_table;
    Node ** lista_noua_noduri;
    lista_noua_noduri = new Node*[this->capacity_table];
    for (int i = 0; i < this->capacity_table; i++) {
        lista_noua_noduri[i] = lista_noduri[i];
    }
    for (int i = 0; i < capacity_table; ++i) {
        Node* aux = lista_noduri[i];
        while (aux != nullptr) {
            Node* toDelete = aux;
            aux = aux->next;
            delete toDelete;
        }
    }
    delete[] lista_noduri;
    lista_noduri = lista_noua_noduri;

}
 */


