#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <message>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pid_t pid;
    int fd;

    printf("Père (PID=%d)\n", getpid());

    if ((pid = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Code exécuté par le fils
        printf("Fils (PID=%d)\n", getpid());

        // Ferme le descripteur STDOUT (1)
        if (close(1) == -1) {
            perror("close");
            exit(EXIT_FAILURE);
        }

        // Ouvre en création et écriture le fichier temporaire /tmp/proc-exercise
        if ((fd = mkstemp("/tmp/proc-exercise.XXXXXX")) == -1) {
            perror("mkstemp");
            exit(EXIT_FAILURE);
        }

        // Affiche le numéro du descripteur de fichier ouvert
        printf("Descripteur de fichier ouvert : %d\n", fd);

        // Utilise dup2 pour rediriger le descripteur de fichier vers STDOUT (1)
        if (dup2(fd, 1) == -1) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }

        // Exécute le programme affiché par son père
        execlp(argv[1], argv[1], NULL);

        // Si execlp échoue, affiche une erreur
        perror("execlp");
        exit(EXIT_FAILURE);
    } else { // Code exécuté par le père
        // Attend la fin du fils
        if (waitpid(pid, NULL, 0) == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }

        printf("Père (PID=%d): That’s All Folks !\n", getpid());
    }

    return 0;
}
