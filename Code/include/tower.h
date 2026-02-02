#pragma once

#include <raylib.h>
#include <vector>
#include <string>

#include "enum.h"

class GameAssets;

class Tower
{
private:
    Vector2 pos;
    float range;
    TowerType type;
    TowerLvl lvl;
    float attackCooldown;
    float attackTimer;
    Vector2 targetPosition;
    bool facingLeft = true;
    int currentTargetIndex = -1;

    float GetRange(TowerLvl currentLvl) const;
    float GetAttackCooldown(TowerLvl currentLvl) const;
    void ApplyUpgradeStats();

public:
    Tower(Vector2 position, TowerType type);

    void Update(float deltaTime);
    void UpgradeLvl(const GameAssets& assets);
    void Draw(const GameAssets& assets) const;
    TowerLvl GetLvl() const { return lvl; }
    int GetDamage() const;
    int GetUpgradeCost() const;
    void SetTarget(Vector2 targetPos);
    float GetRange() const { return range; }

    bool CanAttack() const { return attackTimer >= attackCooldown; }
    void ResetAttackTimer() { attackTimer = 0.0f; }
    Vector2 GetPosition() const { return pos; }
    TowerType GetType() const { return type; }
    Rectangle GetUpgradeHitbox() const;
    Vector2 GetAdjustedTowerPos() const;

    int GetTargetIndex() const { return currentTargetIndex; }
    void SetTargetIndex(int index) { currentTargetIndex = index; }
};