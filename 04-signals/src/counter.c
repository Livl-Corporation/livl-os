#include "counter.h"

/**
 * @volatile: ensures that the variable is loaded from memory each time it’s used
 *           the value of the variable may change at any time
 * @sig_atomic_t: ensures that operations on the variable are atomic, meaning they can’t be interrupted 
 */
volatile sig_atomic_t sigint_count = 0;

void handler(int signal_num) {
    if (signal_num == SIGINT) {
        sigint_count++;
        printf("SIGINT received: %d\n", sigint_count);
    } else if (signal_num == SIGTERM) { // Run the command : kill -TERM <pid> to send a SIGTERM signal
        printf("SIGTERM received. Exiting...\n");
        exit(EXIT_SUCCESS);
    }
}

int main() {

    printf("Run the command : kill -TERM %d to send a SIGTERM signal\n", getpid());

    if (signal(SIGINT, handler) == SIG_ERR) {
        perror("Error setting a signal handler for SIGINT");
        exit(EXIT_FAILURE);
    }

    if (signal(SIGTERM, handler) == SIG_ERR) {
        perror("Error setting a signal handler for SIGTERM");
        exit(EXIT_FAILURE);
    }

    // Infinite loop to keep the program running
    while(1) {}

    return EXIT_SUCCESS;
}
