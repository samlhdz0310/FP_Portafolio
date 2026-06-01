   #include <stdio.h>
   #include <SDL2/SDL.h>

   int main(int argc, char **argv){
        if(SDL_Init(SDL_INIT_VIDEO)==0){
            printf("Error: %s\n", SDL_GetError());
            return 1;
        }

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

        //Cuanto tiempo va a estar abierta la ventana
        SDL_Delay(3000);

        //Para cerar la ventana
        SDL_DestroyWindow(window);

        //Destruye todo lo que crea SDL_Init
        SDL_Quit();
   }