#include <sys/mman.h>
#include <string.h>

#define ADDR(A) ((char*)(A))

int takeaway(int);
int check();
int deep(int);
int giveme();
int end();

int bi0s;
char shell2[] = "\xb8\x08\x00\x00\x00\xbb\x04\x00\x00\x00\xb9\x02\x00\x00\x00\xc3";
char shell1[] = "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\xe8\x02\x00\x00\x00\x90\x90\x58\xc6\x40\xfb\xc3\x90\x90\x90\x90\x90\xeb\xed";

int main()
{
    bi0s = 1337;
    check();
    takeaway(0);
}

int takeaway(int n)
{
    if (n == 0)
    {
        bi0s = 0x1337;
        munmap(ADDR(0x13337000), 0x1000);
        giveme(1);
    }
    else
    {
        munmap(ADDR(0x51dd0000), 0x1000);
        end();
    }
}

int giveme(int n)
{
    if (n == 1)
    {
        mmap(ADDR(0x51dd0000), 0x1000, PROT_EXEC|PROT_READ|PROT_WRITE, MAP_FIXED|MAP_SHARED|MAP_ANONYMOUS, -1, 0);
        memcpy(ADDR(0x51dd0000), shell2, sizeof shell2);
    }
    else
    {
        mmap(ADDR(0x13337000), 0x1000, PROT_EXEC|PROT_READ|PROT_WRITE, MAP_FIXED|MAP_SHARED|MAP_ANONYMOUS, -1, 0);
        memcpy(ADDR(0x13337000), shell1, sizeof shell1);
    }
    deep(n);
}

int check()
{
    giveme(0);
}

int deep(int n)
{
    if (n == 0)
    {
        ((void (*)())0x13337000)();
    }
    else
    {
        ((void (*)())0x51dd0000)();
        takeaway(1);
    }
}

int end()
{

}