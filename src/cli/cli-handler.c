#include "cli-handler.h"

#include <stdlib.h>

#include "retval.h"

struct InputBuf {
  char *buffer;
  size_t buf_len;
};

int smoldb_new_input_buf(InputBuf **buf) {
  if (buf == NULL) {
    return SMOLDB_NULL_PTR_TO_REF_ERR;
  }

  (*buf) = (InputBuf *)malloc(sizeof(InputBuf));
  if ((*buf) == NULL) {
    return SMOLDB_ALLOC_ERR;
  }

  (*buf)->buffer = NULL;
  (*buf)->buf_len = 0;

  return SMOLDB_ALLOC_SUCCESS;
}

int smoldb_free_input_buf(InputBuf **buf) {
  if (buf == NULL) {
    return SMOLDB_ALLOC_SUCCESS;
  }

  free((*buf)->buffer);
  (*buf)->buffer = NULL;
  free((*buf));
  (*buf) = NULL;

  return SMOLDB_ALLOC_SUCCESS;
}
