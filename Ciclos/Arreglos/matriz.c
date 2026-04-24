#include <stdio.h>
#define TAM 1000 //Para definir constantes

//Función para leer una matriz de enteros
void leer(int mat[][TAM], int m, int n){
    for(int i = 0; i < m; i++){//Ciclo externo sirve para cambiar de renglón
        for(int j = 0; j < n; j++){//Ciclo interno sirve para cambiar de columna en el renglón
            printf("Ingresa el valor de la matriz [%d, %d]\n", i, j);
            scanf("%d", &mat[i][j]);
        }
    }
}
/**
 * En la variable que representa el arreglo primera puede estar vacia pero la segunda tiene que contener un tamaño seguida de los renglones y columnas
 * @param mat, representa el arreglo donde guardan los valores leidos
 * @param m, el número de renglones de la matriz
 * @param n, el número de columnas de la matriz
 * */

int main(){
    //Tipo identificador [n1][n2] ... [nk]
    /*int cubo[3][3][3];
    float matriz[2][2];*/
    int matriz[TAM][TAM]; //Una matriz de dos dimensiones se asocia a dos ciclos for
    int m, n;
    
    /*printf("Ingresa el número de renglones: ");
    scanf("%d", &m);
    printf("Ingresa el número de comlumnas: ");
    scanf("%d", &n);*/

    printf("Ingresa el número de renglones y columnas: \n");
    scanf("%d %d", &m, &n);

    printf("La dirección de la matriz es: %p\n", matriz);
    printf("La dirección del primer elemento de la matriz es: %p\n", &matriz[0][0]);

    for(int i = 0; i < m; i++){//Ciclo externo sirve para cambiar de renglón
        for(int j = 0; j < n; j++){//Ciclo interno sirve para cambiar de columna en el renglón
            printf("Ingresa el valor de la matriz [%d, %d]\n", i, j);
            scanf("%d", &matriz[i][j]);
        }
    }

    printf("[ \n");
    for(int i = 0; i < m; i++){
        printf("[ ");
        for(int j = 0; j < n; j++){
            printf("%d ", matriz[i][j]);

        }
        printf("]\n");
    }
    printf("]\n");
    return 0;

}