#include "cli-handler.h"
#include <stdlib.h>

int main(int argc, char *argv[]) {
  InputBuf *buf;
  int retval = smoldb_new_input_buf(&buf);

  smoldb_free_input_buf(&buf);
  return EXIT_SUCCESS;
}