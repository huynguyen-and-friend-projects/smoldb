/**
 * @file cli-handler
 * @brief Declares a set of functions to receive and handle user inputs
 */

#ifndef SMOLDB_CLI_HANDLER_H
#define SMOLDB_CLI_HANDLER_H

#include "general.h"

/* So that the code runs with Cpp */
#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

/**
 * @typedef InputBuf
 * @brief Holds information about user input or input from stdin
 *
 */
typedef struct InputBuf InputBuf;

/**
 * @brief Allocate memory for a new input buffer
 *
 * @param buf The pointer to the address of the input buffer to be allocated
 * memory
 * @return 0 if successful, something else if error, defined in retval.h
 */
SMOL_API int smoldb_new_input_buf(InputBuf **buf);

/**
 * @brief Free memory allocated to the input buffer specified, if any, and
 * points the pointer to NULL.
 *
 * @param buf The pointer to the address of the input buffer to be freed
 * memory. After being freed, (*buf) = NULL.
 * @return 0 if successful or if buf is NULL (hence nothing to remove)
 */
SMOL_API int smoldb_free_input_buf(InputBuf **buf);

/**
 * @brief Prototype to handle prompt, it will get what the user type in and change it into InputBuf
 * @param InputBuf* buf is a pointer point to the InputBuf, argc is the number of arguments, and args is
 * the list of the arguments. Such as when user runs the program like this: 
 * ./smoldb.exe run --> We will have 2 arguments, the former is ./smoldb.exe, and the latter is run.
 * Inside the function, I also have a supporting function named 
 * int smoldb_input_buf_read(InputBuf *buf, const char *input)
 * In this function, my main purpose is that whenever the user insert a new "input" string, the content
 * of the string will be assigned to the string buffer in InputBuf, and the length of the string will also 
 * be assigned to buf_len.
 * Inside the smoldb_input_buf_read function, I reallocate the memory space for InputBuf with the lenght of 
 * the input, and copy the content of the input string to the string buffer.
 * @return status of the prompt. If the user insert the proper input, the function will return 0, else it will
 * return 1.
*/
SMOL_API int prompt_prototype(InputBuf *buf, int argc, char *args[]);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // !SMOLDB_CLI_HANDLER_H

