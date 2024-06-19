#include <stdlib.h>
#include <string.h>

#include "cli-handler.h"
#include "retval.h"

int main(int argc, char *argv[]) {
  prompt_prototype(argc, argv);
  InputBuf *buf;
  int retval = smoldb_new_input_buf(&buf);
  if (retval == SMOLDB_ALLOC_ERR) {
    smoldb_free_input_buf(&buf);
    return EXIT_FAILURE;
  }
  smoldb_free_input_buf(&buf);
  return EXIT_SUCCESS;
}
