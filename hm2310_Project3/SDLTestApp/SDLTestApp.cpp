#include "class.h"


static SDL_Surface* plane;
static SDL_Surface* wall;
static SDL_Surface* land;

static SDL_Window* win;
static SDL_Renderer* renderer;

//Map* map;
Map* map_ptr;
Plane* plane_ptr;

void eventLoop();
void draw();
int isHit();

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Can not init video, %s",SDL_GetError());
        return 1;
    }

    SDL_Window* win = SDL_CreateWindow("Lunar lunder",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,WIDTH,HEIGHT,SDL_WINDOW_SHOWN);
    
    plane = IMG_Load("../assert/plane.png");
    wall = IMG_Load("../assert/wall.png");
    land = IMG_Load("../assert/land.png");

    Map map;
    map_ptr = &map;

    Plane planeobj;
    plane_ptr = &planeobj;

    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    eventLoop();


    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(renderer);
    return 0;

}

void eventLoop()
{
    while (true)
    {
        auto begin = SDL_GetTicks();

        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                break;
            }
            else if(event.type == SDL_KEYDOWN){
                if (event.key.keysym.sym == 1073741904) {
                    plane_ptr->ax -= 1;
                }
                else if (event.key.keysym.sym == 1073741903) 
                {
                    plane_ptr->ax += 1;
                }
                
            }
        }
        draw();

        plane_ptr->clacNextPos();
        // DO NOT MODIFY FOLLOW
        auto end = SDL_GetTicks();
        auto cost = end - begin;
        auto frame = 1000 / FPS;
        if (frame > cost) {
            SDL_Delay(frame - cost);
        }
    }
}

void draw() {
    SDL_Rect dst = { 0,0,STDA,STDA };
    if (isHit() == 1) { // hit wall
        TTF_Init();
        SDL_Log("Mission Failed");
        auto font = TTF_OpenFont("../assert/font.ttf", 50);
        if (font == NULL) {
            SDL_Log("Can not open font, %s", TTF_GetError());
        }
        SDL_Color textColor = { 0xff,0xff,0xff,0xff };
        auto text = TTF_RenderUTF8_Blended(font, "Mission Failed!!", textColor);
        auto text_texture = SDL_CreateTextureFromSurface(renderer, text);
        dst = { (WIDTH - 300)/ 2 ,(HEIGHT - 100) / 2 ,300,60 };
        SDL_RenderCopy(renderer, text_texture, NULL, &dst);
        SDL_RenderPresent(renderer);
        SDL_Delay(5000);
    }
    else if(isHit() == -1) {
        TTF_Init();
        SDL_Log("Mission Successful");
        auto font = TTF_OpenFont("../assert/font.ttf", 50);
        if (font == NULL) {
            SDL_Log("Can not open font, %s", TTF_GetError());
        }
        SDL_Color textColor = { 0xff,0xff,0xff,0xff };
        auto text = TTF_RenderUTF8_Blended(font, "Mission Successful!!", textColor);
        auto text_texture = SDL_CreateTextureFromSurface(renderer, text);
        dst = { (WIDTH - 400) / 2 ,(HEIGHT - 100) / 2 ,400,60 };
        SDL_RenderCopy(renderer, text_texture, NULL, &dst);
        SDL_RenderPresent(renderer);
        SDL_Delay(5000);
    }
    SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
    SDL_RenderClear(renderer);

    
    

    auto wall_texture = SDL_CreateTextureFromSurface(renderer, wall);
    auto land_texture = SDL_CreateTextureFromSurface(renderer, land);
    for (auto i = 0; i < map_ptr->_wall.size(); i++) {
        dst = { map_ptr->_wall[i].x*STDA,map_ptr->_wall[i].y*STDA,STDA,STDA};
        SDL_RenderCopy(renderer, wall_texture, NULL, &dst);
    }

    for (auto i = 0; i < map_ptr->_land.size(); i++) {
        dst = { map_ptr->_land[i].x*STDA,map_ptr->_land[i].y*STDA,STDA,STDA};
        SDL_RenderCopy(renderer, land_texture, NULL, &dst);
    }

    dst = { (int)plane_ptr->x,(int)plane_ptr->y,STDPLANEW,STDPLANEH };
    auto plane_texture = SDL_CreateTextureFromSurface(renderer, plane);
    SDL_RenderCopy(renderer, plane_texture, NULL, &dst);

    
    
    SDL_RenderPresent(renderer);
    
}

int isHit() // 0: nothing; 1:hit; -1:landed
{
    for (auto i = 0; i < map_ptr->_wall.size(); i++) {
        if (!((map_ptr->_wall[i].x + 1) * STDA <= plane_ptr->x ||
            (map_ptr->_wall[i].x - 1) * STDA >= plane_ptr->x ||
            (map_ptr->_wall[i].y * STDA + STDPLANEH) <= plane_ptr->y ||
            (map_ptr->_wall[i].y * STDA - STDPLANEH)>= plane_ptr->y
            ))
            return 1;
    }

    for (auto i = 0; i < map_ptr->_land.size(); i++) {
        if (!((map_ptr->_land[i].x + 1) * STDA <= plane_ptr->x ||
            (map_ptr->_land[i].x - 1) * STDA >= plane_ptr->x ||
            (map_ptr->_land[i].y * STDA + STDPLANEH) <= plane_ptr->y ||
            (map_ptr->_land[i].y * STDA - STDPLANEH) >= plane_ptr->y
            ))
            return -1;
    }
    return 0;
}
