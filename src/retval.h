#ifndef SMOLDB_RETVAL_H
#define SMOLDB_RETVAL_H

/**
 * @typedef SMOL_GENERAL_RETVAL
 * @brief A generic success return code. Used when there isn't any allocation
 * of I/O operation involved.
 *
 * The functions that don't do memory allocation or I/O are much less likely
 * to throw errors anyways.
 *
 */
typedef enum SMOL_GENERAL_RETVAL {
    SMOLDB_SUCCESS = 0,
} SMOL_GENERAL_RETVAL;
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
  SMOLDB_NULL_PTR_ERR,
} SMOL_INPUT_READ_RETVAL;

#endif // !SMOLDB_RETVAL_H
