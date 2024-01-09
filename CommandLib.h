#include <readline/readline.h>
#include <readline/history.h>
#include <dirent.h>
#include "ProcessLib.h"

#define MAXARG 2
#define MAX_PATH_LENGTH 1024

void help() {
    printf("Tiny Shell - Tran Huy Hoang 20210386 - HUST\n");
    printf("LIST OF COMMAND\n");
    printf("======================================================================================================\n");
    printf("No          Command             Function\n");
    printf("------------------------------------------------------------------------------------------------------\n");
    printf("1           help                Explain the meaning of all commands\n");
    printf("2           dir                 List files and subfolders in the current directory\n");
    printf("3           clear               Clear Tiny Shell screen\n");
    printf("4           exit                Exit Tiny Shell\n");
    printf("5           date                Displays the current date\n");
    printf("6           time                Displays the current time\n");
    printf("7           cd [path]           Change the current working directory to the directory with path [path]\n");
    printf("8           path                Displays the PATH environment variable\n");
    printf("9           addpath [path]      Add [path] to the PATH environment variable\n");
    printf("10          [path] fg           Run process with path [path] in foreground mode\n");
    printf("11          [path] bg           Run process with path [path] in background mode\n");
    printf("12          list                Displays a list of processes\n");
    printf("13          kill [id]           Kill a background process with ID [id]\n");
    printf("14          killa               Kill all running background processes\n");
    printf("15          stop [id]           Stop a background process with ID [id]\n");
    printf("16          resume [id]         Resume execution of a paused background process with ID [id]\n");
    printf("17          <Ctr + C>           Terminate the foreground process using the key combination Ctrl+C\n");
    printf("18          exec [path]         Execute the *.sh file whose path is [path]\n");
    printf("=====================================================================================================\n");
}

// Print the path of the current directory
void printDir() {
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("\n%s", cwd);
}

// List files and subfolders in the current directory
void listFiles() {
    struct dirent *entry;
    DIR *dir = opendir(".");

    if (dir == NULL) {
        perror("Error opening directory");
        return;
    }
    printf("\n");
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\t", entry->d_name);
    }
    printf("\n");
    closedir(dir);
}

// Change the current working directory
void changeDir(char *path) {
    if (chdir(path) != 0) {
        printf("Error changing directory. %s is not a directory\n", path);
    } else {
        printf("Current directory has been changed!\n");
    }
}

// Displays the current date
void getDate(){
    time_t t;
    struct tm *tm_info;
    time(&t);
    tm_info = localtime(&t);
    printf("%02d/%02d/%04d\n", tm_info->tm_mday, tm_info->tm_mon + 1, tm_info->tm_year + 1900);
} 

// Displays the current time
void getTime(){
    time_t t;
    struct tm *tm_info;
    time(&t);
    tm_info = localtime(&t);
    printf("%02d:%02d:%02d\n", tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec);
}

// Displays the PATH environment variable
void displayPath() {
    char *pathValue = getenv("PATH");
    printf("PATH = %s\n", pathValue);
}

// Add a path to PATH variable
void addPath(const char *newPath) {
    FILE *file = fopen("/home/hoangtran/.bashrc", "a");
    if (file == NULL) {
        perror("Lỗi khi mở tệp ~/.bashrc");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "export PATH=$PATH:%s\n", newPath);
    printf("Add new path success!");
    fclose(file);
}

void processCmd(char *cmd);
// Exec *.sh (Shell script) file
void execSh(char *scriptPath) {
    FILE *file = fopen(scriptPath, "r");
    if (file == NULL) {
        printf("Can not open file \n");
        return ; 
    }
    char buffer[100]; 
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        size_t length = strlen(buffer);
        if (length > 0 && buffer[length - 1] == '\n') {
            buffer[length - 1] = '\0';
        }
        processCmd(buffer);
    }
    fclose(file);
}

// Process commands
void processCmd(char *cmd) {
    char *token;
    char arr[100][100];

    // Use strtok to split the string
    token = strtok(cmd, " ");

    // Loop through all tokens and copy into "arr" array
    int k = 0; // Starting from arr[0], k is the number of arguments
    while (token != NULL) {
        strcpy(arr[k], token);
        k++;
        token = strtok(NULL, " ");
    }

    // If k > MAXARG then print an error message
    if (k < 1 || k > MAXARG) {
        printf("Bad command. Please try again");
    } else {
        char *cmdName = arr[0];
        // 1 argument
        if (k == 1) {
            if (strcmp(cmdName, "help") == 0) {
                help();
            } else if (strcmp(cmdName, "dir") == 0) {
                listFiles();
            } else if (strcmp(cmdName, "clear") == 0) {
                clear();
            } else if(strcmp(cmdName, "list") == 0){
                listProcess();
            } else if(strcmp(cmdName, "exit") == 0){
                exitTinyShell();
            } else if(strcmp(cmdName, "date") == 0){
                getDate();
            } else if(strcmp(cmdName, "time") == 0){
                getTime();
            } else if(strcmp(cmdName, "path") == 0){
                displayPath();
            } else if(strcmp(cmdName, "killa") == 0){
                killAllProcess();
            } else {
                printf("Bad command! Please try again or type 'help' to see a list of commands.\n");
            }
        } 
        // 2 arguments
        else {
            char *argument = arr[1];
            if ((strcmp(cmdName, "cd") == 0)) {
                changeDir(argument);
            } else if(strcmp(cmdName, "kill") == 0){
                killProcess(atoi(argument));
            } else if(strcmp(cmdName, "stop") == 0){
                stopProcess(atoi(argument));
            } else if(strcmp(cmdName, "resume") == 0){
                resumeProcess(atoi(argument));
            } else if(strcmp(cmdName, "exec") == 0){
                execSh(argument);
            } else if(strcmp(cmdName, "addpath") == 0){
                addPath(argument);
            } else {
                runChildProcess(cmdName, argument);
            }
        }
    }
}

