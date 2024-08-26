#pragma once

#include "SortedMultiMap.h"

class SortedMultiMap;

class KeyIterator {
friend class SortedMultiMap;
private:
    const SortedMultiMap& map;
    KeyIterator(const SortedMultiMap& map);
    SortedMultiMap::Node *current, *head;
    int pos;

public:
    void first();
    void next();
    bool valid() const;
    TElem getCurrent() const;
};