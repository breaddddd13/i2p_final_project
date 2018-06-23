#ifndef MAINWINDOW_H_INCLUDED
#define MAINWINDOW_H_INCLUDED

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <vector>
#include <list>
#include <time.h>
#include "Menu.h"
#include "Level.h"
#include "Attack.h"
#include "Slider.h"
#include "Button.h"
//#include "BaseTank.h"


#define GAME_INIT -1
#define GAME_SETTING 0
#define GAME_SELECT 1
#define GAME_BEGIN 2
#define GAME_CONTINUE 3
#define GAME_FAIL 4
#define GAME_TERMINATE 5
#define GAME_NEXT_LEVEL 6
#define GAME_EXIT 7
#define GAME_BACK 8


// clock rate
const float FPS = 60;

// total number of level
const int LevelNum = 4;

// 1 coin every 2 seconds
const int CoinSpeed = FPS * 2;
const int Coin_Time_Gain = 1;

class GameWindow
{
public:
    // constructor
    GameWindow();
    // each process of scene
    void game_init();
    void game_reset();
    void game_play();
    void game_begin();
/*ToDo: 景僕
 remember to insert the function below on the right space.
 
    void game_start_scene();
    void game_setting();
    void game_win();
    void game_finish();
*/
    int game_run();
    int game_update();
    
    void show_err_msg(int msg);
    void game_destroy();
    
    // draw running game map
    void draw_running_map();
    
    // process of updated event
    int process_event();
    // detect if mouse hovers over a rectangle
    bool mouse_hover(int, int, int, int);
    
//    Tower* create_tower(int);
//    Monster* create_monster();
    
public:
    bool initial = true;
    
    
private:
    ALLEGRO_BITMAP *icon;
    ALLEGRO_BITMAP *tower[Num_TankType];
    ALLEGRO_BITMAP *background = NULL;
    ALLEGRO_BITMAP *startBGD = NULL;
    ALLEGRO_BITMAP *overBGD = NULL;
    
    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_FONT *font = NULL;
    ALLEGRO_FONT *Medium_font = NULL;
    ALLEGRO_FONT *Large_font = NULL;
    ALLEGRO_FONT *startFont = NULL;
    
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_EVENT event;
    ALLEGRO_TIMER *timer = NULL;

    
    ALLEGRO_SAMPLE *sample = NULL;
    ALLEGRO_SAMPLE_INSTANCE *startSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *clearSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *failSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *backgroundSound = NULL;
    
    LEVEL *level = NULL;
    Menu *menu = NULL;
    
    
    
    
//    std::vector<Monster*> monsterSet;
//    std::list<Tower*> towerSet;
    
    int Coin_Inc_Count = 0;
    int mouse_x, mouse_y;
    int levelNum = 1;
    
    bool redraw = false;
    bool mute = false;
    bool pause = false;
};


#endif // MAINWINDOW_H_INCLUDED
