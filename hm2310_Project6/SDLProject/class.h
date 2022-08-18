#ifndef __CLASS__H
#define __CLASS__H
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <vector>
#include <cmath>
#include <random>
#define FPS 60
#define PLANE_SIZE 24

enum {
	LEFT_ARROW = 1073741904,
	RIGHT_ARROW = 1073741903,
	DOWN_ARROW = 1073741905,
	UP_ARROW = 1073741906,
	SPACE = 32,
	ENTER = 13
};

using GAME_STATUS =  enum {
	GAME_PLAY,GAME_RESET,GAME_OVER
} ;

using PLAYER_STATUS = enum {
	PLAYER_PLAYING,PLAYER_WIN,PLAYER_LOSS
};

using SENCE_STATUS = enum {
	MENU,GAME1,GAME2,GAME3,WIN,LOSS
};



void init_game();
void reset_game();

//	music
void play_back_music();
void play_hit_music();

//	sence
void display_menu();
void display_game();
void display_win();
void display_loss();


//	help func
void display_text(const char* str, SDL_Color color, SDL_Rect dst);
void display_img(SDL_Surface * surface,  SDL_Rect dst);
void display_player();
void display_enemy();
void display_bullet();
void display_wall(); // static
void display_health();
void display_time();
void display_back();
void level_up();


// main func
void event_loop();
void draw();


// class
class Player {
public:
	int x, y;
	Player() {
		x = 168;
		y = 540;
	}
};

class Enemy {
public:
	int x, y;
	int shoot_count;
	void auto_move();
	void auto_shoot();
};

class Bullet {
public:
	int x, y;
	int vx, vy;
	int display_count;
	void auto_move();
};

#endif // 
