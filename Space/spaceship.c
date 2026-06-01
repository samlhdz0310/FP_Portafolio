#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define WIDTH 40
#define HEIGHT 25
#define MAX_BALAS 5
#define MAX_ASTEROIDES 5
#define MAX_ESTRELLAS 3 

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"
#define RESET "\033[0m"

#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
#else
    #include <termios.h>
    #include <unistd.h>
    #include <fcntl.h>
#endif

int shipX, shipY; 
int puntaje = 0;
bool juego_terminado = false;
bool juego_pausado = false; 

// Variables para los proyectiles
int balasX[MAX_BALAS];
int balasY[MAX_BALAS];
bool balaActiva[MAX_BALAS] = {false};

// Variables para los asteroides
int astX[MAX_ASTEROIDES];
int astY[MAX_ASTEROIDES];
int astDirX[MAX_ASTEROIDES]; 

// Variables para las estrellas
int estrellasX[MAX_ESTRELLAS];
int estrellasY[MAX_ESTRELLAS];
bool estrellaActiva[MAX_ESTRELLAS] = {false};
int contador_spawn_asteroides = 0; 

// Función modificada para hacer la nave más compacta
void getShipParts(int partsX[3], int partsY[3]) {
    partsX[0] = shipX;     partsY[0] = shipY - 1; // Punta central
    partsX[1] = shipX - 1; partsY[1] = shipY;     // Ala izquierda (más cerca del centro)
    partsX[2] = shipX + 1; partsY[2] = shipY;     // Ala derecha (más cerca del centro)
}

int incrementarPuntaje(){
    static int puntos = 0;
    puntos++;
    return puntos;
}

void moveShip(int *x, int *y, char dir){
    switch (dir) {
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
    return 0; 
}
#else
struct termios oldt;
void enableRawMode(){
    struct termios newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);    
    int flags = fcntl(STDIN_FILENO, F_GETFL, O_NONBLOCK); 
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK); 
}

void disableRawMode(){
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

char readInput(){    
    int ch = getchar();    
    if(ch != EOF) return ch;
    return 0;
}
#endif

void generarEstrella() {
    for(int s = 0; s < MAX_ESTRELLAS; s++) {
        if(!estrellaActiva[s]) {
            estrellasX[s] = (rand() % (WIDTH - 2)) + 1;
            estrellasY[s] = 1;
            estrellaActiva[s] = true;
            break;
        }
    }
}

void generarAsteroide(int i){
    astX[i] = (rand() % (WIDTH - 2)) + 1;
    astY[i] = 1; 
    astDirX[i] = (rand() % 3) - 1; 

    contador_spawn_asteroides++;
    if(contador_spawn_asteroides >= 4) {
        generarEstrella();
        contador_spawn_asteroides = 0; 
    }
}

void disparar() {
    for(int i = 0; i < MAX_BALAS; i++) {
        if(!balaActiva[i]) {
            balaActiva[i] = true;
            balasX[i] = shipX;
            balasY[i] = shipY - 2; 
            break; 
        }
    }
}

void setup(){
    shipX = WIDTH / 2;
    shipY = HEIGHT - 2;  
    
    for(int i = 0; i < MAX_ASTEROIDES; i++) {
        generarAsteroide(i);
        astY[i] = -(rand() % 10); 
    }
}

void draw(){
    clearScreen();
    
    if(juego_pausado) {
        printf(YELLOW"========== JUEGO PAUSADO ==========\n"RESET);
    } else {
        printf("                                   \n"); 
    }

    int partsX[3], partsY[3];
    getShipParts(partsX, partsY);

    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            if(j == 0 || i == 0 || i == HEIGHT - 1 || j == WIDTH - 1){
                 printf(YELLOW"▒");
                 continue;
            }
            
            bool isShip = false;
            for(int k = 0; k < 3; k++) {
                if(j == partsX[k] && i == partsY[k]) {
                    isShip = true;
                    break;
                }
            }
            if(isShip){
                printf(GREEN"#");
                continue;
            }

            bool esBala = false;
            for(int k = 0; k < MAX_BALAS; k++) {
                if(balaActiva[k] && balasX[k] == j && balasY[k] == i) {
                    esBala = true;
                    break;
                }
            }
            if(esBala) {
                printf(CYAN"|"RESET);
                continue;
            }

            bool esEstrella = false;
            for(int s = 0; s < MAX_ESTRELLAS; s++) {
                if(estrellaActiva[s] && estrellasX[s] == j && estrellasY[s] == i) {
                    esEstrella = true;
                    break;
                }
            }
            if(esEstrella) {
                printf(YELLOW"*"RESET);
                continue;
            }

            bool esAsteroide = false;
            for(int k = 0; k < MAX_ASTEROIDES; k++) {
                if(astX[k] == j && astY[k] == i && astY[k] > 0) {
                    esAsteroide = true;
                    break;
                }
            }
            if(esAsteroide){
                printf(RED"O"RESET); 
                continue;
            } 
            
            printf(RESET" ");
        }
        printf(RESET"\n");
    }
    printf(RESET"Puntos: %d | Controles: WASD mover | ESPACIO disparar | P Pausa\n", puntaje);
}

void actualizarAsteroides() {
    for(int i = 0; i < MAX_ASTEROIDES; i++) {
        astY[i]++; 
        astX[i] += astDirX[i]; 

        if(astX[i] <= 1) {
            astX[i] = 1;
            astDirX[i] = 1; 
        } 
        else if (astX[i] >= WIDTH - 2) {
            astX[i] = WIDTH - 2;
            astDirX[i] = -1; 
        }

        if(astY[i] >= HEIGHT - 1) {
            generarAsteroide(i);
        }
    }
}

void actualizarEstrellas() {
    for(int s = 0; s < MAX_ESTRELLAS; s++) {
        if(estrellaActiva[s]) {
            estrellasY[s]++; 
            
            if(estrellasY[s] >= HEIGHT - 1) {
                estrellaActiva[s] = false;
            }
        }
    }
}

void actualizarBalas() {
    for(int i = 0; i < MAX_BALAS; i++) {
        if(balaActiva[i]) {
            balasY[i]--; 

            if(balasY[i] <= 0) {
                balaActiva[i] = false;
            } else {
                bool impacto = false;

                // Colisión con Estrellas
                for(int s = 0; s < MAX_ESTRELLAS; s++) {
                    if(estrellaActiva[s] && balasX[i] == estrellasX[s] && (balasY[i] == estrellasY[s] || balasY[i] == estrellasY[s] + 1)) {
                        balaActiva[i] = false;
                        estrellaActiva[s] = false; 
                        puntaje = incrementarPuntaje(); 
                        impacto = true;
                        break;
                    }
                }

                if(impacto) continue; 

                // Colisión con Asteroides
                for(int j = 0; j < MAX_ASTEROIDES; j++) {
                    if(balasX[i] == astX[j] && (balasY[i] == astY[j] || balasY[i] == astY[j] + 1)) {
                        balaActiva[i] = false;  
                        generarAsteroide(j); 
                        break;
                    }
                }
            }
        }
    }
}

void logic(int prevX, int prevY){
    bool colisionMuro = false;
    int partsX[3], partsY[3];
    getShipParts(partsX, partsY);

    for(int k = 0; k < 3; k++) {
        if(partsX[k] <= 0 || partsX[k] >= WIDTH - 1 || partsY[k] <= 0 || partsY[k] >= HEIGHT - 1){
            colisionMuro = true;
            break;
        }
    }

    if(colisionMuro){
        shipX = prevX;
        shipY = prevY;
        getShipParts(partsX, partsY); 
    }

    // Colisión con Estrellas (Nave recolecta)
    for(int k = 0; k < 3; k++) {
        for(int s = 0; s < MAX_ESTRELLAS; s++) {
            if(estrellaActiva[s] && partsX[k] == estrellasX[s] && partsY[k] == estrellasY[s]) {
                estrellaActiva[s] = false;
                puntaje = incrementarPuntaje(); 
            }
        }
    }

    // Colisión con Asteroides (Destruyen la nave)
    bool naveDestruida = false;
    for(int k = 0; k < 3; k++) {
        for(int a = 0; a < MAX_ASTEROIDES; a++) {
            if(partsX[k] == astX[a] && partsY[k] == astY[a]) {
                naveDestruida = true;
                break;
            }
        }
    }

    if(naveDestruida) {
        printf(RED"¡GAME OVER! Tu nave fue destruida por un asteroide.\n"RESET);
        juego_terminado = true;
    }
}

int main(){
    char nuevaDireccion;
    int frame_counter = 0;
    setup();
    
    #ifndef _WIN32
    enableRawMode();
    #endif

    while(!juego_terminado){
        nuevaDireccion = readInput(); 
        
        if (nuevaDireccion == 'p' || nuevaDireccion == 'P') {
            juego_pausado = !juego_pausado; 
        }
        
        if (!juego_pausado) {
            frame_counter++; 

            if (nuevaDireccion == ' ') {
                disparar();
            } 
            else if (nuevaDireccion == 'w' || nuevaDireccion == 'W' || 
                     nuevaDireccion == 's' || nuevaDireccion == 'S' || 
                     nuevaDireccion == 'a' || nuevaDireccion == 'A' || 
                     nuevaDireccion == 'd' || nuevaDireccion == 'D') {
                
                int prevX = shipX;
                int prevY = shipY;

                moveShip(&shipX, &shipY, nuevaDireccion);
                logic(prevX, prevY);
            }
            
            actualizarBalas();

            if(frame_counter % 8 == 0) {
                actualizarAsteroides();
                actualizarEstrellas(); 
                logic(shipX, shipY);
            }
        }
        
        draw();
        
        #ifdef _WIN32
        Sleep(50);
        #else
        usleep(50000); 
        #endif
    }
    
    #ifndef _WIN32
    disableRawMode();
    #endif
    return 0;
}