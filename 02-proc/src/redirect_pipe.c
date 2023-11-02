
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

#define PID_OF_CHILD_PROCESS 0

int main(int argc, char *argv[]) {
    if (argc >= 2) {
        fprintf(stderr, "Usage: %s <command>\n", argv[0]);
        return 1;
    }

    printf("Étape 1: Message avec le premier mot passé en argument: %s\n", argv[1]);

    // Étape 2: Crée un fils
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("ERROR : Fork failed.\n");
        return EXIT_FAILURE;
    }

    if (child_pid == PID_OF_CHILD_PROCESS) { 
        printf("Étape 2 (Fils): PID du fils = %d\n", getpid());

        // Ferme STDOUT (descripteur 1)
        if (close(1) == -1) {
            perror("close");
            exit(EXIT_FAILURE);
        }

        // Ouvre et écrit dans le fichier temporaire
        int fd = mkstemp("/tmp/proc-exercise");
        if (fd == -1) {
            perror("ERROR: mkstemp");
            exit(EXIT_FAILURE);
        }

        printf("Étape 2 (Fils): Numéro de descripteur du fichier ouvert = %d\n", fd);

        // Utilise dup2 pour rediriger la sortie vers le fichier
        if (dup2(fd, 1) == -1) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }

        // Exécute le programme passé en argument
        execlp(argv[1], argv[1], NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    } else { // Code du père
        printf("Étape 2 (Père): PID du père = %d\n", getpid());

        // Attend la fin du fils
        int status;
        if (wait(&status) == -1) {
            perror("wait");
            return 1;
        }

        // Affiche un message avant de terminer
        printf("That's All Folks !\n");
    }

    // Étape 3: Examine le contenu de /tmp/proc-exercise en fermant le descripteur 2
    int fd = open("/tmp/proc-exercise", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }

    // Affiche le contenu du fichier
    char * buffer = malloc(sizeof(char) * 1024);
    ssize_t nread;

    while ((nread = read(fd, buffer, sizeof(buffer))) > 0) {
        write(1, buffer, nread); // Écrit dans la sortie standard
    }

    close(fd);
    free(buffer);
    return EXIT_SUCCESS;
}
