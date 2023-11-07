#ifndef REDIRECT_STD_H
#define REDIRECT_STD_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define READ_END 0
#define WRITE_END 1
#define MESSAGE "root est connecté\n"
#define MESSAGE_LENGTH 18
#define PID_OF_CHILD_PROCESS 0

void execute_command_in_child(const char* command, const char* argument, int fd[]);
void check_root_and_display_message(int fd[]);

#endif //REDIRECT_STD_H
