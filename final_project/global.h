#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <allegro5/allegro_font.h>
#include <string>
#define font_size 12
#define grid_width 100
#define grid_height 100

#define window_width 1920
#define window_height 1440
#define field_width 1500
#define field_height 1300

#define Num_TankType 4
#define NumOfGrid (field_width / grid_width) * (field_height / grid_height) // 15 * 13 = 195

#endif // GLOBAL_H_INCLUDED
