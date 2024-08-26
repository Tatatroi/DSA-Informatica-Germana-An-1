#include "SortedSet.h"
#include "SortedSetIterator.h"
#include <iostream>
using namespace std;
SortedSet::SortedSet(Relation r) {
	//TODO - Implementation
    this->r = r;
    this->head = NULL;
    this->tail = NULL;
}

/*
 * Best:T(1)
 * Average:T(n)
 * Worst:T(n)
 * */

bool SortedSet::add(TComp elem) {
	if(search(elem) == true)return false; // daca elementul este deja, return false --> proprietatea setului
    else{
        if(head == NULL){ // daca lista este goala adaugam elementul
            DLLNode* aux = new DLLNode; // declaram un aux nou
            aux->next = NULL; // fiind singurul element prev si next sunt NULL iar elementul este si head si tail
            aux->prev = NULL;
            aux->val = elem;

            head = aux;
            tail = aux;
            return true;
        }
        else{// in cazul in care lista nu este goala
            if(this->r(head->val,elem) == false){// daca elem trebuie adaugat pe prima pozitie (relatia intre el si primul el este falsa)
                DLLNode* aux = new DLLNode;
                aux->val = elem;
                aux->next = head;
                aux->prev = NULL;
                head->prev = aux;
                head = aux;
                return true;
            }
            else{// elementul trebuie adaugat undeva in lista
                DLLNode* aux = head;
                DLLNode* insertedElem = NULL;
                while(aux != NULL && this->r(aux->val,elem) == true){ // cautam pozitia unde trebuie inserat
                    insertedElem = aux;
                    aux = aux->next;
                }
                // Avem 2 cazuri, ori se adauga la final ori undeva intre elemente
                if(aux != NULL){ // adaugare undeva in lista, NU final
                    DLLNode* newNode = new DLLNode;
                    newNode->val = elem;
                    insertedElem->next = newNode;
                    newNode->prev = insertedElem;
                    newNode->next = aux;
                    aux->prev = newNode;
                    return true;
                }
                else if(aux == NULL){ // adugare la final
                    DLLNode* newNode = new DLLNode;
                    newNode->next = NULL;
                    newNode->val = elem;
                    newNode->prev = insertedElem;
                    insertedElem->next = newNode;
                    tail = newNode;
                    return true;
                }
            }
        }
    }
}

void SortedSet::afis() {
    DLLNode* aux = head;
    while(aux != NULL){
        cout<<aux->val<<' ' ;
        aux = aux->next;
    }
    cout<<"\n\n";
}

/*
 * Best:T(1)
 * Average:T(n)
 * Worst:T(n)
 * */

bool SortedSet::remove(TComp elem) {
    if(!search(elem)) // Verifică dacă elementul există în set
        return false; // Elementul nu există, deci nu se poate șterge

    if(head == tail) { // Lista conține un singur element
        head = NULL;
        tail = NULL;
        return true;
    }

    DLLNode* aux = head;
    while(aux != NULL && aux->val != elem)
        aux = aux->next;

    if(aux == head) { // Șterge primul element din listă
        head = aux->next;
        head->prev = NULL;
    } else if(aux == tail) { // Șterge ultimul element din listă
        tail = aux->prev;
        tail->next = NULL;
    } else { // Șterge un element din mijlocul listei
        aux->prev->next = aux->next;
        aux->next->prev = aux->prev;
    }

    delete aux; // Eliberează memoria pentru nodul șters
    return true;
}

/*
 * Best:T(1)
 * Average:T(n)
 * Worst:T(n)
 * */

bool SortedSet::search(TComp elem) const {
	if(this->head == NULL)return false; // daca list ete goala se returneaza false->nu avem ce sterge
    DLLNode* aux = head;
    while(aux != NULL && aux->val != elem){ //mergem pana la element daca nu il gasim returnam false mai jos
        aux = aux->next;
    }
    if(aux == NULL)return false;
	return true;
}

/*
 * Best:T(1)
 * Average:T(n)
 * Worst:T(n)
 * */
int SortedSet::size() const {
	if(this->isEmpty() == true)return 0; // daca este goala se returneaza 0
    else {
        int cnt = 0;
        DLLNode *aux = head;
        while (aux != NULL) {
            cnt++;
            aux = aux->next;
        }
        return cnt;
    }
}

/*
* Best:T(1)
* Average:T(1)
* Worst:T(1)
* */
bool SortedSet::isEmpty() const {
	if(head == NULL)return true;
	return false;
}



SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}



/*
 * Best:T(n)
 * Average:T(n)
 * Worst:T(n)
 * */
SortedSet::~SortedSet() { // Ne plimbam prin fiecare nod de la cap la sfarsit si il stergem
    DLLNode* aux = head;
    DLLNode* nodDeSters = NULL;
    while(aux != NULL){
        nodDeSters = aux;
        aux = aux->next;
        delete nodDeSters;
    }
	//TODO - Implementation
}


