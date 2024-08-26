#pragma once

#include "SortedMultiMap.h"


class SMMIterator{
	friend class SortedMultiMap;
private:
	//DO NOT CHANGE THIS PART
	const SortedMultiMap& map;
	SMMIterator(const SortedMultiMap& map);

    SortedMultiMap::Node *current, *head;
    int pos;

public:
	void first();
	void next();
	bool valid() const;
   	TElem getCurrent() const;
};

