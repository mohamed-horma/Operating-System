/**
 * @file four.c
 * @brief Implementation of cross-platform application launching functionality.
 */

#include <stdio.h>    /* Standard I/O functions */
#include <stdlib.h>   /* Standard library definitions */
#include <unistd.h>   /* POSIX operating system API */
#include <sys/wait.h> /* Process waiting functionality */

#include "logger.h"   /* Custom logging functionality */
#include "four.h"     /* Interface definitions */

/* 
void manage_son1() {
    char *path = "/usr/bin/firefox";
    char *args[] = {path, "-url", "https://foad.ensicaen.fr",
                    "-new-tab", "https://gitlab.ecole.ensicaen.fr", NULL};
    execvp(path, args);
    perror("execvp failed for son1");
    exit(EXIT_FAILURE);
}

void manage_son2() {
    char *path = "/usr/bin/firefox";
    char *args[] = {path, "--search", "chatgpt", NULL};
    execvp(path, args);
    perror("execvp failed for son2");
    exit(EXIT_FAILURE);
} */

 
void launch_process(const char* path, char *const args[]){

    pid_t pid = fork();

    if(pid == 0){
        execvp(path, args);
        perror("execvp failed");
        exit(EXIT_FAILURE);
    } else if (pid < 0){
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
} 