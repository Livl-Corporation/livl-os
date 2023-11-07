#ifndef COUNTER_H
#define COUNTER_H

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * Signal handler to either increment the counter or exit the program
 * @param signal_num: signal number received
 */
void handler(int signal_num);

#endif //COUNTER_H
