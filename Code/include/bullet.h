#pragma once

#include <raylib.h>
#include <vector>
#include <string>
#include <memory>

#include "enum.h"
#include "tower.h"
#include "enemy.h"

class GameAssets;
class Game;

class Bullet
{
private:
    Vector2 pos;
    Vector2 speed;
    bool isActive;
    TowerType type;

    int damageAmount;
    float rotationDeg;

    const Game* gamePtr;

    float GetExplosionRadius() const;

public:
    Bullet() : pos{ 0, 0 }, speed{ 0, 0 }, isActive(false), type(TowerType::NONE), damageAmount(0), rotationDeg(0.0f), gamePtr(nullptr) {}
    void SetGamePtr(const Game* ptr) { gamePtr = ptr; }

    void Init(Vector2 from, Vector2 to, TowerType type, int damage);
    void Update(float deltaTime, GameAssets& assets);
    void Draw(const GameAssets& assets) const;
    void CheckCollision(float dt, std::vector<std::unique_ptr<Enemy>>& enemies, const GameAssets& assets);
    int GetDamage() const { return damageAmount; }

    bool IsActive() const { return isActive; }
};

