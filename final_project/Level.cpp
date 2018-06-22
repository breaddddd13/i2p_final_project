#include "Level.h"

LEVEL::LEVEL(const int level) {
    char buffer[50];
    
    setLevel(level);
    
}

LEVEL::~LEVEL()
{
//    for(int i=0;i < NumOfGrid;i++)
//    {
//        levelMap[i].roadPoint = false;
//    }
}

void
LEVEL::setLevel(const int level)
{
    char buffer[50];
    FILE *file;
    
    sprintf(buffer, "LEVEL%d.txt", level);
    file = fopen(buffer, "r");
    
    this->level = level;
    this->road_grid.clear();
    
//    for(int i = 0; i < NumOfGrid; i++)
//    {
//        this->levelMap[i].roadPoint = false;
//    }
    
//    fscanf(file, "%s", buffer);
//    Monster_MAX = atoi(buffer);
    
//    for(int i=0; i < Num_MonsterType; i++)
//    {
//        fscanf(file, "%s", buffer);
//        MonsterNum[i] = atoi(buffer);
//    }
    
    while(fscanf(file, "%s", buffer) != EOF) {
        for (int i = 0; i < field_height/grid_height; i++) {
            for (int j = 0; j < field_width/grid_width; j++) {
                levelMap[i][j].roadPoint = buffer[j];
            }
        }
    }
    
    fclose(file);
}
