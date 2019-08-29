/*
 *
 * Solver.h
 *
 */

#ifndef SOLVER_H_
#define SOLVER_H_
#include "Parser.h"

/*checks how many empty cells are in a given sudoku board*/
int empty_Cells(sudoku* s);

/*checks if the full-sudoku board's solution is correct. TRUE = 1, FALSE = 0*/
int is_Solved (sudoku* s);

sudoku* puzzleGenerator(int H);

void setFixedCells(int H, sudoku* s);

int backtrack(char type, sudoku* s);

/* functions for deterministic backtracking */
int isLegalValue(struct matrix * m, int row, int column, int num);

int isLegalInRow(struct matrix * m, int row, int num);

int isLegalInColumn(struct matrix * m, int column, int num);

int isLegalInBlock(struct matrix * m, int row, int column, int num);

int findNextFreeCell(struct matrix * m);

/* functions for randomized backtracking */
int findLegalOptions(int * vector, struct matrix * m, int row, int column);

int selectDigitForRandomized(int * vector, int size);

/* method 0: deterministic, method 1: randomized */
int backtrackRecursive(struct matrix * m, int method);


/*int isValidInput(sudoku* s, command c);*/

/* the function searches for num in the row: if found, returns not legal, else legal */
/*int isValidInRow(sudoku* s, command c);*/

/*int isValidInColumn(sudoku* s, command c);*/

/* this function is specific to a 3*3 block (for 9*9 sudoku board)
int isValidInBlock(sudoku* s, command c);*/

#endif /* SOLVER_H_ */
