#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL2/SDL.h>
#include "class.h"
#include <SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <vector>
#include <cmath>
#define SPEED_B 4
enum {
    LEFT_ARROW = 1073741904,
    RIGHT_ARROW = 1073741903,
    UP_ARROW = 1073741905,
    DOWN_ARROW = 1073741906,
    SPACE = 32
};

SDL_Window* displayWindow;



std::vector<bullet> *myBullet = new std::vector<bullet>();

auto player = new Player(4,4);
AI_left_right* ai_l_r = new AI_left_right(2,3);
auto ai_u_d = new AI_up_down(2,4);
auto ai_shot = new AI_shot(2,5);
bool win = false;
bool loss = false;
void updateHealth(){
    // player meet enermy
    if((ai_u_d->getHealth()>0)&&(pow(player->getX()-ai_u_d->getX(),2)+pow(player->getY()-ai_u_d->getY(),2) < BLOCK*BLOCK))
    {
        loss = true;
        return;
    }
        if((ai_l_r->getHealth()>0)&&(pow(player->getX()-ai_l_r->getX(),2)+pow(player->getY()-ai_l_r->getY(),2) < BLOCK*BLOCK))
    {
        loss = true;
        return;
    }
    if((ai_shot->getHealth()>0)&&(pow(player->getX()-ai_shot->getX(),2)+pow(player->getY()-ai_shot->getY(),2) < BLOCK*BLOCK))
    {
        loss = true;
        return;
    }
    // enermy meet bullet
    for(auto it:*myBullet){
        if(pow(it.x-ai_u_d->getX(),2)+pow(it.y-ai_u_d->getY(),2) < BLOCK*BLOCK*4/9)
        {
            ai_u_d->setHealth(ai_u_d->getHealth()-50);
            return;
        }
        if(pow(it.x-ai_l_r->getX(),2)+pow(it.y-ai_l_r->getY(),2) < BLOCK*BLOCK*4/9)
        {
            ai_l_r->setHealth(ai_l_r->getHealth()-50);
            return;
        }
        if(pow(it.x-ai_shot->getX(),2)+pow(it.y-ai_shot->getY(),2) < BLOCK*BLOCK*4/9)
        {
            ai_shot->setHealth(ai_shot->getHealth()-50);
            return;
        }
        if(ai_l_r->getHealth()<=0 && ai_u_d->getHealth()<=0&&ai_shot->getHealth()<=0){
            win = true;
            return;
        }
        
    }
    // player meet bullet
    for(auto it:*ai_shot->myBullet){
        if(pow(player->getX()-it.x,2)+pow(player->getY()-it.y,2) < (BLOCK*2/3)*(BLOCK*2/3))
        {
            loss = true;
            return;
        }
        
    }
    
}




SDL_Renderer * renderer;
void drawBullet(){
    for(auto it:*myBullet){
        if(it.from){
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        }else{
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        }
        SDL_Rect r = {it.x,it.y,BLOCK/3,BLOCK/3};
        SDL_RenderFillRect(renderer, &r);
    }
    for(auto it = myBullet->begin();it!=myBullet->end();it++){
        switch (it->direction) {
            case LEFT:
                it->x -= SPEED_B;
                break;
            case RIGHT:
                it->x += SPEED_B;
                break;
            case UP:
                it->y += SPEED_B;
                break;
            case DOWN:
                it->y -= SPEED_B;
                break;
            case STOP:
                break;
        }
    }
    for(auto it:*ai_shot->myBullet){
        if(it.from){
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        }else{
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        }
        SDL_Rect r = {it.x,it.y,BLOCK/3,BLOCK/3};
        SDL_RenderFillRect(renderer, &r);
    }
    for(auto it = (*ai_shot->myBullet).begin();it!=(*ai_shot->myBullet).end();it++){
        switch (it->direction) {
            case LEFT:
                it->x -= SPEED_B;
                break;
            case RIGHT:
                it->x += SPEED_B;
                break;
            case UP:
                it->y += SPEED_B;
                break;
            case DOWN:
                it->y -= SPEED_B;
                break;
            case STOP:
                break;
        }
    }
}


void draw(){
    SDL_SetRenderDrawColor(renderer, 50, 110, 130,255);
    SDL_RenderClear(renderer);
    updateHealth();
    if(win){
        TTF_Init();
        auto font = TTF_OpenFont("font.ttf", 50);
        if (font == NULL) {
            SDL_Log("Can not open font, %s", TTF_GetError());
        }
        SDL_Color textColor = { 0xff,0xff,0xff,0xff };
        auto text = TTF_RenderUTF8_Blended(font, "You Win", textColor);
        auto text_texture = SDL_CreateTextureFromSurface(renderer, text);
        SDL_Rect dst = { 100,200,400,100 };
        SDL_RenderCopy(renderer, text_texture, NULL, &dst);
        SDL_RenderPresent(renderer);
        return;
    }
    if(loss){
        TTF_Init();
        auto font = TTF_OpenFont("font.ttf", 50);
        if (font == NULL) {
            SDL_Log("Can not open font file, %s", TTF_GetError());
        }
        SDL_Color textColor = { 0xff,0xff,0xff,0xff };
        auto text = TTF_RenderUTF8_Blended(font, "You Lose", textColor);
        auto text_texture = SDL_CreateTextureFromSurface(renderer, text);
        SDL_Rect dst = { 100,200,400,100 };
        SDL_RenderCopy(renderer, text_texture, NULL, &dst);
        SDL_RenderPresent(renderer);
        return;
    }
    auto img_player = IMG_LoadTexture(renderer, "player.png");
    auto img_ai_l_r = IMG_LoadTexture(renderer, "AI1.png");
    auto img_ai_u_d = IMG_LoadTexture(renderer, "AI2.png");
    auto img_ai_shot = IMG_LoadTexture(renderer, "AI3.png");
    
    drawBullet();
    
    SDL_Rect pos = {player->getX(),player->getY(),BLOCK,BLOCK};
    SDL_RenderCopy(renderer, img_player, nullptr, &pos);
    
    ai_l_r->move();
    ai_u_d->move();
    player->move();
    ai_shot->move();
    
    if(ai_l_r->getHealth()>0){
        pos = {ai_l_r->getX(),ai_l_r->getY(),BLOCK,BLOCK};
        SDL_RenderCopy(renderer, img_ai_l_r, nullptr, &pos);
    }
    if(ai_u_d->getHealth()>0){
        pos = {ai_u_d->getX(),ai_u_d->getY(),BLOCK,BLOCK};
        SDL_RenderCopy(renderer, img_ai_u_d, nullptr, &pos);
    }

    if(ai_shot->getHealth()>0){
        pos = {ai_shot->getX(),ai_shot->getY(),BLOCK,BLOCK};
        SDL_RenderCopy(renderer, img_ai_shot, nullptr, &pos);
    }
    
    SDL_RenderPresent(renderer);
    
}

void event_loop(){
    while (1) {
        auto start = SDL_GetTicks();
        
        SDL_Event event;
        if(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                break;
            }else if(event.type == SDL_KEYDOWN){
                switch (event.key.keysym.sym) {
                    case UP_ARROW:
                        player->changeDirection(UP);
                        break;
                    case DOWN_ARROW:
                        player->changeDirection(DOWN);
                        break;
                    case LEFT_ARROW:
                        player->changeDirection(LEFT);
                        break;
                    case RIGHT_ARROW:
                        player->changeDirection(RIGHT);
                        break;
                    case SPACE:
                        bullet newBullet;
                        newBullet.direction = player->getDirection();
                        if(newBullet.direction!=STOP){
                            newBullet.from = true;
                            newBullet.x = player->getX();
                            newBullet.y = player->getY();
                            myBullet->push_back(newBullet);
                            
                        }
                    default:
                        break;
                }
            }
        };
        
        
        draw();
        
        auto end = SDL_GetTicks();
        if(end - start < 1000/FPS){
            SDL_Delay(1000/FPS - (end - start));
        }
    }
}

int main(int argc, char* argv[]) {
    std::cout<<argv[0];
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("Lab 4",
                                     SDL_WINDOWPOS_CENTERED,
                                     SDL_WINDOWPOS_CENTERED,
                                     window_height_pixes,
                                     window_width_pixes,
                                     SDL_WINDOW_SHOWN
                                     );
    
    renderer = SDL_CreateRenderer(displayWindow, -1, SDL_RENDERER_ACCELERATED);
    
    
    event_loop();
    
    SDL_DestroyWindow(displayWindow);
    SDL_Quit();
    return 0;
}
