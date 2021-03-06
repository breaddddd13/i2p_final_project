#ifndef ATTACK_H_INCLUDED
#define ATTACK_H_INCLUDED

#include <stdio.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include "Object.h"
#include "Circle.h"
#include "global.h"

#define abs(x) ((x) > 0? (x) : -(x))


class Attack : public Object
{
public:
    Attack(Circle*, int, int, int, ALLEGRO_BITMAP*);
    ~Attack();
    
    // override virtual function "Object::Draw"
    void Draw();
    int getHarmPoint() { return harm_point; }
    float getX() {return pos_x; }
    float getY() {return pos_y; }
    
    static float volume;
    
protected:
    ALLEGRO_BITMAP *attack_img;
    ALLEGRO_SAMPLE *sample;
    ALLEGRO_SAMPLE_INSTANCE *arrow = NULL;
    
    
private:
    int attack_velocity = 15;
    int harm_point = 5;
    float direction_x, direction_y;
    int degree;
    float pos_x, pos_y;
};

#endif // ATTACK_H_INCLUDED
