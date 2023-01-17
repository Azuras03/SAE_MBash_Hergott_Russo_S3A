#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/syscall.h>
#include <sys/reg.h>


#define MAXLI 2048
char cmd[MAXLI];
char path[MAXLI];
int pathidx;
void mbash();

int main(int argc, char** argv) {
  while (1) {
    printf("Commande %s\n: ", path);
    fgets(cmd, MAXLI, stdin);
    mbash(cmd);
  }
  return 0;
}

void mbash() {
    char *args[10];
    char *token;
    token = strtok(cmd, " ");
    int i = 0;
    while (token != NULL) {
        args[i] = token;
        token = strtok(NULL, " ");
        i++;
    }
    args[i] = NULL;

    char comp[] = "/bin/";
    char *result = malloc(strlen(comp)+strlen(args[0])+1);
    strcpy(result, comp);
    strcat(result, args[0]);

    char *arg[256];
    i = 0;
    while(arg[i] != NULL){
        arg[i] = strtok(args[i+1], " \n");
        i++;
    }

    char *argv[] = {args[0], arg[0], arg[1], arg[2]};

    if(strcmp(result, "cd") == 0){
        chdir(argv[0]);
    }else if(strcmp(result, "exit") == 0){
        exit(0);
    }

    int pid = fork();
    if(pid == 0){
        execv(result, argv);
    }
    else{
        waitpid(pid, NULL, 0);
    }

    char buffer[256];
    FILE *fp = popen(cmd, "r");
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }
    pclose(fp);
}