//
//  BaseTank.h
//  final_project
//
//  Created by 馮謙 on 2018/6/24.
//  Copyright © 2018年 Sonic Wang. All rights reserved.
//

#ifndef BaseTank_h
#define BaseTank_h

#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <vector>
#include "Object.h"
#include "Circle.h"
#include "global.h"
using namespace std;

enum {LEFT = 0, RIGHT, UP, DOWN};

class BaseTank: public Object {
public:
    BaseTank(int x, int y);
    ~BaseTank();
    // Draw image per frame
    // override virtual function "Object::Draw"
    void Draw();
    
    // Load bitmaps of animation image into container "moveImg"
    void Load_Move();
    // Update monster position per frame
    // And detect if it reaches end point but not destroyed
    virtual void Move() = 0;
    
    // functions that return informations of monster
    int getDir() { return direction; }
    int getWorth() { return worth; }
    int getScore() { return score; }
    
    bool Subtract_HP(int);
    
protected:
    int direction_count[4];
    int HealthPoint = 20;
    int speed = 1;
    int worth = 10;
    int score = 100;
    char class_name[20];
private:
    int direction;
    // animation counter
    int counter;
    // animation image of current direction
    int sprite_pos;
    
    // set of animation images
    vector<ALLEGRO_BITMAP*> moveImg;
};


#endif /* BaseTank_h */
