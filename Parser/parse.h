#include <ctype.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define MAX_LINE 10240
#define MAX_COMMANDS 32
#define MAX_ARGS 32


struct commandLine
{
    char buf[MAX_LINE];

    int numCommands;
    int cmdStart[MAX_COMMANDS];
    char *argv[(MAX_ARGS+1) * MAX_COMMANDS + 1];
    char *infile, *outfile;
    char append;

};

int Parse(char *line, struct commandLine *sc);

extern void perror(const char *);
