//
//  BlueRoy.h
//  final_project
//
//  Created by 馮謙 on 2018/6/24.
//  Copyright © 2018年 Sonic Wang. All rights reserved.
//

#ifndef BlueRoy_h
#define BlueRoy_h

#include "BaseTank.h"

class BlueRoy : public BaseTank
{
public:
    BlueRoy(int x, int y) : BaseTank(x,y)
    {
        direction_count[LEFT] = 2;
        direction_count[RIGHT] = 2;
        direction_count[UP] = 2;
        direction_count[DOWN] = 2;
        
        HealthPoint = 2;
        speed = 3;
        worth = 30;
        score = 500;
        
        strncpy(class_name, "BlueTank/Roy", 20);
        
        Load_Move();
    }
};

#endif /* BlueRoy_h */
