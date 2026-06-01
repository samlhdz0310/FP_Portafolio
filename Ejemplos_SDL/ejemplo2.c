//Programa que crea una ventana y permanece abierta hasta que se presione una tecla o con el mouse
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>


   int main(int argc, char **argv){
        if(SDL_Init(SDL_INIT_VIDEO)==0){
            printf("Error: %s\n", SDL_GetError());
            return 1;
        }

        bool running = true;
        SDL_Event event;

        //Para crear ventana
        SDL_Window *window = SDL_CreateWindow(
            "HOLA MUNDO", //Titulo de la ventana
            SDL_WINDOWPOS_CENTERED, //Posición de la ventana en x
            SDL_WINDOWPOS_CENTERED, //Posición de la ventana en y
            800, //Ancho de la ventana
            600, //Alto de la ventana
            0 //Siempre va 0
        );

        //Para verificar que se pueda crear la ventana
        if(window == NULL){
            printf("Error: %s\n", SDL_GetError());
            SDL_Quit();
            return 1;
        }

        //Para mandar adelante la ventana
        SDL_RaiseWindow(window);

        //Detecta un evento(cerrar la ventana)
        while(running){//Poll_Event es el que detecta si hubo una acción
            while(SDL_PollEvent(&event)){//El & es porque necesita la dirección de event
                if(event.type == SDL_QUIT){
                    running = false;
                }else
                    if(event.type == SDL_KEYDOWN){
                        if(event.key.keysym.sym == SDLK_x)
                            running = false;
                    }
            }
        }

        //Cuanto tiempo va a estar abierta la ventana
        //SDL_Delay(3000);

        //Para cerar la ventana
        SDL_DestroyWindow(window);

        //Destruye todo lo que crea SDL_Init
        SDL_Quit();
   }