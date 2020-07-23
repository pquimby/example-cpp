#include <stdlib.h>
#include <stdio.h>
#include "mySharedLib.h"

int main(int argc, char* argv[]) {
  int c = special_function(3,4);
  printf("Success is a seven: %d!\n", c);
  return 0;
}
