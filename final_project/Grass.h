//
//  Grass.h
//  final_project
//
//  Created by 景璞 on 2018/6/25.
//  Copyright © 2018年 Sonic Wang. All rights reserved.
//

#ifndef Grass_h
#define Grass_h

#include "Obstacle.h"

class Grass : public Obstacle
{
public:
    Grass(int x, int y) : Obstacle(int x, int y)
    {
        type = GRASS;
        circle = new Circle(x, y, 60);
        img = al_load_bitmap("./obstacle/grass.png");
        tank_ava = true;
        bullet_ava = true;
    }
};
#endif /* Grass_h */
