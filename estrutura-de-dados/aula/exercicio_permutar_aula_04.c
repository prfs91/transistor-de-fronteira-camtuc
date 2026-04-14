#include <stdio.h>

permutar (int *x, int *y){
    int aux = *x;
    *x = *y;
    *y = aux;
}

int main(){
    int a = 5;
    int b = 10;

    permutar(&a,&b);

    printf("%d %d\n", a, b);
}
