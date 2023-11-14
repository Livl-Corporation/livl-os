#include "redirect_pipe.h"

void create_child_process(int* pipe_fd, pid_t* child_pid, char* command, char* command_arg, int std_fd, int pipe_fd_index) {
    if ((*child_pid = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (*child_pid == PID_OF_CHILD_PROCESS) { 
        close(pipe_fd[1 - pipe_fd_index]);

        if (dup2(pipe_fd[pipe_fd_index], std_fd) == -1) {
            perror("dup");
            exit(EXIT_FAILURE);
        }

        close(pipe_fd[pipe_fd_index]);

        if (execlp(command, command, command_arg, (char *)NULL) == -1) {
            perror("execlp");
            exit(EXIT_FAILURE);
        }
    }
}

int main() {
    int pipe_fd[2];
    pid_t child_pid_ps, child_pid_grep;

    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    create_child_process(pipe_fd, &child_pid_ps, "ps", "eaux", STDOUT_FILENO, STDOUT_FILENO);
    create_child_process(pipe_fd, &child_pid_grep, "grep", "^root", STDIN_FILENO, STDIN_FILENO);

    close(pipe_fd[0]);
    close(pipe_fd[1]);

    waitpid(child_pid_ps, NULL, 0);
    waitpid(child_pid_grep, NULL, 0);

    write(STDOUT_FILENO, MESSAGE, MESSAGE_LENGTH);
    return 0;
}
