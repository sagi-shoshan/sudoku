/*
 * Game.c
 *
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Game.h"

int gameOver = 0;
int mark_errors_state = 0;
mode_Type game_mode = init_M;
sudoku s_game;
int cells_To_fill;
Node* DLL;

sudoku* solve(char* file_Name){
	sudoku* s;
	/*checks if the file exist*/
	if ((check_File_Name(file_Name)) == 1){
		s = openFromFile(file_Name);/*****calls to load file from files.c*****/
		cells_To_fill = empty_Cells(s);
		game_mode = solve_M;
	}
	else {
		printf(bad_File);
		game_mode = init_M;
	}
	return s;
}

sudoku* edit (char* file_Name){
	sudoku* s;
	if (file_Name == NULL){
		s = generateSudoku(9, 9);
		cells_To_fill = 81;
		game_mode = edit_M;
	}
	else{
		if((check_File_Name(file_Name)) == 1){
			s = openFromFile(file_Name);/*****calls to load file from files.c*****/
			cells_To_fill = empty_Cells(s);
			game_mode = edit_M;
		}
		else {
			game_mode = init_M;
		}
	}
	return s;
}

void mark_errors(int X) {
	if (check_Mode (mark_errors_C, game_mode) == 1){
		if (X == 1 || X == 0)
			mark_errors_state = X;
		else
			printf(range);
		}
	else {
		printf(cmd_outof_mode);
	}
}

void print_board(sudoku* s){
	if (check_Mode (print_board_C, game_mode) == 1){
		printSudokuBoard(s);
	}
	else {
		printf(cmd_outof_mode);
	}
}

void set(sudoku* s, command c){
	/*if the command is valid to the current mode*/
	if (check_Mode (set_C, game_mode) == 1) {

		/*if user wants to clear the cell*/
		if (c.value == 0){
			if (s->values[c.row][c.column] != 0){
				s->values[c.row][c.column] = 0 ;
				cells_To_fill++;
			}
			printSudokuBoard(s);
			return;
		}

		/*if user wants to insert a new value the cell*/
		else {
			if ( (game_mode == solve_M) && (s->fixed[c.row][c.column] == 1) ) /*blocks fixed cells for 'Solve' mode*/{
				/*if chosen cell is a fixed cell*/
					printf("Error: cell is fixed\n");
					return;
			}

			else { /*'Solve' mode and not fixed, or 'edit' mode*/
				if (s->values[c.row][c.column] == 0){ /*inserting to an empty cell*/
					cells_To_fill--;
				}
				s->values[c.row][c.column] = c.value;
				printSudokuBoard(s);

				if(cells_To_fill == 0){ /*board should be full*/
					if( (checkGameOver(s) == 1) && (is_Solved(s) == 1 ) ){ /*if the board's full-solution is correct*/
						printf("Puzzle solved successfully\n");
						gameOver = 1;
						game_mode = init_M;
						return;
					}
					else /*(checkGameOver(s) == 0)  -> if the board is finished but not correct*/{
						printf(wrong_Solution);
						return;
					}
				}
			}
		}
	}
	else /*(game_mode == init_M)*/{
		printf(cmd_outof_mode);
	}
}

void hint(sudoku* s, command c){
	printf("Hint: set cell to %i\n", s->solution[c.row][c.column]);
	return;
}

void validate(sudoku* s){
	if(backtrack('v', s) == 1){ /*solution is found*/
		printf("Validation passed: board is solvable\n");
	}
	else{
		printf("Validation failed: board is unsolvable\n");
	}
}

/* free memory of sudoku structure using void freeSudokuMemory(s) and start game loop again */
void restart(sudoku* s){
	freeSudokuMemory(s);
	/*gameOver = 0;*/
}

/* free memory of sudoku structure using void freeSudokuMemory(s), print: "Exiting..." and then exit(0) or break game loop */
void exitGame(sudoku* s){
	freeSudokuMemory(s);
	printf("Exiting...\n");
	exit(0);
}

/* if s->values contains 0, not over, otherwise if all is legal: over. returns: 0 or 1 */
int checkGameOver(sudoku* s){
	int row, column;
	for (row = 0; row < 9; row++){
		for (column = 0; column < 9; column++){
			if (s->values[row][column] == 0){
				return 0;
			}
		}
	}
	return 1;
}




