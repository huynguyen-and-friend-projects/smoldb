#include "cli-handler.h"

#include <stdlib.h>

#include "retval.h"

int smoldb_new_input_buf(InputBuf **buf) {
  if (buf == NULL) {
    return SMOLDB_NULL_PTR_TO_REF_ERR;
  }

  (*buf) = (InputBuf *)malloc(sizeof(InputBuf));
  if ((*buf) == NULL) {
    return SMOLDB_ALLOC_ERR;
  }

  smoldb_default_input_buf(*buf);
  return SMOLDB_ALLOC_SUCCESS;
}

int smoldb_free_input_buf(InputBuf **buf) {
  if (buf == NULL) {
    return SMOLDB_ALLOC_SUCCESS;
  }

  smoldb_clean_input_buf(*buf);
  free((*buf));
  (*buf) = NULL;

  return SMOLDB_ALLOC_SUCCESS;
}

int smoldb_default_input_buf(InputBuf *buf) {
    if(buf == NULL){
        return SMOLDB_NULL_PTR_ERR;
    }
  buf->buffer = NULL;
  buf->buf_len = 0;
  return SMOLDB_SUCCESS;
}

int smoldb_clean_input_buf(InputBuf *buf) {
    if(buf == NULL) {
        return SMOLDB_SUCCESS;
    }
    free(buf->buffer);
    buf->buffer = NULL;
    return SMOLDB_SUCCESS;
}
