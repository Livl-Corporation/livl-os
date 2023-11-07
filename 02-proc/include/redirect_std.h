#ifndef REDIRECT_STD_H
#define REDIRECT_STD_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

#define PID_OF_CHILD_PROCESS 0
#define BUFFER_SIZE 1024
#define TEMP_FILE "/tmp/proc-exercise-XXXXXX" // last six characters of template must be “XXXXXX”

void print_usage(char *program_name);
void handle_child_process(char *command);
void handle_parent_process();
void read_temp_file();

#endif //REDIRECT_STD_H