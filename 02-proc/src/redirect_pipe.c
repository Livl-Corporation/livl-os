#include "redirect_pipe.h"

void execute_command_in_child(const char* command, const char* argument, int fd[]) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("ERROR: fork\n");
        exit(EXIT_FAILURE);
    }

    if (pid == PID_OF_CHILD_PROCESS) { 
        dup2(fd[WRITE_END], STDOUT_FILENO);
        close(fd[READ_END]);
        close(fd[WRITE_END]);

        execlp(command, command, argument, NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }
}

void check_root_and_display_message(int fd[]) {
    int status;
    wait(&status); // wait end child

    pid_t pid = fork();
    if (pid == -1) {
        perror("ERROR: fork\n");
        exit(EXIT_FAILURE);
    }

    if (pid == PID_OF_CHILD_PROCESS) { 
        dup2(fd[READ_END], STDIN_FILENO);
        close(fd[READ_END]);
        close(fd[WRITE_END]);

        execlp("grep", "grep", "^root ", NULL);
        perror("execlp grep");
        exit(EXIT_FAILURE);
    } else { // daddy process
        close(fd[READ_END]);
        close(fd[WRITE_END]);
        wait(&status); // wait child
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            write(STDOUT_FILENO, MESSAGE, MESSAGE_LENGTH);
        }
    }
}

int main() {
    int fd[2];

    if (pipe(fd) == -1) {
        perror("ERROR: pipe\n");
        exit(EXIT_FAILURE);
    }

    execute_command_in_child("ps", "eaux", fd);
    check_root_and_display_message(fd);

    return 0;
}
