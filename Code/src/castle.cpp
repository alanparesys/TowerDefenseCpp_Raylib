#include "castle.h"
#include "game.h"
#include "assets.h"
#include <iostream>

void Castle::Init(Vector2 position, int maxLife)
{
    pos = position;
    life = maxLife;
    this->maxLife = maxLife;
    exists = true;
}

void Castle::TakeDamage(int damage)
{
    life -= damage;
    if (life < 0) life = 0;
}

void Castle::Draw(const GameAssets& assets) const
{
    if (!exists) return;

    const float textureWidth = (float)assets.GetCastleTexture().width * 2.0f;
    const float textureHeight = (float)assets.GetCastleTexture().height * 2.0f;

    Vector2 textureDrawPos = {
        pos.x - textureWidth / 2.0f + 100,
        pos.y - textureHeight / 2.0f + 100
    };

    DrawTextureEx(assets.GetCastleTexture(), textureDrawPos, 0.0f, 1.0f, WHITE);
}

void Castle::ResetLife()
{
    life = 1500;
    maxLife = 1500;
}