#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define MAXN 100

// Struct to store process information
typedef struct {
    pid_t pid;
    int id;
    char command[100];
} ProcessInfor;

ProcessInfor processes[MAXN]; // Array of processes
int countProcess = 1; 
int ctrlCPressed = 0;

int stoppedFlag = 0; // stoppedFlag = 0: Process has not stopped, toppedFlag = 1: Process has stopped

// Get status of process. State 0: running, State 1: stopped, State 2: End
int getProcessStatus(pid_t pid) {
    int status;
    int result = waitpid(pid, &status, WNOHANG | WUNTRACED | WCONTINUED);

    if (result == 0) {
        if(stoppedFlag == 1){
            return 1; // Process has stopped
        }
        else return 0; // Process is running
    } else if (WIFSTOPPED(status)) {
        stoppedFlag = 1; // Set stoppedFalg = 1 if process has stopped
        return 1;// Process has stopped
    } else if (WIFCONTINUED(status)) {
        stoppedFlag = 0; // Set stoppedFalg = 0 if process continues to run
        return 0; // Process is running
    }
    else {
        return 2; // Process has ended
    }
}

// Add a process to processes[MAXN]
void addProcess(pid_t p, char * cmd) {
    ProcessInfor process;
    process.pid = p;
    countProcess++;
    process.id = countProcess;
    strcpy(process.command, cmd);
    processes[process.id] = process;
}

// Run process in background mode
void runInBackground(char *cmd) {
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // Child process
        if (execlp("xterm", "xterm", "-e", cmd, (char *)NULL) == -1) {
            perror("execlp failed");
            exit(EXIT_FAILURE);
        }
    } else {
        // Parent process
        char cmdName[MAXN] = "";
        strcat(cmdName, cmd);
        strcat(cmdName, " bg");
        addProcess(child_pid, cmdName);
        printf("Process is running in the background.\n");
    }
}

// Run process in foreground mode
void runInForeground(char *cmd) {
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // Child process
        if (execlp("xterm", "xterm", "-e", cmd, (char *)NULL) == -1) {
            perror("execlp failed");
            exit(EXIT_FAILURE);
        }
    } else {
        // Parent process
        char cmdName[MAXN] = "";
        strcat(cmdName, cmd);
        strcat(cmdName, " fg");
        addProcess(child_pid, cmdName);
        printf("Process is running in the foreground.\n");
        waitpid(child_pid, NULL, 0); // Parent waits for the child to finish
    }
}

// Check if a file is an executable file or not
int isExecutableInPath(char *filename) {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "command -v %s >/dev/null 2>&1 || { exit 1; }", filename);
    return system(cmd) == 0;
}

// Run child process in foreground mode or background mode
void runChildProcess(char *cmd, char * mode){
    int execAble = isExecutableInPath(cmd);
    if(execAble == 0){
        printf("Bad command! Please try again or type 'help' to see a list of commands\n");
    } else {
        if (strcmp(mode, "bg") == 0) {
            runInBackground(cmd);
        } else if (strcmp(mode, "fg") == 0) {
            runInForeground(cmd);
        } else {
            printf("Invalid mode. Please use 'bg' for background mode or 'fg' for foreground mode.\n");
        }
    }
}

// List processes
char stringStatus[3][MAXN] = {"running", "stopped", "end"}; // Status of processes
void listProcess() {
    printf("==================================================\n");
    printf("ID          COMMAND                 STATUS\n");
    printf("--------------------------------------------------\n");
    printf("1           TinyShell               running\n");
    for (int i = 2; i <= countProcess; i++) {
        if(getProcessStatus(processes[i].pid) != 2){
            printf("%-12d%-24s%-s\n", processes[i].id, processes[i].command, stringStatus[getProcessStatus(processes[i].pid)]);
        }
    }
    printf("==================================================\n");
}

// Clear terminal
void clear() {
    printf("\033[H\033[J");
}

void exitTinyShell(){
    printf("Exit TinyShell... Goodbye!\n");
    sleep(1);
    exit(0);
}

// Kill process
void killProcess(int id) {
    if (id < 1 || id > countProcess) {
        printf("Invalid process ID.\n");
        return;
    } else if (id == 1){
        exitTinyShell();
    } else {
        pid_t pidToKill = processes[id].pid;
        // Send signal SIGTERM to kill process
        if ((kill(pidToKill, SIGTERM) == 0)) {
            printf("Process with ID %d has been terminated.\n", id);
        } else {
            perror("Error killing process");
        }
    }
}

// Kill all running processes, except TinyShell
void killAllProcess() {
    for(int i = 2; i <= countProcess; i++){
        if(getProcessStatus(processes[i].pid) == 0){
            pid_t pidToKill = processes[i].pid;
            // Send signal SIGTERM to kill process
            if ((kill(pidToKill, SIGTERM) != 0)) {
                perror("Error killing process");
                printf("Some processes have been terminated. End kill all processes. The remaining processes are not terminated!\n");
                return;
            }
        }
    }
    printf("All processes have been terminated.\n");
}

// Stop process
void stopProcess(int id) {
    if (id < 1 || id > countProcess) {
        printf("Invalid process ID.\n");
        return;
    } else if(id == 1){
        printf("Can not stop Tiny Shell!");
    } else {
        pid_t pidToStop = processes[id].pid;
        // Send signal SIGSTOP to stop process
        if ((kill(pidToStop, SIGSTOP) == 0) && (kill(pidToStop+1, SIGSTOP) == 0)) {
            printf("Process with ID %d has been stopped.\n", id);
        } else {
            perror("Error stopping process");
        }
    }
}

// Resume stopped process
void resumeProcess(int id) {
    if (id < 1 || id > countProcess) {
        printf("Invalid process ID.\n");
        return;
    } else if (id == 1){
        return;
    } else {
        pid_t pidToResume = processes[id].pid;
        // Send signal SIGCONT to resume process
        if ((kill(pidToResume, SIGCONT) == 0) && (kill(pidToResume+1, SIGCONT) == 0)) {
            printf("Process with ID %d has been resumed.\n", id);
        } else {
            perror("Error resuming process");
        }
    }
}

// Signal handler function for SIGINT
void sigintHandler(int signum) {
    if (signum == SIGINT) {
        printf("\nCtrl+C pressed. Foreground process has terminated\n");
    }
}

// Register a signal handling function for SIGINT
void handleCtrl_C(){
    struct sigaction sa;
    sa.sa_handler = sigintHandler;
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
}

