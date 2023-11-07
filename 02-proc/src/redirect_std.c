#include "redirect_std.h"


void print_usage(char *program_name) {
    fprintf(stderr, "Usage: %s <command>\n", program_name);
}

void handle_child_process(char *command) {
    printf("Child process: PID = %d\n", getpid());

    // Close stdout (fd = 1)
    if (close(1) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }

    // Create a temporary file and open it for writing
    int fd = mkstemp(TEMP_FILE); 
    if (fd == -1) {
        perror("mkstemp");
        exit(EXIT_FAILURE);
    }

    // Display the file descriptor number of the temporary file
    printf("Child process: File descriptor = %d\n", fd);

    if (dup2(fd, 1) == -1) {
        perror("dup2");
        exit(EXIT_FAILURE);
    }

    execlp(command, command, NULL); 
    perror("execlp");
    exit(EXIT_FAILURE);
}

void handle_parent_process() {
    printf("Parent process: PID = %d\n", getpid());

    // Wait for the child process to terminate
    int status;
    if (wait(&status) == -1) {
        perror("wait");
        exit(EXIT_FAILURE);
    }

    printf("That's All Folks !\n");
}

void read_temp_file() {
    int fd = open(TEMP_FILE, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    char *buffer = malloc(sizeof(char) * BUFFER_SIZE);
    ssize_t nread;

    while ((nread = read(fd, buffer, BUFFER_SIZE)) > 0) {
        write(1, buffer, nread);
    }

    close(fd);
    free(buffer);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    printf("Step 1: Message with the first argument: %s\n", argv[1]);

    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (child_pid == PID_OF_CHILD_PROCESS) {
        handle_child_process(argv[1]);
    } else {
        handle_parent_process();
    }

    read_temp_file();

    return EXIT_SUCCESS;
}
