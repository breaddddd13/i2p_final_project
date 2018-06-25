//
//  RedRoy.h
//  final_project
//
//  Created by 馮謙 on 2018/6/25.
//  Copyright © 2018年 Sonic Wang. All rights reserved.
//

#ifndef RedRoy_h
#define RedRoy_h

#include "BaseTank.h"

class RedRoy : public BaseTank
{
public:
    RedRoy(int x, int y) : BaseTank(x,y)
    {
        direction_count[LEFT] = 2;
        direction_count[RIGHT] = 2;
        direction_count[UP] = 2;
        direction_count[DOWN] = 2;
        
        HealthPoint = 10;
        speed = 3;
        worth = 30;
        score = 500;
        
        strncpy(class_name, "RedTank/Roy", 20);
        
        attack_img = al_load_bitmap("./beams/red_beam.png");
        
        Load_Move();
    }
};

#endif /* RedRoy_h */
