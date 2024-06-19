#include "cli-handler.h"
#include "retval.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

struct InputBuf {
  char *buffer;
  size_t buf_len;
};

// int prompt_prototype(int argc, char *args[]){
//   printf("Welcome to Mogwarts database!\n");
//   if (argc == 2 && strcmp(args[1], "exit") != 0 ){
//     while (true){
//       printf(">>> ");
//       char prompt_input[1000];
//       scanf("%s", prompt_input);
//       // if (result == 1){
//       //   printf("Try again, using rizz!\n");
//       //   continue;
//       // }
//       if (strcmp(prompt_input, "mogging") == 0){
//         printf("Bro can rizz now!\n");
//         exit(0);
//         return 0;
//       }
//     }
//   }
//   printf("Bro is NOT Jordan Barrett\n");
//   exit(1);
//   return 1;
// }

int prompt_prototype(InputBuf *buf){
  if(buf == NULL){
    perror("Saddam Hussein would like to know your coordinates\n");
    return 1;
  }

}

int smoldb_new_input_buf(InputBuf **buf) {
  if (buf == NULL)
    return SMOLDB_NULL_PTR_TO_REF_ERR;
  //trả về một pointer mà trỏ đến bộ nhớ, *buf có giá trị là địa chỉ, hay nó là con trỏ trỏ vào InputBuf.
  //** **buf --> *buf --> Memory for InputBuf */
  (*buf) = (InputBuf *)malloc(sizeof(InputBuf)); 
  if ((*buf) == NULL)
    return SMOLDB_ALLOC_ERR;

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
  int len = strlen(input);
  buf->buffer = realloc(buf->buffer, len + 1);
  if(buf->buffer == NULL){
    perror("Error allocating memory\n");
    return SMOLDB_ALLOC_ERR;
  }
  strncpy(buf->buffer, input, len);
  return SMOLDB_ALLOC_SUCCESS;
}

int smoldb_free_input_buf(InputBuf **buf) {
  if (buf == NULL)
    return SMOLDB_ALLOC_SUCCESS;

  free((*buf)->buffer);
  (*buf)->buffer = NULL;
  free((*buf));
  (*buf) = NULL;

  return SMOLDB_ALLOC_SUCCESS;
}
