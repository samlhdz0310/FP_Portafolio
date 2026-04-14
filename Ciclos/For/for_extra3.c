//Imprime piramide vacia inversa
#include <stdio.h>

void main(){
    int n, i = 0, j = 0, k = 0;
    printf("Ingresa un número\n");
    scanf("%d", &n);

    for (i = 1; i <= n; i++){

        for (j = 1; j <= i; j++)
            printf("%d ", j);

        for (k=1; k<=((n-i)*2); k++)
            printf(" ");

        for (j = i; j >= 1; j--)
            printf("%d ", j);
        
        printf("\n");    
    }
}