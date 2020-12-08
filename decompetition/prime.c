#include <stdio.h>
#include <stdlib.h>

int is_prime(int n) {
  // TODO...
  if (n <= 1) return 0;
  if (n == 2 || n == 3) return 1;
  if (n%2 == 0 || n%3 == 0) return 0;
  int i = 5;
  while (i*i < n)
  {
    if (n%i == 0 || n%(i+2) == 0) return 0;
    i += 6;
  }
  return 1;
}

int main(int argc, char** argv) {
  // IS PRIME?
  if (argc != 2) {
    fprintf(stderr, "USAGE: %s <num>\n", argv[0]);
    exit(1);
  }
  int n = atoi(argv[1]);
  printf("is_prime(%d) = %d\n", n, is_prime(n));
}
