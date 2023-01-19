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
int pathidx;
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

    //add the current command to history
    strcpy(history[count], cmd);

    if (strcmp(args[0], "cd") == 0) {
        if (chdir(args[1]) == -1) {
        printf("Répertoire inexistant ❄\n");
        }
        getcwd(path, MAXLI);
        pathidx = strlen(path);
    } else if (strcmp(args[0], "exit") == 0) {
        printf("Bye ! Have a great day ! :D\n\n");
        exit(0);
    } else if (strcmp(args[0], "history") == 0) {
        for (int j = 0; j < count; j++) {
            printf("%s\n", history[j]);
        }
    } else {
        int pid = fork();
        if (pid == 0) {
            execvp(args[0], args);
            printf("Commande inconnue ❄\n");
            exit(0);
        } else {
        wait(NULL);
        }
    }
}