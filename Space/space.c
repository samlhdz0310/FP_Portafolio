#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define WIDTH 30
#define HEIGHT 15

#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
#else
    #include <termios.h>
    #include <unistd.h>
    #include <fcntl.h>
#endif

int rocketX, rocketY; // posición de la primera parte de la vibora
int tail1X, tail1Y;
int tail2X, tail2Y;
char direction ='d';
int score=0;
bool game_over = false;

void moveRocket(int *x, int *y, char dir){
    switch (dir)
    {
    case 'w': case 'W': (*y)--; break;
    case 's': case 'S': (*y)++; break;
    case 'a': case 'A': (*x)--; break;
    case 'd': case 'D': (*x)++; break;
    }
}

void clearScreen(){
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

#ifdef _WIN32
char readInput(){
    if(_kbhit()) return _getch();
    return direction;
}
#else
struct termios oldt;
void enableRawMode(){
    struct termios  newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON| ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);    
    int flags = fcntl(STDIN_FILENO, F_GETFL, O_NONBLOCK); 
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK); 

}
void disableRawMode(){
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}
char readInput(){    
    int ch;    
    ch = getchar();    
    if(ch!= EOF) return ch;
    return 0;
}
#endif

/**
 * Función que sirve  para iniciar el juego
 */
void setup(){
    rocketX=WIDTH/2;
    rocketY=HEIGHT-3;
    tail1X=(WIDTH/2)-3;
    tail1Y=HEIGHT-1;
}

void draw(){
    bool printed;
    clearScreen();
    for(int i=0; i<HEIGHT;i++){
        for(int j=0; j< WIDTH; j++){
            printed= false;
            if(j==0 || i ==0 || i==HEIGHT-1 || j == WIDTH-1){
                 printf("▒");
                 continue;
            }
            if(rocketX==j && rocketY==i){
                printf("#");
                continue;
            } 

            if(printed) continue;

            printf(" ");
        }
        printf("\n");
    }
}

int main(){
    char newDirection;
    setup();
    #ifndef _WIN32
    enableRawMode();
    #endif
    while(!game_over){
        draw();
        newDirection = readInput();
        if((newDirection=='W' || newDirection=='w') && direction != 's' && direction != 'S')        
            direction = newDirection;
        else if((newDirection=='S' || newDirection=='s') && direction != 'w' && direction != 'W')
            direction = newDirection;
        else if((newDirection=='A' || newDirection=='a') && direction != 'd' && direction != 'D')
            direction = newDirection;
        else if((newDirection=='D' || newDirection=='d') && direction != 'a' && direction != 'A')
            direction = newDirection;
        
        moveRocket(&rocketX, &rocketY, direction);
        #ifdef _WIN32
        Sleep(150);
        #else
        usleep(300000);
        #endif
    }
    #ifndef _WIN32
    disableRawMode();
    #endif
    return 0;
}