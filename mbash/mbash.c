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
void mbash();

int main(int argc, char** argv) {
  printf("-- Welcome to MBash ! --\n");
  getcwd(path, MAXLI);
  while (1) {
    printf("%s : ", path);
    fgets(cmd, MAXLI, stdin);
    mbash(cmd);

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
    str
    if (strcmp(args[0], "cd") == 0) {
        if (chdir(args[1]) == -1) {
        printf("Répertoire inexistant ❄\n");
        }
        getcwd(path, MAXLI);
        pathidx = strlen(path);
    } else if (strcmp(args[0], "exit") == 0) {
        printf("By ! Hav a niec dai ahaha eeeeeeeeeeeee\n\n");
        exit(0);
    } else if (strcmp(args[0], "history") == 0) {
        for (int j = 0; j < i; j++) {
            printf("%s\n", history[j]);
        }
    } else {
        int pid = fork();
        if (pid == 0) {
        if(args[0][0] == '.' && args[0][1] == '/') {
            args[0] = args[0] + 2;
        }
            execvp(args[0], args);
            printf("Commande inconnue ❄\n");
            exit(0);
        } else {
        wait(NULL);
        }
    }
}