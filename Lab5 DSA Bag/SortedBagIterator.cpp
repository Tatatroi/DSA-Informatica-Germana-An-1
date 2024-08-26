#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

// Theta(n)
SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
    currentNode = nullptr;
    first();
}

// Theta(1)
TComp SortedBagIterator::getCurrent() {
    if (!valid()) {
        throw exception();
    }
    return currentNode->element;
}

//Theta(1)
bool SortedBagIterator::valid() {
	return currentNode != nullptr;
}

/*
 * Best Case: Theta(1)
 * Average Case: Theta(log n)
 * Worst case: Theta(n) degenerat
 * Complexity O(n)
 * */
void SortedBagIterator::next() {
    if (!valid()) {
        throw exception();
    }
    if (currentNode->rightNode != nullptr) {
        currentNode = currentNode->rightNode;
        while (currentNode != nullptr) {
            stack.push(currentNode);
            currentNode = currentNode->leftNode;
        }
    }
    if (!stack.isEmpty()) {
        currentNode = stack.top();
        stack.pop();
    } else {
        currentNode = nullptr;
    }

}

// Theta(n)
void SortedBagIterator::first() {
    // In Order
    while (!stack.isEmpty()) { // golire stiva pentru a evita problemele
        stack.pop();
    }
    currentNode = bag.root;
    while (currentNode != nullptr) {
        stack.push(currentNode);
        currentNode = currentNode->leftNode;
    }
    if (!stack.isEmpty()) {
        currentNode = stack.top();
        stack.pop();
    } else {
        currentNode = nullptr;
    }

}

