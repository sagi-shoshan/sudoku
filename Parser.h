#ifndef PARSER_H_
#define PARSER_H_
#include "MainAux.h"

#define MAX_STRING 256*sizeof(char)

/*Error prints*/
#define too_Long "Error: Too many characters were entered in a single line\n"
#define wrong_Mode "Error: This command does not fit the current mode\n"
#define name  "Error: There is no such command\n"
#define few "Error: not enough parameters for this command\n"
#define many "Error: too many parameters for this command\n"
#define range "Error: parameter is out of range\n"
#define board "Error: parameter is not suitable for this board\n"
#define bad_File "Error: there is no such file\n"
#define cmd_outof_mode "Error: This command is unavailable in the current mode\n"
#define wrong_Solution "Error: the solution is erroneous\n"

extern command read;

/* this function parses information we get as input into a usable command using fgets */
command read_Play();


#endif /* PARSER_H_ */
