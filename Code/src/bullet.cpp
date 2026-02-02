#include <raylib.h>
#include <cmath>
#include <vector>

#include "bullet.h"
#include "game.h"
#include "enemy.h"
#include "assets.h"
#include "tower.h"


void Bullet::Init(Vector2 from, Vector2 to, TowerType type, int damage)
{
    pos = from;
    this->type = type;
    isActive = true;
    this->damageAmount = damage;

    float dx = to.x - from.x;
    float dy = to.y - from.y;
    float dist = sqrt(dx * dx + dy * dy);
    float bulletSpeed = (type == TowerType::WIZARD) ? 10.0f : 8.0f;

    if (dist != 0) {
        speed = { (dx / dist) * bulletSpeed, (dy / dist) * bulletSpeed };
        rotationDeg = atan2f(speed.y, speed.x) * RAD2DEG;
    }
    else {
        speed = { 0, 0 };
        rotationDeg = 0.0f;
    }
}

void Bullet::Update(float dt, GameAssets& assets)
{
    if (!isActive) return;

    if (gamePtr == nullptr) return;

    if (gamePtr->GetPauseGame()) return;

    switch (type)
    {
    case (TowerType::ARCHER):
        PlaySound(assets.GetArcherShot());
        break;
    case (TowerType::WIZARD):
        PlaySound(assets.GetWizardShot());
        break;
    case (TowerType::CATAPULT):
        PlaySound(assets.GetCatapultShot());
        break;
    }
    pos.x += speed.x * dt * 60.0f;
    pos.y += speed.y * dt * 60.0f;

    rotationDeg += 720.0f * dt; // spin

    if (pos.x < 0 || pos.x > 1920 || pos.y < 0 || pos.y > 1200)
    {
        isActive = false;
    }
}

void Bullet::CheckCollision(float dt, std::vector<std::unique_ptr<Enemy>>& enemies, const GameAssets& assets)
{
    if (!isActive) return;

    for (auto& enemy : enemies)
    {
        if (enemy->IsAlive() && CheckCollisionCircles(pos, 10.0f, enemy->GetPosition(), 30.0f))
        {
            if (type == TowerType::ARCHER)
            {
                enemy->TakeDamage(damageAmount, assets);

                isActive = false;
                break;
            }
            else if (type == TowerType::WIZARD || type == TowerType::CATAPULT)
            {
                float explosionRadius = GetExplosionRadius();
                int damageAmount = this->damageAmount;

                for (auto& target : enemies)
                {
                    if (target->IsAlive() && CheckCollisionCircles(pos, explosionRadius, target->GetPosition(), 30.0f))
                    {
                        target->TakeDamage(damageAmount, assets);
                    }
                }
                isActive = false;
                break;
            }
        }
    }
}

void Bullet::Draw(const GameAssets& assets) const
{
    if (!isActive) return;

    const Texture2D& tex = assets.GetBulletTexture();
    float scale = 0.6f;
    Rectangle src{ 0, 0, (float)tex.width, (float)tex.height };
    Rectangle dst{ pos.x, pos.y, tex.width * scale, tex.height * scale };
    Vector2 origin{ (tex.width * scale) / 2.0f, (tex.height * scale) / 2.0f };

    DrawTexturePro(tex, src, dst, origin, rotationDeg, WHITE);
}


float Bullet::GetExplosionRadius() const
{
    switch (type)
    {
    case TowerType::WIZARD: return 35.0f;
    case TowerType::CATAPULT: return 50.0f;
    default: return 0.0f;
    }
}
