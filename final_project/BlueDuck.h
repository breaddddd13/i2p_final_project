//
//  BlueDuck.h
//  final_project
//
//  Created by 景璞 on 2018/6/24.
//  Copyright © 2018年 Sonic Wang. All rights reserved.
//

#ifndef BlueDuck_h
#define BlueDuck_h

#include "BaseTank.h"

class BlueDuck : public BaseTank
{
public:
    BlueDuck(int x, int y) : BaseTank(x,y)
    {
        direction_count[LEFT] = 2;
        direction_count[RIGHT] = 2;
        direction_count[UP] = 2;
        direction_count[DOWN] = 2;
        
        HealthPoint = 1;
        speed = 1;
        worth = 10;
        score = 100;
        
        strncpy(class_name, "BlueTank/Duck", 20);
        attack_img = al_load_bitmap("./beams/blue_beam.png");
        
        Load_Move();
    }
};
#endif /* BlueDuck_h */
