
#include "SortedBag.h"
#include "SortedBagIterator.h"

#include<iostream>
using namespace std;

SortedBag::SortedBag(Relation r) : r(r), root(nullptr), nr_elems(0) {
}

/*
 * Best Case: Theta(1)
 * Average Case: Theta(log n)
 * Worst case: Theta(n) degenerat
 * Complexity O(n)
 * */

void SortedBag::insert_rec(Node*& node, TComp e) {
    if (node == nullptr) {
        node = new Node{e, nullptr, nullptr};
        nr_elems++;
        return;
    }
    if (r(e, node->element)) {
        insert_rec(node->leftNode, e);
    } else {
        insert_rec(node->rightNode, e);
    }
}

void SortedBag::add(TComp e) {
    insert_rec(root, e);
}

/*
 * Best Case: Theta(1)
 * Average Case: Theta(log n)
 * Worst case: Theta(n) degenerat
 * Complexity O(n)
 * */

bool SortedBag::delete_rec(Node*& root, TComp e) {
    if (root == nullptr) {
        return false;
    }
    if (root->element == e) {
        if (root->leftNode == nullptr && root->rightNode == nullptr) { // frunza
            delete root;
            root = nullptr;
        } else if (root->leftNode == nullptr) { // copil in dreapta
            Node* temp = root;
            root = root->rightNode;
            delete temp;
        } else if (root->rightNode == nullptr) { // copil in stanga
            Node* temp = root;
            root = root->leftNode;
            delete temp;
        } else { // nodul are si copil stanga si copil dreapta
            Node* temp = root->rightNode;
            Node* parent = root;
            while (temp->leftNode != nullptr) { // inlocuim elementul cu cel mai mic element din subarborele drept
                parent = temp;
                temp = temp->leftNode;
            }
            root->element = temp->element;
            if (parent->leftNode == temp) {
                parent->leftNode = temp->rightNode;
            } else {
                parent->rightNode = temp->rightNode;
            }
            delete temp;
        }
        nr_elems--;
        return true;
    } else if (r(e, root->element)) {
        return delete_rec(root->leftNode, e);
    } else {
        return delete_rec(root->rightNode, e);
    }
}

bool SortedBag::remove(TComp e) {
    return delete_rec(root, e);
}

/*
 * Best Case: Theta(1)
 * Average Case: Theta(log n)
 * Worst case: Theta(n) degenerat
 * Complexity O(n)
 * */

bool SortedBag::search_rec(Node* root, TComp e) const {
    if (root == nullptr) {
        return false;
    }
    if (root->element == e) {
        return true;
    }
    if (r(e, root->element)) {
        return search_rec(root->leftNode, e);
    } else {
        return search_rec(root->rightNode, e);
    }
}

bool SortedBag::search(TComp elem) const {
    return search_rec(root, elem);
}

/*
 * Best Case: Theta(1)
 * Average Case: Theta(log n)
 * Worst case: Theta(n) degenerat
 * Complexity O(n)
 * */

int SortedBag::nrOcur_rec(Node* root, TComp e) const {
    if (root == nullptr) {
        return 0;
    }
    if (e == root->element) {
        return 1 + nrOcur_rec(root->leftNode, e) + nrOcur_rec(root->rightNode, e);
    } else if (r(e, root->element)) {
        return nrOcur_rec(root->leftNode, e);
    } else {
        return nrOcur_rec(root->rightNode, e);
    }
}

int SortedBag::nrOccurrences(TComp elem) const {
    return nrOcur_rec(root, elem);
}

int SortedBag::size() const {
    return nr_elems;
}

bool SortedBag::isEmpty() const {
    return nr_elems == 0;
}

SortedBagIterator SortedBag::iterator() const {
    return SortedBagIterator(*this);
}
/*
 * Complexity Theta(n)
 * */

void SortedBag::destroy_tree(Node* root) {
    if (root != nullptr) {
        destroy_tree(root->leftNode);
        destroy_tree(root->rightNode);
        delete root;
    }
}

bool SortedBag::compareTrees(SortedBag::Node *node1, SortedBag::Node *node2) const {

    if (node1 == nullptr && node2 == nullptr) {
        return true;
    }

    // Dacă unul este nul și celălalt nu, nu sunt egale
    if (node1 == nullptr || node2 == nullptr) {
        return false;
    }

    if(node1->element == node2->element){ // daca au aceeasi valoare
        //cout<<node1->element<<'\n';
        compareTrees(node1->leftNode, node2->leftNode);
        compareTrees(node1->rightNode, node2->rightNode);
    }
    else return false; // daca n au returneaza false
}

bool SortedBag::operator==(SortedBag& other) const {
    return compareTrees(this->root, other.root);
}

SortedBag::~SortedBag() {
    destroy_tree(root);
}
