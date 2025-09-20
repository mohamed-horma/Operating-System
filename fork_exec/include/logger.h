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
 * @file logger.h
 * @brief Header for logging functionality with different log levels.
 */

#ifndef LOGGER_H
#define LOGGER_H

/**
 * @brief Loads configuration from a file.
 * 
 * @param filename Path to the configuration file.
 * @return 0 on success, -1 on failure.
 */
int load_config(const char *filename);

/**
 * @brief Initializes the logger with a log file.
 * 
 * @param log_file Path to the log file.
 */
void log_init(const char *log_file);

/**
 * @brief Closes and cleans up the logger.
 */
void log_close(void);

/**
 * @brief Logs an error message.
 * 
 * @param message Format string for the message.
 * @param ... Variable arguments for the format string.
 */
void log_error(const char *message, ...);

/**
 * @brief Logs an informational message.
 * 
 * @param message Format string for the message.
 * @param ... Variable arguments for the format string.
 */
void log_info(const char *message, ...);

/**
 * @brief Logs a warning message.
 * 
 * @param message Format string for the message.
 * @param ... Variable arguments for the format string.
 */
void log_warning(const char *message, ...);

/**
 * @brief Logs a debug message.
 * 
 * @param message Format string for the message.
 * @param ... Variable arguments for the format string.
 */
void log_debug(const char *message, ...);

/**
 * @brief Logs a system error message using errno.
 * 
 * @param message Prefix for the error message.
 */
void log_system_error(const char *message);

#endif /* LOGGER_H */
