#include <assert.h>
#include "Matrix.h"

#include <iostream>

using namespace std;

void testAll() { 
	Matrix m(4, 4);
	assert(m.nrLines() == 4);
	assert(m.nrColumns() == 4);	
	m.modify(1, 1, 5);
    m.element(1,1);
	assert(m.element(1, 1) == 5);
	m.modify(1, 1, 6);
	assert(m.element(1, 2) == NULL_TELEM);


    m.modify(2,2,10);
    m.resizeMatrix(6,6);
    assert(m.element(4,4) == 0);
    m.resizeMatrix(2,2);
    assert(m.element(1,1) == 6);


}