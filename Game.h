
#pragma once

#include "Player.h"
#include "Enemy.h"
#include "ObjectPool.h"

class Game
{
private:
    bool running = true;

    Player player;
    ObjectPool enemyPool;
    Enemy* currentEnemy;

    int currentMap = 0;
    int defeatedOnMap = 0;

    void Title();
    void Battle();
    void MapClear();
    void Victory();
    void GameOver();
    void CreateNextEnemy();

public:
    Game();
    void Run();
    void Update();
    void Draw();
};
