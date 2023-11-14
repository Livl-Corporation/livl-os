#include "redirect_std.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <command>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pid_t child_pid;
    int fd_temp_file;

    /**
     * This is a template is needed to create a temporary file
    */
    char temp_file[] = TEMP_FILENAME;

    printf("Père (PID=%d)\n", getpid());

    if ((child_pid = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == PID_OF_CHILD_PROCESS) { 
        printf("Fils (PID=%d)\n", getpid());

        /**
         * 2.2 : Close the standart output file descriptor (stdout)
         *      --> But we get an error message on the terminal
         *      --> <command of argv[1]>: write error: Bad file descriptor
         *      --> We have this error since we run the command execpl() 
         *          with the file descriptor STDOUT_FILENO closed
         * 3. Close the error output file descriptor (stderr)
         *     --> We don't get an error message on the terminal anymore
         * */
        if (close(STDERR_FILENO) == -1) {
            perror("close");
            exit(EXIT_FAILURE);
        }

        // Ouvre en création et écriture le fichier temporaire /tmp/proc-exercise
        if ((fd_temp_file = mkstemp(temp_file)) == -1) {
            perror("mkstemp");
            exit(EXIT_FAILURE);
        }

        printf("Descripteur de fichier ouvert : %d\n", fd_temp_file);

        if (dup2(fd_temp_file, STDOUT_FILENO) == -1) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }

        close(fd_temp_file);

        // Execute the command specified by argv[1]
        if(execlp(argv[1], argv[1], NULL) == -1) {
            perror("execlp");
            exit(EXIT_FAILURE);
        } 
    } 

    if (waitpid(child_pid, NULL, 0) == -1) {
        perror("waitpid");
        exit(EXIT_FAILURE);
    }

    printf("Père (PID=%d): Thats All Folks !\n", getpid());

    return 0;
}
