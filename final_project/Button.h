////
////  Button.h
////  miniProject_2
////
////  Created by 馮謙 on 2018/5/30.
////  Copyright © 2018年 馮謙. All rights reserved.
////
//
//#ifndef Button_h
//#define Button_h
//
//#define WHITE al_map_rgb(255, 255, 255)
//#define BLACK al_map_rgb(0, 0, 0)
//#define ORANGE_LIGHT al_map_rgb(255, 196, 87)
//#define ORANGE_DARK al_map_rgb(255, 142, 71)
//#define PURPLE al_map_rgb(149, 128, 255)
//#define BLUE al_map_rgb(77, 129, 179)
//#include <allegro5/allegro_font.h>
//#include <allegro5/allegro_ttf.h>
//#include <allegro5/allegro.h>
//#include <allegro5/allegro_image.h>
//#include <allegro5/allegro_primitives.h>
//#include <stdlib.h>
//
//class Button
//{
//public:
//    Button(float x, float y, float Width, float Height, char* word){
//        center_x = x;
//        center_y = y;
//        topLeft_x = x - width/2;;
//        topLeft_y = y - height/2;
//        width = Width;
//        height = Height;
//        bottomRight_x = topLeft_x + width;
//        bottomRight_y = topLeft_y + height;
//        center_x = topLeft_x + width/2;
//        center_y = topLeft_y + height/2;
//        strcpy(text, word);
//        color = al_map_rgb(255, 255, 255);
//        textColor = ORANGE_LIGHT;
//        font = al_load_ttf_font("./Font/Cardiff.ttf", 70, 0);
//    };
//    ~Button()
//    {
//
//    }
//    void setWH(float Width, float Height){
//        width = Width;
//        height = Height;
//    }
//    void setColor(ALLEGRO_COLOR Color){
//        color = Color;
//    }
//    void setTextColor(ALLEGRO_COLOR Color){
//        textColor = Color;
//    }
//    void setFont( char *s, int size){
//        font = al_load_ttf_font(s, size, 0);
//    }
//    void setText( char *s ){
//        strcpy(text, s);
//    }
//    void setPosition( float x, float y ){
//        center_x = x;
//        center_y = y;
//        topLeft_x = center_x - width/2;
//        topLeft_y = center_y - height/2;
//        bottomRight_x = topLeft_x + width;
//        bottomRight_y = topLeft_y + height;
//    }
//    void Draw(){
//        al_draw_filled_rectangle(topLeft_x, topLeft_y, bottomRight_x, bottomRight_y, color);
//        al_draw_text(font, textColor, center_x, center_y - al_get_font_line_height(font)/2, ALLEGRO_ALIGN_CENTRE, text);
//
//    }
//    bool selectButton(int mouse_x, int mouse_y){
//        if(mouse_x >= topLeft_x && mouse_x <= topLeft_x + width){
//            if(mouse_y >= topLeft_y && mouse_y <= topLeft_y + height)
//                return true;
//        }
//        return false;
//    }
//private:
//    float topLeft_x;
//    float topLeft_y;
//    float width;
//    float height;
//    float bottomRight_x;
//    float bottomRight_y;
//    float center_x;
//    float center_y;
//    char text[50];
//    ALLEGRO_COLOR color, textColor;
//    ALLEGRO_FONT *font = NULL;
//};
//
//
//#endif /* Button_h */

//
//  Button.h
//  miniProject_2
//
//  Created by 馮謙 on 2018/5/30.
//  Copyright © 2018年 馮謙. All rights reserved.
//

#ifndef Button_h
#define Button_h

#define WHITE al_map_rgb(255, 255, 255)
#define BLACK al_map_rgb(0, 0, 0)
#define ORANGE_LIGHT al_map_rgb(255, 196, 87)
#define ORANGE_DARK al_map_rgb(255, 142, 71)
#define PURPLE al_map_rgb(149, 128, 255)
#define BLUE al_map_rgb(77, 129, 179)
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdlib.h>

class Button
{
public:
    Button(float x, float y, float Width, float Height, char* word){
        center_x = x;
        center_y = y;
        topLeft_x = x - width/2;;
        topLeft_y = y - height/2;
        width = Width;
        height = Height;
        bottomRight_x = topLeft_x + width;
        bottomRight_y = topLeft_y + height;
        center_x = topLeft_x + width/2;
        center_y = topLeft_y + height/2;
        strcpy(text, word);
        color = WHITE;
        textColor = WHITE;
        font = al_load_ttf_font("./Font/Cardiff.ttf", 110, 0);
        background = al_load_bitmap("./Background/button_background.jpg");
        ALLEGRO_SAMPLE *sample = al_load_sample("./music/button_voice.wav");
        buttonvoice = al_create_sample_instance(sample);
        al_set_sample_instance_playmode(buttonvoice, ALLEGRO_PLAYMODE_ONCE);
        al_attach_sample_instance_to_mixer(buttonvoice, al_get_default_mixer());
    };
    ~Button()
    {
        
    }
    void setWH(float Width, float Height){
        width = Width;
        height = Height;
    }
    void setColor(ALLEGRO_COLOR Color){
        color = Color;
    }
    void setTextColor(ALLEGRO_COLOR Color){
        textColor = Color;
    }
    void setFont( char *s, int size){
        font = al_load_ttf_font(s, size, 0);
    }
    void setText( char *s ){
        strcpy(text, s);
    }
    void setPosition( float x, float y ){
        center_x = x;
        center_y = y;
        topLeft_x = center_x - width/2;
        topLeft_y = center_y - height/2;
        bottomRight_x = topLeft_x + width;
        bottomRight_y = topLeft_y + height;
    }
    void Draw(){
        al_draw_filled_rectangle(topLeft_x, topLeft_y, bottomRight_x, bottomRight_y, color);
        al_draw_bitmap(background, topLeft_x, topLeft_y, 0);
        al_draw_text(font, textColor, center_x, center_y - al_get_font_line_height(font)/2, ALLEGRO_ALIGN_CENTRE, text);
        
    }
    bool selectButton(int mouse_x, int mouse_y){
        if(mouse_x >= topLeft_x && mouse_x <= topLeft_x + width){
            if(mouse_y >= topLeft_y && mouse_y <= topLeft_y + height)
                return true;
        }
        return false;
    }
    void playButtonVoice()
    {
        al_play_sample_instance(buttonvoice);
    }
    bool ButtonVoice(){return buttonVoice;}
    void reButtonVoice(){buttonVoice = !buttonVoice;}
private:
    float topLeft_x;
    float topLeft_y;
    float width;
    float height;
    float bottomRight_x;
    float bottomRight_y;
    float center_x;
    float center_y;
    char text[50];
    bool buttonVoice = false;
    ALLEGRO_COLOR color, textColor;
    ALLEGRO_FONT *font = NULL;
    ALLEGRO_BITMAP *background = NULL;
    ALLEGRO_SAMPLE_INSTANCE *buttonvoice = NULL;
};


#endif /* Button_h */

