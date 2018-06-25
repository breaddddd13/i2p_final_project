#include "GameWindow.h"
#include "global.h"
#include <iostream>
#include "Button.h"

#define WHITE al_map_rgb(255, 255, 255)
#define BLACK al_map_rgb(0, 0, 0)
#define ORANGE_LIGHT al_map_rgb(255, 196, 87)
#define ORANGE_DARK al_map_rgb(255, 142, 71)
#define PURPLE al_map_rgb(149, 128, 255)
#define BLUE al_map_rgb(77, 129, 179)
#define KHAKI al_map_rgb(189,183,107)

#define min(a, b) ((a) < (b)? (a) : (b))
#define max(a, b) ((a) > (b)? (a) : (b))


float Attack::volume = 1.0;

void set_attack_volume(float volume)
{
    Attack::volume = volume;
}

void
GameWindow::game_init()
{
    char buffer[50];
    
    icon = al_load_bitmap("./icon.png");
    background = al_load_bitmap("./StartBackground.jpg");
    startBGD = al_load_bitmap("./Background/startbackground.png");
    overBGD = al_load_bitmap("./Background/over_background.jpg");
    settingBGD = al_load_bitmap("./Background/settingbackground.png");
    
    if(!startBGD)std::cout<<"failed"<<std::endl;
    //    for(int i = 0; i < Num_TowerType; i++)
    //    {
    //        sprintf(buffer, "./Tower/%s.png", TowerClass[i]);
    //        tower[i] = al_load_bitmap(buffer);
    //    }
    
    al_set_display_icon(display, icon);
    al_reserve_samples(5);
    
    sample = al_load_sample("growl.wav");
    startSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(startSound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(startSound, al_get_default_mixer());
    
    sample = al_load_sample("8+9.ogg");
    backgroundSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(backgroundSound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(backgroundSound, al_get_default_mixer());
    
    sample = al_load_sample("./music/startmusic.wav");
    startBGM = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(startBGM, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(startBGM, al_get_default_mixer());
    
    sample = al_load_sample("./music/word_appear.wav");
    word_appear = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(word_appear, ALLEGRO_PLAYMODE_ONCE);
    al_set_sample_instance_gain(word_appear, 0.5);
    al_attach_sample_instance_to_mixer(word_appear, al_get_default_mixer());
    
    level = new LEVEL(1);
    menu = new Menu();
    
}

bool
GameWindow::mouse_hover(int startx, int starty, int width, int height)
{
    if(mouse_x >= startx && mouse_x <= startx + width)
        if(mouse_y >= starty && mouse_y <= starty + height)
            return true;
    
    return false;
}


//Monster*
//GameWindow::create_monster()
//{
//    Monster *m = NULL;
//
//    if(level->MonsterNum[WOLF])
//    {
//        level->MonsterNum[WOLF]--;
//        m = new Wolf(level->ReturnPath());
//    }
//    else if(level->MonsterNum[WOLFKNIGHT])
//    {
//        level->MonsterNum[WOLFKNIGHT]--;
//        m = new WolfKnight(level->ReturnPath());
//    }
//    else if(level->MonsterNum[DEMONNIJIA])
//    {
//        level->MonsterNum[DEMONNIJIA]--;
//        m = new DemonNijia(level->ReturnPath());
//    }
//    else if(level->MonsterNum[CAVEMAN])
//    {
//        level->MonsterNum[CAVEMAN]--;
//        m = new CaveMan(level->ReturnPath());
//    }
//    else
//    {
//        al_stop_timer(monster_pro);
//    }
//
//    return m;
//}

void
GameWindow::game_play()
{
    int msg;
    
    srand(time(NULL));
    
    msg = -1;
    
    /*
     *  We start the game by calling game_begin to start timer and play music
     * [TODO]:
     *     You may add some function to create starting scene before calling game_begin
     *     e.g: game_start_scene()
     */
//    game_start();
//    game_over();
    game_begin();
    
    /*
     *  while game is running, the result of game_run will be returned to msg.
     *  If msg is GAME_EXIT, then tower game will terminate.
     */
    while(msg != GAME_EXIT)
        msg = game_run();
    
    show_err_msg(msg);
}

void
GameWindow::show_err_msg(int msg)
{
    if(msg == GAME_TERMINATE)
        fprintf(stderr, "Game Terminated...");
    else
        fprintf(stderr, "unexpected msg: %d", msg);
    
    game_destroy();
    exit(9);
}

GameWindow::GameWindow()
{
    if (!al_init())
        show_err_msg(-1);
    printf("Game Initializing...\n");
    //    ALLEGRO_DISPLAY       *display = NULL;
    //    ALLEGRO_DISPLAY_MODE   disp_data;
    //    al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);
    //
    //    al_set_new_display_flags(ALLEGRO_FULLSCREEN);
    //    display = al_create_display(disp_data.width, disp_data.height);
    //
    
    display = al_create_display(window_width, window_height);
    event_queue = al_create_event_queue();
    
    /*
     * Create two timers to control different parts of tower game:
     *    a. timer: control the animation of each object, stopped when game doesn't run.
     */
    timer = al_create_timer(1.0 / FPS);
    
    if(timer == NULL)
        show_err_msg(-1);
    
    if (display == NULL || event_queue == NULL)
        show_err_msg(-1);
    
    al_init_primitives_addon();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon
    
    al_install_keyboard(); // install keyboard event
    al_install_mouse();    // install mouse event
    al_install_audio();    // install audio event
    
    font = al_load_ttf_font("./Font/BLKCHCRY.ttf",24,0); // load small font
    Medium_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",24,0); //load medium font
    Large_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",36,0); //load large font
    
    startFont = al_load_font("./Font/Cardiff.ttf", 280, 0);
    if(!startFont) std::cout<<"fuck\n";
    
    overFont = al_load_font("./Font/BLKCHCRY.TTF", 120, 0);
    
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    
    
    // Initializing resources that tower game needs.
    game_init();
}

void
GameWindow::game_begin()
{
    printf(">>> Start Level[%d]\n", level->getLevel());
    P1 = new BlueRoy((game_start_x + game_end_x)/4, (game_start_y + game_end_y)/2);
    P2 = new RedRoy(3*(game_start_x + game_end_x)/4, (game_start_y + game_end_y)/2);
    for(int i = 0; i < field_height/100; i++)
    {
        for(int j = 0; j < field_width/100 ; j++)
        {
            switch (level->getInfo(i, j)) {
                case 3:
                    ob[i][j] = new River((j + 1) * 100 + 20,(i + 1) * 100 + 20);
                    break;
                case 1:
                    ob[i][j] = new Wall((j + 1) * 100 + 20,(i + 1) * 100 + 20);
                    break;
                case 7:
                    ob[i][j] = new Grass((j + 1) * 100 + 20,(i + 1) * 100 + 20);
                    break;
                default:
                    ob[i][j] = new Obstacle((j + 1) * 100 + 20,(i + 1) * 100 + 20);
                    break;
            }
        }
    }
    draw_running_map();
    
    al_play_sample_instance(startSound);
    while(al_get_sample_instance_playing(startSound));
    al_play_sample_instance(backgroundSound);
    
    al_start_timer(timer);
}

int
GameWindow::game_run()
{
    int error = GAME_CONTINUE;
    
    if (!al_is_event_queue_empty(event_queue)) {
        
        error = process_event();
    }
    return error;
}

int
GameWindow::game_update()
{
    unsigned int i, j;
    
    if (pause) {
        return GAME_CONTINUE;
    }
    
    /*TODO:*/
    /*Allow towers to detect if monster enters its range*/
    /*Hint: Tower::DetectAttack*/
    
    
    
    // update every monster
    // check if it is destroyed or reaches end point
    
    
    /*TODO:*/
    /*1. For each tower, traverse its attack set*/
    /*2. If the monster collide with any attack, reduce the HP of the monster*/
    /*3. Remember to set isDestroyed to "true" if monster is killed*/
    /*Hint: Tower::TriggerAttack*/
    
    P1->UpdateAttack();
    P2->UpdateAttack();
    
    /*TODO:*/
    /*1. Update the attack set of each tower*/
    /*Hint: Tower::UpdateAttack*/
    
    
    return GAME_CONTINUE;
}

void
GameWindow::game_reset()
{
    // clear all towers
    
    
    
    Coin_Inc_Count = 0;
    mute = false;
    redraw = false;
    menu->Reset();
    
    // stop sample instance
    al_stop_sample_instance(backgroundSound);
    al_stop_sample_instance(startSound);
    
    // stop timer
    al_stop_timer(timer);
    
}

void
GameWindow::game_destroy()
{
    game_reset();
    
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_font(font);
    al_destroy_font(Medium_font);
    al_destroy_font(Large_font);
    
    al_destroy_timer(timer);
    
    
    al_destroy_bitmap(icon);
    al_destroy_bitmap(background);
    
    al_destroy_sample(sample);
    al_destroy_sample_instance(startSound);
    al_destroy_sample_instance(backgroundSound);
    
    delete level;
    delete menu;
}

int
GameWindow::process_event()
{
    int i;
    int instruction = GAME_CONTINUE;
    
    al_wait_for_event(event_queue, &event);
    redraw = false;
    
    if(event.type == ALLEGRO_EVENT_TIMER) {
        if(event.timer.source == timer) {
            redraw = true;
            
            if(Coin_Inc_Count == 0)
                menu->Change_Coin(Coin_Time_Gain);
            
            Coin_Inc_Count = (Coin_Inc_Count + 1) % CoinSpeed;
            
            // All monsters are created and destroyed -> Game Exit
            
            
        }
        else {
            
        }
    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        return GAME_EXIT;
    }
    else if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
        switch(event.keyboard.keycode) {
                
            case ALLEGRO_KEY_P:
                /* ToDo
                 * You can add some variable to control if game is paused.
                 * e.g: pause
                 * In addition to add variable, you also have to modify draw_running_map() and game_update()
                 * Or, monsters and towers can still work without being paused
                 */
        
                break;
            case ALLEGRO_KEY_M:
                mute = !mute;
                if(mute)
                    al_stop_sample_instance(backgroundSound);
                else
                    al_play_sample_instance(backgroundSound);
                break;
            case ALLEGRO_KEY_SPACE:
                P1->TriggerAttack();
                redraw = true;
                break;
            case ALLEGRO_KEY_ESCAPE:
                return GAME_EXIT;
            case ALLEGRO_KEY_RIGHT:
                
                return GAME_CONTINUE;
            case ALLEGRO_KEY_W:
                P1->move_valid(UP);
                
                redraw = true;
                break;
            case ALLEGRO_KEY_A:
                P1->move_valid(LEFT);
                redraw = true;
                break;
            case ALLEGRO_KEY_D:
                P1->move_valid(RIGHT);
                redraw = true;
                break;
            case ALLEGRO_KEY_S:
                P1->move_valid(DOWN);
                redraw = true;
                break;
            
        }
    }
    else if(event.type == ALLEGRO_EVENT_KEY_UP) {
        switch(event.keyboard.keycode) {
            case ALLEGRO_KEY_W:
                P1->move_invalid(UP);
                redraw = true;
                break;
            case ALLEGRO_KEY_A:
                P1->move_invalid(LEFT);
                redraw = true;
                break;
            case ALLEGRO_KEY_D:
                P1->move_invalid(RIGHT);
                redraw = true;
                break;
            case ALLEGRO_KEY_S:
                P1->move_invalid(DOWN);
                redraw = true;
                break;
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        if(event.mouse.button == 1) {
                        
            // check if user wants to create some kind of tower
            // if so, show tower image attached to cursor

        } else if (event.mouse.button == 2) {
            
            return GAME_CONTINUE;
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
        mouse_x = event.mouse.x;
        mouse_y = event.mouse.y;
        
        menu->MouseIn(mouse_x, mouse_y);
        
    }
    
    if(redraw) {
        // update each object in game
        instruction = game_update();
        
        // Re-draw map
        draw_running_map();
        redraw = false;
    }
    
    return instruction;
}

void
GameWindow::draw_running_map()
{
    unsigned int i, j;
    al_clear_to_color(al_map_rgb(100, 100, 100));
    //al_draw_bitmap(background, 0, 0, 0);
    al_draw_filled_rectangle(70, 70, 1570, 1370, KHAKI);
    
    
    
    
    P1->Draw();
    P2->Draw();
    for(i = 0; i < field_height/100; i++)
    {
        for(j = 0; j < field_width/100 ; j++)
        {
            if(level->getInfo(i, j) != 0){
                ob[i][j]->Draw();
            }
            
            char buffer[50];
            sprintf(buffer, "%d", i*15 + j);
            //            if(level->isRoad(i*15 + j)) {
            //                al_draw_filled_rectangle(j*40, i*40, j*40+40, i*40+40, al_map_rgb(255, 244, 173));
            //            }
            //            // For debug usage, if you want to create a new map, you may turn off this comment.
            //                 al_draw_text(font, al_map_rgb(0, 0, 0), (j+1)*100 + 20, (i+1)*100 + 20, ALLEGRO_ALIGN_CENTER, buffer);
        }
        //            printf("\n");
    
    
//    al_draw_filled_rectangle(field_width, 0, window_width, window_height, al_map_rgb(100, 100, 100));
    
    //    menu->Draw();
    }
    
    al_flip_display();
}

void GameWindow::game_start()
{
    int flag=0;
    al_play_sample_instance(startBGM);
    while(flag==0)
    {
        flag = draw_start_scene();
    }
}



int GameWindow::draw_start_scene()
{
    const double tank_pos_x_fin = window_width/2-500;
    const double game_pos_x_fin = window_width/2-50;
    const double button_pos_x_fin = window_width-400;
    static double tank_pos_x = -3000;
    static double game_pos_x = -3000;
    static double button_pos_x = window_width+3000;
    static double t = 1;
    static unsigned long long int counter = 0;
    if(counter <=300000)counter+=1;
    else counter = 0;
    
    static bool done1=false, done2=false, done3=false;
    if(counter%2 == 0)
    {
        if(tank_pos_x<=tank_pos_x_fin)tank_pos_x += 3*t+0.5*t*t;
        else done1 = true;
        if(game_pos_x<=game_pos_x_fin)game_pos_x += 3*t+0.5*t*t;
        else done2 = true;
        if(button_pos_x>=button_pos_x_fin)button_pos_x -= 3*t+t*t;
        else done3 = true;
        t+=0.00000000000001;
        //t= 0.5;
    }
    static Button start(button_pos_x, window_height-450 ,400,200, "START");
    static Button setting(button_pos_x, window_height-150 ,400, 200, "SETTING");
    //al_clear_to_color(WHITE);
    start.setPosition(button_pos_x, window_height-450);
    setting.setPosition(button_pos_x, window_height-150);
    al_draw_bitmap(startBGD, 0, 0, 0);
    al_draw_text(startFont, WHITE, tank_pos_x, 2*window_height/3-100, ALLEGRO_ALIGN_CENTER, "Tank");
    al_draw_text(startFont, WHITE, game_pos_x, 2*window_height/3+150, ALLEGRO_ALIGN_CENTER, "Game");
    al_play_sample_instance(startBGM);
    start.Draw();
    setting.Draw();
    al_flip_display();
    if(done1&&done2&&done3)
    {
        al_wait_for_event(event_queue, &event);
        
        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) exit(9);
        else if(event.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            if(start.selectButton(event.mouse.x, event.mouse.y))
            {
                start.setTextColor(BLACK);
                if(!start.ButtonVoice())
                {
                    start.playButtonVoice();
                    start.reButtonVoice();
                }
            }
            
            else
            {
                start.setTextColor(WHITE);
                if(start.ButtonVoice())
                    start.reButtonVoice();
            }
            
            if(setting.selectButton(event.mouse.x, event.mouse.y))
            {
                setting.setTextColor(BLACK);
                if(!setting.ButtonVoice())
                {
                    setting.playButtonVoice();
                    setting.reButtonVoice();
                }
            }
            
            else
            {
                setting.setTextColor(WHITE);
                if(setting.ButtonVoice())
                    setting.reButtonVoice();
            }
        }
        else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            if(start.selectButton(event.mouse.x, event.mouse.y))
            {
                al_stop_sample_instance(startBGM);
                return 1;
            }
            if(setting.selectButton(event.mouse.x, event.mouse.y))
                Setting();
        }
    }
    start.Draw();
    setting.Draw();
    
    return 0;
}

void GameWindow::game_over()
{
    int flag=0;
    
    while(flag==0)
    {
        flag = draw_over_scene();
    }
}

int GameWindow::draw_over_scene()
{
    static unsigned long long int counter=0;
    static bool canDo = false;
    static bool play1 = true;
    static bool play2 = true;
    static bool play3 = true;
    static bool play4 = true;
    al_draw_bitmap(overBGD, 0, 0, 0);
    if(counter>=600)
    {
        al_draw_text(overFont, WHITE, window_width/2, 50, ALLEGRO_ALIGN_CENTER, "SCORE");
        if(play1)
        {
            al_play_sample_instance(word_appear);
            play1 = false;
        }
        if(counter>=1000)
        {
            al_draw_text(overFont, WHITE, 100, 300, ALLEGRO_ALIGN_CENTER, "p1:");
            if(play2)
            {
                al_play_sample_instance(word_appear);
                play2 = false;
            }
            if(counter>=1400)
            {
                al_draw_text(overFont, WHITE, 100, 700, ALLEGRO_ALIGN_CENTER, "p2:");
                if(play3)
                {
                    al_play_sample_instance(word_appear);
                    play3 = false;
                }
                if(counter>=1800)
                {
                    al_draw_text(overFont, WHITE, window_width/2, window_height-200, ALLEGRO_ALIGN_CENTER, "press enter to continue");
                    if(play4)
                    {
                        al_play_sample_instance(word_appear);
                        play4 = false;
                    }
                    canDo = true;
                }
                //canDo = true;
            }
            //canDo = true;
        }
        
    }
    if(counter == 3000000) counter = 3000000;
    else counter++;
    al_flip_display();
    if(canDo)
    {
        al_wait_for_event(event_queue, &event);
        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) exit(9);
        else if(event.type == ALLEGRO_EVENT_KEY_DOWN)
            if(event.keyboard.keycode == ALLEGRO_KEY_ENTER)
                return 1;
    }
    return 0;
}

void GameWindow::Setting()
{
    int flag = 0;
    while(flag == 0)
    {
        flag = draw_setting_scene();
    }
}

int GameWindow::draw_setting_scene()
{
    al_draw_bitmap(settingBGD, 0, 0, 0);
    //al_draw_filled_rounded_rectangle(0, 0, window_width, window_height, 0, 0, al_map_rgba(0, 0, 0, 20));
    al_flip_display();
    al_wait_for_event(event_queue, &event);
    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) exit(9);
    return 0;
}

/*bool GameWindow::move_judge(BaseTank* tank, Obstacle* obs)
{
    if(obs->TankAva())
        
    return true;
}*/
