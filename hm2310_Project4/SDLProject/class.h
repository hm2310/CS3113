//
//  class.h
//  SDLProject
//
//  Created by hm2310 on 2022/7/29.
//  Copyright © 2022 ctg. All rights reserved.
//

#ifndef class_h
#define class_h

#pragma once

#ifdef _WINDOWS
    #include <GL/glew.h>
#endif
#define GL_GLEXT_PROTOTYPES 1
#include <SDL_opengl.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>
#include <ctime>

#include "glm/mat4x4.hpp"


#define NET_HEIGHT 10
#define NET_WIDTH 8

#define FPS 60

#define BLOCK 60

const int window_height_pixes = NET_HEIGHT*BLOCK;
const int window_width_pixes = NET_WIDTH*BLOCK;

#define SPEED 0.1
#define FPS 60



using POSITION = struct {
    double x;
    double y;
    int health;
    int attack;
};

enum DIRECTION {
    LEFT, RIGHT, UP, DOWN, STOP
};
using bullet = struct {
    bool from;// true from player and false from enermy
    DIRECTION direction;
    int x;
    int y;
};
class AI {
protected:
    POSITION position_;
    DIRECTION myDirection_;
    int count = 0;
public:
    AI(int x, int y) {
        position_.x = x;
        position_.y = y;
        position_.health = 100;
        position_.attack = 5;
        myDirection_ = STOP;
    }

    ~AI() = default;
    int getHealth(){
        return position_.health;
    }
    void setHealth(int health){
        position_.health =health;
    }
    int getAttack(){return position_.attack;}
    
    DIRECTION getDirection(){return myDirection_;}
    
    int getX(){
        return position_.x * BLOCK;
    }
    int getY(){
        return position_.y * BLOCK;
    }
    
    virtual void move() {
        switch (myDirection_) {
            case LEFT:
                position_.x -= SPEED;
                break;
            case RIGHT:
                position_.x += SPEED;
                break;
            case UP:
                position_.y += SPEED;
                break;
            case DOWN:
                position_.y -= SPEED;
                break;
                
            case STOP:
                break;
        }
        if(count++ % 60 == 0){changeDirection(STOP);};
    };
    virtual void changeDirection(DIRECTION newDirection){};
};

class Player :public AI {
private:

public:
    Player(int x, int y) : AI(x, y) {
        position_.health = 100;
        position_.attack = 10;
        myDirection_ = STOP;
    }
    
    void move() override{
    switch (myDirection_) {
        case LEFT:
            if(position_.x <=0)break;
            position_.x -= SPEED;
            break;
        case RIGHT:
            if(position_.x >= NET_WIDTH + 1)break;
            position_.x += SPEED;
            break;
        case UP:
            if(position_.y >= 7)break;
            position_.y += SPEED;
            break;
        case DOWN:
            if(position_.y <= 0)break;
            position_.y -= SPEED;
            break;
        case STOP:
            break;
    }
    }
    
    
    void changeDirection(DIRECTION newDirection) override{
        myDirection_ = newDirection;
    }
};

// can move to left or right
class AI_left_right :public AI {
public:
    AI_left_right(int x,int y): AI(x,y){
        myDirection_ = LEFT;
    }
    void changeDirection(DIRECTION newDirection) override{
       
            if(myDirection_ == LEFT){
                myDirection_ = RIGHT;
            } else if(myDirection_ == RIGHT){
                myDirection_ = LEFT;
            }
            
        
        
    }
};

class AI_up_down :public AI {
public:
    AI_up_down(int x,int y): AI(x,y){
        myDirection_ = UP;
    }
    void changeDirection(DIRECTION newDirection) override{
        if(myDirection_ == UP){
            myDirection_ = DOWN;
        } else if(myDirection_ == DOWN){
            myDirection_ = UP;
        }
    }
};

class AI_shot :public AI {
public:
    std::vector<bullet> *myBullet = new std::vector<bullet>();
    
    AI_shot(int x,int y):AI(x,y){
        myDirection_ = STOP;
    };
    
    void move() override{
        switch (myDirection_) {
            case LEFT:
                position_.x -= SPEED;
                break;
            case RIGHT:
                position_.x += SPEED;
                break;
            case UP:
                position_.y += SPEED;
                break;
            case DOWN:
                position_.y -= SPEED;
                break;
                
            case STOP:
                break;
        }
        if(count% 60 == 0){changeDirection(STOP);};
        
        if(count++ % 60 == 0 && position_.health > 0){
            bullet newBullet;
            srand((unsigned)time(nullptr));
            int a = int(rand()%4)+1;
            switch (a) {
                case 1:
                    newBullet.direction = LEFT;
                    break;
                case 2:
                    newBullet.direction = RIGHT;
                    break;
                case 3:
                    newBullet.direction = UP;
                    break;
                case 4:
                    newBullet.direction = DOWN;
                    break;
                default:
                    break;
            }
            newBullet.x = getX();
            newBullet.y = getY();
            newBullet.from = false;
            myBullet->push_back(newBullet);
        };
        
    };
};

class shot :public AI {
private:
    int from;// 0: from p ; 1 from AI
};


#endif /* class_h */
