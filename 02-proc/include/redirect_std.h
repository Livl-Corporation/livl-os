#ifndef REDIRECT_STD_H
#define REDIRECT_STD_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

#define PID_OF_CHILD_PROCESS 0
#define TEMP_FILENAME "temp/redirect-std-XXXXXX" // last six characters of template must be “XXXXXX”

#endif //REDIRECT_STD_H