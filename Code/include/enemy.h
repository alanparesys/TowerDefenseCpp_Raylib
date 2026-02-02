#pragma once

#include <raylib.h>
#include <vector>
#include <string>
#include <memory>

#include "enum.h"
#include "pathpoint.h"
#include "sprites.h"


class DamageText
{
public:
    int value;
    Vector2 startPos;
    float timeRemaining;

    static const float duration;

    DamageText(int val, Vector2 pos)
        : value(val),
        startPos(pos),
        timeRemaining(duration)
    {
    }
};

class GameAssets;
class Game;

class Enemy
{
protected:
    Vector2 pos;
    int health;
    int maxHealth;
    int damage;
    int reward;
    Vector2 targetRandomPos;
    float attackCooldown;
    float attackTimer;
    int nextPoint;
    bool isMoving;
    float slowTimer;
    float speedSlow = 1;
    float speedMultiplier = 1.0f;
    int bossTextureIndex;

    const Game* gamePtr;

    std::vector<DamageText> floatingDamages;

    virtual int GetBaseHealth() const = 0;
    virtual float GetBaseSpeed() const = 0;
    virtual int GetBaseDamage() const = 0;
    virtual int GetBaseReward() const = 0;
    virtual float GetBaseAttackCooldown() const = 0;
    virtual Texture2D GetTexture(const GameAssets& assets) const = 0;
    virtual float GetTextureScale() const = 0;
    virtual Vector2 GetLifeBarPosition() const = 0;

    float GetSpeed(float slow) const;
    float GetAttackSpeed() const;
    void InitializeStats(float healthMultiplier);

public:
    Enemy(Vector2 startPos, const Game& settings, float healthMultiplier = 1.0f, float speedMultiplier = 1.0f);
    virtual ~Enemy() = default;

    void Update(float dt, const std::vector<PathPoint>& path, int& castleLife, const GameAssets& assets);
    void Movements(float dt, const std::vector<PathPoint>& path);
    virtual void Draw(const GameAssets& assets) const;
    void TakeDamage(int damage, const GameAssets& assets);
    void InitializeTarget(Vector2 center, float radius);
    bool IsAlive() const { return health > 0; }
    bool IsMoving() const { return isMoving; }
    Vector2 GetPosition() const { return pos; }
    int GetDamage() const { return damage; }
    bool CanAttack() const { return attackTimer >= attackCooldown; }
    void ResetAttackTimer() { attackTimer = 0.0f; }
    int GetReward() const { return reward; }
};

class FastEnemy : public Enemy
{
protected:
    int GetBaseHealth() const override { return 60; }
    float GetBaseSpeed() const override { return 3.0f; }
    int GetBaseDamage() const override { return 30; }
    int GetBaseReward() const override { return 35; }
    float GetBaseAttackCooldown() const override { return 0.4f; }
    Texture2D GetTexture(const GameAssets& assets) const override;
    float GetTextureScale() const override { return 3.0f; }
    Vector2 GetLifeBarPosition() const override { return { pos.x - 40, pos.y - 100 }; }

public:
    FastEnemy(Vector2 startPos, const Game& settings, float healthMultiplier = 1.0f, float speedMultiplier = 1.0f);
};

class NormalEnemy : public Enemy
{
protected:
    int GetBaseHealth() const override { return 100; }
    float GetBaseSpeed() const override { return 1.6f; }
    int GetBaseDamage() const override { return 50; }
    int GetBaseReward() const override { return 25; }
    float GetBaseAttackCooldown() const override { return 1.2f; }
    Texture2D GetTexture(const GameAssets& assets) const override;
    float GetTextureScale() const override { return 0.2f; }
    Vector2 GetLifeBarPosition() const override { return { pos.x - 50, pos.y - 70 }; }
public:
    NormalEnemy(Vector2 startPos, const Game& settings, float healthMultiplier = 1.0f, float speedMultiplier = 1.0f);
};

class TankEnemy : public Enemy
{
private:
    mutable SpriteInstance spriteInstance;
    mutable bool useAnimation;
    mutable bool isAttacking;

protected:
    int GetBaseHealth() const override { return 350; }
    float GetBaseSpeed() const override { return 0.8f; }
    int GetBaseDamage() const override { return 150; }
    int GetBaseReward() const override { return 80; }
    float GetBaseAttackCooldown() const override { return 2.5f; }
    Texture2D GetTexture(const GameAssets& assets) const override;
    float GetTextureScale() const override { return 2.0f; }
    Vector2 GetLifeBarPosition() const override { return { pos.x - 30, pos.y - 70 }; }

public:
    TankEnemy(Vector2 startPos, const Game& settings, float healthMultiplier = 1.0f, float speedMultiplier = 1.0f);
    void UpdateAnimation(float dt, const GameAssets& assets);
    void PlayAttackAnimation(const GameAssets& assets);
    void Draw(const GameAssets& assets) const override;
};


class BossEnemy : public Enemy
{
protected:
    int GetBaseHealth() const override { return 500; }
    float GetBaseSpeed() const override { return 1.8f; }
    int GetBaseDamage() const override { return 200; }
    int GetBaseReward() const override { return 0; }
    float GetBaseAttackCooldown() const override { return 1.5f; }
    Texture2D GetTexture(const GameAssets& assets) const override;
    float GetTextureScale() const override { return 0.3f; }
    Vector2 GetLifeBarPosition() const override { return { pos.x - 30, pos.y - 70 }; }

public:
    BossEnemy(Vector2 startPos, const Game& settings, float healthMultiplier = 1.0f, float speedMultiplier = 1.0f);
};

std::unique_ptr<Enemy> CreateEnemy(EnemyType type, Vector2 startPos, const Game& settings, float healthMultiplier = 1.0f, float speedMultiplier = 1.0f);
