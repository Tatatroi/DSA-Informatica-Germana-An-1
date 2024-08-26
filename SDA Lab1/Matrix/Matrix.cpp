#include <iostream>

#include "Matrix.h"
#include <exception>
using namespace std;

// Constructor
Matrix::Matrix(int nrLines, int nrCols) {
    this->nrlines = nrLines;
    this-> nrcols = nrCols;

    this->capacity_non_zero_values = 10;
    this->len_non_zero_values = 0;

    this->non_zero_elements = new TElem[10];
    this->column_indexes = new int[10];
    this->start_row_indexes = new int[this->nrlines+1];

    // make 0 all indexes_lines
    for(int i = 0; i<= nrlines; i++){
        start_row_indexes[i] = 0;
    }
}


int Matrix::nrLines() const { // return nrLines
	return this->nrlines;
}


int Matrix::nrColumns() const { // return nrCols
	return this->nrcols;
}

/*
For all cases complexity is ⊝(n) because in all cases it makes n steps
* */
void Matrix::resizeUp(){
    int newCap = capacity_non_zero_values * 2; // declare new capacity

    TElem* non_zero_el = new TElem[newCap]; // new elements with capacity new_Capacity
    int* new_columns = new int[newCap];

    for(int i = 0; i < len_non_zero_values;i++){ // copy the values from the old vectors in the new one
        non_zero_el[i] = non_zero_elements[i];
        new_columns[i] = column_indexes[i];
    }

    delete[] this->non_zero_elements; // dealocate space in the memory
    delete[] this->column_indexes;

    this->capacity_non_zero_values = newCap; // reinizializare valori vechi cu valori noi
    this->non_zero_elements = non_zero_el;
    this->column_indexes = new_columns;


}

//redimensionare matrice 5*4 -> 2*7

void Matrix::resizeMatrix(int newLines, int newColumns) {
    if(newLines < 0 || newColumns < 0){
        throw runtime_error("Nu se poate redimensiona");
    }

    if(newLines >= nrlines && newColumns >= nrcols){
        // toate elementele raman la fel, dar se actualizeaza nrLines si nrCols si se da resize up
        this->nrlines = newLines;
        this-> nrcols = newColumns;
        resizeUp();
    }
    else if(newLines < nrlines && newColumns >= nrcols){
        // merg pe intervalul de la linia i pana la sfarsit si sterg elementele --> sterg toate elementele care se afla pe liniile in plus
        int start = start_row_indexes[newLines];
        for(int liniiDeSters = 1; liniiDeSters <= nrlines-newLines; liniiDeSters++) {
            for (int elementeSterse = start; elementeSterse < len_non_zero_values - 1; elementeSterse++) {
                non_zero_elements[elementeSterse] = non_zero_elements[elementeSterse + 1];

            }
            len_non_zero_values--;
        }

        nrlines = newLines;
        nrcols = newColumns;
    }
    else if(newColumns < nrcols && newLines >= nrlines){
        // merg pe intervalul de la coloana pana la sfarsit si sterg elementele din non_zero_elements si column_idexes
        for(int coloana = 0; coloana<len_non_zero_values; coloana++){ // ma plimb prin toate coloanele elementelor
            if(column_indexes[coloana] > newColumns){ //daca da True sterg elementul deoarece nu mai are ce sa caute in matrice
                for (int l = coloana; l < len_non_zero_values - 1; l++) { // delete the element in the memory
                    this->non_zero_elements[l] = this->non_zero_elements[l + 1];
                    this->column_indexes[l] = this->column_indexes[l + 1];
                }
                this->len_non_zero_values--; // decrease the length due to deletion

            }
        }
        nrlines = newLines;
        nrcols = newColumns;
    }
    else if(newColumns < nrcols && newLines < nrlines){
        // sterg valorile de pe randurile in plus
        int start = start_row_indexes[newLines];
        for(int liniiDeSters = 1; liniiDeSters <= nrlines-newLines; liniiDeSters++) {
            for (int elementeSterse = start; elementeSterse < len_non_zero_values - 1; elementeSterse++) {
                non_zero_elements[elementeSterse] = non_zero_elements[elementeSterse + 1];

            }
            len_non_zero_values--;
        }
        // sterg valorile de pe randurile in plus

        for(int coloana = 0; coloana<len_non_zero_values; coloana++){ // ma plimb prin toate coloanele elementelor
            if(column_indexes[coloana] > newColumns){ //daca da True sterg elementul deoarece nu mai are ce sa caute in matrice
                for (int l = coloana; l < len_non_zero_values - 1; l++) { // delete the element in the memory
                    this->non_zero_elements[l] = this->non_zero_elements[l + 1];
                    this->column_indexes[l] = this->column_indexes[l + 1];
                }
                this->len_non_zero_values--; // decrease the length due to deletion
            }
        }
        nrlines = newLines;
        nrcols = newColumns;
    }
}

/*
For all cases complexity is ⊝(n) because in all cases it makes n steps
* */
void Matrix::resizeDown(){
    this->capacity_non_zero_values = this->capacity_non_zero_values / 2;

    int newCap = capacity_non_zero_values / 2; // declare new capacity

    TElem* non_zero_el = new TElem[newCap]; // new elements with capacity new_Capacity
    int* new_columns = new int[newCap];

    for(int i = 0; i < len_non_zero_values;i++){ // copy the values from the old vectors in the new one
        non_zero_el[i] = non_zero_elements[i];
        new_columns[i] = column_indexes[i];
    }

    delete[] this->non_zero_elements; // dealocate space in the memory
    delete[] this->column_indexes;

    this->capacity_non_zero_values = newCap; // reinizializare valori vechi cu valori noi
    this->non_zero_elements = non_zero_el;
    this->column_indexes = new_columns;

}

/*
* Best Case: ⊝(1) -> the element is at the first position
* Average Case: O(n) --> almost as linear search
* Worst Case: ⊝(n) -> the element is at the last position
* */
TElem Matrix ::element(int i, int j) const{
    if(i >= this->nrlines || j >= this->nrcols || i < 0 || j < 0){ // check the matrix bounderies
        throw runtime_error("Indicii sunt in afara limitelor matricei");
    }
    for (int k = start_row_indexes[i]; k < start_row_indexes[i + 1]; k++) { // this for goes in the interval of the values on line i
        if (this->column_indexes[k] == j) { // check the existance of the on the line i and column j
            return this->non_zero_elements[k]; // return it
        }
    }
    return NULL_TELEM; // if no element found at (i,j) return NULL_TELEM
}

/* for deletion
             * Best Case: ⊝(1) -> when the element is on the first position in interval [i,i+1)
             * Average Case: ⊝(n^2)
             * Worst Case: ⊝(n^2) -> when the element is at the last position in interval [i,i+1)
* */
TElem Matrix::modify(int i, int j, TElem e) {
    if(i >= this->nrLines() || j >= this->nrColumns() || i < 0 ||j < 0){ // check indexes to be in the bounderies of the matrix
        throw runtime_error("Indicii sunt in afara limitelor matricei");
    }
    else {
        if(e == NULL_TELEM){ // delete the element ( NULL_TELEM means we want to delete the element)

            for (int k = this->start_row_indexes[i]; k < this->start_row_indexes[i + 1]; k++) { // check elemnts at the line i
                if (this->column_indexes[k] == j) { // if there is an element at the line i and column j

                    TElem previousValue = this->non_zero_elements[k]; // save the elemnt to return it later

                    for (int l = k; l < this->len_non_zero_values - 1; l++) { // delete the element in the memory
                        this->non_zero_elements[l] = this->non_zero_elements[l + 1];
                        this->column_indexes[l] = this->column_indexes[l + 1];
                    }

                    this->len_non_zero_values--; // decrease the length due to deletion

                    for (int row = i + 1; row <= this->nrlines; row++) { // decrease intervals by one due to deletion.
                        this->start_row_indexes[row]--;
                    }
                    return previousValue; // return the oldValue
                }
            }
            return NULL_TELEM; // if no element found at (i,j) then return NULL_TELEM
        }

        // if I want to modify an element I need to check if it s in the vector, so I look for his pozition

        int indice_val = -1;
        for(int poz = start_row_indexes[i]; poz<start_row_indexes[i+1]; poz++){  // takes the index of the element 'e' in the non_zero_elements vector
            if(column_indexes[poz] == j){
                indice_val = poz;
                break;
            }
        }

        if(indice_val != -1){ // if the element exist --> Change: save the value of it, update it with the new value (als Parameter) and return the old one
            TElem oldValue = non_zero_elements[indice_val];
            non_zero_elements[indice_val] = e;
            return oldValue;
        }
        else{ // if no element found at (i,j) --> Insertion of the new element
            if(len_non_zero_values >= capacity_non_zero_values){ // resize it up for more space
                resizeUp();
            }

            indice_val = start_row_indexes[i];
            while (indice_val < this->start_row_indexes[i + 1] && this->column_indexes[indice_val] < j) {
                indice_val++;
            } // it looks for the indices where the new element shoud be inserted

            for (int k = this->len_non_zero_values; k > indice_val; k--) { // make space for the new element
                this->non_zero_elements[k] = this->non_zero_elements[k - 1];
                this->column_indexes[k] = this->column_indexes[k - 1];
            }

            this->non_zero_elements[indice_val] = e; // insert it in the elements and cols
            this->column_indexes[indice_val] = j;

            for (int k = i + 1; k <= this->nrlines; k++) { //increase the row indexes from line i+1 to nrlines
                this->start_row_indexes[k]++;
            }
            this->len_non_zero_values++; // increase the len
            return NULL_TELEM; // return NULL_TELEM because nothing was before
        }

    }

}

Matrix::~Matrix() {
	//TODO - Implementation
    delete[] this->non_zero_elements;
    delete[] this->column_indexes;
    delete[] this->start_row_indexes;
}


