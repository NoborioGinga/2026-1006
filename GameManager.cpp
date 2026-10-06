#include "GameManager.h"

GameManager::GameManager()
{
    state = GameState::Title;
    defeatedEnemies = 0;
}

GameManager& GameManager::GetInstance()
{
    static GameManager instance;

    return instance;
}

void GameManager::SetState(GameState newState)
{
    state = newState;
}

GameState GameManager::GetState() const
{
    return state;
}

int GameManager::GetDefeatedEnemies() const
{
    return defeatedEnemies;
}

void GameManager::AddDefeatedEnemy()
{
    defeatedEnemies++;
}

void GameManager::Reset()
{
    state = GameState::Title;
    defeatedEnemies = 0;
}