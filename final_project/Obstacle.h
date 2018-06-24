//
//  Obstacle.h
//  final_project
//
//  Created by 景璞 on 2018/6/25.
//  Copyright © 2018年 Sonic Wang. All rights reserved.
//

#ifndef Obstacle_h
#define Obstacle_h

#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "Object.h"
#include "Circle.h"
#include "global.h"

class Obstacle : public Object
{
public:
    Obstacle(int x, int y);
    ~Obstacle(){};
    
    void Draw();
    bool BulletAva(){return bullet_ava;}
    bool TankAva(){return tank_ava;}
    void setImg(ALLEGRO_BITMAP * new_img){img = new_img;}
protected:
    bool bullet_ava = true;
    bool tank_ava = true;
    int health_point = 3;
    int type;
    ALLEGRO_BITMAP *img = NULL;
};
#endif /* Obstacle_h */
