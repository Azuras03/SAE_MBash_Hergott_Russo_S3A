#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define MAXLI 2048
char cmd[MAXLI];
char path[MAXLI];
char history[MAXLI][MAXLI];
int count;
void mbash();

int main(int argc, char** argv) {
  printf("-- Welcome to MBash ! --\n");
  count = 0;
  getcwd(path, MAXLI);
  while (1) {
    printf("%s : ", path);
    fgets(cmd, MAXLI, stdin);
    mbash(cmd);
    count++;
  }
  return 0;
}

void mbash() {
    char* token;
    char* args[100];
    int i = 0;
    token = strtok(cmd, " \n");
    while (token != NULL) {
        args[i] = token;
        token = strtok(NULL, " \n");
        i++;
    }
    args[i] = NULL;

    //ajout de la commande dans l'historique
    strcpy(history[count], cmd);

    //vérification du &
    int tacheFond = 0;
    if (strcmp(args[i-1], "&") == 0) {
        tacheFond = 1;
        args[i-1] = NULL;
    }
    //Mise en place de la commande cd
    if (strcmp(args[0], "cd") == 0) {
        if (chdir(args[1]) == -1) {
        printf("Répertoire inexistant ❄\n");
        }
        getcwd(path, MAXLI);
    } else if (strcmp(args[0], "exit") == 0) {
    //comportement de la commande exit
        printf("Bye ! Have a great day ! :D\n\n");
        exit(0);
    } else if (strcmp(args[0], "history") == 0) {
    //comportement de la commande history
        for (int j = 0; j < count; j++) {
            printf("%s\n", history[j]);
        }
    } else {
    //comportement des commandes directement exécutables par la méthode execvp
        int pid = fork();
        if (pid == 0) {
            execvp(args[0], args);
            printf("Commande inconnue ❄\n");
            exit(0);
        } else {
            if (tacheFond == 0) {
                wait(NULL);
            }
        }
    }
}