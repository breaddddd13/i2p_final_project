//
//  Wall.h
//  final_project
//
//  Created by 景璞 on 2018/6/25.
//  Copyright © 2018年 Sonic Wang. All rights reserved.
//

#ifndef Wall_h
#define Wall_h

#include "Obstacle.h"

class Wall : public Obstacle
{
public:
    Wall(int x, int y) : Obstacle(int x, int y)
    {
        type = WALL;
        circle = new Circle(x, y, 60);
        img = al_load_bitmap("./obstacle/wall.png");
        tank_ava = false;
        bullet_ava = false;
    }
};
#endif /* Wall_h */
