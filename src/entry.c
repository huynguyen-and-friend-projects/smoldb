#include <stdio.h>
#include <stdlib.h>

#include "cli-handler.h"

int main(/*int argc, char *argv[]*/ void) {
  InputBuf buf = {0};
  smoldb_default_input_buf(&buf);
  printf("%zu\n", buf.buf_len);
  return EXIT_SUCCESS;
}
