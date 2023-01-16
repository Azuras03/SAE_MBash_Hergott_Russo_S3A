#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#define MAXLI 2048
char cmd[MAXLI];
char path[MAXLI];
int pathidx;
void mbash();
int main(int argc, char** argv) {
  while (1) {
    printf("Commande: ");
    fgets(cmd, MAXLI, stdin);
    mbash(cmd);
  }
  return 0;
}

void mbash() {
  /*printf("Execute: %s", cmd);
  system(cmd);*/
  //execve
    char *args[10];
    char *token;
    int i = 0;
    token = strtok(cmd, " ");
    while (token != NULL) {
        args[i] = token;
        token = strtok(NULL, " ");
        i++;
    }
    args[i] = NULL;
    //concat two char
    char comp[] = "/bin/";
    char *result = malloc(strlen(comp)+strlen(args[0])+1);
    strcpy(result, comp);
    strcat(result, args[0]);
    printf("%s",args[0]);
    char res = execve(result, args, NULL);
    printf("res: %s", result);
}