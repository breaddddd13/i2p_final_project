//
//  BlueGeep.h
//  final_project
//
//  Created by 景璞 on 2018/6/24.
//  Copyright © 2018年 Sonic Wang. All rights reserved.
//

#ifndef BlueGeep_h
#define BlueGeep_h

#include "BaseTank.h"

class BlueGeep : public BaseTank
{
public:
    BlueGeep(int x, int y) : BaseTank(x,y)
    {
        direction_count[LEFT] = 2;
        direction_count[RIGHT] = 2;
        direction_count[UP] = 2;
        direction_count[DOWN] = 2;
        
        HealthPoint = 4;
        speed = 4;
        worth = 60;
        score = 1000;
        
        strncpy(class_name, "BlueTank/Geep", 20);
        attack_img = al_load_bitmap("./beams/blue_beam.png");
        
        Load_Move();
    }
};

#endif /* BlueGeep_h */
