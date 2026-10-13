
#include "Game.h"
#include "GameManager.h"
#include "EnemyFactory.h"
#include "MapData.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

Game::Game()
{
    currentEnemy = nullptr;
    running = true;

    currentMap = 0;
    defeatedOnMap = 0;

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

        case GameState::MapClear:
            MapClear();
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

    std::cout << "1. ゲーム開始" << std::endl;
    std::cout << "2. 終了" << std::endl;
    std::cout << "番号を入力してください：";

    int command;
    std::cin >> command;

    if (command == 1)
    {
        player = Player();

        enemyPool.Reset();
        currentEnemy = nullptr;

        currentMap = 0;
        defeatedOnMap = 0;

        manager.Reset();

        CreateNextEnemy();

        if (currentEnemy != nullptr)
        {
            manager.SetState(GameState::Battle);
        }
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

        if (currentEnemy == nullptr)
        {
            manager.SetState(GameState::MapClear);
            return;
        }
    }

    const MapData& map = GetMapData(currentMap);

    std::cout << std::endl;
    std::cout << "==============================" << std::endl;
    std::cout << "            戦闘              " << std::endl;
    std::cout << "==============================" << std::endl;

    std::cout << "現在のマップ：" << map.name << std::endl;
    std::cout << "討伐数：" << defeatedOnMap
        << " / " << map.enemyCount << std::endl;

    std::cout << std::endl;
    std::cout << "プレイヤー HP : "
        << player.GetHP() << " / "
        << player.GetMaxHP() << std::endl;

    std::cout << "EXP : " << player.GetExp() << std::endl;
    std::cout << "ゴールド : " << player.GetGold() << std::endl;

    std::cout << std::endl;
    std::cout << currentEnemy->GetName()
        << " HP : " << currentEnemy->GetHP()
        << " / " << currentEnemy->GetMaxHP()
        << std::endl;

    std::cout << std::endl;
    std::cout << "1. 攻撃" << std::endl;
    std::cout << "2. 回復" << std::endl;
    std::cout << "3. 逃げる" << std::endl;
    std::cout << "番号を入力してください：";

    int command;
    std::cin >> command;

    if (command == 1)
    {
        player.Attack();

        int damage = player.GetAttack();
        currentEnemy->TakeDamage(damage);

        std::cout << currentEnemy->GetName()
            << "に " << damage
            << " ダメージ！" << std::endl;

        if (currentEnemy->IsDead())
        {
            std::cout << currentEnemy->GetName()
                << "を倒した！" << std::endl;

            // マップごとの報酬倍率を適用
            int getExp =
                currentEnemy->GetExp() * map.expMultiplier;

            int getGold =
                currentEnemy->GetGold() * map.goldMultiplier;

            player.AddExp(getExp);
            player.AddGold(getGold);

            std::cout << "EXP "
                << getExp << " 獲得！" << std::endl;

            std::cout << "ゴールド "
                << getGold << " 獲得！" << std::endl;

            // 総討伐数を管理（既存のSingletonを利用）
            manager.AddDefeatedEnemy();

            // 倒した敵をObject Poolに返す
            enemyPool.ReleaseEnemy(currentEnemy);
            currentEnemy = nullptr;

            ++defeatedOnMap;

            if (defeatedOnMap >= map.enemyCount)
            {
                // このマップの敵を全滅
                manager.SetState(GameState::MapClear);
            }
            else
            {
                CreateNextEnemy();
            }

            return;
        }

        // 敵が生きていれば反撃
        std::cout << currentEnemy->GetName()
            << "の攻撃！" << std::endl;

        int enemyDamage = currentEnemy->GetAttack();
        player.TakeDamage(enemyDamage);

        std::cout << enemyDamage
            << " ダメージ受けた！" << std::endl;
    }
    else if (command == 2)
    {
        std::cout << "薬草を使った！" << std::endl;
        player.Heal(20);
        std::cout << "HPが20回復した！" << std::endl;
    }
    else if (command == 3)
    {
        std::cout << "戦闘から逃げた！" << std::endl;

        enemyPool.ReleaseEnemy(currentEnemy);
        currentEnemy = nullptr;

        manager.SetState(GameState::Title);
        return;
    }
    else
    {
        std::cout << "1～3を選択してください。" << std::endl;
    }

    if (player.IsDead())
    {
        manager.SetState(GameState::GameOver);
    }
}

void Game::MapClear()
{
    GameManager& manager = GameManager::GetInstance();

    const MapData& map = GetMapData(currentMap);

    std::cout << std::endl;
    std::cout << "==============================" << std::endl;
    std::cout << map.name << " クリア！" << std::endl;
    std::cout << "敵を " << defeatedOnMap
        << " 体倒しました！" << std::endl;
    std::cout << "現在のEXP：" << player.GetExp() << std::endl;
    std::cout << "所持ゴールド：" << player.GetGold() << std::endl;
    std::cout << "==============================" << std::endl;

    // 最終マップか確認
    if (currentMap >= GetMapCount() - 1)
    {
        manager.SetState(GameState::Victory);
        return;
    }

    std::cout << std::endl;
    std::cout << "1. 次のマップへ進む" << std::endl;
    std::cout << "2. タイトルに戻る" << std::endl;
    std::cout << "3. ゲームを終了する" << std::endl;
    std::cout << "番号を入力してください：";

    int command;
    std::cin >> command;

    if (command == 1)
    {
        ++currentMap;
        defeatedOnMap = 0;

        std::cout << std::endl;
        std::cout << "次のマップへ進みます！" << std::endl;

        CreateNextEnemy();

        if (currentEnemy != nullptr)
        {
            manager.SetState(GameState::Battle);
        }
    }
    else if (command == 2)
    {
        enemyPool.Reset();
        currentEnemy = nullptr;

        currentMap = 0;
        defeatedOnMap = 0;

        manager.Reset();
        manager.SetState(GameState::Title);
    }
    else if (command == 3)
    {
        manager.SetState(GameState::Exit);
    }
    else
    {
        std::cout << "正しい番号を入力してください。" << std::endl;
    }
}

void Game::Victory()
{
    GameManager& manager = GameManager::GetInstance();

    std::cout << std::endl;
    std::cout << "==============================" << std::endl;
    std::cout << "          GAME CLEAR!         " << std::endl;
    std::cout << "==============================" << std::endl;

    std::cout << "すべてのマップをクリアしました！" << std::endl;
    std::cout << "獲得EXP合計：" << player.GetExp() << std::endl;
    std::cout << "所持ゴールド：" << player.GetGold() << std::endl;

    std::cout << std::endl;
    std::cout << "1. タイトルに戻る" << std::endl;
    std::cout << "2. 終了" << std::endl;
    std::cout << "番号を入力してください：";

    int command;
    std::cin >> command;

    if (command == 1)
    {
        enemyPool.Reset();
        currentEnemy = nullptr;

        currentMap = 0;
        defeatedOnMap = 0;

        manager.Reset();
        manager.SetState(GameState::Title);
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
    std::cout << "          GAME OVER           " << std::endl;
    std::cout << "==============================" << std::endl;

    std::cout << "プレイヤーは力尽きた……" << std::endl;
    std::cout << "到達マップ：" << currentMap + 1 << std::endl;
    std::cout << "獲得EXP：" << player.GetExp() << std::endl;
    std::cout << "所持ゴールド：" << player.GetGold() << std::endl;

    std::cout << std::endl;
    std::cout << "1. タイトルに戻る" << std::endl;
    std::cout << "2. 終了" << std::endl;
    std::cout << "番号を入力してください：";

    int command;
    std::cin >> command;

    if (command == 1)
    {
        enemyPool.Reset();
        currentEnemy = nullptr;

        currentMap = 0;
        defeatedOnMap = 0;

        manager.Reset();
        manager.SetState(GameState::Title);
    }
    else
    {
        manager.SetState(GameState::Exit);
    }
}

void Game::CreateNextEnemy()
{
    const MapData& map = GetMapData(currentMap);

    if (map.enemyTypes.empty())
    {
        currentEnemy = nullptr;
        return;
    }

    currentEnemy = enemyPool.GetEnemy();

    if (currentEnemy == nullptr)
    {
        enemyPool.Reset();
        currentEnemy = enemyPool.GetEnemy();
    }

    // Poolから取得できなかった場合は安全に終了
    if (currentEnemy == nullptr)
    {
        std::cout << "敵を生成できませんでした。" << std::endl;

        GameManager::GetInstance().SetState(GameState::Exit);
        return;
    }

    // 現在のマップで設定された敵からランダムに選択
  // 出現する敵6種類
    const EnemyType enemyTypes[] =
    {
        EnemyType::Slime,
        EnemyType::Goblin,
        EnemyType::Golem,
        EnemyType::Skeleton,
        EnemyType::Witch,
        EnemyType::Dragon
    };

    // 0～5の中からランダムに選ぶ
    int index = std::rand() % 6;

    EnemyType enemyType = enemyTypes[index];

    EnemyFactory::CreateEnemy(*currentEnemy, enemyType);
}
