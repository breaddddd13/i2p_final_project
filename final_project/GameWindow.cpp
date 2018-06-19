#include "GameWindow.h"
#include "global.h"
#include <iostream>

#define WHITE al_map_rgb(255, 255, 255)
#define BLACK al_map_rgb(0, 0, 0)
#define ORANGE_LIGHT al_map_rgb(255, 196, 87)
#define ORANGE_DARK al_map_rgb(255, 142, 71)
#define PURPLE al_map_rgb(149, 128, 255)
#define BLUE al_map_rgb(77, 129, 179)

#define min(a, b) ((a) < (b)? (a) : (b))
#define max(a, b) ((a) > (b)? (a) : (b))


float Attack::volume = 1.0;

void set_attack_volume(float volume)
{
    Attack::volume = volume;
}

//bool compare(Tower *t1, Tower *t2)
//{
//    return (t1->getY() <= t2->getY());
//}

void
GameWindow::game_init()
{
    char buffer[50];
    
    icon = al_load_bitmap("./icon.png");
    background = al_load_bitmap("./StartBackground.jpg");
    
    
    for(int i = 0; i < Num_TowerType; i++)
    {
        sprintf(buffer, "./Tower/%s.png", TowerClass[i]);
        tower[i] = al_load_bitmap(buffer);
    }
    
    al_set_display_icon(display, icon);
    al_reserve_samples(3);
    
    sample = al_load_sample("growl.wav");
    startSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(startSound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(startSound, al_get_default_mixer());
    
    sample = al_load_sample("BackgroundMusic.ogg");
    backgroundSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(backgroundSound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(backgroundSound, al_get_default_mixer());
    
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

bool
GameWindow::isOnRoad()
{
    int startx, starty;
    int widthOfTower;
    
    widthOfTower = TowerWidth[selectedTower];
    
    for(int i=0; i < NumOfGrid; i++)
    {
        startx = (i % 15) * 40;
        starty = (i / 15) * 40;
        
        if(level->isRoad(i)) {
            if((mouse_x + (widthOfTower/2) < startx) || (mouse_x - (widthOfTower/2) > startx + grid_width))
                continue;
            else if((mouse_y + (widthOfTower/2) < starty) || (mouse_y > starty + grid_height))
                continue;
            else
                return true;
        }
    }
    return false;
}

Tower*
GameWindow::create_tower(int type)
{
    Tower *t = NULL;
    
    if(isOnRoad())
        return t;
    
    switch(type)
    {
        case ARCANE:
            t = new Arcane(mouse_x, mouse_y);
            break;
        case ARCHER:
            t = new Archer(mouse_x, mouse_y);
            break;
        case CANON:
            t = new Canon(mouse_x, mouse_y);
            break;
        case POISON:
            t = new Poison(mouse_x, mouse_y);
            break;
        case STORM:
            t = new Storm(mouse_x, mouse_y);
            break;
        case MAGMA:
            t = new Magma(mouse_x, mouse_y);
            break;
        default:
            break;
    }
    
    menu->Change_Coin(menu->getTowerCoin(type));
    
    return t;
}

Monster*
GameWindow::create_monster()
{
    Monster *m = NULL;
    
    if(level->MonsterNum[WOLF])
    {
        level->MonsterNum[WOLF]--;
        m = new Wolf(level->ReturnPath());
    }
    else if(level->MonsterNum[WOLFKNIGHT])
    {
        level->MonsterNum[WOLFKNIGHT]--;
        m = new WolfKnight(level->ReturnPath());
    }
    else if(level->MonsterNum[DEMONNIJIA])
    {
        level->MonsterNum[DEMONNIJIA]--;
        m = new DemonNijia(level->ReturnPath());
    }
    else if(level->MonsterNum[CAVEMAN])
    {
        level->MonsterNum[CAVEMAN]--;
        m = new CaveMan(level->ReturnPath());
    }
    else
    {
        al_stop_timer(monster_pro);
    }
    
    return m;
}

void GameWindow::game_setting(){
    Slider *bgm_slider = NULL;
    Slider *effect_slider = NULL;
    int msg;
    char s[] = "BackgroundSound";
    char t[] = "Effects";
    msg = -1;
    
    al_draw_filled_rectangle(0, 0, 800, 600, BLUE);
    
    //set bgm_slider
    bgm_slider = new Slider(window_width/2, window_height/3);
    bgm_slider->set_label_content(s);
    bgm_slider->Draw();
    
    //set effects
    effect_slider = new Slider(window_width/2, window_height/3 + 100);
    effect_slider->set_label_content(t);
    effect_slider->Draw();
    
    al_flip_display();
    
    while (1) {
        al_wait_for_event(event_queue, &event);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            show_err_msg(GAME_EXIT);
        } else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            if (event.mouse.button == 1) {
                if (bgm_slider->isClicked(mouse_x, mouse_y)) {
                    bgm_slider->toggleDrag();
                } else if (effect_slider->isClicked(mouse_x, mouse_y)){
                    effect_slider->toggleDrag();
                }
            }
        } else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
            if (bgm_slider->isDragged()) {
                bgm_slider->toggleDrag();
            } else if(effect_slider->isDragged()){
                effect_slider->toggleDrag();
            }
        } else if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
            mouse_x = event.mouse.x;
            mouse_y = event.mouse.y;
            if (bgm_slider->isDragged() || effect_slider->isDragged()) {
                if (bgm_slider->isDragged()) {
                    bgm_slider->Drag(mouse_x, mouse_y);
                    al_set_sample_instance_gain(backgroundSound, bgm_slider->getDegree());
                } else {
                    effect_slider->Drag(mouse_x, mouse_y);
                    set_attack_volume(effect_slider->getDegree());
                }
                al_draw_filled_rectangle(0, 0, 800, 600, BLUE);
                bgm_slider->Draw();
                effect_slider->Draw();
                al_flip_display();
            }
        }
        if (event.type == ALLEGRO_EVENT_KEY_DOWN){
            switch(event.keyboard.keycode) {
                case ALLEGRO_KEY_ESCAPE:
                    return;
            }
        }
    }
    
    
    
}

void GameWindow::game_start_scene(){
    
    Dragon *D = new Dragon();
    al_start_timer(dragon_pro);
    
    Button *start_bt = new Button(125, 50);
    Button *setting_bt = new Button(125, 50);
    Button *exit_bt = new Button(125, 50);
    
    char ft[] = "./LifeCraft_Font.ttf";
    char s[] = "start";
    char t[] = "setting";
    char r[] = "exit";
    int start_msg;
    
    start_msg = -1;
    
    startBGD = al_load_bitmap("./startBGD.png");
    startFont = al_load_ttf_font("./LifeCraft_Font.ttf", 96, 0);
    al_play_sample_instance(backgroundSound);
    al_draw_bitmap(startBGD, 0, 0, 0);
    al_draw_text(startFont, ORANGE_LIGHT, window_width/2, window_height/7.0, ALLEGRO_ALIGN_CENTER, "TowerGame");
    
    
    //set start_button and draw
    start_bt->setPosition(window_width/2, window_height/2);
    start_bt->setFont(ft, 48);
    start_bt->setColor(al_map_rgba(0, 0, 0, 1.0));
    start_bt->setText(s);
    
    
    //set setting_button and draw
    setting_bt->setPosition(window_width/2, window_height/2 + 60);
    setting_bt->setFont(ft, 48);
    setting_bt->setColor(al_map_rgba(0, 0, 0, 1.0));
    setting_bt->setText(t);
    
    //set exit_button
    exit_bt->setPosition(window_width/2, window_height/2 + 120);
    exit_bt->setFont(ft, 48);
    exit_bt->setColor(al_map_rgba(0, 0, 0, 1.0));
    exit_bt->setText(r);
    
    
    
    while (1) {
        al_draw_bitmap(startBGD, 0, 0, 0);
        al_draw_text(startFont, ORANGE_LIGHT, window_width/2, window_height/7.0, ALLEGRO_ALIGN_CENTER, "TowerGame");
        start_bt->Draw();
        setting_bt->Draw();
        exit_bt->Draw();
        D->Draw();
        al_flip_display();
        
        if (!al_is_event_queue_empty(event_queue)) {
            al_wait_for_event(event_queue, &event);
            if (event.type == ALLEGRO_EVENT_TIMER) {
                D->Move();
            }else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                show_err_msg(GAME_EXIT);
            } else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                if (event.mouse.button == 1) {
                    if ( start_bt->selectButton(mouse_x, mouse_y) ) {
                        al_stop_timer(dragon_pro);
                        return;
                    } else if ( setting_bt->selectButton(mouse_x, mouse_y) ) {
                        game_setting();
                    } else if ( exit_bt->selectButton(mouse_x, mouse_y) ) {
                        show_err_msg(GAME_EXIT);
                    }
                }
            } else if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
                
                mouse_x = event.mouse.x;
                mouse_y = event.mouse.y;
                if (setting_bt->selectButton(mouse_x, mouse_y)) {
                    setting_bt->setTextColor(ORANGE_DARK);
                } else if (start_bt->selectButton(mouse_x, mouse_y)) {
                    start_bt->setTextColor(ORANGE_DARK);
                    D->speed = 5;
                } else if ( exit_bt->selectButton(mouse_x, mouse_y) ) {
                    exit_bt->setTextColor(ORANGE_DARK);
                    al_stop_timer(dragon_pro);
                } else {
                    setting_bt->setTextColor(ORANGE_LIGHT);
                    exit_bt->setTextColor(ORANGE_LIGHT);
                    start_bt->setTextColor(ORANGE_LIGHT);
                    D->speed = 3;
                    al_resume_timer(dragon_pro);
                }
            } else if (event.type == ALLEGRO_EVENT_KEY_DOWN){
                switch(event.keyboard.keycode) {
                    case ALLEGRO_KEY_ESCAPE:
                        start_msg = GAME_EXIT;
                        show_err_msg(start_msg);
                }
            }
            
        }
        
        
    }
    
}

void GameWindow::game_win(){
    
    Button *exit_bt = new Button(125, 50);
    Button *nextLevel = new Button(125, 50);
    ALLEGRO_FONT *Font = al_load_ttf_font("./LifeCraft_Font.ttf", 76, 0);;
    
    char ft[] = "./LifeCraft_Font.ttf";
    char s[] = "next";
    char t[] = "exit";
    
    
    overBGD = al_load_bitmap("./Frozen_Throne.jpg");
    
    //set exit_button
    nextLevel->setPosition(window_width/4, window_height/2.5);
    nextLevel->setFont(ft, 48);
    nextLevel->setColor(al_map_rgba(0, 0, 0, 1.0));
    nextLevel->setText(s);
    
    //set exit_button
    exit_bt->setPosition(window_width/4, window_height/2.5 + 70);
    exit_bt->setFont(ft, 48);
    exit_bt->setColor(al_map_rgba(0, 0, 0, 1.0));
    exit_bt->setText(t);
    
    
    while (1) {
        
        al_draw_bitmap(overBGD, 0, 0, 0);
        al_draw_text(Font, ORANGE_LIGHT, window_width/4, window_height/7.0, ALLEGRO_ALIGN_CENTER, "Game Win!");
        exit_bt->Draw();
        nextLevel->Draw();
        al_flip_display();
        
        al_wait_for_event(event_queue, &event);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            show_err_msg(GAME_EXIT);
        } else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            if (event.mouse.button == 1) {
                if ( exit_bt->selectButton(mouse_x, mouse_y) ) {
                    show_err_msg(GAME_EXIT);
                } else if (nextLevel->selectButton(mouse_x, mouse_y)) {
                    levelNum++;
                    if (levelNum == 5) {
                        show_err_msg(GAME_EXIT);
                    }
                    level->setLevel(levelNum);
                    game_reset();
                    game_begin();
                    return;
                }
            }
        } else if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
            mouse_x = event.mouse.x;
            mouse_y = event.mouse.y;
            if ( exit_bt->selectButton(mouse_x, mouse_y) ) {
                exit_bt->setTextColor(ORANGE_DARK);
            } else {
                exit_bt->setTextColor(ORANGE_LIGHT);
            }
            if (nextLevel->selectButton(mouse_x, mouse_y)) {
                nextLevel->setTextColor(ORANGE_DARK);
            } else {
                nextLevel->setTextColor(ORANGE_LIGHT);
            }
        } else if (event.type == ALLEGRO_EVENT_KEY_DOWN){
            switch(event.keyboard.keycode) {
                case ALLEGRO_KEY_ESCAPE:
                    show_err_msg(GAME_EXIT);
            }
        }
    }
}

void GameWindow::game_over(){
    Button *exit_bt = new Button(125, 50);
    Button *nextLevel = new Button(125, 50);
    
    char ft[] = "./LifeCraft_Font.ttf";
    char s[] = "restart";
    char t[] = "exit";
    
    overBGD = al_load_bitmap("./WoW.jpg");
    
    //set exit_button
    nextLevel->setPosition(window_width/3, window_height/2.25);
    nextLevel->setFont(ft, 48);
    nextLevel->setColor(al_map_rgba(0, 0, 0, 1.0));
    nextLevel->setText(s);
    
    //set exit_button
    exit_bt->setPosition(window_width/3, window_height/2.25 + 70);
    exit_bt->setFont(ft, 48);
    exit_bt->setColor(al_map_rgba(0, 0, 0, 1.0));
    exit_bt->setText(t);
    
    
    while (1) {
        
        al_draw_bitmap(overBGD, 0, 0, 0);
        al_draw_text(startFont, ORANGE_LIGHT, window_width/3, window_height/7.0, ALLEGRO_ALIGN_CENTER, "You Suck!");
        exit_bt->Draw();
        nextLevel->Draw();
        al_flip_display();
        
        al_wait_for_event(event_queue, &event);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            show_err_msg(GAME_EXIT);
        } else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            if (event.mouse.button == 1) {
                if ( exit_bt->selectButton(mouse_x, mouse_y) ) {
                    show_err_msg(GAME_EXIT);
                } else if (nextLevel->selectButton(mouse_x, mouse_y)) {
                    level->setLevel(levelNum);
                    game_reset();
                    game_begin();
                    return;
                }
            }
        } else if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
            mouse_x = event.mouse.x;
            mouse_y = event.mouse.y;
            if ( exit_bt->selectButton(mouse_x, mouse_y) ) {
                exit_bt->setTextColor(ORANGE_DARK);
            } else {
                exit_bt->setTextColor(ORANGE_LIGHT);
            }
            if (nextLevel->selectButton(mouse_x, mouse_y)) {
                nextLevel->setTextColor(ORANGE_DARK);
            } else {
                nextLevel->setTextColor(ORANGE_LIGHT);
            }
        } else if (event.type == ALLEGRO_EVENT_KEY_DOWN){
            switch(event.keyboard.keycode) {
                case ALLEGRO_KEY_ESCAPE:
                    show_err_msg(GAME_EXIT);
            }
        }
    }
}

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
    game_start_scene();
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
    al_resize_display(display, window_width/2, window_height/2);
    event_queue = al_create_event_queue();
    
    /*
     * Create two timers to control different parts of tower game:
     *    a. timer: control the animation of each object, stopped when game doesn't run.
     *    b. monster_pro: control the production of monster, stopped when there is no need to produce monster.
     */
    timer = al_create_timer(1.0 / FPS);
    monster_pro = al_create_timer(1.0 * 80 / FPS);
    dragon_pro = al_create_timer(1.0 / FPS);
    
    if(timer == NULL || monster_pro == NULL)
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
    
    font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",12,0); // load small font
    Medium_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",24,0); //load medium font
    Large_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",36,0); //load large font
    
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_timer_event_source(monster_pro));
    al_register_event_source(event_queue, al_get_timer_event_source(dragon_pro));
    
    // Initializing resources that tower game needs.
    game_init();
}

void
GameWindow::game_begin()
{
    printf(">>> Start Level[%d]\n", level->getLevel());
    draw_running_map();
    
    al_play_sample_instance(startSound);
    while(al_get_sample_instance_playing(startSound));
    al_play_sample_instance(backgroundSound);
    
    al_start_timer(timer);
    al_start_timer(monster_pro);
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
    std::list<Tower*>::iterator it;
    
    if (pause) {
        return GAME_CONTINUE;
    }
    
    /*TODO:*/
    /*Allow towers to detect if monster enters its range*/
    /*Hint: Tower::DetectAttack*/
    for (int i=0; i<monsterSet.size(); i++) {
        for (it = towerSet.begin(); it != towerSet.end(); it++) {
            if ( (*it)->DetectAttack(monsterSet[i]) ) {
                (*it)->Draw();
            }
        }
    }
    
    // update every monster
    // check if it is destroyed or reaches end point
    for(i=0; i < monsterSet.size(); i++)
    {
        bool isDestroyed = false, isReachEnd = false;
        
        /*TODO:*/
        /*1. For each tower, traverse its attack set*/
        /*2. If the monster collide with any attack, reduce the HP of the monster*/
        /*3. Remember to set isDestroyed to "true" if monster is killed*/
        /*Hint: Tower::TriggerAttack*/
        for (it = towerSet.begin(); it != towerSet.end(); it++) {
            if ( (*it)->TriggerAttack(monsterSet[i]) ) {
                isDestroyed = true;
            }
        }
        
        
        isReachEnd = monsterSet[i]->Move();
        
        if(isDestroyed)
        {
            Monster *m = monsterSet[i];
            
            menu->Change_Coin(m->getWorth());
            menu->Gain_Score(m->getScore());
            monsterSet.erase(monsterSet.begin() + i);
            i--;
            delete m;
            
        }
        else if(isReachEnd)
        {
            Monster *m = monsterSet[i];
            
            if(menu->Subtract_HP()){
                game_over();
            }
            
            monsterSet.erase(monsterSet.begin() + i);
            i--;
            delete m;
        }
    }
    
    /*TODO:*/
    /*1. Update the attack set of each tower*/
    /*Hint: Tower::UpdateAttack*/
    for (it = towerSet.begin(); it != towerSet.end(); it++) {
        (*it)->UpdateAttack();
    }
    
    return GAME_CONTINUE;
}

void
GameWindow::game_reset()
{
    // clear all towers
    for(auto&& child : towerSet) {
        delete child;
    }
    towerSet.clear();
    monsterSet.clear();
    
    selectedTower = -1;
    lastClicked = -1;
    Coin_Inc_Count = 0;
    mute = false;
    redraw = false;
    menu->Reset();
    
    // stop sample instance
    al_stop_sample_instance(backgroundSound);
    al_stop_sample_instance(startSound);
    
    // stop timer
    al_stop_timer(timer);
    al_stop_timer(monster_pro);
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
    al_destroy_timer(monster_pro);
    
    for(int i=0;i<5; i++)
        al_destroy_bitmap(tower[i]);
    
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
            if(monsterSet.size() == 0 && !al_get_timer_started(monster_pro))
            {
                game_win();
                return GAME_CONTINUE;
            }
            
        }
        else {
            Monster *m = create_monster();
            
            if(m != NULL)
                monsterSet.push_back(m);
        }
    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        return GAME_EXIT;
    }
    else if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
        switch(event.keyboard.keycode) {
                
            case ALLEGRO_KEY_P:
                /*
                 * You can add some variable to control if game is paused.
                 * e.g: pause
                 * In addition to add variable, you also have to modify draw_running_map() and game_update()
                 * Or, monsters and towers can still work without being paused
                 */
                pause = !pause;
                if (pause) {
                    al_stop_timer(monster_pro);
                } else {
                    al_resume_timer(monster_pro);
                }
                
                break;
            case ALLEGRO_KEY_M:
                mute = !mute;
                if(mute)
                    al_stop_sample_instance(backgroundSound);
                else
                    al_play_sample_instance(backgroundSound);
                break;
            case ALLEGRO_KEY_ESCAPE:
                return GAME_EXIT;
            case ALLEGRO_KEY_RIGHT:
                game_over();
                return GAME_CONTINUE;
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        if(event.mouse.button == 1) {
            //click button
            
            
            
            // Create tower
            if(selectedTower != -1 && mouse_hover(0, 0, field_width, field_height)) {
                Tower *t = create_tower(selectedTower);
                
                if(t == NULL)
                    printf("Guava Wrong place\n");
                else {
                    towerSet.push_back(t);
                    towerSet.sort(compare);
                }
            }
            /*
             *  Check if any tower is clicked.
             *  If so, cancel the shown circle range of the tower.
             *  In addition, we also re-check if any circle range should show up.
             */
            else if(selectedTower == -1){
                std::list<Tower*>::iterator it = towerSet.begin();
                if(lastClicked != -1)
                {
                    std::advance(it, lastClicked);
                    (*it)->ToggleClicked();
                }
                for(i=0, it = towerSet.begin(); it != towerSet.end(); it++, i++)
                {
                    Circle *circle = (*it)->getCircle();
                    int t_width = (*it)->getWidth();
                    
                    if(mouse_hover(circle->x - t_width/2, circle->y, t_width, t_width/2))
                    {
                        (*it)->ToggleClicked();
                        lastClicked = i;
                        break;
                    } else {
                        lastClicked = -1;
                    }
                }
                
            }
            // check if user wants to create some kind of tower
            // if so, show tower image attached to cursor
            selectedTower = menu->MouseIn(mouse_x, mouse_y);
            
        } else if (event.mouse.button == 2) {
            menu->Change_Coin(100);
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
    al_draw_bitmap(background, 0, 0, 0);
    
    for(i = 0; i < field_height/40; i++)
    {
        for(j = 0; j < field_width/40; j++)
        {
            char buffer[50];
            sprintf(buffer, "%d", i*15 + j);
            if(level->isRoad(i*15 + j)) {
                al_draw_filled_rectangle(j*40, i*40, j*40+40, i*40+40, al_map_rgb(255, 244, 173));
            }
            // For debug usage, if you want to create a new map, you may turn off this comment.
            // al_draw_text(font, al_map_rgb(0, 0, 0), j*40 + 20, i*40 + 14, ALLEGRO_ALIGN_CENTER, buffer);
        }
    }
    for(i=0; i<monsterSet.size(); i++)
    {
        monsterSet[i]->Draw();
    }
    
    
    for(std::list<Tower*>::iterator it = towerSet.begin(); it != towerSet.end(); it++)
        (*it)->Draw();
    
    if (!pause) {
        if(selectedTower != -1)
            Tower::SelectedTower(mouse_x, mouse_y, selectedTower);
    }
    
    
    al_draw_filled_rectangle(field_width, 0, window_width, window_height, al_map_rgb(100, 100, 100));
    
    menu->Draw();
    
    
    al_flip_display();
}
