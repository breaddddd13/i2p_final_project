//
//  BaseTank.cpp
//  final_project
//
//  Created by 馮謙 on 2018/6/24.
//  Copyright © 2018年 Sonic Wang. All rights reserved.
//
#include "BaseTank.h"

const int axis_x[] = {-1, 1, 0, 0};
const int axis_y[] = {0, 0, -1, 1};
const char direction_name[][10] = {"LEFT", "RIGHT", "UP", "DOWN"};

const int draw_frequency = 10;

BaseTank::BaseTank(int x, int y){
    // default direction is right
    direction = RIGHT;

    circle = new Circle;
    circle->x = x;
    circle->y = y;
    circle->r = grid_width/2;
    
    attackCircle = new Circle;
    attackCircle->x = x;
    attackCircle->y = y;
    attackCircle->r = 600;
    
    front = new Circle;
    front->x = x;
    front->y = y - grid_height/2;
    front->r = grid_width/2 - 10;
    
    back = new Circle;
    back->x = x;
    back->y = y + grid_height/2;
    back->r = grid_width/2 -10;
    
    direction_count[LEFT] = 2;
    direction_count[RIGHT] = 2;
    direction_count[UP] = 2;
    direction_count[DOWN] = 2;
    
    move_flag = 0;
//    upDown = 0;
//    leftRight = 3;
    degree = 0;

    sprite_pos = 0;
    counter = 0;
    
    strncpy(class_name, "BlueTank", 20);
}

BaseTank::~BaseTank(){
    for(unsigned int i=0; i<moveImg.size(); i++)
    {
        ALLEGRO_BITMAP *img = moveImg[i];
        
        moveImg.erase(moveImg.begin() + i);
        
        i--;
        al_destroy_bitmap(img);
    }
    moveImg.clear();
    
    delete circle;
}

void
BaseTank::Load_Move()
{
    char buffer[50];
    
    for(int i=0; i < 4; i++)
    {
        for(int j=0; j<direction_count[i]; j++)
        {
            ALLEGRO_BITMAP *img;
            
            sprintf(buffer, "./%s/%s_%d.png", class_name, direction_name[i], j);

            
            img = al_load_bitmap(buffer);
            if(img)
                moveImg.push_back(img);
        }
    }
}

void
BaseTank::Draw()
{
    
    int offset = 2;
    
    // calculate the number of pictures before current direction
//    for(int i=0; i<direction; i++)
//        offset += direction_count[i];
    
    if(!moveImg[offset + sprite_pos])
        return;
    
    attack_counter = (attack_counter + 1) % attack_frequency;
    
    
    if (move_flag) {
        Move();
    }
    for(unsigned int i=0; i<attack_set.size(); i++)
        attack_set[i]->Draw();
    
    
    // draw bitmap align grid edge
//    al_draw_bitmap(moveImg[offset + sprite_pos], circle->x - grid_width/2, circle->y - grid_height/2, 0);
    
    
    al_draw_rotated_bitmap(moveImg[offset + sprite_pos], grid_width/2 , grid_height/2 , circle->x, circle->y, degree*rad, 0);
//    al_draw_filled_circle(circle->x, circle->y, circle->r, al_map_rgba(196, 79, 79, 100));
}

void
BaseTank::Move(){
    
    counter = (counter + 1) % draw_frequency;
    
    if(counter == 0)
        sprite_pos = (sprite_pos + 1) % direction_count[direction];
    if (!leftRight.empty()) {
        degree += axis_x[leftRight.back()];
        
    }
    if (!upDown.empty()) {
        if (upDown.back() == DOWN) {
            printf("1 %d %f\n", circle->y, sin(degree*rad));
            attackCircle->y = circle->y -= 3*sin(degree*rad);
            printf("2 %d %f\n", circle->y, sin(degree*rad));
            attackCircle->x = circle->x -= 3*cos(degree*rad);
        } else {
            printf("1 %d %f\n", circle->y, sin(degree*rad));
            attackCircle->y = circle->y += 3*sin(degree*rad);
            printf("2 %d %f\n", circle->y, sin(degree*rad));
            attackCircle->x = circle->x += 3*cos(degree*rad);
        }
    }

}

void
BaseTank::move_invalid(int dir) {
    
    move_flag -= 1;
    switch (dir) {
        case UP:
            if (!upDown.empty()) {
                upDown.erase(upDown.begin());
            }
            break;
        case DOWN:
            if (!upDown.empty()) {
                upDown.erase(upDown.begin());
            }
            break;
        case LEFT:
            if (!leftRight.empty()) {
                leftRight.erase(leftRight.begin());
            }
            break;
        case RIGHT:
            if (!leftRight.empty()) {
                leftRight.erase(leftRight.begin());
            }
            break;
        default:
            break;
    }
}

void
BaseTank::move_valid(int dir) {
    direction = dir;
    move_flag += 1;
    switch (dir) {
        case UP:
            upDown.push_back(UP);
            printf("Z\n");
            break;
        case DOWN:
            upDown.push_back(DOWN);
            break;
        case LEFT:
            leftRight.push_back(LEFT);
            break;
        case RIGHT:
            leftRight.push_back(RIGHT);
            break;
        default:
            break;
    }
    
}

bool
BaseTank::DetectAttack(std::vector<Attack*> atk_set){
    int destroyed = false;
    for(unsigned int i=0; i < atk_set.size(); i++)
    {
        if(Circle::isOverlap(atk_set[i]->getCircle(), this->circle))
        {
            if (Subtract_HP(atk_set[i]->getHarmPoint())) {
                destroyed = true;
            }
//            Attack *attack = atk_set[i];
            
            atk_set.erase(atk_set.begin() + i);
            i--;
            
            //delete attack;
            
            printf("%d\n", atk_set.size());
            return destroyed;
        }
    }
    return false;
}

void
BaseTank::TriggerAttack(){
    
    Attack *attack;
//    while (attack_set.size() < 2) {
        if ( attack_counter == 0 ){
            attack = new Attack(
                                this->circle,
                                this->degree,
                                this->attack_harm_point,
                                this->attack_velocity,
                                this->attack_img
                                );
            
            this->attack_set.push_back(attack);
        }
//    }
}

void
BaseTank::UpdateAttack()
{
    for(unsigned int i=0; i < this->attack_set.size(); i++)
    {
        if(!Circle::isOverlap(this->attack_set[i]->getCircle(), this->attackCircle))
        {
            Attack *attack = this->attack_set[i];

            this->attack_set.erase(this->attack_set.begin() + i);
            i--;
            delete attack;
        } else if (this->attack_set[i]->getX() < game_start_x || this->attack_set[i]->getX() > game_end_x || this->attack_set[i]->getY() < game_start_y || this->attack_set[i]->getY() > game_end_y) {
            
            Attack *attack = this->attack_set[i];
            
            this->attack_set.erase(this->attack_set.begin() + i);
            i--;
            delete attack;
            
        }
    }
}

bool
BaseTank::Subtract_HP(int harm_point)
{
    HealthPoint -= harm_point;
    
    return (HealthPoint <= 0);
}


