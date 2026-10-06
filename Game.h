#pragma once

#include "GameState.h"
#include "Player.h"
#include "Enemy.h"
#include "ObjectPool.h"

class Game
{
public:
    Game();

    void Run();

private:
    void Update();

    void Draw();

    void Title();

    void Battle();

    void Victory();

    void GameOver();

    void CreateNextEnemy();

private:
    Player player;

    ObjectPool enemyPool;

    Enemy* currentEnemy;

    bool running;
};