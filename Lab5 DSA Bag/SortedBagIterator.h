#pragma once
#include "SortedBag.h"

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
	const SortedBag& bag;
	SortedBagIterator(const SortedBag& b);
    SortedBag::Node  *currentNode;
    struct StackNode{
        SortedBag::Node * data;
        StackNode* next;
    };
    class Stack{
    private:
        StackNode* topNode;
    public:
        Stack(){ topNode = nullptr; }
        // Complexity Theta(1) in afara de destructor Theta(n)
        void push(SortedBag::Node* pushNode){
            StackNode* newNode = new StackNode;
            newNode->data = pushNode;
            newNode->next = topNode;
            topNode = newNode;
        }
        void pop(){
            if(topNode != nullptr) {
                StackNode *deletedNode = topNode;
                topNode = topNode->next;
                delete deletedNode;
            }
        }
        SortedBag::Node* top(){
            return topNode->data;
        }
        bool isEmpty(){
            return topNode == nullptr;
        }
        ~Stack(){
            while(topNode != nullptr){
                StackNode* aux = topNode;
                topNode = topNode->next;
                delete aux;
            }
        }
    };
    Stack stack;


public:
	TComp getCurrent();
	bool valid();
	void next();
	void first();
};

