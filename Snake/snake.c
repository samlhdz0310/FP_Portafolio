#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define WIDTH 30
#define HEIGHT 15
//Definir el tamaño del tablero

int x, y; //posición de la primera parte de la serpiente
int fruitX, fruitY;
int score;
char input;
/*Variables afuera de una función son variables goblales y son validas para todo el programa, cualquier cambio de estas variables en cualquier parte del código afecta en todo el código*/

/*Funcíon que sirve para iniciar el juego*/
void setup(){
    x=WIDTH/2;
    y=HEIGHT/2;
    //Fijando la posición inicial de la serpiente al centro del tablero

    fruitX = rand()%WIDTH;
    fruitY = rand()%HEIGHT;
    /* Posición aleatoria de la fruta, se usa mod para restringir que no se salga del tablero
    rand genera una número aleatorio */

    score = 0; 
}

void draw(){
    system ("clear");
    //system sirve para ejecutar comandos de la terminal
    for(int i=0; i < HEIGHT; i++){
        for (int j = 0; j <WIDTH;j++){
            if (j==0 || i==0 || j==WIDTH-1 || i==HEIGHT-1){ // los simbolos || se llaman pide
                printf("#");
                continue;
            }
            if (x==j && y==i){
                printf("s");
                continue;
            }
            if (fruitX==j && fruitY==i){
                printf("f");
                continue;

            printf(" ");
        
            }
        }

        printf("\n");
    }
    printf("Score: %d\n", score);
    printf("presiona W o S o A o D\n");
}

void input_func(){
    input=getchar();
    getchar();
}

int main(){
    setup();
    while(true){
        draw();
        input_func();
    }
    return 0;
}