//
//  River.h
//  final_project
//
//  Created by 景璞 on 2018/6/25.
//  Copyright © 2018年 Sonic Wang. All rights reserved.
//

#ifndef River_h
#define River_h
#include "Obstacle.h"

class River : public Obstacle
{
public:
    River(int x, int y) : Obstacle(int x, int y)
    {
        type = RIVER;
        circle = new Circle(x, y, 60);
        img = al_load_bitmap("./obstacle/river.png");
        tank_ava = false;
        bullet_ava = true;
    }
};
#endif /* River_h */
