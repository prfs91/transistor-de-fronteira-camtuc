#include <stdio.h>

int main() {
    int a=5;
    int b=7;
    int *p=&a;
    p=&b;
    printf("%d %d %d\n", a,b,*p);
    b+=*p;
    printf("%d %d %d\n", a,b,*p);
    a=*p+2;
    printf("%d %d %d\n", a,b,*p);
    *p-=5;
    printf("%d %d %d\n", a,b,*p);
}