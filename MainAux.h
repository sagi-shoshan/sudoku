/*
 *
 * MainAux.h
 *
 */

#ifndef MAINAUX_H_
#define MAINAUX_H_

typedef enum {init_M, edit_M, solve_M} mode_Type;

typedef enum {
	solve_C, edit_C, mark_errors_C, print_board_C, set_C, validate_C, guess_C, generate_C,
	undo_C, redo_C, save_C, hint_C, guess_hint_C, num_solutions_C, autofill_C, reset_C, exit_C,
	invalid_C, empty_C} command_Type;

/*
 * sudoku is a structure made of 2 matrixes:
 * 1. a matrix containing the sudoku puzzle's values (fixed or entered by the user)
 * 2. a matrix specifying whether values are fixed (1) or not (0).
 * 3. the size of the matrixes
 * */
typedef struct sudoku{
	int ** values;
	int ** fixed;
	int ** solution;
	int ** errors;
	int matrixSize;
	int markErrors;
	int n;
	int m;
} sudoku;

/* matrix is a structure used only for backtracking
 * row and column represent the next row, column to visit
 * */
typedef struct matrix{
	int ** mat;
	int size;
	int row;
	int column;
}matrix;

typedef struct command{
	command_Type C_Type;
	char* C_Type_Name;
	char* file_Name;
	int mark_errors;
	int value;
	int row;
	int column;
	int threshold;
	int empty_cells;
	int dont_empty_cells;
} command;

typedef struct Node { /*doubly linked list node*/
	command c;
	int X;
	int Y;
	int from;
	int to;
    struct Node* next; /* Pointer to next node in*/
    struct Node* prev; /* Pointer to previous node*/
}Node;


/* functions creating and deleting the sudoku structure */
sudoku* generateSudoku(int n, int m);

void freeSudokuMemory(struct sudoku * s);

/*checks if the command is valid in the given mode. return 1 = TRUE, 0 = FALSE*/
int check_Mode(command_Type C_type, mode_Type M_type);

/* functions creating and deleting a matrix used for backtracking */
struct matrix * generateMatrix(struct sudoku * s);

void freeMatrixMemory(struct matrix * m);

/* getting random numbers */
int getRandomNumber(int X); /* the function returns a random number between 0 and X-1 */

/* printing function */
void printSudokuBoard(sudoku * s); /* the function prints the board as specified in the instruction doc */

void funcFailed(char * func);

#endif /* MAINAUX_H_ */
