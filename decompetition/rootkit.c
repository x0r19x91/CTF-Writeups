#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct fuck {
  struct fuck* next;
  int i;
  char *buf;
};

typedef struct fuck FUCK;
typedef struct fuck* PFUCK;

int find_rootkit(PFUCK fp) {
    // void
    if (!fp) return -1;
    do {
      if (fp->i == 0x539 && strcmp(fp->buf, "h4x0r") == 0) return 1;
      fp = fp->next;
    } while (fp);
    return 0;
}

PFUCK alloc_task(char* l, int b, PFUCK* c) {
    PFUCK ret = (PFUCK) malloc(sizeof (FUCK));
    ret->buf = (char*) malloc(strlen(l)+1);
    strcpy(ret->buf, l);
    ret->i = b;
    ret->next = c;
    return ret;
}

int main(int argc, char** argv) {
    PFUCK fp = 0;
    int n;
    char buf[16+0x30];
    while (scanf("%s %d", buf, &n) == 2)
    {
      fp = alloc_task(buf, n, fp);
    }
    int x = find_rootkit(fp);
    printf("find_rootkit() = %d\n", x);
    return 0;
}
