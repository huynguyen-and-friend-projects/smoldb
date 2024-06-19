#include "cli-handler.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "retval.h"

struct InputBuf {
  char *buffer;
  size_t buf_len;
};

static int smoldb_input_buf_read(InputBuf *buf, const char *input);

/**
 * @brief This function handle the input of user and create a prompt 
 * @param buf for buffer, argc = number of arguments, *args[] = array of arguments
 * @return status: 0 = success, 1 = failed
 */
int prompt_prototype(InputBuf *buf, int argc, char *args[]){
  if (buf == NULL){
    perror("Point to NULL");
    return SMOLDB_NULL_PTR_TO_REF_ERR;
  };
  printf("Welcome to Mogwarts university\n");
  if (argc == 2 && strcmp(args[1], "exit") != 0){
    while (true){
      printf(">>> ");
      char prompt_input[1000];
      scanf("%s", prompt_input);
      smoldb_input_buf_read(buf, prompt_input);
      if (strcmp(prompt_input, "mogging") == 0){
        printf("Bro can rizz now!\n");
        exit(0);
        return 0;        
      }
    }
  }
  printf("Bro is NOT Jordan Barrett\n");
  exit(1);
  return 1;
}

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
/**
 * @brief Helper function to read input and write to buffer. This function reallocates the buffer contained inside 
 * buf.
 * @param buf the buffer to pass in. If buffer is NULL, the function fails. If allocation fails, the function also
 * fails
 * @return SMOLDB_ALLOC_SUCCESS if succeeded, SMOLDB_ALLOC_ERR if fail
 */
static int smoldb_input_buf_read(InputBuf *buf, const char *input){
  if (buf == NULL){
    perror("Point to NULL!");
    return SMOLDB_NULL_PTR_TO_REF_ERR;
  }
  int length = strlen(input);
  buf->buffer = realloc(buf->buffer, length + 1);
  if (buf->buffer == NULL){
    perror("Error allocating memory!");
    return SMOLDB_ALLOC_ERR;
  }
  strncpy(buf->buffer, input, length);
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
