#include "GameController.h"
#include "EnemyFactory.h"
#include "GameManager.h"
#include "MapData.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

GameController::GameController()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void GameController::Run()
{
    GameManager& manager = GameManager::GetInstance();

    while (manager.GetState() != GameState::Exit)
    {
        switch (manager.GetState())
        {
        case GameState::Title:
            HandleTitle();
            break;
        case GameState::Battle:
            HandleBattle();
            break;
        case GameState::MapClear:
            HandleMapClear();
            break;
        case GameState::Victory:
            HandleVictory();
            break;
        case GameState::GameOver:
            HandleGameOver();
            break;
        case GameState::Exit:
            break;
        }
    }
}

void GameController::HandleTitle()
{
    view.DisplayTitle();
    view.DisplayTitleMenu();

    int command = GetUserInput();

    if (command == 1)
    {
        model.ResetGameState();
        CreateNextEnemy();

        if (model.GetCurrentEnemy() != nullptr)
        {
            GameManager::GetInstance().SetState(GameState::Battle);
        }
    }
    else if (command == 2)
    {
        GameManager::GetInstance().SetState(GameState::Exit);
    }
}

void GameController::HandleBattle()
{
    GameManager& manager = GameManager::GetInstance();

    if (model.GetCurrentEnemy() == nullptr)
    {
        CreateNextEnemy();

        if (model.GetCurrentEnemy() == nullptr)
        {
            manager.SetState(GameState::MapClear);
            return;
        }
    }

    const MapData& map = GetMapData(model.GetCurrentMap());
    view.DisplayBattle(map, model.GetDefeatedOnMap(), 
                       model.GetPlayer(), model.GetCurrentEnemy());
    view.DisplayBattleMenu();

    int command = GetUserInput();

    if (command == 1)
    {
        int damage = 0;
        model.ExecutePlayerAttack(damage);
        view.DisplayPlayerAttackResult(model.GetCurrentEnemy()->GetName(), damage);

        if (model.GetCurrentEnemy()->IsDead())
        {
            int expGain = 0;
            int goldGain = 0;
            model.HandleEnemyDefeated(expGain, goldGain);
            view.DisplayEnemyDefeated(model.GetCurrentEnemy()->GetName(), expGain, goldGain);

            if (model.GetPlayer().IsLeveledUp())
            {
                view.DisplayLevelUp(model.GetPlayer());
                model.GetPlayer().ResetLevelUpFlag();
            }

            model.IncrementDefeatedOnMap();

            if (model.GetDefeatedOnMap() >= map.enemyCount)
            {
                manager.SetState(GameState::MapClear);
            }
            else
            {
                CreateNextEnemy();
            }

            return;
        }

        int enemyDamage = 0;
        model.ExecuteEnemyAttack(enemyDamage);
        view.DisplayEnemyAttackResult(enemyDamage);
    }
    else if (command == 2)
    {
        model.ExecutePlayerHeal(20);
        view.DisplayPlayerHealed(20);
    }
    else if (command == 3)
    {
        view.DisplayEscapeBattle();
        model.GetEnemyPool().ReleaseEnemy(model.GetCurrentEnemy());
        model.SetCurrentEnemy(nullptr);
        manager.SetState(GameState::Title);
        return;
    }
    else
    {
        view.DisplayInvalidInput();
    }

    if (model.GetPlayer().IsDead())
    {
        manager.SetState(GameState::GameOver);
    }
}

void GameController::HandleMapClear()
{
    GameManager& manager = GameManager::GetInstance();
    const MapData& map = GetMapData(model.GetCurrentMap());

    view.DisplayMapClear(map, model.GetDefeatedOnMap(), model.GetPlayer());

    bool isLastMap = (model.GetCurrentMap() >= GetMapCount() - 1);

    if (isLastMap)
    {
        manager.SetState(GameState::Victory);
        return;
    }

    model.GetPlayer().AddExp(150);

    if (model.GetPlayer().IsLeveledUp())
    {
        view.DisplayLevelUp(model.GetPlayer());
        model.GetPlayer().ResetLevelUpFlag();
    }

    view.DisplayMapClearMenu(false);

    int command = GetUserInput();

    if (command == 1)
    {
        model.SetCurrentMap(model.GetCurrentMap() + 1);
        model.SetDefeatedOnMap(0);
        view.DisplayClearedNextMap();
        CreateNextEnemy();

        if (model.GetCurrentEnemy() != nullptr)
        {
            manager.SetState(GameState::Battle);
        }
    }
    else if (command == 2)
    {
        model.ResetGameState();
        manager.Reset();
        manager.SetState(GameState::Title);
    }
    else if (command == 3)
    {
        manager.SetState(GameState::Exit);
    }
}

void GameController::HandleVictory()
{
    GameManager& manager = GameManager::GetInstance();

    view.DisplayVictory(model.GetPlayer());
    view.DisplayVictoryMenu();

    int command = GetUserInput();

    if (command == 1)
    {
        model.ResetGameState();
        manager.Reset();
        manager.SetState(GameState::Title);
    }
    else
    {
        manager.SetState(GameState::Exit);
    }
}

void GameController::HandleGameOver()
{
    GameManager& manager = GameManager::GetInstance();

    view.DisplayGameOver(model.GetCurrentMap(), model.GetPlayer());
    view.DisplayGameOverMenu();

    int command = GetUserInput();

    if (command == 1)
    {
        model.ResetGameState();
        manager.Reset();
        manager.SetState(GameState::Title);
    }
    else
    {
        manager.SetState(GameState::Exit);
    }
}

void GameController::CreateNextEnemy()
{
    const MapData& map = GetMapData(model.GetCurrentMap());

    if (map.enemyTypes.empty())
    {
        model.SetCurrentEnemy(nullptr);
        return;
    }

    Enemy* enemy = model.GetEnemyPool().GetEnemy();

    if (enemy == nullptr)
    {
        model.GetEnemyPool().Reset();
        enemy = model.GetEnemyPool().GetEnemy();
    }

    if (enemy == nullptr)
    {
        view.DisplayErrorEnemyCreationFailed();
        GameManager::GetInstance().SetState(GameState::Exit);
        return;
    }

    const EnemyType enemyTypes[] =
    {
        EnemyType::Slime,
        EnemyType::Goblin,
        EnemyType::Golem,
        EnemyType::Skeleton,
        EnemyType::Witch,
        EnemyType::Dragon
    };

    int index = std::rand() % 6;
    EnemyFactory::CreateEnemy(*enemy, enemyTypes[index]);
    model.SetCurrentEnemy(enemy);
}

int GameController::GetUserInput() const
{
    int input;
    std::cin >> input;
    return input;
}