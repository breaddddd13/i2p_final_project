//
//  BlueBread.h
//  final_project
//
//  Created by 景璞 on 2018/6/24.
//  Copyright © 2018年 Sonic Wang. All rights reserved.
//

#ifndef BlueBread_h
#define BlueBread_h

#include "BaseTank.h"

class BlueBread : public BaseTank
{
public:
    BlueBread(int x, int y) : BaseTank(x,y)
    {
        direction_count[LEFT] = 2;
        direction_count[RIGHT] = 2;
        direction_count[UP] = 2;
        direction_count[DOWN] = 2;
        
        HealthPoint = 7;
        speed = 7;
        worth = 100;
        score = 2000;
        
        strncpy(class_name, "BlueTank/Bread", 20);
        attack_img = al_load_bitmap("./beams/blue_beam.png");
        
        Load_Move();
    }
};

#endif /* BlueBread_h */
