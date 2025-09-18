/*
 * Unix System Programming Practical Work / TP de programmation système Unix
 * Copyright (C) 1995-2024 Alain Lebret (alain.lebret@ensicaen.fr)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file logger.c
 * @brief Provides logging functionality with different log levels.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <errno.h>
#include "logger.h"

/* ANSI terminal color codes */
#define RED "\033[31m"
#define CYN "\033[36m"
#define YEL "\033[33m"
#define RESET "\033[0m"

/* Global flags for log levels */
static int log_error_enabled = 1;  /* Default to enabled */
static int log_info_enabled  = 0;
static int log_warning_enabled = 1;  /* Default to enabled */
static int log_debug_enabled = 0;
static FILE *log_fp   = NULL;
static int log_fd     = -1;

/**
 * @brief Formats and outputs a log message.
 * 
 * @param tag Log level tag (Error, Info, Debug).
 * @param message Format string for the message.
 * @param args Variable argument list.
 */
static void log_format(const char *tag, const char *message, va_list args) {
    time_t now;
    struct tm *timeinfo;
    char time_buffer[26];
    
    /* Get current time */
    if (time(&now) == -1) {
        fprintf(stderr, "Failed to get current time\n");
        return;
    }
    
    /* Format time in a thread-safe manner */
    timeinfo = localtime(&now);
    if (timeinfo == NULL) {
        fprintf(stderr, "Failed to convert time\n");
        return;
    }
    
    if (strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d %H:%M:%S", timeinfo) == 0) {
        fprintf(stderr, "Failed to format time\n");
        return;
    }
    
    /* Determine output stream */
    FILE* output = (strcmp(tag, "Error") == 0) ? stderr : stdout;
    
    /* Output to console */
    fprintf(output, "%s [%s] ", time_buffer, tag);
    vfprintf(output, message, args);
    fprintf(output, "\n");
    
    /* Output to log file if initialized */
    if (log_fp != NULL) {
        fprintf(log_fp, "%s [%s] ", time_buffer, tag);
        vfprintf(log_fp, message, args);
        fprintf(log_fp, "\n");
        if (fflush(log_fp) != 0) {
            fprintf(stderr, "Failed to flush log file: %s\n", strerror(errno));
        }
    }
}

/**
 * @brief Loads configuration from a file.
 * 
 * @param filename Path to the configuration file.
 * @return 0 on success, -1 on failure.
 */
int load_config(const char *filename) {
    FILE *file;
    char line[256];
    
    if (filename == NULL) {
        fprintf(stderr, "Invalid configuration filename\n");
        return -1;
    }
    
    file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Failed to open the config file: %s\n", strerror(errno));
        return -1;
    }
    
    while (fgets(line, sizeof(line), file) != NULL) {
        /* Remove trailing newline if present */
        size_t len = strlen(line);
        if (len > 0 && line[len-1] == '\n') {
            line[len-1] = '\0';
        }
        
        if (strstr(line, "ERROR = ON")) {
            log_error_enabled = 1;
        } else if (strstr(line, "INFO = ON")) {
            log_info_enabled = 1;
        } else if (strstr(line, "DEBUG = ON")) {
            log_debug_enabled = 1;
        } else if (strstr(line, "ERROR = OFF")) {
            log_error_enabled = 0;
        } else if (strstr(line, "INFO = OFF")) {
            log_info_enabled = 0;
        } else if (strstr(line, "DEBUG = OFF")) {
            log_debug_enabled = 0;
        } else if (strstr(line, "WARNING = ON")) {
            log_warning_enabled = 1;
        } else if (strstr(line, "WARNING = OFF")) {
            log_warning_enabled = 0;
        }
    }
    
    if (fclose(file) != 0) {
        fprintf(stderr, "Failed to close the config file: %s\n", strerror(errno));
    }
    
    return 0;
}

/**
 * @brief Initializes the logger with a log file.
 * 
 * @param log_file Path to the log file.
 */
void log_init(const char *log_file) {
    if (log_file == NULL) {
        fprintf(stderr, "Invalid log file path\n");
        return;
    }
    
    log_fp = fopen(log_file, "a");
    if (log_fp == NULL) {
        fprintf(stderr, "Failed to open the log file: %s\n", strerror(errno));
        return;
    }
    
    log_fd = fileno(log_fp);
    if (log_fd == -1) {
        fprintf(stderr, "Failed to get file descriptor: %s\n", strerror(errno));
        fclose(log_fp);
        log_fp = NULL;
    }
}

/**
 * @brief Closes and cleans up the logger.
 */
void log_close(void) {
    if (log_fp != NULL) {
        if (fclose(log_fp) != 0) {
            fprintf(stderr, "Failed to close log file: %s\n", strerror(errno));
        }
        log_fp = NULL;
        log_fd = -1;
    }
}

/**
 * @brief Logs an error message.
 * 
 * @param message Format string for the message.
 * @param ... Variable arguments for the format string.
 */
void log_error(const char *message, ...) {
    va_list args;
    
    if (log_error_enabled && message != NULL) {
        va_start(args, message);
        fprintf(stderr, RED);
        log_format("Error", message, args);
        fprintf(stderr, RESET);
        va_end(args);
    }
}

/**
 * @brief Logs an informational message.
 * 
 * @param message Format string for the message.
 * @param ... Variable arguments for the format string.
 */
void log_info(const char *message, ...) {
    va_list args;
    
    if (log_info_enabled && message != NULL) {
        va_start(args, message);
        log_format("Info", message, args);
        va_end(args);
    }
}

/**
 * @brief Logs a warning message.
 * 
 * @param message Format string for the message.
 * @param ... Variable arguments for the format string.
 */
void log_warning(const char *message, ...) {
    va_list args;
    
    if (log_warning_enabled && message != NULL) {
        va_start(args, message);
        fprintf(stdout, YEL);
        log_format("Warning", message, args);
        fprintf(stdout, RESET);
        va_end(args);
    }
}

/**
 * @brief Logs a debug message.
 * 
 * @param message Format string for the message.
 * @param ... Variable arguments for the format string.
 */
void log_debug(const char *message, ...) {
    va_list args;
    
    if (log_debug_enabled && message != NULL) {
        va_start(args, message);
        fprintf(stdout, CYN);
        log_format("Debug", message, args);
        fprintf(stdout, RESET);
        va_end(args);
    }
}

/**
 * @brief Logs a system error message using errno.
 * 
 * @param message Prefix for the error message.
 */
void log_system_error(const char *message) {
    if (message != NULL) {
        log_error("%s: %s", message, strerror(errno));
    }
}
