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
    al_draw_bitmap(img, getCircle()->x , getCircle()->y , 0);
    
}
Obstacle::Obstacle(int x,int y){
    bullet_ava = true;
    tank_ava = true;
    health_point = 3;
//    circle->x = x;
//    circle->y = y;
//    circle->r = grid_width/2;
}
