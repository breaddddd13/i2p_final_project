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
#include <set>
#include <cmath>
#include "Object.h"
#include "Circle.h"
#include "global.h"
#include "Attack.h"



using namespace std;

class BaseTank: public Object {
    Circle *front = NULL;
    Circle *back = NULL;
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
    void Move();
    
    void TriggerAttack();
    void UpdateAttack();
    
    
    // functions that return informations of Tank
    int getDir() { return direction; }
    int getWorth() { return worth; }
    int getScore() { return score; }
    void move_valid(int dir);
    void move_invalid(int dir);
    
    bool Subtract_HP(int);
    
protected:
    int direction_count[4];
    int HealthPoint = 20;
    int speed = 1;
    int worth = 10;
    int score = 100;
    char class_name[20];
    int move_flag;
    vector<int> upDown;
    vector<int> leftRight;
    
    // setting of attack
    int attack_frequency = 1;
    int attack_counter = 0;
    int attack_harm_point = 5;
    int attack_velocity = 13;
    ALLEGRO_BITMAP *attack_img;
    std::vector<Attack*> attack_set;

    Circle *attackCircle = NULL;
    
    
private:
    int degree;
    
    int direction;
    // animation counter
    int counter;
    // animation image of current direction
    int sprite_pos;
    
    // set of animation images
    vector<ALLEGRO_BITMAP*> moveImg;
};


#endif /* BaseTank_h */
