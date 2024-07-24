#include "cli-handler.h"

#include <stdlib.h>

#include "retval.h"

struct InputBuf {
  char *buffer;
  size_t buf_len;
};

int smoldb_new_input_buf(InputBuf **buf) {
  if (buf == nullptr) {
    return SMOLDB_NULL_PTR_TO_REF_ERR;
  }

  (*buf) = (InputBuf *)malloc(sizeof(InputBuf));
  if ((*buf) == nullptr) {
    return SMOLDB_ALLOC_ERR;
  }

  (*buf)->buffer = nullptr;
  (*buf)->buf_len = 0;

  return SMOLDB_ALLOC_SUCCESS;
}

int smoldb_free_input_buf(InputBuf **buf) {
  if (buf == nullptr) {
    return SMOLDB_ALLOC_SUCCESS;
  }

  free((*buf)->buffer);
  (*buf)->buffer = nullptr;
  free((*buf));
  (*buf) = nullptr;

  return SMOLDB_ALLOC_SUCCESS;
}
