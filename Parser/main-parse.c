#include "parse.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[])
{
    FILE *input;
    char line[MAX_LINE];

    if(argc == 2)
    {
	input = fopen(argv[1], "r");
	if(input == NULL)
	{
	    perror(argv[1]);
	    exit(1);
	}
    }
    else
    {
	assert(argc == 1);
	input = stdin;
	printf("? ");

	fflush(stdout);
    }

    setlinebuf(input);
    while(fgets(line, sizeof(line), input))
    {
		int i;
		struct commandLine cmdLine;

		if(line[strlen(line)-1] == '\n')
			line[strlen(line)-1] = '\0';

		Parse(line, &cmdLine);

		printf("%d: ", cmdLine.numCommands);

		if(cmdLine.infile)
			printf("< '%s' ", cmdLine.infile);

		for(i=0; i < cmdLine.numCommands; i++)
		{
			int j;
			for(j=cmdLine.cmdStart[i]; cmdLine.argv[j] != NULL; j++)
			printf("'%s' ", cmdLine.argv[j]);
			if(i < cmdLine.numCommands - 1)
			printf("| ");
		}

		if(cmdLine.append)
		{
			assert(cmdLine.outfile);
			printf(">");
		}
		if(cmdLine.outfile)
			printf(">'%s'", cmdLine.outfile);


		printf("\n");

		if(input == stdin)
		{
			printf("? ");
			fflush(stdout);
		}
    }

    return 0;
}
