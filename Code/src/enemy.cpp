#include "enemy.h"
#include "game.h"
#include "assets.h"
#include "sprites.h"
#include "enum.h"
#include "pathpoint.h"
#include <cmath>
#include <memory>
#include <raylib.h>

const float DamageText::duration = 1.0f;

Vector2 GetRandomPointInCircle(Vector2 center, float radius)
{
    float angle = GetRandomValue(0, 360) * DEG2RAD;
    float r = radius * sqrt((float)GetRandomValue(0, 1000) / 1000.0f);

    Vector2 randomPoint;
    randomPoint.x = center.x + r * cosf(angle);
    randomPoint.y = center.y + r * sinf(angle);

    return randomPoint;
}

Enemy::Enemy(Vector2 startPos, const Game& settings, float healthMultiplier, float speedMultiplier)
    : pos(startPos),
    health(0),
    maxHealth(0),
    damage(0),
    reward(0),
    targetRandomPos(startPos),
    attackCooldown(0.0f),
    attackTimer(0.0f),
    nextPoint(1),
    isMoving(true),
    slowTimer(0.0f),
    speedSlow(1.0f),
    speedMultiplier(speedMultiplier),
    bossTextureIndex(0),
    gamePtr(&settings)
{
}


float Enemy::GetSpeed(float slow) const
{
    return GetBaseSpeed() * speedMultiplier * slow;
}

float Enemy::GetAttackSpeed() const
{
    return attackCooldown > 0.0f ? 1.0f / attackCooldown : 0.0f;
}

void Enemy::InitializeStats(float healthMultiplier)
{
    int baseHealth = GetBaseHealth();
    damage = GetBaseDamage();
    attackCooldown = GetBaseAttackCooldown();
    reward = GetBaseReward();

    maxHealth = (int)(baseHealth * healthMultiplier);
    health = maxHealth;
    bossTextureIndex = GetRandomValue(1, 4);
}

void Enemy::InitializeTarget(Vector2 center, float radius)
{
    targetRandomPos = GetRandomPointInCircle(center, radius);
}

void Enemy::Update(float dt, const std::vector<PathPoint>& path, int& castleLife, const GameAssets& assets)
{
    if (!IsAlive()) return;

    if (gamePtr->GetPauseGame() == false)
    {
        attackTimer += dt;

        if (nextPoint >= path.size())
        {
            isMoving = false;

            if (attackTimer >= attackCooldown)
            {
                if (castleLife > 0)
                {
                    castleLife -= damage;
                    if (castleLife < 0) castleLife = 0;
                }
                if (damage > 0)
                {
                    if (auto* tankEnemy = dynamic_cast<TankEnemy*>(this))
                    {
                        tankEnemy->PlayAttackAnimation(gamePtr->GetAssets());
                    }
                }
                attackTimer = 0.0f;
            }
        }
        else
        {
            Movements(dt, path);
        }

        TankEnemy* tankEnemy = dynamic_cast<TankEnemy*>(this);
        if (tankEnemy != nullptr)
        {
            tankEnemy->UpdateAnimation(dt, gamePtr->GetAssets());
        }

        for (auto it = floatingDamages.begin(); it != floatingDamages.end(); )
        {
            it->timeRemaining -= dt;

            if (it->timeRemaining <= 0)
            {
                it = floatingDamages.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
}

void Enemy::Movements(float dt, const std::vector<PathPoint>& path)
{
    Vector2 target = targetRandomPos;

    float speedFactor = GetSpeed(speedSlow) * dt * 60.0f;

    float dx = target.x - pos.x;
    float dy = target.y - pos.y;
    float dist = sqrtf(dx * dx + dy * dy);

    if (dist < speedFactor)
    {
        pos = target;
        nextPoint++;

        if (nextPoint < path.size())
        {
            InitializeTarget(path[nextPoint].position, path[nextPoint].radius);
        }
        else
        {
            isMoving = false;
        }
    }
    else
    {
        pos.x += (dx / dist) * speedFactor;
        pos.y += (dy / dist) * speedFactor;
    }
}

void Enemy::TakeDamage(int damage, const GameAssets& assets)
{
    floatingDamages.emplace_back(damage, GetRandomPointInCircle(pos, 5.0f));

    health -= damage;

    if (health <= 0)
    {
        health = 0;

        int randomDeathSound = GetRandomValue(1, 3);
        const Sound* deathSound = nullptr;

        if (randomDeathSound == 1) deathSound = &assets.GetDeath1();
        else if (randomDeathSound == 2) deathSound = &assets.GetDeath2();
        else deathSound = &assets.GetDeath3();

        PlaySound(*deathSound);
    }
}
void Enemy::Draw(const GameAssets& assets) const
{
    if (!IsAlive()) return;

    Texture2D enemyTexture = GetTexture(assets);
    float scale = GetTextureScale();

    float offset = (enemyTexture.width * scale) / 2.0f;
    DrawTextureEx(enemyTexture, Vector2{ pos.x - offset, pos.y - offset }, 0, scale, WHITE);

    float lifePercent = (float)health / maxHealth * 100.0f;
    Vector2 lifePos = GetLifeBarPosition();
    if (bossTextureIndex == 1)
    {
        lifePos = { GetLifeBarPosition().x, GetLifeBarPosition().y - 30 };
    }

    if (bossTextureIndex == 3)
    {
        lifePos = { GetLifeBarPosition().x - 20, GetLifeBarPosition().y - 30 };
    }

    if (bossTextureIndex == 4)
    {
        lifePos = { GetLifeBarPosition().x, GetLifeBarPosition().y - 50 };
    }

    if (gamePtr->GetLifeBarButton())
    {
        DrawTextureEx(assets.GetLifeTexture(lifePercent), lifePos, 0, 1.5f, WHITE);
    }

    if (gamePtr->GetDamageNumberButton())
    {
        Vector2 baseDrawPos = { pos.x, pos.y - 40.0f };

        for (const auto& damageText : floatingDamages)
        {
            float progress = 1.0f - (damageText.timeRemaining / damageText.duration);

            const float maxHeight = 40.0f;
            float jumpFactor = 4.0f * progress * (1.0f - progress);
            float jumpOffset = jumpFactor * maxHeight;

            float alpha = damageText.timeRemaining / damageText.duration;
            Color drawColor = Fade(WHITE, alpha);

            Vector2 textPos = baseDrawPos;
            textPos.x += (damageText.startPos.x - pos.x);
            textPos.y -= jumpOffset;

            DrawTextPro(assets.GetMedievalFont(), TextFormat("%i", damageText.value), textPos, { 0.0f, 0.0f }, 0.0f, 30.0f, 2.0f, drawColor);
        }
    }
}

FastEnemy::FastEnemy(Vector2 startPos, const Game& settings, float healthMultiplier, float speedMultiplier)
    : Enemy(startPos, settings, healthMultiplier, speedMultiplier)
{
    InitializeStats(healthMultiplier);
}

Texture2D FastEnemy::GetTexture(const GameAssets& assets) const
{
    return assets.GetFerretTexture();
}

NormalEnemy::NormalEnemy(Vector2 startPos, const Game& settings, float healthMultiplier, float speedMultiplier)
    : Enemy(startPos, settings, healthMultiplier, speedMultiplier)
{
    InitializeStats(healthMultiplier);
}

Texture2D NormalEnemy::GetTexture(const GameAssets& assets) const
{
    return assets.GetNecromancerTexture();
}

TankEnemy::TankEnemy(Vector2 startPos, const Game& settings, float healthMultiplier, float speedMultiplier)
    : Enemy(startPos, settings, healthMultiplier, speedMultiplier),
    useAnimation(false),
    isAttacking(false)
{
    InitializeStats(healthMultiplier);
    spriteInstance.Position = { 0, 0 };
    spriteInstance.Offset = { 0, 0 };
    spriteInstance.Sheet = nullptr;
    spriteInstance.Animation = nullptr;
    spriteInstance.AnimationDone = false;
    spriteInstance.CurrentFrame = -1;
    spriteInstance.FrameLifetime = 0.0f;
}

Texture2D TankEnemy::GetTexture(const GameAssets& assets) const
{
    return assets.GetCacodaemonTexture();
}

void TankEnemy::UpdateAnimation(float dt, const GameAssets& assets)
{
    if (!useAnimation && assets.GetTankWalkSheet().SheetTexture.id > 0)
    {
        spriteInstance.Sheet = &assets.GetTankWalkSheet();
        spriteInstance.Animation = &assets.GetTankWalkAnimation();
        SetSpriteAnimation(spriteInstance, assets.GetTankWalkAnimation());
        useAnimation = true;
    }
    const SpriteSheet* desiredSheet = isAttacking && assets.GetTankAttackSheet().SheetTexture.id > 0
        ? &assets.GetTankAttackSheet()
        : &assets.GetTankWalkSheet();
    const SpriteAnimation* desiredAnim = isAttacking && assets.GetTankAttackSheet().SheetTexture.id > 0
        ? &assets.GetTankAttackAnimation()
        : &assets.GetTankWalkAnimation();

    if (desiredSheet != nullptr && desiredAnim != nullptr && spriteInstance.Animation != desiredAnim)
    {
        spriteInstance.Sheet = desiredSheet;
        spriteInstance.Animation = desiredAnim;
        SetSpriteAnimation(spriteInstance, *desiredAnim);
    }

    if (useAnimation && spriteInstance.Sheet != nullptr && spriteInstance.Animation != nullptr)
    {
        spriteInstance.Position = pos;
        spriteInstance.Offset = { GetTextureScale() * spriteInstance.Sheet->Frames[0].width / 2.0f,
                                 GetTextureScale() * spriteInstance.Sheet->Frames[0].height / 2.0f };

        spriteInstance.FrameLifetime += dt;
        if (spriteInstance.FrameLifetime > 1.0f / spriteInstance.Animation->FPS)
        {
            spriteInstance.FrameLifetime = 0;
            spriteInstance.CurrentFrame++;
            spriteInstance.AnimationDone = false;
            if (spriteInstance.CurrentFrame > spriteInstance.Animation->EndFrame)
            {
                if (spriteInstance.Animation->Loops)
                    spriteInstance.CurrentFrame = spriteInstance.Animation->StartFrame;
                else
                {
                    spriteInstance.AnimationDone = true;
                    spriteInstance.CurrentFrame--;
                    isAttacking = false;
                }
            }
        }
    }
}

void TankEnemy::PlayAttackAnimation(const GameAssets& assets)
{
    if (assets.GetTankAttackSheet().SheetTexture.id <= 0) return;

    isAttacking = true;
    spriteInstance.Sheet = &assets.GetTankAttackSheet();
    spriteInstance.Animation = &assets.GetTankAttackAnimation();
    SetSpriteAnimation(spriteInstance, assets.GetTankAttackAnimation());
    useAnimation = true;
}

void TankEnemy::Draw(const GameAssets& assets) const
{
    if (!IsAlive()) return;

    if (useAnimation && spriteInstance.Sheet != nullptr && spriteInstance.CurrentFrame >= 0)
    {
        float scale = GetTextureScale();
        Rectangle frame = spriteInstance.Sheet->Frames[spriteInstance.CurrentFrame];

        Rectangle destRec = { pos.x - (frame.width * scale) / 2.0f, pos.y - (frame.height * scale) / 2.0f,
                              frame.width * scale, frame.height * scale };

        DrawTexturePro(spriteInstance.Sheet->SheetTexture, frame, destRec, { 0, 0 }, 0.0f, WHITE);
    }
    else
    {
        Enemy::Draw(assets);
    }

    float lifePercent = (float)health / maxHealth * 100.0f;
    Vector2 lifePos = GetLifeBarPosition();

    if (gamePtr->GetLifeBarButton())
    {
        DrawTextureEx(assets.GetLifeTexture(lifePercent), lifePos, 0, 1.5f, WHITE);
    }

    if (gamePtr->GetDamageNumberButton())
    {
        Vector2 baseDrawPos = { pos.x, pos.y - 40.0f };

        for (const auto& damageText : floatingDamages)
        {
            float progress = 1.0f - (damageText.timeRemaining / damageText.duration);

            const float maxHeight = 40.0f;
            float jumpFactor = 4.0f * progress * (1.0f - progress);
            float jumpOffset = jumpFactor * maxHeight;

            float alpha = damageText.timeRemaining / damageText.duration;
            Color drawColor = Fade(WHITE, alpha);

            Vector2 textPos = baseDrawPos;
            textPos.x += (damageText.startPos.x - pos.x);
            textPos.y -= jumpOffset;

            DrawTextPro(assets.GetMedievalFont(), TextFormat("%i", damageText.value), textPos, { 0.0f, 0.0f }, 0.0f, 30.0f, 2.0f, drawColor);
        }
    }
}

BossEnemy::BossEnemy(Vector2 startPos, const Game& settings, float healthMultiplier, float speedMultiplier)
    : Enemy(startPos, settings, healthMultiplier, speedMultiplier)
{
    InitializeStats(healthMultiplier);
}

Texture2D BossEnemy::GetTexture(const GameAssets& assets) const
{
    if (bossTextureIndex == 1) return assets.GetBoss1Texture();
    if (bossTextureIndex == 2) return assets.GetBoss2Texture();
    if (bossTextureIndex == 3) return assets.GetBoss3Texture();
    return assets.GetBoss4Texture(); // Fallback ou Boss 4
}

std::unique_ptr<Enemy> CreateEnemy(EnemyType type, Vector2 startPos, const Game& settings, float healthMultiplier, float speedMultiplier)
{
    switch (type)
    {
    case EnemyType::FAST:
        return std::make_unique<FastEnemy>(startPos, settings, healthMultiplier, speedMultiplier);
    case EnemyType::NORMAL:
        return std::make_unique<NormalEnemy>(startPos, settings, healthMultiplier, speedMultiplier);
    case EnemyType::TANK:
        return std::make_unique<TankEnemy>(startPos, settings, healthMultiplier, speedMultiplier);
    case EnemyType::BOSS:
        return std::make_unique<BossEnemy>(startPos, settings, healthMultiplier, speedMultiplier);
    default:
        return std::make_unique<NormalEnemy>(startPos, settings, healthMultiplier, speedMultiplier);
    }
}