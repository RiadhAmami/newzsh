#ifndef Parse
#define Parse
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<readline/readline.h>
#include<readline/history.h>
#define MAXCOM 1000 // max number of letters to be supported
#define MAXLIST 100 // max number of commands to be supported

int parsing(char ***cmd);
int takeInput(char* str);
int parsePipe(char* str, char** strpiped);
int findspecificChar(char *str);
int ownCmdHandler(char** parsed);
void openHelp();
void parseSpace(char *str, char **cmd);
int processString(char *str,char ***cmd);
#endif
