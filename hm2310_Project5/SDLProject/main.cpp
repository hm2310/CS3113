#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_mixer.h>
#include "class.h"
#include <SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <vector>
#include <cmath>





//const int window_height =   600;
//const int window_width = 1000;



void event_loop() {
    while (1) {
        auto start = SDL_GetTicks();

        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                break;
            }
            else if(event.type == SDLK_RETURN)
            {
                menu_flag = false;
            }
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                case UP_ARROW:
                    player->jump();
                    break;
                case DOWN_ARROW:

                    break;
                case LEFT_ARROW:
                    player->status.x -= 10;
                    break;
                case RIGHT_ARROW:
                    player->status.x += 10;
                    break;
                case SPACE:
                    break;
                case ENTER:
                    menu_flag = false;
                    break;
                default:
                    SDL_Log("%d", event.key.keysym.sym);
                }
            }
        };


        draw();

        auto end = SDL_GetTicks();
        if (end - start < 1000 / FPS) {
            SDL_Delay(1000 / FPS - (end - start));
        }
    }
}

int main(int argc, char* argv[]) {

    SDL_Init(SDL_INIT_EVERYTHING);

    displayWindow = SDL_CreateWindow("Avoid monsters",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        window_width,
        window_height,
        SDL_WINDOW_SHOWN
    );

    renderer = SDL_CreateRenderer(displayWindow, -1, SDL_RENDERER_ACCELERATED);

    play_music();

   
    event_loop();

    SDL_DestroyWindow(displayWindow);
    SDL_Quit();
    return 0;
}
