/**
 * @file simple.c
 * @brief A process that creates and manages a child process.
 */

#include <stdio.h>    /* Standard I/O functions */
#include <stdlib.h>   /* Standard library definitions */
#include <unistd.h>   /* POSIX operating system API */
#include <sys/wait.h> /* Process waiting functionality */

#include "logger.h"   /* Custom logging functionality */

/**
 * @brief Logs an error message, prints the system error, and exits.
 *
 * @param msg The error message to log and print.
 */
void manage_error_and_exit(const char *msg) {
    perror(msg);
    log_error("%s", msg);
    exit(EXIT_FAILURE);
}

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
    
    log_info("Starting \"simple\" process");
    
    pid_t pid;

    pid = fork();
    
    if(pid < 0){
        manage_error_and_exit("Error");
    }
    if (pid > 0){
        printf("Parentis PID is %d\n", getpid());
    }else{
        printf("Child process PID %d\n", getpid() );
        execlp("bin/very_simple", "very_simple", NULL);
    }
    
    
    log_info("Exiting \"simple\" process");

    return EXIT_SUCCESS;
}
