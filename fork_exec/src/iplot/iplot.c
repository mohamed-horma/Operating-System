/**
 * @file iplot.c
 * @brief Functions used to plot the sinc function using gnuplot.
 */

#include <stdio.h>    /* Standard I/O functions */
#include <stdlib.h>   /* Standard library definitions */
#include <unistd.h>   /* POSIX operating system API */
#include <sys/wait.h> /* Process waiting functionality */

#include "logger.h"   /* Custom logging functionality */
#include "iplot.h"    /* Interface definitions */


void iplot_function(int borne){
    FILE* f = fopen("/tmp/commandes.gp", "w");
    if (f == NULL) {
        printf("Erreur : impossible de créer le fichier.\n");
        return;
    }

    fprintf(f, "set samples 500\n");
    fprintf(f, "set title \"Sinus Cardinal (TP Unix)\"\n");
    fprintf(f, "set xlabel \"x\"\n");
    fprintf(f, "set ylabel \"sin(x)/x\"\n");
    fprintf(f, "set xrange [0:%d]\n", borne);
    fprintf(f, "set border\n");
    fprintf(f, "set grid\n");
    fprintf(f, "plot sin(x)/x title \"f(x) = sin(x)/x\"\n");
    fprintf(f, "pause -1 \"Fermez la fenêtre puis appuyez sur Entrée dans le terminal pour continuer...\"\n");

    fclose(f);

}
