#include "../include/parse.h"

void openHelp()
{
    puts("\n***WELCOME TO MY SHELL HELP***"
        "\nList of Commands supported:"
        "\n>cd"
        "\n>ls"
        "\n>exit"
        "\n>all other general commands available in UNIX shell"
        "\n>pipe handling"
        "\n>improper space handling");

    return;
}

int ownCmdHandler(char** parsed)
{
    int NoOfOwnCmds = 4, i, switchOwnArg = 0;
    char* ListOfOwnCmds[NoOfOwnCmds];
    char* username;

    ListOfOwnCmds[0] = "exit";
    ListOfOwnCmds[1] = "cd";
    ListOfOwnCmds[2] = "help";
    ListOfOwnCmds[3] = "hello";

    for (i = 0; i < NoOfOwnCmds; i++) {
        if (strcmp(parsed[0],ListOfOwnCmds[i]) == 0) {
            switchOwnArg = i + 1;
            break;
        }
    }

    switch (switchOwnArg) {
    case 1:
        printf("\nGoodbye\n");
        exit(0);
    case 2:
        chdir(parsed[1]);
        return 1;
    case 3:
        openHelp();
        return 1;
    case 4:
        username = getenv("USER");
        printf("\nHello %s.\nMind that this is "
            "not a place to play around."
            "\nUse help to know more..\n",
            username);
        return 1;
    default:
        break;
    }

    return 0;
}



int takeInput(char* str)
{
    char* buf;

    buf = readline("\n>>> ");
    if (strlen(buf) != 0) {
        add_history(buf);
        strcpy(str,buf);
        return 0;
    } else {
        return 1;
    }
}


int parsePipe(char* str, char** strpiped) {
    int i=0;
        strpiped[i] = strtok(str, "|");
    while(strpiped[i] != NULL) {
        i++;
        strpiped[i] = strtok(NULL, "|");
    }
        printf("%d",i);
    return i+1;
}




int findspecificChar(char *str) {
    if(strchr(str,'&')!=NULL)
        return 0;
    else if(strchr(str,';')!=NULL)
        return 1;
    else if(strchr(str,'\\')!=NULL)
        return 2;
    else
        return -1;
}





void parseSpace(char* str, char** cmd)
{
    int i;
    char *parsed[MAXLIST];
    for (i = 0; i < MAXLIST; i++) {
        parsed[i] = strsep(&str, " ");
        cmd=parsed;
        if (parsed[i] == NULL)
            break;
        if (strlen(parsed[i]) == 0)
            i--;
    }
}





int processString(char* str,char ***cmd){
    char* strpiped[MAXLIST];

    int piped = 0;

    piped = parsePipe(str, strpiped);

    if (piped) {
        for(int i=0;i<piped;i++){
            parseSpace(strpiped[i], cmd[i]);
        }

    } else {

        parseSpace(str, cmd[0]);
    }

    strpiped=cmd[0];
    if (ownCmdHandler(cmd[0]))
        return 0;
    else
        return piped;
}


