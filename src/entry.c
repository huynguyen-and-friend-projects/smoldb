#include <stdlib.h>

#include "cli-handler.h"

int main(/*int argc, char *argv[]*/ void) {
  InputBuf buf = {0};
  smoldb_default_input_buf(&buf);
  return EXIT_SUCCESS;
}
