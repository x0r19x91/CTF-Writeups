#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void win() {
  printf("How did you get here??\n");
  exit(42);
}

void sum(int argc, char** argv)
{
  unsigned char a = atoi(argv[1]);
  char fucker[0xf7];
  printf("SIZE: %d\n", a);
  if (a > 0xf7) {
    puts("Too long!");
  } else {
    memset(fucker, 0, 0xf7);
    memcpy(fucker, argv[2], atoi(argv[1]));
    printf("Got: %s\n", fucker);
  }
}

int main(int argc, char** argv)
{
  if (argc <=2 ) return 0;
  sum(argc, argv);
  return 0;
}
