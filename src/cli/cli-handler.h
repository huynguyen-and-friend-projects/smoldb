/**
 * @file cli-handler
 * @brief Declares a set of functions to receive and handle user inputs
 */

#ifndef SMOL_DB_CLI_HANDLER_H
#define SMOL_DB_CLI_HANDLER_H

#include <stdlib.h>

#include "general.h"
#include "retval.h"

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

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // !SMOL_DB_CLI_HANDLER_H
