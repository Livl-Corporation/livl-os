#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main() {
    int pipe_fd[2];
    pid_t child_pid;

    // Création du pipe
    if (pipe(pipe_fd) == -1) {
        error("Erreur lors de la création du pipe");
    }

    // Création du processus fils
    if ((child_pid = fork()) == -1) {
        error("Erreur lors de la création du processus fils");
    }

    if (child_pid == 0) { // Code du fils
        // Fermeture du descripteur de lecture inutilisé
        close(pipe_fd[0]);

        // Redirection de la sortie standard vers le descripteur d'écriture du pipe
        if (dup2(pipe_fd[1], STDOUT_FILENO) == -1) {
            error("Erreur lors de la redirection de la sortie standard");
        }

        // Fermeture du descripteur d'écriture du pipe après la redirection
        close(pipe_fd[1]);

        // Exécution de la commande ps
        if (execlp("ps", "ps", "eaux", (char *)NULL) == -1) {
            error("Erreur lors de l'exécution de ps");
        }
    } else { // Code du parent
        // Fermeture du descripteur d'écriture inutilisé
        close(pipe_fd[1]);

        // Redirection de l'entrée standard vers le descripteur de lecture du pipe
        if (dup2(pipe_fd[0], STDIN_FILENO) == -1) {
            error("Erreur lors de la redirection de l'entrée standard");
        }

        // Fermeture du descripteur de lecture du pipe après la redirection
        close(pipe_fd[0]);

        // Exécution de la commande grep
        if (execlp("grep", "grep", "^root", (char *)NULL) == -1) {
            error("Erreur lors de l'exécution de grep");
        }

        // Attente de la fin du processus fils
        wait(NULL);
    }

            // Affichage du message final
        write(STDOUT_FILENO, "root est connecté\n", 18);

    return 0;
}
