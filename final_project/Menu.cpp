#include "Menu.h"

const int ThumbWidth = 100;
const int ThumbHeight = 100;
const int gapX = 40, gapY = 30;
const int offsetX = 30 + field_width, offsetY = 150;
const int Initial_Health = 10;
const int Initial_Coin = 10;

bool
Menu::isInRange(int point, int startPos, int length)
{
    if(point >= startPos && point <= startPos + length)
        return true;
    
    return false;
}

Menu::Menu()
{
    char filename[50];
    
    HealthPoint = Initial_Health;
    Coin = Initial_Coin;
    Score = 0;
    
    for(int i=1;i<=Num_TankType; i++)
    {
        ALLEGRO_BITMAP *tank;
        sprintf(filename, "./RedTank/%d_Menu.png", i);
        
        tank = al_load_bitmap(filename);
        menu_tank.push_back(tank);
    }
    
    love = al_load_bitmap("./RedTank/love.png");
    
    menuFont = al_load_ttf_font("pirulen.ttf", 12, 0); // load font
}

Menu::~Menu()
{
    al_destroy_bitmap(love);
    al_destroy_font(menuFont);
    
    for(int i=0; i < Num_TankType; i++)
        al_destroy_bitmap(menu_tank[i]);
    
    menu_tank.clear();
}

void
Menu::Reset()
{
    HealthPoint = Initial_Health;
    Coin = Initial_Coin;
    Score = 0;
    killedTank = 0;
}

void
Menu::Draw()
{
    char buffer[50];
    
    sprintf(buffer, "%d", HealthPoint);
    al_draw_bitmap(love, offsetX, 20, 0);
    al_draw_text(menuFont, al_map_rgb(255, 255, 255), 2*al_get_bitmap_width(love) + offsetX, 20, 0, buffer);
    
//    sprintf(buffer, "Coin: %d", Coin);
//    al_draw_text(menuFont, al_map_rgb(255, 255, 255), offsetX, 20 + gapY, 0, buffer);
    
    sprintf(buffer, "Score: %d", Score);
    al_draw_text(menuFont, al_map_rgb(255, 255, 255), offsetX, 20 + 2*gapY, 0, buffer);
    
    for(int i=0; i < Num_TankType; i++)
    {
        int pos_x = offsetX + (ThumbWidth + gapX) * (i % 2);
        int pos_y = offsetY + (ThumbHeight + gapY) * (i / 2);
        
        al_draw_bitmap(menu_tank[i], pos_x, pos_y, 0);
        al_draw_rectangle(pos_x, pos_y, pos_x + ThumbWidth, pos_y + ThumbHeight, al_map_rgb(255, 255, 255), 0);
    }
}

//int
//Menu::MouseIn(int mouse_x, int mouse_y)
//{
//    
//    
//    
//}

bool
Menu::Subtract_HP(int escapeNum)
{
    HealthPoint -= escapeNum;
    
    return (HealthPoint == 0);
}

void
Menu::Gain_Score(int scoreWorth)
{
    killedTank++;
    Score += scoreWorth;
}


