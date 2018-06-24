#include "Attack.h"


const int axis_x[] = {-1, 1, 0, 0};
const int axis_y[] = {0, 0, -1, 1};

Attack::Attack( Circle* created_circle, int dir, int harm_point, int velocity, ALLEGRO_BITMAP* attack_img)
{
    
    this->pos_x = created_circle->x;
    this->pos_y = created_circle->y;
    this->circle = new Circle(created_circle->x, created_circle->y, 10);

    this->direction = dir;
    this->attack_velocity = velocity;
    this->harm_point = harm_point;
    this->attack_img = attack_img;

    // initialize the effect sound of attack
    sample = al_load_sample("Arrow.wav");
    arrow = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(arrow, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(arrow, al_get_default_mixer());
    al_set_sample_instance_gain(arrow, Attack::volume);
    al_play_sample_instance(arrow);
}

Attack::~Attack()
{
    delete circle;
    al_destroy_sample_instance(arrow);
    al_destroy_sample(sample);
}

void
Attack::Draw()
{
    al_draw_bitmap(attack_img, pos_x - circle->r, pos_y - circle->r, 0);
    pos_x += attack_velocity * direction;
    pos_y += attack_velocity * direction;

    circle->x = (int)pos_x;
    circle->y = (int)pos_y;
    
    //al_draw_filled_circle(pos_x, pos_y, circle->r, al_map_rgba(196, 79, 79, 200));
}

