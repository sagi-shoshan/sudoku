/*
 *
 * Files.h
 *
 */

#ifndef FILES_H_
#define FILES_H_
#include "MainAux.h"

/* save sudoku puzzle to file
 * this command does not free the memory of the sudoku sturcture the file is based on
 * */
void saveToFile(struct sudoku * s, char * filename);

/* load sudoku from file */
struct sudoku * openFromFile(char * filename);

/*checks if the file path is valid. TRUE = 1, FALSE = 0*/
int check_File_Name (char* file_Name);

#endif /* FILES_H_ */

