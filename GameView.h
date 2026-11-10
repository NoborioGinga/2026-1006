#pragma once

#include "Player.h"
#include "Enemy.h"
#include "MapData.h"

// ゲーム画面表示を担当する View クラス
class GameView
{
public:
    GameView() = default;

    // タイトル画面表示
    void DisplayTitle() const;
    void DisplayTitleMenu() const;

    // バトル画面表示
    void DisplayBattle(const MapData& map, int defeatedOnMap,
                       const Player& player, const Enemy* enemy) const;
    void DisplayBattleMenu() const;
    void DisplayPlayerAttackResult(const char* enemyName, int damage) const;
    void DisplayEnemyDefeated(const char* enemyName, int expGain, int goldGain) const;
    void DisplayEnemyAttackResult(int damage) const;
    void DisplayPlayerHealed(int healAmount) const;
    void DisplayEscapeBattle() const;
    void DisplayInvalidInput() const;

    // レベルアップ表示
    void DisplayLevelUp(const Player& player) const;

    // マップクリア画面表示
    void DisplayMapClear(const MapData& map, int defeatedOnMap,
                         const Player& player) const;
    void DisplayMapClearMenu(bool isLastMap) const;

    // ビクトリー画面表示
    void DisplayVictory(const Player& player) const;
    void DisplayVictoryMenu() const;

    // ゲームオーバー画面表示
    void DisplayGameOver(int currentMap, const Player& player) const;
    void DisplayGameOverMenu() const;

    // その他の表示
    void DisplayClearedNextMap() const;
    void DisplayErrorEnemyCreationFailed() const;

private:
    // ヘッダー表示
    void DisplayHeader(const char* title) const;
    // プレイヤーステータス表示
    void DisplayPlayerStatus(const Player& player) const;
    // 敵ステータス表示
    void DisplayEnemyStatus(const Enemy* enemy) const;
};