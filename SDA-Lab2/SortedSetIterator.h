#pragma once
#include "SortedSet.h"
// container iterator enuntt complet
//DO NOT CHANGE THIS PART
class SortedSetIterator
{
	friend class SortedSet;
private:
	const SortedSet& multime;

    SortedSetIterator(const SortedSet& m);

    SortedSet::DLLNode* currentNode;

	//TODO - Representation

public:
	void first();//facut
	void next();//facut
	TElem getCurrent();//facut
	bool valid() const;//facut
    void modificareElem(TComp newElem);
};

