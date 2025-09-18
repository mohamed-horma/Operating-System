/**
 * @file main.c
 * @brief Program to plot the sinc function using gnuplot.
 */

#include <stdio.h>    /* Standard I/O functions */
#include <stdlib.h>   /* Standard library definitions */
#include <unistd.h>   /* POSIX operating system API */
#include <sys/wait.h> /* Process waiting functionality */
#include <sys/types.h>
#include <fcntl.h>
 

#include "iplot.h"
#include "logger.h"

/**
 * @brief Main entry point for the program.
 *
 * @return EXIT_SUCCESS on successful execution.
 */
int main(void) {
    const char *config_file = "logger.conf";
    
    /* Initialize logging system */
    if (load_config(config_file) != 0) {
        fprintf(stderr, "Failed to load logger configuration\n");
        return EXIT_FAILURE;
    }
    
    log_info("Starting the curve plotting program");
    
    /* TO COMPLETE */
    
    
    pid_t pid;
    int borne;
    printf("saisir un entier positive : ");
    scanf("%d", &borne);
    while (borne != -1 ){
        iplot_function(borne);
    
        pid = fork();

        if(pid<0){
            perror("error");
            exit(EXIT_FAILURE);
        }
        if(pid>0){
            printf("PID parent : %d", getpid());
            wait(0);
        } else{
            printf("PID child: %d", getpid());
            execlp("gnuplot","gnuplot", "/tmp/commandes.gp", NULL);
        }

        printf("\nsaisir un entier positive : \n");
        scanf("%d", &borne);
    }
    
    log_info("Exiting the curve plotting program");

    return EXIT_SUCCESS;
}
