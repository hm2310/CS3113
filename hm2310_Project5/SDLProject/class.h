#ifndef __CLASS__H
#define __CLASS__H
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_mixer.h>
#include "class.h"
#include <SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <vector>
#include <cmath>
#define FPS 60
enum {
LEFT_ARROW = 1073741904,
RIGHT_ARROW = 1073741903,
DOWN_ARROW = 1073741905,
UP_ARROW = 1073741906,
SPACE = 32,
ENTER = 13
};
static SDL_Window* displayWindow;
static SDL_Renderer* renderer;
#define BLOCK_SIZE 50

static int level = 1;
static const char* player_img_path = "player.png";
static const char* monster_img_path = "monster.png";
static const char* platform_img_path = "wall.png";
static const char* back_music_path = "back.wav";
static const char* hit_music_path = "hit.wav";

static const char* menu_img_path = "menu.png";
static const char* back_img_path = "back.png";
static const char* font_path = "font.ttf";

static bool pause = false;

static SDL_Surface* player_img = IMG_Load(player_img_path);
static SDL_Surface* monster_img = IMG_Load(monster_img_path);
static SDL_Surface* platform_img = IMG_Load(platform_img_path);
static SDL_Surface* back_music = IMG_Load(back_music_path);
static SDL_Surface* menu_img = IMG_Load(menu_img_path);
static SDL_Surface* back_img = IMG_Load(back_img_path);

static const int window_height = 600;
static const int window_width = 1000;

static bool menu_flag = true;
static bool win_flag = false;
static bool loss_flag = false;
static int player_HP = 3;


const int g = 4;
static int offsetx = 0;
using SportStatus = struct { int x,y,vy; };
using PlatformStatus = struct { int x, y, w; };
class Player;
static bool onPlatform(Player* p,int off);
class Player {
public:
	SportStatus status;
	Player() {
		this->status = { 100,100,0 };
	}
	void jump() {
		status.vy = -100;
	}
	

}; 
static auto platform = std::vector<PlatformStatus>(
	{ {100,300,3},{300,250,2} }
);
static Player* player = new Player();
static SportStatus sportEngine(SportStatus istatus, int offsetx) {
		{
			//SDL_Log("%d", istatus.y);
			if (onPlatform(player, offsetx) && istatus.vy > 0) {
				istatus.vy = 0;
			}
			else {
				istatus.y += istatus.vy;
				//SDL_Log("%d", istatus.y);
				// vy = v0+gt

				if (istatus.vy > 0) {
					istatus.vy -= g;
				}
				else
				{
					istatus.vy = g;
				}
			}
			return istatus;
		}
	}



static void displayBack() {
	offsetx--;
	offsetx %= window_width;
	auto back_texture = SDL_CreateTextureFromSurface(renderer, back_img);
	SDL_Rect dst = { offsetx,0,window_width,window_height };
	SDL_RenderCopy(renderer, back_texture, NULL, &dst);
	dst = { offsetx + window_width,0,window_width,window_height };
	SDL_RenderCopy(renderer, back_texture, NULL, &dst);
	SDL_DestroyTexture(back_texture);
}

static bool onPlatform(Player*player,int offsetx) {

	
	for (auto it : platform) {
		if ((  (player->status.x + BLOCK_SIZE /2 >= it.x + offsetx && player->status.x + BLOCK_SIZE /2 <= it.x + offsetx + it.w * BLOCK_SIZE)\
			|| (player->status.x + BLOCK_SIZE/2 >= it.x + offsetx + window_width && player->status.x + BLOCK_SIZE /2 <= it.x + offsetx + window_width + it.w * BLOCK_SIZE)\
			) 
			&& 
			(	((player->status.y - it.y) >= (-BLOCK_SIZE - 2)))
				&& 
				((player->status.y - it.y) <= (-BLOCK_SIZE+2))
			)
		{
			return true;
		}
	}

	return false;
}

static void displayPlatform() {
	
	for (auto it : platform) {
		auto platform_texture = SDL_CreateTextureFromSurface(renderer,platform_img);
		SDL_Rect dst = {it.x + offsetx,it.y,BLOCK_SIZE*it.w,BLOCK_SIZE};
		SDL_RenderCopy(renderer, platform_texture, NULL, &dst);
		dst = { it.x + offsetx + window_width,it.y,BLOCK_SIZE * it.w,BLOCK_SIZE };
		SDL_RenderCopy(renderer, platform_texture, NULL, &dst);
		SDL_DestroyTexture(platform_texture);
	}
	
}

static void displayPlayer() {
	auto player_texture = SDL_CreateTextureFromSurface(renderer, player_img);
	SDL_Rect dst = { player->status.x,player->status.y,BLOCK_SIZE,BLOCK_SIZE };
	SDL_RenderCopy(renderer, player_texture, NULL, &dst);
	SDL_DestroyTexture(player_texture);
	player->status = sportEngine(player->status,offsetx);
}

static void displayMenu() {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);
	auto img_menu_texture = SDL_CreateTextureFromSurface(renderer, menu_img);
	SDL_Rect total_win = { 0,0,window_width,window_height };
	SDL_RenderCopy(renderer, img_menu_texture, NULL, &total_win);
	SDL_DestroyTexture(img_menu_texture);
	TTF_Init();
	auto font = TTF_OpenFont(font_path, 50);
	if (font == NULL) {
		SDL_Log("Can not open font, %s", TTF_GetError());
	}
	SDL_Color textColor = { 0xff,0xff,0xff,0xff };
	auto text = TTF_RenderUTF8_Blended(font, "Avoid monsters", textColor);
	auto text_texture = SDL_CreateTextureFromSurface(renderer, text);
	SDL_Rect dst = { 100,200,600,100 };
	SDL_RenderCopy(renderer, text_texture, NULL, &dst);
	SDL_DestroyTexture(text_texture);
	char ch[20];
	sprintf(ch, "Level: %d", level);
	text = TTF_RenderUTF8_Blended(font, ch, textColor);
	text_texture = SDL_CreateTextureFromSurface(renderer, text);
	dst = { 100,300,300,100 };
	SDL_RenderCopy(renderer, text_texture, NULL, &dst);
	SDL_DestroyTexture(text_texture);
	SDL_RenderPresent(renderer);
	return;
}

static void displayHP() {
	TTF_Init();
	auto font = TTF_OpenFont(font_path, 50);
	if (font == NULL) {
		SDL_Log("Can not open font, %s", TTF_GetError());
	}
	SDL_Color textColor = { 0xff,0xff,0xff,0xff };


	char ch[20];
	sprintf(ch, "HP: %d", player_HP);
	auto text = TTF_RenderUTF8_Blended(font, ch, textColor);
	auto text_texture = SDL_CreateTextureFromSurface(renderer, text);
	SDL_Rect dst = { 100,500,300,100 };
	SDL_RenderCopy(renderer, text_texture, NULL, &dst);
	SDL_DestroyTexture(text_texture);
	SDL_RenderPresent(renderer);
}
static void displayWin() {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);
	auto img_menu_texture = SDL_CreateTextureFromSurface(renderer, menu_img);
	SDL_Rect total_win = { 0,0,window_width,window_height };
	SDL_RenderCopy(renderer, img_menu_texture, NULL, &total_win);
	SDL_DestroyTexture(img_menu_texture);
	TTF_Init();
	auto font = TTF_OpenFont(font_path, 50);
	if (font == NULL) {
		SDL_Log("Can not open font, %s", TTF_GetError());
	}
	SDL_Color textColor = { 0xff,0xff,0xff,0xff };
	auto text = TTF_RenderUTF8_Blended(font, "You Win the game.", textColor);
	auto text_texture = SDL_CreateTextureFromSurface(renderer, text);
	SDL_Rect dst = { 100,200,600,100 };
	SDL_RenderCopy(renderer, text_texture, NULL, &dst);
	SDL_DestroyTexture(text_texture);

	SDL_RenderPresent(renderer);
	return;
}

static void displayLoss() {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);
	auto img_menu_texture = SDL_CreateTextureFromSurface(renderer, menu_img);
	SDL_Rect total_win = { 0,0,window_width,window_height };
	SDL_RenderCopy(renderer, img_menu_texture, NULL, &total_win);
	SDL_DestroyTexture(img_menu_texture);
	TTF_Init();
	auto font = TTF_OpenFont(font_path, 50);
	if (font == NULL) {
		SDL_Log("Can not open font, %s", TTF_GetError());
	}
	SDL_Color textColor = { 0xff,0xff,0xff,0xff };
	auto text = TTF_RenderUTF8_Blended(font, "You Loss the game.", textColor);
	auto text_texture = SDL_CreateTextureFromSurface(renderer, text);
	SDL_Rect dst = { 100,200,600,100 };
	SDL_RenderCopy(renderer, text_texture, NULL, &dst);
	SDL_DestroyTexture(text_texture);
	SDL_RenderPresent(renderer);
	return;
}

static void displayMonster() {
	switch (level)
	{
	case 1:
		for (auto it : platform) {
			auto monster_texture = SDL_CreateTextureFromSurface(renderer, monster_img);
			SDL_Rect dst = { it.x + offsetx,it.y - BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE };
			SDL_RenderCopy(renderer, monster_texture, NULL, &dst);
			dst = { it.x + offsetx + window_width,it.y - BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE };
			SDL_RenderCopy(renderer, monster_texture, NULL, &dst);
			SDL_DestroyTexture(monster_texture);
		}
		break;
	case 2:
		for (auto it : platform) {
			auto monster_texture = SDL_CreateTextureFromSurface(renderer, monster_img);
			SDL_Rect dst = { it.x + offsetx,it.y - BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE };
			SDL_RenderCopy(renderer, monster_texture, NULL, &dst);
			dst = { it.x + offsetx + window_width,it.y - BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE };
			SDL_RenderCopy(renderer, monster_texture, NULL, &dst);
			dst = { it.x + offsetx + window_width + BLOCK_SIZE,it.y - BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE };
			SDL_RenderCopy(renderer, monster_texture, NULL, &dst);
			dst = { it.x + offsetx + BLOCK_SIZE,it.y - BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE };
			SDL_RenderCopy(renderer, monster_texture, NULL, &dst);
			SDL_DestroyTexture(monster_texture);
		}
		break;
	case 3:
		for (auto it : platform) {
			auto monster_texture = SDL_CreateTextureFromSurface(renderer, monster_img);
			SDL_Rect dst = { it.x + offsetx,it.y - BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE };
			SDL_RenderCopy(renderer, monster_texture, NULL, &dst);
			dst = { it.x + offsetx + window_width,it.y - BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE };
			SDL_RenderCopy(renderer, monster_texture, NULL, &dst);
			dst = { it.x + offsetx + window_width + BLOCK_SIZE,it.y - BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE };
			SDL_RenderCopy(renderer, monster_texture, NULL, &dst);
			dst = { it.x + offsetx + BLOCK_SIZE,it.y - BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE };
			SDL_RenderCopy(renderer, monster_texture, NULL, &dst);
			dst = { it.x + offsetx + window_width + 2*BLOCK_SIZE,it.y - BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE };
			SDL_RenderCopy(renderer, monster_texture, NULL, &dst);
			dst = { it.x + offsetx + 2*BLOCK_SIZE,it.y - BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE };
			SDL_RenderCopy(renderer, monster_texture, NULL, &dst);
			SDL_DestroyTexture(monster_texture);
		}
	default:
		break;
	}
}

static void levelUP() {
	if (level != 3) {
		level++;
		menu_flag = true;
	}
	else {
		win_flag = true;
	}
}
static void play_music() {
    Mix_VolumeMusic(100);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    auto sound = Mix_LoadMUS(back_music_path);
    Mix_PlayMusic(sound, -1);
}
static void play_hit_music() {
	Mix_VolumeMusic(100);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	auto sound = Mix_LoadMUS(hit_music_path);
	Mix_PlayMusic(sound, 1);
}
static void judgeStatus() {

		for (auto it : platform) {
			if (((player->status.x + BLOCK_SIZE / 2 >= it.x + offsetx && player->status.x + BLOCK_SIZE / 2 <= it.x + offsetx + level * BLOCK_SIZE)\
				|| (player->status.x + BLOCK_SIZE / 2 >= it.x + offsetx + window_width && player->status.x + BLOCK_SIZE / 2 <= it.x + offsetx + window_width + level * BLOCK_SIZE)\
				)
				&&
				(((player->status.y - it.y) >= (-2*BLOCK_SIZE - 2)))
				&&
				((player->status.y - it.y) <= (-2*BLOCK_SIZE + 2))
				)
			{
				player_HP--;
                play_hit_music();
                play_music();
				player->status.x = 100;
				player->status.y = 100;

				if (player_HP == 0) {
					loss_flag = true;
					return;
				}
			}
		}

}

static void draw() {
	if (menu_flag) {
		displayMenu();
		return;
	}
	if (win_flag) {
		displayWin();
		return;
	}
	if (loss_flag) {
		displayLoss();
		return;
	}
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);
	displayBack();
	displayPlatform();
	displayPlayer();
	displayMonster();
	displayHP();
	judgeStatus();
	static int time_count = 0;
	time_count++;
	SDL_Log("%d",time_count);
	if (time_count % 300 == 0)
	{
		levelUP();
	}
	SDL_RenderPresent(renderer);
	return;
}





#endif // 
