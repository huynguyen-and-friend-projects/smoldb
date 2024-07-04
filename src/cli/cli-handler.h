/**
 * @file cli-handler
 * @brief Declares a set of functions to receive and handle user inputs
 */

#ifndef SMOLDB_CLI_HANDLER_H
#define SMOLDB_CLI_HANDLER_H

#include "general.h"
#include <stdlib.h>

/* So that the code runs with Cpp */
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
/**
 * @typedef InputBuf
 * @brief Holds information about user input or input from stdin
 *
 * WARNING: do NOT modify the fields inside. This should be done through
 * API calls.
 * NOTE: You can still get the values inside. Just don't modify them.
 * TODO: Add more API to change values inside InputBuf
 */
struct InputBuf {
  char *buffer;
  size_t buf_len;
};

typedef struct InputBuf InputBuf;

/**
 * @brief Heap-allocate memory for a new input buffer, and set defaults values.
 *
 * The defaults set by this function is the same as smoldb_default_input_buf.
 *
 * @param buf The pointer to the address of the input buffer to be allocated
 * memory
 * @return 0 if successful, something else if error, defined in retval.h
 */
SMOL_API int smoldb_new_input_buf(InputBuf **buf);

/**
 * @brief Set default values for an InputBuf.
 *
 * NOTE: Works for stack-allocated InputBuf. In fact, any stack-allocated
 * InputBufs should be passed into this function.
 *
 * @param buf
 */
SMOL_API int smoldb_default_input_buf(InputBuf *buf);

/**
 * @brief Free heap-allocated memory to the input buffer specified, if any, and
 * points the pointer to NULL.
 *
 * WARNING: you don't and should NOT pass in a stack-allocated InputBuf.
 *
 * @param buf The pointer to the address of the input buffer to be freed
 * memory. After being freed, (*buf) = NULL.
 * @return 0 if successful or if buf is NULL (hence nothing to remove)
 */
SMOL_API int smoldb_free_input_buf(InputBuf **buf);

/**
 * @brief Frees heap-allocated memory inside an InputBuf.
 *
 * NOTE: Call this for stack-allocated InputBuf. For heap-allocated InputBuf,
 * one can call the smoldb_free_input_buf method to free the entire InputBuf.
 *
 * @param buf 
 * @return 
 */
SMOL_API int smoldb_clean_input_buf(InputBuf *buf);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !SMOLDB_CLI_HANDLER_H
