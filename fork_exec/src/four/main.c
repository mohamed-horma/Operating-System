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
    char *firefox_args1[] = {"firefox", "-url", "https://foad.ensicaen.fr",
                      "-new-tab", "-url", "https://gitlab.ecole.ensicaen.fr", NULL };
    
    char *firefox_args2[] = {"firefox", "--search", "Codeium", 
                             "-new-tab", "--search", "Vim", NULL};
    
    char *gedit_args[] = {"gedit", "files.txt", NULL};

    char *evince_args[] = {"evince", "report.pdf", NULL};

     /* child 1 executes firefox with firefox_args1 */
    launch_process("/usr/bin/firefox", firefox_args1);
    /* child 2 executes firefox with firefox_args2 */
    launch_process("/usr/bin/firefox", firefox_args2);
    /* child 3 executes gedit with gedit_args */
    launch_process("/usr/bin/gedit", gedit_args);
    /* child 4 executes EVINCE with evince_args */
    launch_process("/usr/bin/vlc", evince_args);
    
    for(int i=0; i<4;i++){
        wait(NULL);
    }

    
    log_info("Exiting the \"four\" program");
    return EXIT_SUCCESS;
}
