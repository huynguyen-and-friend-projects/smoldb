#include "cli-handler.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>  // For usleep function
#include "retval.h"

// I will define some styling here:

#define RESET_ALL "\033[0m"

/* List of colors */

#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGNETA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define DEFAULT_COLOR "\033[39m"

/* List of formats */

#define BOLD "\033[1m"
#define DIM "\033[2m"
#define ITALIC "\033[3m"
#define UNDERLINE "\033[4m"
#define STRIKETHROUGH "\033[9m" 
#define CLEAR_SCREEN "\033[H\033[J"

struct InputBuf {
  char *buffer;
  size_t buf_len;
};

void animate_intro() {
    char intro[] = "Welcome to Mogwarts University!";
    int len = strlen(intro);
    int index = 0;

    while (index < len) {
        printf(CLEAR_SCREEN);  // Clear the console
        printf(GREEN BOLD);    // Set text color and style

        for (int i = 0; i < len; i++) {
            if (i == index) {
                printf("%c", toupper(intro[i]));  // Uppercase the current character
            } else {
                printf("%c", intro[i]);
            }
        }

        printf(RESET_ALL);  // Reset text attributes
        fflush(stdout);     // Flush the output buffer
        // Create a timespec structure for nanosleep
        struct timespec req;
        req.tv_sec = 0;
        req.tv_nsec = 100000000L;  // 100 milliseconds
        nanosleep(&req, NULL);     // Sleep for the specified time
        index++;            // Move to the next character
    }
    printf("\n");
}

static int smoldb_input_buf_read(InputBuf *buf, const char *input);

/**
 * @brief This function handle the input of user and create a prompt 
 * @param buf for buffer, argc = number of arguments, *args[] = array of arguments
 * @return status: 0 = success, 1 = failed
 */
int prompt_prototype(InputBuf *buf, int argc, char *args[]){
  if (buf == NULL){
    perror(RED BOLD "Point to NULL\n" RESET_ALL);
    return SMOLDB_NULL_PTR_TO_REF_ERR;
  };
  animate_intro();
  printf(YELLOW BOLD "~~What do you want to learn to day?~~ \n" RESET_ALL);
  if (argc == 2 && strcmp(args[1], "exit") != 0){
    while (true){
      printf(">>> ");
      char prompt_input[1000];
      // Read the entire line
      if (fgets(prompt_input, sizeof(prompt_input), stdin) == NULL) {
          break;  // Handle EOF if needed
      }
      // Remove the newline character at the end of the input
      size_t len = strlen(prompt_input);
      if (len > 0 && prompt_input[len - 1] == '\n') {
          prompt_input[len - 1] = '\0';
      }

      if (strcmp(prompt_input, "") == 0) {
          continue;  // If input is empty, display the prompt again
      }
      smoldb_input_buf_read(buf, prompt_input);
      if (strcmp(prompt_input, "mogging") == 0){
        printf(YELLOW BOLD "Bro can rizz now!\n" RESET_ALL);
        exit(0);
        return 0;        
      }
    }
  }
  printf(BOLD "\nBro is NOT Jordan Barrett\n" RESET_ALL);
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
    perror(RED BOLD "Point to NULL\n" RESET_ALL);
    return SMOLDB_NULL_PTR_TO_REF_ERR;
  }
  int length = strlen(input);
  buf->buffer = realloc(buf->buffer, length + 1);
  if (buf->buffer == NULL){
    perror(RED BOLD "Error allocating memory!\n" RESET_ALL);
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
