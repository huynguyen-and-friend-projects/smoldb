#ifndef SMOL_DB_RETVAL_H
#define SMOL_DB_RETVAL_H

/**
 * @typedef SMOL_ALLOC_RETVAL
 * @brief Defines the return codes from functions that allocate memory
 *
 */
typedef enum SMOL_ALLOC_RETVAL {
  /* Nothing special happened, and allocation was successful */
  SMOLDB_ALLOC_SUCCESS = 0,

  /* Malloc failed and returned NULL */
  SMOLDB_ALLOC_ERR,

  /* The pointer to address is NULL,
   * NOTE: this won't happen to NULL pointer (void*) but only to null
   * pointer-to-pointer (void**)
   *
   * */
  SMOLDB_NULL_PTR_TO_REF_ERR,
} SMOLDB_ALLOC_RETVAL;

/**
 * @typedef SMOL_INPUT_READ_RETVAL
 * @brief Defines the return codes from functions that read user input
 *
 */
typedef enum SMOL_INPUT_READ_RETVAL {
  SMOLDB_READ_SUCCESS = 0,
  SMOLDB_READ_ERR,
} SMOL_INPUT_READ_RETVAL;

#endif  // !SMOL_DB_RETVAL_H
