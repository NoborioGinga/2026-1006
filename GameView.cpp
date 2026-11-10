#include "GameView.h"
#include <iostream>

// ヘッダーと区切り線を表示
void GameView::DisplayHeader(const char* title) const
{
    std::cout << std::endl;
    std::cout << "==============================" << std::endl;
    std::cout << title << std::endl;
    std::cout << "==============================" << std::endl;
}

// プレイヤーのステータスを表示
void GameView::DisplayPlayerStatus(const Player& player) const
{
    std::cout << "プレイヤー レベル : " << player.GetLevel() << std::endl;
    std::cout << "プレイヤー HP : " << player.GetHP() << " / "
              << player.GetMaxHP() << std::endl;
    std::cout << "攻撃力 : " << player.GetAttack() << std::endl;
    std::cout << "EXP : " << player.GetExp() << " / "
              << player.GetNextLevelExp() << std::endl;
    std::cout << "ゴールド : " << player.GetGold() << std::endl;
}

// 敵のステータスを表示
void GameView::DisplayEnemyStatus(const Enemy* enemy) const
{
    if (enemy != nullptr)
    {
        std::cout << enemy->GetName() << " HP : " << enemy->GetHP()
                  << " / " << enemy->GetMaxHP() << std::endl;
    }
}

// タイトル画面を表示
void GameView::DisplayTitle() const
{
    DisplayHeader("       SIMPLE CONSOLE RPG     ");
}

// タイトルメニューを表示
void GameView::DisplayTitleMenu() const
{
    std::cout << "1. ゲーム開始" << std::endl;
    std::cout << "2. 終了" << std::endl;
    std::cout << "番号を入力してください：";
}

// バトル画面を表示
void GameView::DisplayBattle(const MapData& map, int defeatedOnMap,
                             const Player& player, const Enemy* enemy) const
{
    DisplayHeader("            戦闘              ");
    std::cout << "現在のマップ：" << map.name << std::endl;
    std::cout << "討伐数：" << defeatedOnMap << " / " << map.enemyCount << std::endl;
    std::cout << std::endl;
    DisplayPlayerStatus(player);
    std::cout << std::endl;
    DisplayEnemyStatus(enemy);
}

// バトルメニューを表示
void GameView::DisplayBattleMenu() const
{
    std::cout << std::endl;
    std::cout << "1. 攻撃" << std::endl;
    std::cout << "2. 回復" << std::endl;
    std::cout << "3. 逃げる" << std::endl;
    std::cout << "番号を入力してください：";
}

// プレイヤーの攻撃結果を表示
void GameView::DisplayPlayerAttackResult(const char* enemyName, int damage) const
{
    std::cout << enemyName << "に " << damage << " ダメージ！" << std::endl;
}

// 敵を倒した時の報酬を表示
void GameView::DisplayEnemyDefeated(const char* enemyName, int expGain, int goldGain) const
{
    std::cout << enemyName << "を倒した！" << std::endl;
    std::cout << "EXP " << expGain << " 獲得！" << std::endl;
    std::cout << "ゴールド " << goldGain << " 獲得！" << std::endl;
}

// 敵の攻撃結果を表示
void GameView::DisplayEnemyAttackResult(int damage) const
{
    std::cout << "敵の攻撃！" << std::endl;
    std::cout << damage << " ダメージ受けた！" << std::endl;
}

// 回復処理を表示
void GameView::DisplayPlayerHealed(int healAmount) const
{
    std::cout << "薬草を使った！" << std::endl;
    std::cout << "HPが" << healAmount << "回復した！" << std::endl;
}

// 逃げた事を表示
void GameView::DisplayEscapeBattle() const
{
    std::cout << "戦闘から逃げた！" << std::endl;
}

// 無効な入力を表示
void GameView::DisplayInvalidInput() const
{
    std::cout << "1～3を選択してください。" << std::endl;
}

// レベルアップ画面を表示
void GameView::DisplayLevelUp(const Player& player) const
{
    std::cout << std::endl;
    std::cout << " レベルアップ！" << std::endl;
    std::cout << "レベル：" << player.GetLevel() << std::endl;
    std::cout << "最大 HP が 7 上昇！" << std::endl;
    std::cout << "攻撃力が 2 上昇！" << std::endl;
    std::cout << "HP が全回復した！" << std::endl;
    std::cout << std::endl;
}

// マップクリア画面を表示
void GameView::DisplayMapClear(const MapData& map, int defeatedOnMap,
                               const Player& player) const
{
    std::string header = std::string(map.name) + " クリア！";
    DisplayHeader(header.c_str());
    
    std::cout << "敵を " << defeatedOnMap << " 体倒しました！" << std::endl;
    std::cout << "現在のEXP：" << player.GetExp() << std::endl;
    std::cout << "所持ゴールド：" << player.GetGold() << std::endl;
    std::cout << "\nマップクリア報酬！" << std::endl;
    std::cout << "==============================" << std::endl;
}

// マップクリア後のメニューを表示
void GameView::DisplayMapClearMenu(bool isLastMap) const
{
    std::cout << std::endl;
    if (!isLastMap)
    {
        std::cout << "1. 次のマップへ進む" << std::endl;
        std::cout << "2. タイトルに戻る" << std::endl;
        std::cout << "3. ゲームを終了する" << std::endl;
    }
    else
    {
        std::cout << "1. タイトルに戻る" << std::endl;
        std::cout << "2. ゲームを終了する" << std::endl;
    }
    std::cout << "番号を入力してください：";
}

// ビクトリー画面を表示
void GameView::DisplayVictory(const Player& player) const
{
    DisplayHeader("          GAME CLEAR!         ");
    std::cout << "すべてのマップをクリアしました！" << std::endl;
    std::cout << "獲得EXP合計：" << player.GetExp() << std::endl;
    std::cout << "所持ゴールド：" << player.GetGold() << std::endl;
}

// ビクトリーメニューを表示
void GameView::DisplayVictoryMenu() const
{
    std::cout << std::endl;
    std::cout << "1. タイトルに戻る" << std::endl;
    std::cout << "2. 終了" << std::endl;
    std::cout << "番号を入力してください：";
}

// ゲームオーバー画面を表示
void GameView::DisplayGameOver(int currentMap, const Player& player) const
{
    DisplayHeader("          GAME OVER           ");
    std::cout << "プレイヤーは力尽きた……" << std::endl;
    std::cout << "到達マップ：" << currentMap + 1 << std::endl;
    std::cout << "獲得EXP：" << player.GetExp() << std::endl;
    std::cout << "所持ゴールド：" << player.GetGold() << std::endl;
}

// ゲームオーバーメニューを表示
void GameView::DisplayGameOverMenu() const
{
    std::cout << std::endl;
    std::cout << "1. タイトルに戻る" << std::endl;
    std::cout << "2. 終了" << std::endl;
    std::cout << "番号を入力してください：";
}

// 次マップへの進行を表示
void GameView::DisplayClearedNextMap() const
{
    std::cout << std::endl;
    std::cout << "次のマップへ進みます！" << std::endl;
}

// 敵生成失敗エラーを表示
void GameView::DisplayErrorEnemyCreationFailed() const
{
    std::cout << "敵を生成できませんでした。" << std::endl;
}