#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Files.h"

#define UNUSED(x) (void)(x)


int check_File_Name (char* file_Name){
	UNUSED(file_Name);
	return 0;
}


/*Ofir: does not deal with relative paths!!!*/
void saveToFile(struct sudoku * s, char * filename){
	int i, j;
	const char *newline = "\n";
	const char *space = " ";
	FILE *f = fopen(filename, "w");
	if (f == NULL) {
	    printf("Error opening file!\n");
	    exit(1);
	}
	/* writing: m, n to file */
	fprintf(f, "%d %d\n", s->m, s->n);

	/* writing sudoku matrix to file */
	for (i = 0; i < s->matrixSize; i++){
		for (j = 0; j<s->matrixSize; j++){
			if (s->fixed[i][j] == 1){
				fprintf(f, "%d.", s->values[i][j]);
			}
			else {
				fprintf(f, "%d", s->values[i][j]);
			}
			if (j == s->matrixSize - 1){
				fprintf(f, "%s", newline);
			}
			else {
				fprintf(f, "%s", space);
			}
		}
	}
	fclose(f);
}

struct sudoku * openFromFile(char * filename){
	struct sudoku * s;
	int n, m, counter, i, j, num;
	char isFixed;
	FILE *f;
	f=fopen(filename ,"r");
	if (f == NULL) {
	    printf("Error opening file!\n");
	    exit(1);
	}
	else {
		/* reading parameters m, n from top line of file */
		counter = 0;
		while ((!feof(f)) && (counter < 2)){
			if(fscanf(f,"%d %d", &m, &n) == 2){
				counter += 2;
			}
			else{
				printf("the file format is incorrect!\n");
				exit(1);
			}
		}
		/* generating sudoku structure based on m, n read from file */
		s = generateSudoku(m, n);
		/* reading form file and populating sudoku structure */
		for (i = 0; i < s->matrixSize; i++){
			for (j = 0; j < s->matrixSize; j++){
				if(!feof(f)){
					if(fscanf(f,"%d%c", &num, &isFixed) == 2){
						s->values[i][j] = num;
						if (isFixed == '.'){
							s->fixed[i][j] = 1;
						}
						else{
							s->fixed[i][j] = 0;
						}
					}
				}
				else {
					printf("The End of File was reached before all necessary parameters were read!\n");
					exit(1);
				}
			}
		}
	}
	fclose(f);
	return s;
}
