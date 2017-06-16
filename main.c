/*
    DEVOIR DE C
    RENDU MAXIME DORFFER, F2A, LUDUS ACADEMIE
    TP : CASSE BRIQUE EN C, AVEC LA SDL
    14/06/2017

*/

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 780


// __________________________________________________________________DECLARATIONS

typedef struct game{


     SDL_Window *g_pWindow;
     SDL_Renderer *g_pRenderer;
     SDL_Texture *g_texture;
     SDL_Surface *g_surface;


}game;

typedef struct gameState{

    int g_bRunning;
    int left;
    int right;


}gameState;


typedef struct coordonnees{

    double x;
    double y;



}coordonnees;


typedef struct ball{

    double x;
    double y;
    int direction;



}ball;

typedef enum destroyed{
True,False



}destroyed;


typedef struct SDL_Rect2{

    SDL_Rect brique;
    destroyed destroyed;


}SDL_Rect2;


int init(char *title, int xpos,int ypos,int height, int width,int flags,game *myGame);
void handleEvents(gameState *state, SDL_Rect *paddle);
void delay(unsigned int frameLimit);
void destroyTexture(game *myGame);
void destroy(game *myGame);


// __________________________________________________________________PROGRAMME PRINCIPAL

int main(int argc, char *argv[])
{

     game myGame;
     gameState state;
     double *paddlex=(15);
     double *paddley=(SCREEN_HEIGHT-10);
     SDL_Rect paddle;
     ball ball;
     int i;
     ball.x=SCREEN_WIDTH-50;
     ball.y=SCREEN_HEIGHT/2;
     ball.direction=2;
     paddle.x=15;
     paddle.y=(SCREEN_HEIGHT-10);
     paddle.w=80;
     SDL_Rect2 briques[32];

     initbriques(briques);



    //Pour les 60 fps
    unsigned int frameLimit = SDL_GetTicks() + 16;


    if(init("Casse-Briques",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN,&myGame)){

                state.g_bRunning=1;


    }else{

            return 1;//something's wrong

    }

    state.right=1;
    state.left=0;

    while(state.g_bRunning){

           handleEvents(&state,&paddle);

        // Gestion des 60 fps (1000ms/60 = 16.6 -> 16)
            delay(frameLimit);
            frameLimit = SDL_GetTicks() + 16;

    }

        destroy(&myGame);

        // unload the dynamically loaded image libraries
        IMG_Quit();
        //quit sdl2
        SDL_Quit();


  return 0;
}


int init(char *title, int xpos,int ypos,int height, int width,int flags,game *myGame){


    //initialize SDL

    if(SDL_Init(SDL_INIT_EVERYTHING)>=0)
    {
            //if succeeded create our window
            myGame->g_pWindow=SDL_CreateWindow(title,xpos,ypos,height,width,flags);
            //if succeeded create window, create our render
            if(myGame->g_pWindow!=NULL){
                myGame->g_pRenderer=SDL_CreateRenderer(myGame->g_pWindow,-1,SDL_RENDERER_ACCELERATED);
                SDL_SetRenderDrawColor(myGame->g_pRenderer, 0, 0, 0, 255);
                SDL_RenderClear(myGame->g_pRenderer);

                int flags=IMG_INIT_JPG|IMG_INIT_PNG;
                int initted=IMG_Init(flags);
                if((initted&flags) != flags) {
                        printf("IMG_Init: Failed to init required jpg and png support!\n");
                        printf("IMG_Init: %s\n", IMG_GetError());
                        // handle error
                }

            }


    }else{


        return 0;
    }


    return 1;


}

// __________________________________________________________________FONCTIONS ET PROCEDURES


void handleEvents(gameState *state, SDL_Rect *paddle){


    SDL_Event event;

    if(SDL_PollEvent(&event)){
        switch(event.type){
        case SDL_QUIT:
              state->g_bRunning=0;break;
        case SDL_KEYDOWN:
                        switch (event.key.keysym.sym)
                            {
                                case SDLK_LEFT:state->left=1;state->right=0;paddle->x=paddle->x-20;
                                if (paddle->x<-10){
                                    paddle->x=paddle->x+20;
                                }  break;
                                case SDLK_RIGHT: state->right=1;state->left=0;paddle->x=paddle->x+20;
                                 if (paddle->x>(SCREEN_WIDTH-paddle->w)){
                                    paddle->x=paddle->x-20;
                                }
                                  break;
                                case SDLK_UP:    ; break;
                                case SDLK_DOWN:  ; break;
                                case SDLK_d:  break;
                                case SDLK_q:  break;
                            }
                            break;

        case SDL_KEYUP:;break;

        default:break;

        }
    }


}


void delay(unsigned int frameLimit){
    // Gestion des 60 fps (images/seconde)
    unsigned int ticks = SDL_GetTicks();

    if (frameLimit < ticks)
    {
        return;
    }

    if (frameLimit > ticks + 16)
    {
        SDL_Delay(16);
    }

    else
    {
        SDL_Delay(frameLimit - ticks);
    }
}


void destroy(game *myGame){

    //Destroy render
    if(myGame->g_pRenderer!=NULL)
        SDL_DestroyRenderer(myGame->g_pRenderer);


    //Destroy window
    if(myGame->g_pWindow!=NULL)
        SDL_DestroyWindow(myGame->g_pWindow);

}


void destroyTexture(game *myGame){

    //Destroy texture
    if(myGame->g_texture!=NULL)
            SDL_DestroyTexture(myGame->g_texture);


}
