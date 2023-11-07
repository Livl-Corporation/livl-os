#ifndef FORK_H
#define FORK_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define PID_OF_CHILD_PROCESS 0

void print_child_process_details();
void print_parent_process_details(pid_t child_pid, int status);

#endif  //FORK_H