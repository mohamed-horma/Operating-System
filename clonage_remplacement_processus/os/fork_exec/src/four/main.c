/**
 * @file main.c
 * @brief Main program that launches multiple applications.
 */

#include <stdio.h>    /* Standard I/O functions */
#include <stdlib.h>   /* Standard library definitions */
#include <unistd.h>   /* POSIX operating system API */
#include <sys/wait.h> /* Process waiting functionality */

#include "logger.h"   /* Custom logging functionality */
#include "four.h"     /* Application launching functionality */

/**
 * @brief Main entry point for the program.
 *
 * @return EXIT_SUCCESS on successful execution.
 */
int main(void) {
    const char *config_file = "logger.conf";
    
    /* Initialize logging system */
    if (load_config(config_file) != 0) {
        fprintf(stderr, "Failed to load logger configuration: %s\n", config_file);
        return EXIT_FAILURE;
    }
    
    log_info("Starting the \"four\" program");

    /* TO COMPLETE */
    
    log_info("Exiting the \"four\" program");
    return EXIT_SUCCESS;
}
