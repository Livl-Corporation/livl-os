/**
 * fork.c
 * @author Julien and Franck
*/

#include "fork.h"

void print_child_process_details() 
{
    printf("** CHILD PROCESS **\n");
    printf(" - Child PID: %d\n", getpid());
    printf(" - Parent's PID: %d\n", getppid());
    int last_pid_digit = getpid() % 10;
    printf(" - Exit code from last child's PID: %d\n", last_pid_digit);
    exit(last_pid_digit); // last digit of parent's PID between 0 and 9
}

void print_parent_process_details(pid_t child_pid, int status) 
{
    printf("** PARENT PROCESS **\n");
    printf(" - Child PID: %d\n", child_pid);
    if (WIFEXITED(status)) { // if child exited normally
        printf(" - Child exit code: %d\n", WEXITSTATUS(status));
    }
}

int main() 
{
    pid_t child_pid = fork();

    if (child_pid < PID_OF_CHILD_PROCESS) 
    {
        perror("ERROR : Fork failed.\n");
        return EXIT_FAILURE;
    }

    if (child_pid == PID_OF_CHILD_PROCESS) 
    {
        print_child_process_details();
    } else { 
        int status;
        wait(&status); // wait for child to terminate -> dad process is blocked here
        print_parent_process_details(child_pid, status);
    }

    return EXIT_SUCCESS;
}
