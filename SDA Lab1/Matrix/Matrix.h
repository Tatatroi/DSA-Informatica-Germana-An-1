#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

/*
ADT Matrix (CRS) – repräsentiert als schwachbesetze Matrix (sparse) in dem Compressed Row
Storage Format (CRS) mithilfe von dynamischen Arrays
 * */


class Matrix {

private:
	//TODO - Representation
    int nrlines,nrcols;
    int capacity_non_zero_values; // capacity of the non_zero values and column indexes
    TElem *non_zero_elements;
    int *column_indexes;
    int *start_row_indexes;
    int len_non_zero_values;  // length1 -> non_zero_elements && column_indexes || length2 -> start_row_indexes
    void resizeUp();
    void resizeDown();

public:
	//constructor
	Matrix(int nrLines, int nrCols);

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);


    void resizeMatrix(int newLines, int newColumns);
    // destructor
	~Matrix();

};
