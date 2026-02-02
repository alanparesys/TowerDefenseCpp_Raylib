#pragma once

#include <raylib.h>
#include <vector>
#include <string>

#include "enum.h"

class GameAssets;

class Castle
{
private:
    Vector2 pos;
    int life;
    int maxLife;
    bool exists;

public:
    Castle() : pos{ 0, 0 }, life(0), maxLife(0), exists(false) {}

    void Init(Vector2 position, int maxLife);
    void TakeDamage(int damage);
    void Draw(const GameAssets& assets) const;
    void ResetLife();

    bool IsAlive() const { return life > 0; }
    bool Exists() const { return exists; }
    Vector2 GetPosition() const { return pos; }
    int GetLife() const { return life; }
    int& GetLifeRef() { return life; }
	int GetMaxLife() const { return maxLife; }
};