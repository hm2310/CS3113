#ifndef __CLASS__H
#define __CLASS__H
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <SDL_ttf.h>

#define FPS 60
#define HEIGHT_N 8
#define WIDTH_N 10
#define STDA 40
#define PTSIZE 20

const int STDPLANEH = STDA * 2 / 3;
const int STDPLANEW = STDA;
const int WIDTH = WIDTH_N * STDA;
const int HEIGHT = HEIGHT_N * STDA;



struct Point {
	int x,y; 
};

class Map {
	
public:
	Map() {
		std::string map_str = "*........**........****......**........**....***.**........**........*****--****";
		for (int y = 0; y < HEIGHT_N; y++) {
			for (int x = 0; x < WIDTH_N; x++) {
				if (map_str[y * WIDTH_N + x] == '*') { // wall
					_wall.push_back({ x,y });
				}
				else if (map_str[y * WIDTH_N + x] == '-')// land
				{
					_land.push_back({ x,y });
				}
			}
		}
	}
	std::vector<Point> _wall;
	std::vector<Point> _land;
};

class Plane {
public:
	Plane() {
		x = WIDTH / 2 - STDA/2;
		y = 0;
		ax = 0;
		g = 1;
	}
	void clacNextPos() {
		x += ax;
		y += g;
	}
	double x, y;
	double ax, g;//
};




#endif // 
