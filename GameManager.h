#pragma once

#include "GameState.h"

class GameManager
{
public:
    static GameManager& GetInstance();

    void SetState(GameState state);

    GameState GetState() const;

    int GetDefeatedEnemies() const;

    void AddDefeatedEnemy();

    void Reset();

private:
    GameManager();

    GameState state;

    int defeatedEnemies;
};