#ifndef REDIRECT_PIPE_H
#define REDIRECT_PIPE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MESSAGE "\nRoot est connecté\n"
#define MESSAGE_LENGTH 21
#define PID_OF_CHILD_PROCESS 0

/**
 * Create a child process and redirect its standard input or output to a pipe.
 * @param pipe_fd The pipe file descriptors.
 * @param child_pid The child process ID.
 * @param command The command to execute.
 * @param command_arg The command argument.
 * @param std_fd The standard input or output file descriptor.
 * @param pipe_fd_index The pipe file descriptor index.
*/
void create_child_process(int* pipe_fd, pid_t* child_pid, char* command, char* command_arg, int std_fd, int pipe_fd_index);


#endif //REDIRECT_PIPE_H
