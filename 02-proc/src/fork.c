/**
 * fork.c
 * @author Julien and Franck
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define PID_OF_CHILD_PROCESS 0

int main() 
{
    pid_t pid = fork();

    if (pid < PID_OF_CHILD_PROCESS) 
    {
        perror("ERROR : Fork failed.\n");
        return EXIT_FAILURE;
    }

    if (pid == PID_OF_CHILD_PROCESS) 
    {
        printf("** CHILD PROCESS **\n");
        printf(" - Child PID: %d\n", getpid());
        printf(" - Parent's PID: %d\n", getppid());
        int last_parent_pid_digit = getpid() % 10;
        printf(" - Parent exit code: %d\n", last_parent_pid_digit);
        exit(last_parent_pid_digit); // last digit of parent's PID between 0 and 9
    } else { 
        int status;
        wait(&status);
        printf("** PARENT PROCESS **\n");
        printf(" - Child PID: %d\n", pid);
        if (WIFEXITED(status)) { // if child exited normally
            printf(" - Child exit code: %d\n", WEXITSTATUS(status));
        }
    }

    return EXIT_SUCCESS;
}
