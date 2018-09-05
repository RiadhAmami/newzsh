#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include "./Parser/parse.h"
// Clearing the shell using escape sequences
#define clear() printf("\033[H\033[J")



// Function where the system command is executed
void ExecuteCommand(struct commandLine *sc)
{
    // Forking a child
    int i=0,backg=0;
    while(sc->argv[i]) {
        if(strcmp(sc->argv[i],"&")==0){
            sc->argv[i]=NULL;
            backg=1;
        }
        i++;
    }
    pid_t pid = fork();
    if (pid == -1) {
            perror("forking error :");
        return;
    } else if (pid == 0) {
        if (execvp(sc->argv[0],sc->argv ) < 0) {
            perror("execution error :");
        }
        exit(0);
    } else {
        // waiting for child to terminate
        if(backg==0)
        wait(NULL);
        else
            printf("parent go\n");
        return;
    }
}

void CommandOutFile(struct commandLine *cmd) {
    pid_t pid;
    int fd = open(cmd->outfile, O_WRONLY|O_TRUNC|O_CREAT, 0644);
    if (fd < 0) {
        perror("open"); abort();
    }
    switch (pid = fork()) {
      case -1: perror("fork"); abort();
      case 0:
        if (dup2(fd, 1) < 0){
            perror("dup2"); abort();
        }
        close(fd);
        execvp(cmd->argv[0],cmd->argv);
        perror("execvp");
        abort();
      default:
        close(fd);
        /* do whatever the parent wants to do. */
    }
}

void ExecutePipedCommand(struct commandLine *cmdLine)
{
    // 0 is read end, 1 is write end
    int backg;
    char *cmd[40];
    int i=0,j=0,k=0;
    int pipefd[2];
    int fd_in=0;
    pid_t pid;

    for(i=0;i<cmdLine->numCommands;i++) {
        backg=0;
        for(j=cmdLine->cmdStart[i];j<cmdLine->cmdStart[i+1];j++){
            cmd[j-cmdLine->cmdStart[i]]=cmdLine->argv[j];
            perror(":");
            printf("\n\n%s\n\n",cmd[j-cmdLine->cmdStart[i]]);
            perror(":");
        }
    }
        /*if (pipe(pipefd) < 0) {
            printf("\nPipe could not be initialized");
            return;
        }
        pid = fork();
        if (pid < 0) {
            printf("\nCould not fork");
            return;
        }

        if (pid == 0) {
            // Child 1 executing..
            // It only needs to write at the write end
            dup2(fd_in,0);
            close(pipefd[0]);
            dup2(pipefd[1], STDOUT_FILENO);
            close(pipefd[0]);

            if (execvp(cmd[0],cmd) < 0) {
                printf("\nCould not execute command 1..");
                exit(0);
            }
        } else {
             if(backg==0)
                 wait(NULL);
             close(pipefd[1]);
             fd_in=pipefd[0];
         }
*/
}


int ExaptionCommands(struct commandLine *cmd)
{
    int Cmds_nub = 2, i, switchOwnArg = 0;
    char* Cmds[Cmds_nub];
    char* username;

    Cmds[0] = "cd";
    Cmds[1] = "exit";

    for (i = 0; i < Cmds_nub; i++) {
        if (strcmp(cmd->argv[0], Cmds[i]) == 0) {
            switchOwnArg = i + 1;
            break;
        }
    }

}






int main(int argc ,char **argv)
{
    int execFlag = 0;
    struct commandLine cmdLine;
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
            if(line[strlen(line)-1] == '\n')
                line[strlen(line)-1] = '\0';

            Parse(line, &cmdLine);

                if (strcmp(cmdLine.argv[0], "exit") == 0) {
                    exit(EXIT_SUCCESS);
                }
            if(cmdLine.numCommands > 0){
                if (strcmp(cmdLine.argv[0], "cd") == 0) {
                    chdir(cmdLine.argv[1]);
                    printf("? ");
                }
                else if(strcmp(cmdLine.argv[0], "cd") == 0&&cmdLine.numCommands==2){
                    chdir(cmdLine.argv[1]);
                    printf("? ");
                }

                else if (cmdLine.outfile!=NULL) {
                    CommandOutFile(&cmdLine);
                    cmdLine.outfile=NULL;
                printf("? ");
                }
                else if(cmdLine.numCommands == 1 ){
                    ExecuteCommand(&cmdLine);
                    printf("? ");
                }
                else{
                    ExecutePipedCommand(&cmdLine);
                    printf("? ");
                }
            }
            else
	            printf("? ");
    }
    return 0;
}
