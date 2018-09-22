#include "../include/excuting.h"
#include "../include/parse.h"


int main(int argc,char **argv){
    char **cmd[MAXLIST];
    char src[MAXCOM];
    char *shit[MAXCOM];
    int numCMD;
    while(1) {
        if (takeInput(src))
            continue;
        processString(src,cmd);
    }

}
