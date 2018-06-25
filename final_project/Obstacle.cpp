//
//  Obstacle.cpp
//  final_project
//
//  Created by 景璞 on 2018/6/25.
//  Copyright © 2018年 Sonic Wang. All rights reserved.
//

#include "Obstacle.h"
#include <iostream>
void Obstacle::Draw()
{
    al_draw_bitmap(img, getCircle()->x - 50 , getCircle()->y - 50 , ALLEGRO_ALIGN_CENTER);
    al_draw_filled_circle(circle->x, circle->y, circle->r, al_map_rgba(196, 79, 79, 100));
}
Obstacle::Obstacle(int x,int y){
    bullet_ava = true;
    tank_ava = true;
    health_point = 3;
    circle = new Circle(x,y,60);
//    circle->x = x;
//    circle->y = y;
//    circle->r = grid_width/2;
}

bool Obstacle::TankAva(BaseTank * Tank){
    
    //std::cout<<type<<std::endl;
    //if(tank_ava)return true;
    if(type==-1) return true;
    std::cout<<"enter\n";
    if(Circle::isOverlap(this->circle, Tank->getCircle()) )
    {
        std::cout<<"overlap\n";
    }
    else std::cout<<"not overlap\n";
    return (Circle::isOverlap(this->circle, Tank->getCircle()) ) ? false : true;
}

bool Obstacle::BulletAva(Attack * beam){
    
    return (Circle::isOverlap(this->circle, beam->getCircle())) ? false : true;
}
