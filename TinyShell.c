#include "CommandLib.h"

// Tran Huy Hoang 20210386 - Hanoi University of Science and Technology
// gcc -o TinyShell TinyShell.c -lreadline && ./TinyShell

// Init Tiny Shell
void initShell() {
    clear();
    printf("\n\n");
    printf("\t\t******************************************\n");
    printf("\t\t*                                        *\n");
    printf("\t\t*     WELCOME TO MY LINUX TINY SHELL     *\n");
    printf("\t\t*                                        *\n");
    printf("\t\t*     Tran Huy Hoang - 20210386- HUST    *\n");
    printf("\t\t*                                        *\n");
    printf("\t\t******************************************\n\n");
    sleep(2);
    clear();
}

// Get input from user
int getInput(char *str) {
    char *buf;
    buf = readline(":TINY_SHELL>> ");
    if (strlen(buf) != 0) {
        add_history(buf);
        strcpy(str, buf);
        return 0;
    } else
        return 1;
}

int main() {
    initShell();
    handleCtrl_C();
    while (1) {
        printDir();
        char str[100];
        getInput(str);
        processCmd(str);     
    }
    return 1;
}
