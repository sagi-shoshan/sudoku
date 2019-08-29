/*
 *
 * Game.h
 *
 */

#ifndef GAME_H_
#define GAME_H_
#include "Solver.h"
#include "Files.h"

extern int gameOver;
extern int mark_errors_state;
extern mode_Type game_mode;
extern sudoku s_game;
extern int cells_To_fill;
extern Node* DLL;



/*Starts a puzzle in Solve mode, loaded from a file with the name "X", where X includes a full or relative path to the file.
 *returns a sudoku with mode 'solve_M' if X exists, or 'init_M' if the address is wrong*/
sudoku* solve(char* X);

/*Starts a puzzle in Edit mode, loaded from a file with the name "X", where X includes a full or relative path to the file.
 *The parameter X is optional. If no parameter is supplied, the program should enter Edit mode with an empty 9x9 board.
 *returns a sudoku with mode 'edit_M' if X exists, or 'init_M' if the address is wrong*/
sudoku* edit(char* X);

/*Sets the "mark errors" setting to X, where X is either 0 or 1.
 * only available in 'Solve' mode. */
void mark_errors(int X);

/*Prints the board to the user.
 *This command is only available in 'Edit' and 'Solve' modes. */
void print_board(sudoku* s);


void set(sudoku* s, command c);

void validate(sudoku* s);

void guess();

void generate();

void undo();

void redo();

void save();

void hint(sudoku* s, command c);

void guess_hint();

void num_solutions();

void autofill();

void reset();


/* free memory of sudoku structure using void freeSudokuMemory(s), print: "Exiting..." and then exit() or break game loop */
void exitGame(sudoku* s);

/* free memory of sudoku structure using void freeSudokuMemory(s) and start game loop again */
void restart(sudoku* s);

/* if s->values contains 0, not over, otherwise if all is legal: over. returns: 0 or 1 */
int checkGameOver(struct sudoku* s);



#endif /* GAME_H_ */
