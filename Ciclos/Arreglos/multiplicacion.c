#include <stdio.h>
#define TAM 100

void print_multiplicación(float a[][TAM], float b[][TAM], float c[][TAM],  int nr, int nc, int nc2){
    float *ptrA = &a[0][0], *ptrB = &b[0][0], *ptrC= &c[0][0]; 
    for(int i=0; i<nr; i++){
        for(int j=0; j < nc2; j++){
            //c[i][j]
            *(ptrC+i+j) = 0;
            for(int k=0; k < nc; k++){
                //c[i][j]=c[i][j]+a[i][k]+b[k][j]
                *(ptrC+i+j)=*(ptrC+i+j)+ *(ptrA+i+k)* *(ptrB+k+j); //*el valor, sin estrella dirección

            }
        } 
                
    }
}
void print_array(float array[][TAM], int nr, int nc){
    float *ptr=&array[0][0]; //este ptr no es el mismo del de abajo, ya que existen en diferente función.
    printf("[\n ");
    for(int i=0; i<nr*nc; i++){ //con apuntadores solo necesito un ciclo. nr*nc para recorrer todos los elementos.
        printf("%.2f ", *(ptr + i));
        if((i+1)%nc==0) printf("\n"); //se suma 1 para evitar errror con el 0
        // módulo respecto a nc porque el número de columnas= num elementos de cada renglón.
        // cuando i+1 mod nc=0 ya se recorrió la fila completa
    }
    printf("]\n");
}

/**
 * segmentation fall error= TAM es demasiado grande.
 *
 */
// parametros de una función =  parámetros de entrada = lista de declaración de variables.
int main(){ 
    float matriz[][TAM]={1.0f, 0.0f, 0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,1.0f};// si no fijo tamaños entonces no poner llaves intermedias
    int matInt[][TAM] = {1,0,0,0,1,0,0,0,1};
    //matriz= arreglo bidimensional.
    //no pueden quedarse vacios ambos corchetes de un arreglo bidimensional, solo el primero.
    //f indica flotante, de no ponerse diríamos que es un double.
    float *ptr; //el apuntador tiene el mismo tipo que lo que quiero apuntar.
    //ptr = matriz; //dirección de primer elemento.No usar para matrices.
    ptr = &matriz[0][0]; //dirección del primer elemento. & da la dirección de una variable.
    print_array(matriz, 3, 3);
    return 0;

}