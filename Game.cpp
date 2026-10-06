#include "Game.h"
#include "GameManager.h"
#include "EnemyFactory.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

Game::Game()
{
    currentEnemy = nullptr;
    running = true;

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void Game::Run()
{
    GameManager& manager = GameManager::GetInstance();

    while (running)
    {
        switch (manager.GetState())
        {
        case GameState::Title:

            Title();

            break;

        case GameState::Battle:

            Battle();

            break;

        case GameState::Victory:

            Victory();

            break;

        case GameState::GameOver:

            GameOver();

            break;

        case GameState::Exit:

            running = false;

            break;
        }
    }
}

void Game::Update()
{
}

void Game::Draw()
{
}

void Game::Title()
{
    GameManager& manager = GameManager::GetInstance();

    std::cout << std::endl;
    std::cout << "==============================" << std::endl;
    std::cout << "       SIMPLE CONSOLE RPG     " << std::endl;
    std::cout << "==============================" << std::endl;

    std::cout << std::endl;

    std::cout << "1. ゲーム開始" << std::endl;
    std::cout << "2. 終了" << std::endl;

    std::cout << std::endl;
    std::cout << "番号を入力してください：";

    int command;

    std::cin >> command;

    if (command == 1)
    {
        player = Player();

        enemyPool.Reset();

        manager.Reset();

        CreateNextEnemy();

        manager.SetState(GameState::Battle);
    }
    else if (command == 2)
    {
        manager.SetState(GameState::Exit);
    }
}

void Game::Battle()
{
    GameManager& manager = GameManager::GetInstance();

    if (currentEnemy == nullptr)
    {
        CreateNextEnemy();
    }

    std::cout << std::endl;
    std::cout << "==============================" << std::endl;
    std::cout << "            戦闘              " << std::endl;
    std::cout << "==============================" << std::endl;

    std::cout << std::endl;

    std::cout
        << "プレイヤー HP : "
        << player.GetHP()
        << " / "
        << player.GetMaxHP()
        << std::endl;

    std::cout
        << currentEnemy->GetName()
        << " HP : "
        << currentEnemy->GetHP()
        << " / "
        << currentEnemy->GetMaxHP()
        << std::endl;

    std::cout << std::endl;

    std::cout << "1. 攻撃" << std::endl;
    std::cout << "2. 回復" << std::endl;
    std::cout << "3. 逃げる" << std::endl;

    std::cout << std::endl;
    std::cout << "番号を入力してください：";

    int command;

    std::cin >> command;

    if (command == 1)
    {
        player.Attack();

        int damage = player.GetAttack();

        currentEnemy->TakeDamage(damage);

        std::cout
            << currentEnemy->GetName()
            << "に "
            << damage
            << " ダメージ！"
            << std::endl;

        if (currentEnemy->IsDead())
        {
            std::cout << std::endl;

            std::cout
                << currentEnemy->GetName()
                << "を倒した！"
                << std::endl;

            manager.AddDefeatedEnemy();

            enemyPool.ReleaseEnemy(currentEnemy);

            currentEnemy = nullptr;

            if (manager.GetDefeatedEnemies() >= 3)
            {
                manager.SetState(GameState::Victory);
                return;
            }

            CreateNextEnemy();

            return;
        }

        
        std::cout
            << currentEnemy->GetName()
            << "の攻撃！"
            << std::endl;

        player.TakeDamage(currentEnemy->GetAttack());

        std::cout
            << currentEnemy->GetAttack()
            << "ダメージ受けた！"
            << std::endl;


    }
    else if (command == 2)
    {
        std::cout << "薬草を使った！" << std::endl;

        player.Heal(20);

        std::cout
            << "HPが20回復した！"
            << std::endl;
    }
    else if (command == 3)
    {
        std::cout << "戦闘から逃げた！" << std::endl;

        manager.SetState(GameState::Title);

        return;
    }

    if (player.IsDead())
    {
        manager.SetState(GameState::GameOver);
    }
}

void Game::Victory()
{
    GameManager& manager = GameManager::GetInstance();

    std::cout << std::endl;
    std::cout << "==============================" << std::endl;
    std::cout << "          GAME CLEAR!         " << std::endl;
    std::cout << "==============================" << std::endl;

    std::cout << std::endl;

    std::cout << "3体の敵を倒しました！" << std::endl;

    std::cout << std::endl;

    std::cout << "1. タイトルに戻る" << std::endl;
    std::cout << "2. 終了" << std::endl;

    std::cout << std::endl;

    std::cout << "番号を入力してください：";

    int command;

    std::cin >> command;

    if (command == 1)
    {
        manager.Reset();
        currentEnemy = nullptr;
    }
    else
    {
        manager.SetState(GameState::Exit);
    }
}

void Game::GameOver()
{
    GameManager& manager = GameManager::GetInstance();

    std::cout << std::endl;
    std::cout << "==============================" << std::endl;
    std::cout << "          GAME OVER            " << std::endl;
    std::cout << "==============================" << std::endl;

    std::cout << std::endl;

    std::cout << "プレイヤーは力尽きた……" << std::endl;

    std::cout << std::endl;

    std::cout << "1. タイトルに戻る" << std::endl;
    std::cout << "2. 終了" << std::endl;

    std::cout << std::endl;

    std::cout << "番号を入力してください：";

    int command;

    std::cin >> command;

    if (command == 1)
    {
        manager.Reset();
        currentEnemy = nullptr;
    }
    else
    {
        manager.SetState(GameState::Exit);
    }
}

void Game::CreateNextEnemy()
{
    int enemyType = std::rand() % 3;

    currentEnemy = enemyPool.GetEnemy();

    if (currentEnemy == nullptr)
    {
        enemyPool.Reset();

        currentEnemy = enemyPool.GetEnemy();
    }

    EnemyFactory::CreateEnemy(
        *currentEnemy,
        static_cast<EnemyType>(enemyType)
    );
}