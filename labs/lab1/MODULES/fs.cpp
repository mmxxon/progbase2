#include "fs.h"

void check_args(int arg, int num) {
  if (arg != num) {
    perror("\033[;;41mWRONG COUNT OF ARGUMENTS. EXITING\033[0m\n");
    exit(EXIT_FAILURE);
  }
}
void check_open(FILE* file) {
  if (!file) {
    perror("\033[;;41mCAN'T OPEN FILE. EXITING\033[0m\n");
    exit(EXIT_FAILURE);
  }
}
void check_close(FILE* file) {
  if (fclose(file) == EOF) {
    perror("\033[;;41mCAN'T CLOSE FILE. EXITING\033[0m\n");
    exit(EXIT_FAILURE);
  }
}
