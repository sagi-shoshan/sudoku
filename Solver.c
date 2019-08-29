/*
 *
 * Solver.c
 *
 */


#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Solver.h"

int empty_Cells(sudoku* s){
	int count = 0;
	int i, j;
	for (i = 0; i < (s->n); i++){
		for (j = 0; j < (s->m); j++){
			if (s->values[i][j] == 0)
				count++;
		}
	}
	return count;
}

int is_Solved (sudoku* s){
	(void)(s);
	return 1;
}

/* this function creates an empty board, uses randomized backtracking to generate a solved board, and sets H fixed cells */
sudoku* puzzleGenerator(int H){
	/* creating empty sudoku board */
	sudoku* s = generateSudoku(3, 3);
	/* getting a random solved board */
	backtrack('r', s);
	/* setting H random fixed cells */
	setFixedCells(H, s);
	return s;
}

/* this function gets a sudoku structure with a solution and leaves the structure with H random fixed cells */
void setFixedCells(int H, sudoku* s){
	/* in instructions, X is column, Y is row */
	int counter, column, row;
	counter = 0;
	while (counter < H){
		column = getRandomNumber(s->matrixSize);
		row = getRandomNumber(s->matrixSize);
		if (s->fixed[row][column] == 1)
			continue;
		else{
			s->fixed[row][column] = 1;
			s->values[row][column] = s->solution[row][column];
			counter++;
		}
	}
}

/* this function gets a sudoku structure and a type:
 * type = 'h' --> deterministic backtracking for hints
 * type = 'v' --> deterministic backtracking for validity check
 * type = 'r' --> randomized
 * int paramaters r, c are used only when checking for hints (their values don't matter for other types)
 *
 * */
int backtrack(char type, sudoku* s){
	int i, j, res;
	matrix* m;
	m = generateMatrix(s);

	/* adding values to matrix from sudoku structure - creating 'values' copy */
	for (i = 0; i < s->matrixSize; i++){
		for (j = 0; j < s->matrixSize; j++){
			m->mat[i][j] = s->values[i][j];
		}
	}
	/* backtrack */

	/* performing deterministic backtracking for validity check */
	if (type == 'v'){
		res = backtrackRecursive(m, 0);
		if (res == 1){
			for (i = 0; i < s->matrixSize; i++){
				for (j = 0; j < s->matrixSize; j++){
					s->solution[i][j] = m->mat[i][j];
				}
			}
		}
		freeMatrixMemory(m);
		return res;
		/*res == 0 --> invalid, res == 1 --> valid */
	}
	/* performing deterministic backtracking for hints check - this is currently not relevant
	 * in the big project we should receive int r, int c as part of the func input, and 'value' as func int field.
	if (type == 'h'){
		res = backtrackRecursive(m, 0);
		if (res == 1){
			value = m->mat[r][c];
			freeMatrixMemory(m);
			return value;
		}
		freeMatrixMemory(m);
		return 0;
	}
	*/

	/* performing randomized backtracking generating a board */
	if (type == 'r'){
		backtrackRecursive(m, 1);
		/* copying results of backtracking into s->solution and setting all fields to NOT fixed */
		for (i = 0; i < s->matrixSize; i++){
			for (j = 0; j < s->matrixSize; j++){
				s->solution[i][j] = m->mat[i][j];
				s->fixed[i][j] = 0;
			}
		}
		freeMatrixMemory(m);
		return 0;
	}

	return 0; /*this will not be used*/
}

/* method 0: deterministic, method 1: randomized */
int backtrackRecursive(matrix* m, int method){
	int row, column, value;
	if (findNextFreeCell(m) == 0) /*matrix ix full*/
		return 1;
	else{
		/* setting row, column variables (m->row/column change throughout the runs) */
		row = m->row;
		column = m->column;
		/* performing randomized backtracking with recursion */
		if (method == 1){
			int i, count;
			int vector[9]; /* I got an error for int vector[m->size] so this is not dynamic */
			int * v; /*initiate a vector {1, 1, 1... ,1}*/
			for (i = 0; i < m->size; i++){
				vector[i] = 1;
			}
			v = &vector[0];
			count = findLegalOptions(v, m, row, column);
			for (i = 1; i < count+1; i++){
				/*select digits for randomized for (&vector)*/
				value = selectDigitForRandomized(v, 9);
				m->mat[row][column] = value;
				if (backtrackRecursive(m, 1) == 1)
					return 1;
				else
					/*change*/
					vector[value-1] = 0;
					m->mat[row][column] = 0;
			}
		}
		/* performing deterministic backtracking with recursion */
		else{
			for (value = 1; value < 10; value++){
				if (isLegalValue(m, row, column, value) == 1){
					m->mat[row][column] = value;
					if (backtrackRecursive(m, 0) == 1)
						return 1;
					else
						m->mat[row][column] = 0;
				}
			}
		}
		return 0;
	}
}

/* the function gets a vector of legal values for a cell and selects one of them */
int selectDigitForRandomized(int* vector, int size){
	int i = 0, vector_count = 0, random_res = 0, counter = 0, latest_one = 0;
	/* counting number of options in vector */
	for (i = 0; i < size; i++){
		if (vector[i] == 1){
			vector_count++;
			latest_one = i + 1;
		}
	}
	/* if only one value is legal, return that value */
	if (vector_count == 1){
		return latest_one;
	}
	/* getting a random number between 0 to vector_count-1 */
	random_res = getRandomNumber(vector_count);
	/* finding the corresponding value between 1-9 */
	for (i = 0; i < size; i++){
		if ((vector[i] == 1) && (counter == random_res)) {
			return (i + 1);
		}
		else {
			if (vector[i] == 1)
				counter += 1;
		}
	}
	return 0; /* this shouldn't happen */
}

int isLegalValue(matrix* m, int row, int column, int num){
	if ((isLegalInRow(m, row, num) == 1) &&
		(isLegalInColumn(m, column, num) == 1) &&
		(isLegalInBlock(m, row, column, num) == 1))
		return 1;
	return 0;
}

/* the function searches for num in the row: if found, returns not legal, else legal */
int isLegalInRow(matrix* m, int row, int num){
	int i = 0;
	for (i = 0; i < m->size; i++){
		if (i != m->column){ /*ignore the cell itself*/
			if(m->mat[row][i] == num)
				return 0;
		}
	}
	return 1;
}

int isLegalInColumn(matrix* m, int column, int num){
	int i = 0;
	for (i = 0; i < m->size; i++){
		if ( i != m->row){ /*ignore the cell itself*/
			if(m->mat[i][column] == num)
				return 0;
		}
	}
	return 1;
}

/* this function is specific to a 3*3 block (for 9*9 sudoku board) */
int isLegalInBlock(matrix* m, int row, int column, int num){
	int start_row, start_col, i, j;
	start_row = (row - (row % 3));
	start_col = (column - (column % 3));
	for (i = start_row; i < start_row + 3; i++){
		for (j = start_col; j < start_col + 3; j++){
			if(i != m->row || j != m->column){ /*ignore the cell itself*/
				if (m->mat[i][j] == num)
					return 0;
			}
		}
	}
	return 1;
}

/* this function sets the matrix structure's row & column parameters every iteration.
 * It returns 1 when a free cell is found and 0 when no free cell is found.
 *  */
int findNextFreeCell(matrix* m){
	int i, j;
	m->row = 0;
	m->column = 0;
	for (i = 0; i < m->size; i++){
		for (j = 0; j < m->size; j++){
			if (m->mat[i][j] == 0){
				m->row = i;
				m->column = j;
				return 1;
			}
		}
	}
	return 0;
}


/* the function gets a pointer to vector[9] of 1s and returns pointer to the vector containing 0s and 1s
 * this represents the numbers between 1-9 that are available to place in a given cell
 * the function checks which numbers already exist in the row, column and block, and places 0s in their indexes
 * creating and freeing the memory occurs elsewhere
 * */
int findLegalOptions(int* vector, matrix* m, int row, int column){
	int i = 0, j = 0, value = 0, start_row = 0, start_col = 0, count = 0;
	/* run on row: delete from vectors values already in row */
	for (i = 0; i < m->size; i++){
		value = 0; /*we can skip the usage of 'value' and re-zero cells if needed - same thing*/
		/* if a matrix value is not 0, find the corresponding place in the vector and set it to 1 */
		if (m->mat[row][i] != 0){
			value = m->mat[row][i];
			if (vector[value - 1] != 0){
				vector[value - 1] = 0;
			}
		}
	}
	/* run on column: delete from vectors values already in column */
	for (i = 0; i < m->size; i++){
		value = 0;
		/* if a matrix value is not 0, find the corresponding place in the vector and set it to 1 */
		if (m->mat[i][column] != 0){
			value = m->mat[i][column];
			if (vector[value - 1] != 0){
				vector[value - 1] = 0;
			}
		}
	}
	/* run on block: delete from vectors values already in column */
	start_row = (row - (row % 3));
	start_col = (column - (column % 3));
	for (i = start_row; i < start_row + 3; i++){
		for (j = start_col; j < start_col + 3; j++){
			value = 0;
			if (m->mat[i][j] != 0){
				value = m->mat[i][j];
				if (vector[value - 1] != 0){
					vector[value - 1] = 0;
				}
			}
		}
	}
	/*previously: function returned int * with: return vector*/
	for (i = 0; i < m->size; i++){
		if(vector[i] == 1){
			count++;
		}
	}
	return count;
}

/*****check legality of user input
int isValidInput(struct sudoku * s, struct command c){
	if ((isValidInRow(s, c) == 1) &&
		(isValidInColumn(s, c) == 1) &&
		(isValidInBlock(s, c) == 1))
		return 1;
	return 0;
}
*/

/* the function searches for num in the row: if found, returns not legal, else legal */
/*
int isValidInRow(struct sudoku * s, struct command c){
	int i = 0;
	for (i = 0; i < s->matrixSize ; i++){
		if (i != c.column){
			if(s->values[c.row][i] == c.value)
				return 0;
		}
	}
	return 1;
}

int isValidInColumn(struct sudoku * s, struct command c){
	int i = 0;
	for (i = 0; i < s->matrixSize; i++){
		if (i != c.row){
			if(s->values[i][c.column] == c.value)
				return 0;
		}
	}
	return 1;
}

 this function is specific to a 3*3 block (for 9*9 sudoku board)
int isValidInBlock(struct sudoku * s, struct command c){
	int start_row, start_col, i, j;
	start_row = (c.row - (c.row % 3));
	start_col = (c.column - (c.column % 3));
	for (i = start_row; i < start_row + 3; i++){
		for (j = start_col; j < start_col + 3; j++){
			if (i != c.row || j != c.column){
				if (s->values[i][j] == c.value)
					return 0;
			}
		}
	}
	return 1;
}
*/


