#include <stdlib.h>
#include <string.h>

#include "cli-handler.h"
#include "retval.h"

int main(int argc, char *argv[]) {
  InputBuf *buf = NULL;
  int retval = smoldb_new_input_buf(&buf);
  prompt_prototype(buf, argc, argv);
  if (retval == SMOLDB_ALLOC_ERR) {
    smoldb_free_input_buf(&buf);
    return EXIT_FAILURE;
  }
  smoldb_free_input_buf(&buf);
  return EXIT_SUCCESS;
}
