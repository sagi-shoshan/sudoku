#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Parser.h"

command read;

command invalid(char* error){ /*this function is called when the input is found invalid*/
	command invalid_Input;
	invalid_Input.C_Type = invalid_C;
	invalid_Input.C_Type_Name = "invalid_C\n";
	printf(error);
	printf("test  (line 12) -> invalid \n");
	return (invalid_Input);
}


command read_Play(){
	char string [MAX_STRING + 1] = ""; /*limit input length, +1 check if greater then allowed max length*/
	char* token;
	printf("test  (line 20) -> read_Play \n");

	/*V input is not EOF*/
		/* +1 the final null-character +1 check if greater then allowed max length */
    if (fgets(string, MAX_STRING + 2, stdin) != NULL){
    	token = strtok(string, " \t\r\n");
    	printf("test  (line 25) -> first input: token = %s \n", token);
    	printf("test - strlen(token) = %d \n", (int)strlen(token));

    	/*V input is empty*/
    	if (token == NULL) {
    		printf("test (line 29) -> token = NULL = %s \n", token);
    		read.C_Type = empty_C;
    		read.C_Type_Name = "empty_C\n";
    		return read;
    	}

    	/*input is too long*/
    	else if (strlen(token)>MAX_STRING) {
    		printf("test (line 37) -> MAX_STRING mode \n");
    		printf("(line 38) -> entering INVALID with error: %s \n", "too_long");
    		return invalid(too_Long);
    	}

    	/*input is 'solve' command*/
    	else if (strcmp("solve", token) == 0) {
    		printf("test (line 44) -> solve mode \n");
    		/*reading assigned file name*/
    		token = strtok(NULL, " \t\r\n");
    		/*missing parameter*/
    		if (token == NULL){
    			printf("(line 49) -> entering INVALID with error: %s \n", "few");
    			return invalid(few);
    		}
    		else
    			read.file_Name = token;
    		/*checking for extra unneeded inputs*/
    		token = strtok(NULL, " \t\r\n");
    		if (token != NULL){
    			printf("(line 57) -> entering INVALID with error: %s \n", "many");
    			return invalid(many);
    		}

    		read.C_Type = solve_C;
    		read.C_Type_Name = "solve_C\n";
    		return read;
    	}

    	/*input is 'edit' command*/
    	else if (strcmp("edit", token) == 0) {
    		printf("test (line 68) -> edit mode \n");
    		/*reading assigned file name*/
    		token = strtok(NULL, " \t\r\n");
    		/*optional assigned file name (value or NULL)*/
    		read.file_Name = token;
    		/*checking for extra unneeded inputs*/
    		token = strtok(NULL, " \t\r\n");
    		if (token != NULL){
    			printf("(line 76) -> entering INVALID with error: %s \n", "many");
    			return invalid(many);
    		}

    		read.C_Type = edit_C;
    		read.C_Type_Name = "edit_C\n";
    		return read;
    	}

    	/*input is 'mark_errors' command*/
    	else if (strcmp("mark_errors", token) == 0) {
    		printf("test (line 87) -> mark_errors mode \n");
    		token = strtok(NULL, " \t\r\n");
    		/*missing parameter*/
    		if (token == NULL){
    			printf("(line 91) -> entering INVALID with error: %s \n", "few");
    			return invalid(few);
    		}
    		else
    			read.mark_errors = atoi(token);

    		/*checking for extra unneeded inputs*/
    		token = strtok(NULL, " \t\r\n");
       		if (token != NULL){
       			printf("(line 100) -> entering INVALID with error: %s \n", "many");
       			return invalid(many);
       		}

    		read.C_Type = mark_errors_C;
    		read.C_Type_Name = "mark_errors_C\n";
    		return read;
    	}

    	/*input is 'print_board' command*/
    	else if (strcmp("print_board", token) == 0) {
    		printf("test (line 111) -> print_board mode \n");
    		/*checking for extra unneeded inputs*/
    		token = strtok(NULL, " \t\r\n");
    		if (token != NULL){
    			printf("(line 115) -> entering INVALID with error: %s \n", "many");
    			return invalid(many);
    		}

    		read.C_Type = print_board_C;
    		read.C_Type_Name = "print_board_C\n";
    		return read;
    	}

    	/*input is 'set' command*/
    	else if (strcmp("set", token) == 0) {
    		printf("test (line 126) -> set mode\n");
    		/*reading parameter 'row'*/
    		token = strtok(NULL, " \t\r\n");
    		/*missing parameter*/
    		if (token == NULL){
    			printf("(line 131) -> entering INVALID with error: %s \n", "few");
    			return invalid(few);
    		}
    		else
    			read.row = atoi(token);

    		/*reading parameter 'column'*/
    		token = strtok(NULL, " \t\r\n");
    		/*missing parameter*/
    		if (token == NULL){
    			printf("(line 141) -> entering INVALID with error: %s \n", "few");
    			return invalid(few);
    		}
    		else
    			read.column = atoi(token);

    		/*reading parameter 'value'*/
    		token = strtok(NULL, " \t\r\n");
    		/*missing parameter*/
    		if (token == NULL){
    			printf("(line 151) -> entering INVALID with error: %s \n", "few");
    			return invalid(few);
    		}
    		else
    			read.value = atoi(token);


    		/*checking for extra unneeded inputs*/
    		token = strtok(NULL, " \t\r\n");
    		if (token != NULL){
    			printf("(line 161) -> entering INVALID with error: %s \n", "many");
    			return invalid(many);
    		}

    		read.C_Type = set_C;
    		read.C_Type_Name = "set_C\n";
    		return read;
    	}

    	/*input is 'validate' command*/
    	else if (strcmp("validate", token) == 0) {
    		printf("test (line 172) -> validate mode \n");
    		/*checking for extra unneeded inputs*/
    		token = strtok(NULL, " \t\r\n");
    		if (token != NULL){
    			printf("(line 176) -> entering INVALID with error: %s \n", "many");
    			return invalid(many);
    		}

    		read.C_Type = validate_C;
    		read.C_Type_Name = "validate_C\n";
    		return read;
    	}

    	/*input is 'guess' command*/
    	else if (strcmp("guess", token) == 0) {
    		printf("test (line 187) -> guess mode \n");
    		/*reading parameter*/
    		token = strtok(NULL, " \t\r\n");
    		/*missing parameter*/
    		if (token == NULL){
    			printf("(line 192) -> entering INVALID with error: %s \n", "few");
    			return invalid(few);
    		}
    		else
    			read.threshold = atoll(token);

    		/*checking for extra unneeded inputs*/
    		token = strtok(NULL, " \t\r\n");
    		if (token != NULL){
    			printf("(line 201) -> entering INVALID with error: %s \n", "many");
    			return invalid(many);
    		}

    		read.C_Type = guess_C;
    		read.C_Type_Name = "guess_C\n";
    		return read;
    	}

    	/*input is 'generate' command*/
    	else if (strcmp("generate", token) == 0) {
    		printf("test (line 212) -> generate mode \n");
    		/*reading parameter 'X'*/
    		token = strtok(NULL, " \t\r\n");
    		/*missing parameter*/
    		if (token == NULL){
    			printf("(line 217) -> entering INVALID with error: %s \n", "few");
    			return invalid(few);
    		}
    		else
    			read.empty_cells = atoi(token);

    		/*reading parameter 'Y'*/
    		token = strtok(NULL, " \t\r\n");
    		/*missing parameter*/
    		if (token == NULL){
    			printf("(line 227) -> entering INVALID with error: %s \n", "few");
    			return invalid(few);
    		}
    		else
    			read.dont_empty_cells = atoi(token);


    		/*checking for extra unneeded inputs*/
    		token = strtok(NULL, " \t\r\n");
    		if (token != NULL){
    			printf("(line 237) -> entering INVALID with error: %s \n", "many");
    			return invalid(many);
    		}

    		read.C_Type = generate_C;
    		read.C_Type_Name = "generate_C\n";
    		return read;
    	}

    	/*input is 'undo' command*/
    	else if (strcmp("undo", token) == 0) {
    		printf("test (line 248) -> undo mode \n");
    		/*checking for extra unneeded inputs*/
    		token = strtok(NULL, " \t\r\n");
    		if (token != NULL){
    			printf("(line 252) -> entering INVALID with error: %s \n", "many");
    			return invalid(many);
    		}

    		read.C_Type = undo_C;
    		read.C_Type_Name = "undo_C\n";
    		return read;
    	}

    	/*input is 'redo' command*/
    	else if (strcmp("redo", token) == 0) {
    		printf("test (line 263) -> redo mode \n");
    		/*checking for extra unneeded inputs*/
    		token = strtok(NULL, " \t\r\n");
    		if (token != NULL){
    			printf("(line 267) -> entering INVALID with error: %s \n", "many");
    			return invalid(many);
    		}

    		read.C_Type = redo_C;
    		read.C_Type_Name = "redo_C\n";
    		return read;
    	}

    	/*input is 'save' command*/
    	else if (strcmp("save", token) == 0) {
    		printf("test (line 278) -> save mode \n");
    		/*reading assigned file name*/
    		token = strtok(NULL, " \t\r\n");
    		/*missing parameter*/
    		if (token == NULL){
    			printf("(line 283) -> entering INVALID with error: %s \n", "few");
    			return invalid(few);
    		}
    		else
    			read.file_Name = token;
    		/*checking for extra unneeded inputs*/
    		token = strtok(NULL, " \t\r\n");
    		if (token != NULL){
    			printf("(line 291) -> entering INVALID with error: %s \n", "many");
    			return invalid(many);
    		}

    		read.C_Type = save_C;
    		read.C_Type_Name = "save_C\n";
    		return read;
    	}

    	/*input is 'hint' command*/
    	else if (strcmp("hint", token) == 0) {
    		printf("test (line 302) -> hint mode \n");
    		/*reading parameter 'X'*/
    		token = strtok(NULL, " \t\r\n");
    		/*missing parameter*/
    		if (token == NULL){
    			printf("(line 307) -> entering INVALID with error: %s \n", "few");
    			return invalid(few);
    		}
    		else
    			read.row = atoi(token);

    		/*reading parameter 'Y'*/
    		token = strtok(NULL, " \t\r\n");
    		/*missing parameter*/
    		if (token == NULL){
    			printf("(line 317) -> entering INVALID with error: %s \n", "few");
    			return invalid(few);
    		}
    		else
    			read.column = atoi(token);


    		/*checking for extra unneeded inputs*/
    		token = strtok(NULL, " \t\r\n");
    		if (token != NULL){
    			printf("(line 327) -> entering INVALID with error: %s \n", "many");
    			return invalid(many);
    		}

    		read.C_Type = hint_C;
    		read.C_Type_Name = "hint_C\n";
    		return read;
    	}

    	/*input is 'guess_hint' command*/
    	else if (strcmp("guess_hint", token) == 0) {
    		printf("test (line 338) -> guess_hint mode \n");
    		/*reading parameter 'X'*/
    		token = strtok(NULL, " \t\r\n");
    		/*missing parameter*/
    		if (token == NULL){
    			printf("(line 343) -> entering INVALID with error: %s \n", "few");
    			return invalid(few);
    		}
    		else
    			read.row = atoi(token);

    		/*reading parameter 'Y'*/
    		token = strtok(NULL, " \t\r\n");
    		/*missing parameter*/
    		if (token == NULL){
    			printf("(line 353) -> entering INVALID with error: %s \n", "few");
    			return invalid(few);
    		}
    		else
    			read.column = atoi(token);

    		/*checking for extra unneeded inputs*/
    		token = strtok(NULL, " \t\r\n");
    		if (token != NULL){
    			printf("(line 362) -> entering INVALID with error: %s \n", "many");
    			return invalid(many);
    		}

    		read.C_Type = guess_hint_C;
    		read.C_Type_Name = "guess_hint_C\n";
    		return read;
    	}

    	/*input is 'num_solutions' command*/
    	else if (strcmp("num_solutions", token) == 0) {
    		printf("test (line 373) -> num_solutions mode \n");
    		/*checking for extra unneeded inputs*/
    		token = strtok(NULL, " \t\r\n");
    		if (token != NULL){
    			printf("(line 377) -> entering INVALID with error: %s \n", "many");
    			return invalid(many);
    		}

    		read.C_Type = num_solutions_C;
    		read.C_Type_Name = "num_solutions_C\n";
    		return read;
    	}

    	/*input is 'autofill' command*/
    	else if (strcmp("autofill", token) == 0) {
    		printf("test (line 388) -> autofill mode \n");
    		/*checking for extra unneeded inputs*/
    		token = strtok(NULL, " \t\r\n");
    		if (token != NULL){
    			printf("(line 392) -> entering INVALID with error: %s \n", "many");
    			return invalid(many);
    		}

    		read.C_Type = autofill_C;
    		read.C_Type_Name = "autofill_C\n";
    		return read;
    	}

    	/*input is 'reset' command*/
    	else if (strcmp("reset", token) == 0) {
    		printf("test (line 403) -> reset mode \n");
    		/*checking for extra unneeded inputs*/
    		token = strtok(NULL, " \t\r\n");
    		if (token != NULL){
    			printf("(line 407) -> entering INVALID with error: %s \n", "many");
    			return invalid(many);
    		}

    		read.C_Type = reset_C;
    		read.C_Type_Name = "reset_C\n";
    		return read;
    	}

    	/*input is 'exit' command*/
    	else if (strcmp("exit", token) == 0) {
    		printf("test (line 418) -> exit mode \n");
    		/*checking for extra unneeded inputs*/
    		token = strtok(NULL, " \t\r\n");
    		if (token != NULL){
    			printf("(line 422) -> entering INVALID with error: %s \n", "many");
    			return invalid(many);
    		}

    		read.C_Type = exit_C;
    		read.C_Type_Name = "exit_C\n";
    		return read;
    	}

    	else {
    		printf("(line 422) -> entering INVALID with error: %s \n", "name");
    		return invalid(name);

    	}
    }

    /* we reached EOF and should exit */
    else {
    	printf("test (line 434) -> EOF");
    	read.C_Type = exit_C;
    	read.C_Type_Name = "exit_C\n";
    }

    return read;

}
