#include "../include/excuting.h"

int execNonePipedCmd(char **str){

    // Forking a child
    pid_t pid = fork();

    if (pid == -1) {
        printf("\nFailed forking child..");
        return 0;
    } else if (pid == 0) {
        if (execvp(str[0],str) < 0) {
            printf("\nCould not execute command..");
        }
        exit(0);
    } else {
        // waiting for child to terminate
        wait(NULL);
        return 1;
    }
}




int execPipedCmd(char **str,int number_of_parsers) {
/*



for( i = 0; i < num-pipes; i++ ){
    if( pipe(pipefds + i*2) < 0 ){
        perror and exit
    }
}

commandc = 0
while( command ){
    pid = fork()
    if( pid == 0 ){
        if( not first command ){
            if( dup2(pipefds[(commandc-1)*2], 0) < ){
                perror and exit
            }
        }
        if( not last command ){
            if( dup2(pipefds[commandc*2+1], 1) < 0 ){
                perror and exit
            }
        }
        close all pipe-fds
        execvp
        perror and exit
    } else if( pid < 0 ){
        perror and exit
    }
    cmd = cmd->next
    commandc++
}

for( i = 0; i < 2 * num-pipes; i++ ){
    close( pipefds[i] );
}




*/
}

