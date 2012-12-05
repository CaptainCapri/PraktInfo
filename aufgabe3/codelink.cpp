#include <cstdio>
#include <cstdlib>

extern "C" unsigned calc_expr(unsigned x);

int main() {
  printf("architecture %s\n", sizeof(void *) == 8 ? "64bit" : "32bit");
  printf("expr(compiled) = %d\n", calc_expr(23));

  return EXIT_SUCCESS;
}
