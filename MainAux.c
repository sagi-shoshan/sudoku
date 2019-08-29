/*
 *
 * MainAux.c
 *
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "MainAux.h"

int check_Mode(command_Type C_type, mode_Type M_type){

	/*available at all modes*/
	if (C_type == solve_C || C_type == edit_C || C_type == exit_C){
		return 1;
	}

	/*available only at solve mode*/
	if (C_type == mark_errors_C || C_type == guess_C || C_type == hint_C || C_type == guess_hint_C || C_type == autofill_C){
		if (M_type == solve_M){
			return 1;
		}
		else {
			return 0;
		}
	}

	/*available only at edit mode*/
	if (C_type == generate_C){
		if (M_type == edit_M){
			return 1;
		}
		else {
			return 0;
		}
	}

	/*available at solve & edit mode*/
	if (C_type == print_board_C || C_type == set_C || C_type == validate_C || C_type == undo_C || C_type == redo_C
			|| C_type == save_C || C_type == num_solutions_C || C_type == reset_C){
		if (M_type == solve_M || M_type == edit_M){
			return 1;
		}
		else {
			return 0;
		}

	}
	return 0;
}


/* the function generates a sudoku structure of a specified size
 * (s is a pointer to a sudoku structure)*/
sudoku* generateSudoku(int m, int n){
	int i = 0;
	int size;
	struct sudoku * s;
	size = n * m;
	s = malloc(sizeof(*s));
    s->values = calloc(size, sizeof(int*));
    s->fixed = calloc(size, sizeof(int*));
    s->solution = calloc(size, sizeof(int*));
    s->errors = calloc(size, sizeof(int*));
    for(i = 0; i < size; i++){
    	s->values[i] = calloc(size, sizeof(int));
    	s->fixed[i] = calloc(size, sizeof(int));
    	s->solution[i] = calloc(size, sizeof(int));
    	s->errors[i] = calloc(size, sizeof(int));
    }
    s->matrixSize = size;
    s->markErrors = 1;
    s->n = n;
    s->m = m;
    return s;
}

void freeSudokuMemory(sudoku* s){
	int i = 0;
	/* freeing dynamically allocated memory */
	for(i = 0; i < s->matrixSize; i++){
		free(s->values[i]);
		free(s->fixed[i]);
		free(s->solution[i]);
		free(s->errors[i]);
	}
	free(s->values);
	free(s->fixed);
	free(s->solution);
	free(s->errors);
	free(s);
	return;
}

matrix* generateMatrix(sudoku* s){
	int i = 0;
	matrix* m;
	m = malloc(sizeof(*m));
	m->mat = calloc(s->matrixSize, sizeof(int*));
	for(i = 0; i < s->matrixSize; i++){
		m->mat[i] = calloc(s->matrixSize, sizeof(int));
	}
	m->size = s->matrixSize;
	m->row = 0;
	m->column = 0;
	return m;
}

void freeMatrixMemory(matrix* m){
	int i = 0;
	/* freeing dynamically allocated memory */
	for(i = 0; i < m->size; i++){
		free(m->mat[i]);
	}
	free(m->mat);
	free(m);
	return;
}

/* the function returns a random number between 0 and X-1 */
 int getRandomNumber(int X){
 	return rand()%X;
 }

 /* the function prints the board as specified in the instruction doc
  * these rules are specific to a 9*9 board!*/
 void printSudokuBoard(sudoku* s){
	 int N, i, j, k;
	 N = (s->n)*(s->m);
	 for (i = 0; i < N; i++) {
	     if (i % s->m == 0) {
	    	 /*print separator lines*/
	         for (k = 0; k < 4 * N + s->m + 1; k++) {
	             printf("-");
	         }
	         printf("\n");
	     }
	     for (j = 0; j < N; j++) {
	    	 /*print pipes*/
	    	 if (j % s->n == 0 && j != 0) {
	    		 printf("|");
	    	 }
			 else if (j == 0) {
				 printf("|");
			 }
	    	 /*print values, as specified in instructions*/
	    	 if (s->values[i][j] == 0){
	    		 printf("    ");
	    	 }
	    	 else {
                 if(s->fixed[i][j] == 1) {
                     printf(" %2d.", s->values[i][j]);
                 }
                 else if ((s->errors[i][j] == 1) && (s->markErrors == 1)) {
                	 printf(" %2d*", s->values[i][j]);
                 }
                 else {
                	 printf(" %2d ", s->values[i][j]);
                 }
	    	 }
	     }
	     printf("|\n");
	 }
	 /*print separator lines*/
     for (k = 0; k < 4 * N + s->m + 1; k++) {
         printf("-");
     }
     printf("\n");
 }

 void funcFailed(char* func){
 	printf("Error: %s has failed\n",func);
 	exit(0);
 }
