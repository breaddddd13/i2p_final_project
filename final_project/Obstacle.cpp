//
//  Obstacle.cpp
//  final_project
//
//  Created by 景璞 on 2018/6/25.
//  Copyright © 2018年 Sonic Wang. All rights reserved.
//

#include "Obstacle.h"

void Obstacle::Draw()
{
    al_draw_bitmap(img, getCircle()->x - 50 , getCircle()->y - 50 , ALLEGRO_ALIGN_CENTER);
    
}
Obstacle::Obstacle(int x,int y){
    bullet_ava = true;
    tank_ava = true;
    health_point = 3;
//    circle->x = x;
//    circle->y = y;
//    circle->r = grid_width/2;
}

bool Obstacle::TankAva(BaseTank * Tank){
    
    return (Circle::isOverlap(this->circle, Tank->front) || Circle::isOverlap(this->circle, Tank->back)) ? false : true;
}

bool Obstacle::BulletAva(Attack * beam){
    
    return (Circle::isOverlap(this->circle, beam->getCircle())) ? false : true;
}
