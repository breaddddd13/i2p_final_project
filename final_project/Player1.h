//
//  Player1.h
//  final_project
//
//  Created by 馮謙 on 2018/6/24.
//  Copyright © 2018年 Sonic Wang. All rights reserved.
//

#ifndef Player1_h
#define Player1_h

#include "BaseTank.h"

class Player1 : public BaseTank
{
public:
    Player1(int x, int y) : BaseTank(x,y)
    {
        direction_count[LEFT] = 1;
        direction_count[RIGHT] = 1;
        direction_count[UP] = 1;
        direction_count[DOWN] = 1;
        
        HealthPoint = 3;
        speed = 3;
        worth = 30;
        score = 500;
        
        strncpy(class_name, "BlueTank", 20);
        
        Load_Move();
    }
};

#endif /* Player1_h */
