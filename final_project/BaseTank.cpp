//
//  BaseTank.cpp
//  final_project
//
//  Created by 馮謙 on 2018/6/24.
//  Copyright © 2018年 Sonic Wang. All rights reserved.
//
#include "BaseTank.h"

const int axis_x[] = {-1, 1, 0, 0};
const int axis_y[] = {0, 0, -1, 1};
const char direction_name[][10] = {"LEFT", "RIGHT", "UP", "DOWN"};

BaseTank::BaseTank(int x, int y){
    // default direction is right
    direction = UP;

    circle = new Circle;
    circle->x = x;
    circle->y = y;
    circle->r = grid_width/2;

    direction_count[LEFT] = 1;
    direction_count[RIGHT] = 1;
    direction_count[UP] = 1;
    direction_count[DOWN] = 1;

    sprite_pos = 0;
    counter = 0;
    strncpy(class_name, "BlueTank", 20);
}

BaseTank::~BaseTank(){
    for(unsigned int i=0; i<moveImg.size(); i++)
    {
        ALLEGRO_BITMAP *img = moveImg[i];
        
        moveImg.erase(moveImg.begin() + i);
        
        i--;
        al_destroy_bitmap(img);
    }
    moveImg.clear();
    
    delete circle;
}

void
BaseTank::Load_Move()
{
    char buffer[50];
    
    for(int i=0; i < 4; i++)
    {
        for(int j=0; j<direction_count[i]; j++)
        {
            ALLEGRO_BITMAP *img;
            sprintf(buffer, "./%s/%s_%d.png", class_name, direction_name[i], j);
            
            img = al_load_bitmap(buffer);
            if(img)
                moveImg.push_back(img);
        }
    }
}

void
BaseTank::Draw()
{
    
    int w, h;
    int offset = 0;
    
    // calculate the number of pictures before current direction
    for(int i=0; i<direction; i++)
        offset += direction_count[i];
    
    if(!moveImg[offset + sprite_pos])
        return;
    
    // draw bitmap align grid edge
    al_draw_bitmap(moveImg[offset + sprite_pos], circle->x /*- grid_width/2*/, circle->y /*- grid_height/2*/, ALLEGRO_ALIGN_CENTRE);
    
    //al_draw_filled_circle(circle->x, circle->y, circle->r, al_map_rgba(196, 79, 79, 200));
}



bool
BaseTank::Subtract_HP(int harm_point)
{
    HealthPoint -= harm_point;
    
    return (HealthPoint <= 0);
}

