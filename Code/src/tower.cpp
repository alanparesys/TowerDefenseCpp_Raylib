#include "tower.h"
#include "game.h"
#include "assets.h"

float Tower::GetRange(TowerLvl currentLvl) const
{
    switch (type)
    {
    case TowerType::ARCHER:
        switch (currentLvl)
        {
        case TowerLvl::LVL1: return 200.0f;
        case TowerLvl::LVL2: return 210.0f;
        case TowerLvl::LVL3: return 220.0f;
        case TowerLvl::LVL4: return 230.0f;
        case TowerLvl::LVL5: return 245.0f;
        case TowerLvl::LVL6: return 260.0f;
        case TowerLvl::LVL7: return 280.0f;
        default: return 150.0f;
        }

    case TowerType::WIZARD:
        switch (currentLvl)
        {
        case TowerLvl::LVL1: return 200.0f;
        case TowerLvl::LVL2: return 210.0f;
        case TowerLvl::LVL3: return 220.0f;
        case TowerLvl::LVL4: return 230.0f;
        case TowerLvl::LVL5: return 245.0f;
        case TowerLvl::LVL6: return 260.0f;
        case TowerLvl::LVL7: return 280.0f;
        default: return 200.0f;
        }

    case TowerType::CATAPULT:
        switch (currentLvl)
        {
        case TowerLvl::LVL1: return 350.0f;
        case TowerLvl::LVL2: return 380.0f;
        case TowerLvl::LVL3: return 410.0f;
        case TowerLvl::LVL4: return 450.0f;
        case TowerLvl::LVL5: return 500.0f;
        case TowerLvl::LVL6: return 550.0f;
        case TowerLvl::LVL7: return 600.0f;
        default: return 350.0f;
        }
    default: return 0.0f;
    }
}
float Tower::GetAttackCooldown(TowerLvl currentLvl) const
{
    switch (type)
    {
    case TowerType::ARCHER:
        switch (currentLvl)
        {
        case TowerLvl::LVL1: return 0.60f;
        case TowerLvl::LVL2: return 0.55f;
        case TowerLvl::LVL3: return 0.50f;
        case TowerLvl::LVL4: return 0.45f;
        case TowerLvl::LVL5: return 0.35f;
        case TowerLvl::LVL6: return 0.25f;
        case TowerLvl::LVL7: return 0.15f;
        default: return 0.60f;
        }

    case TowerType::WIZARD:
        switch (currentLvl)
        {
        case TowerLvl::LVL1: return 1.00f;
        case TowerLvl::LVL2: return 0.95f;
        case TowerLvl::LVL3: return 0.90f;
        case TowerLvl::LVL4: return 0.80f;
        case TowerLvl::LVL5: return 0.70f;
        case TowerLvl::LVL6: return 0.60f;
        case TowerLvl::LVL7: return 0.50f;
        default: return 1.00f;
        }

    case TowerType::CATAPULT:
        switch (currentLvl)
        {
        case TowerLvl::LVL1: return 2.5f;
        case TowerLvl::LVL2: return 2.3f;
        case TowerLvl::LVL3: return 2.1f;
        case TowerLvl::LVL4: return 1.9f;
        case TowerLvl::LVL5: return 1.7f;
        case TowerLvl::LVL6: return 1.5f;
        case TowerLvl::LVL7: return 1.2f;
        default: return 2.5f;
        }
    default: return 1.0f;
    }
}

int Tower::GetDamage() const
{
    switch (type)
    {
    case TowerType::ARCHER:
        switch (lvl)
        {
        case TowerLvl::LVL1: return 12;
        case TowerLvl::LVL2: return 18;
        case TowerLvl::LVL3: return 25;
        case TowerLvl::LVL4: return 35;
        case TowerLvl::LVL5: return 50;
        case TowerLvl::LVL6: return 70;
        case TowerLvl::LVL7: return 100;
        default: return 12;
        }

    case TowerType::WIZARD:
        switch (lvl)
        {
        case TowerLvl::LVL1: return 25;
        case TowerLvl::LVL2: return 35;
        case TowerLvl::LVL3: return 45;
        case TowerLvl::LVL4: return 60;
        case TowerLvl::LVL5: return 75;
        case TowerLvl::LVL6: return 90;
        case TowerLvl::LVL7: return 11000;
        default: return 25;
        }

    case TowerType::CATAPULT:
        switch (lvl)
        {
        case TowerLvl::LVL1: return 110;
        case TowerLvl::LVL2: return 140;
        case TowerLvl::LVL3: return 180;
        case TowerLvl::LVL4: return 250;
        case TowerLvl::LVL5: return 350;
        case TowerLvl::LVL6: return 500;
        case TowerLvl::LVL7: return 800;
        default: return 110;
        }
    default: return 0;
    }
}

int Tower::GetUpgradeCost() const
{
    if (lvl == TowerLvl::LVL7) return 0;

    switch (type)
    {
    case TowerType::ARCHER:
        switch (lvl)
        {
        case TowerLvl::LVL1: return 75;
        case TowerLvl::LVL2: return 100;
        case TowerLvl::LVL3: return 150;
        case TowerLvl::LVL4: return 250;
        case TowerLvl::LVL5: return 400;
        case TowerLvl::LVL6: return 600;
        default: return 0;
        }

    case TowerType::WIZARD:
        switch (lvl)
        {
        case TowerLvl::LVL1: return 125;
        case TowerLvl::LVL2: return 175;
        case TowerLvl::LVL3: return 275;
        case TowerLvl::LVL4: return 450;
        case TowerLvl::LVL5: return 700;
        case TowerLvl::LVL6: return 1100;
        default: return 0;
        }

    case TowerType::CATAPULT:
        switch (lvl)
        {
        case TowerLvl::LVL1: return 200;
        case TowerLvl::LVL2: return 300;
        case TowerLvl::LVL3: return 500;
        case TowerLvl::LVL4: return 800;
        case TowerLvl::LVL5: return 1200;
        case TowerLvl::LVL6: return 1800;
        default: return 0;
        }
    default: return 0;
    }
}

void Tower::ApplyUpgradeStats()
{
    range = GetRange(lvl);
    attackCooldown = GetAttackCooldown(lvl);
}


Tower::Tower(Vector2 position, TowerType type) : pos(position), type(type), attackTimer(0.0f), lvl(TowerLvl::LVL1)
{
    range = GetRange(TowerLvl::LVL1);
    attackCooldown = GetAttackCooldown(TowerLvl::LVL1);
}

void Tower::Update(float deltaTime)
{
    attackTimer += deltaTime;
}

void Tower::UpgradeLvl(const GameAssets& assets)
{
    Rectangle upgradeButtonHitbox = GetUpgradeHitbox();
    Vector2 mouse = GetMousePosition();
    PlaySound(assets.GetLevelUpSound());
    if (CheckCollisionPointRec(mouse, upgradeButtonHitbox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        switch (lvl)
        {
        case TowerLvl::LVL1: lvl = TowerLvl::LVL2; break;
        case TowerLvl::LVL2: lvl = TowerLvl::LVL3; break;
        case TowerLvl::LVL3: lvl = TowerLvl::LVL4; break;
        case TowerLvl::LVL4: lvl = TowerLvl::LVL5; break;
        case TowerLvl::LVL5: lvl = TowerLvl::LVL6; break;
        case TowerLvl::LVL6: lvl = TowerLvl::LVL7; break;
        default: return;
        }

        ApplyUpgradeStats();
    }
}

Rectangle Tower::GetUpgradeHitbox() const
{
    Vector2 currentTowerPos = GetAdjustedTowerPos();

    Vector2 upgradeButtonContainerPos = { currentTowerPos.x - 64, currentTowerPos.y - 128 };

    Rectangle upgradeButtonHitbox = { upgradeButtonContainerPos.x + 112.0f, upgradeButtonContainerPos.y + 54.0f, 32.0f, 36.0f };

    if (type == TowerType::ARCHER)
    {
        switch (lvl)
        {
        case TowerLvl::LVL4:
            upgradeButtonHitbox.y = upgradeButtonContainerPos.y + 55;
            break;

        case TowerLvl::LVL5:
            upgradeButtonHitbox.y = upgradeButtonContainerPos.y + 55;
            break;

        case TowerLvl::LVL6:
            upgradeButtonHitbox.y = upgradeButtonContainerPos.y + 55;
            break;

        default:
            break;
        }
    }

    if (type == TowerType::WIZARD)
    {
        switch (lvl)
        {
        case TowerLvl::LVL4:
            upgradeButtonHitbox.y = upgradeButtonContainerPos.y + 75;
            break;

        case TowerLvl::LVL5:
            upgradeButtonHitbox.y = upgradeButtonContainerPos.y + 96;
            break;

        case TowerLvl::LVL6:
            upgradeButtonHitbox.y = upgradeButtonContainerPos.y + 96;
            break;

        default:
            break;
        }
    }

    if (type == TowerType::CATAPULT)
    {
        switch (lvl)
        {
        case TowerLvl::LVL1:
            upgradeButtonHitbox.y = upgradeButtonContainerPos.y + 60;
            break;

        case TowerLvl::LVL2:
            upgradeButtonHitbox.y = upgradeButtonContainerPos.y + 60;
            break;

        case TowerLvl::LVL3:
            upgradeButtonHitbox.y = upgradeButtonContainerPos.y + 60;
            break;

        case TowerLvl::LVL4:
            upgradeButtonHitbox.x = upgradeButtonContainerPos.x + 127;
            upgradeButtonHitbox.y = upgradeButtonContainerPos.y + 60;
            break;

        case TowerLvl::LVL5:
            upgradeButtonHitbox.y = upgradeButtonContainerPos.y + 60;
            break;

        case TowerLvl::LVL6:
            upgradeButtonHitbox.y = upgradeButtonContainerPos.y + 60;
            break;

        default:
            break;
        }
    }
    return upgradeButtonHitbox;
}

Vector2 Tower::GetAdjustedTowerPos() const
{
    Vector2 basePos = { pos.x - 64, pos.y - 64 };

    if (type == TowerType::ARCHER)
    {
        switch (lvl)
        {
        case TowerLvl::LVL2:
            return basePos;

        case TowerLvl::LVL3:
            return { pos.x - 64, pos.y - 66 };

        case TowerLvl::LVL4:
            return { pos.x - 64, pos.y - 96 };

        case TowerLvl::LVL5:
            return { pos.x - 64, pos.y - 128 };

        case TowerLvl::LVL6:
            return { pos.x - 64, pos.y - 128 };

        case TowerLvl::LVL7:
            return { pos.x - 64, pos.y - 128 };

        default:
            return basePos;
        }
    }

    else if (type == TowerType::WIZARD)
    {
        switch (lvl)
        {
        case TowerLvl::LVL3:
            return basePos;

        case TowerLvl::LVL4:
            return { pos.x - 64, pos.y - 128 };

        case TowerLvl::LVL5:
            return { pos.x - 64, pos.y - 156 };

        case TowerLvl::LVL6:
            return { pos.x - 64, pos.y - 170 };

        case TowerLvl::LVL7:
            return { pos.x - 64, pos.y - 216 };

        default:
            return basePos;
        }
    }

    else if (type == TowerType::CATAPULT)
    {
        switch (lvl)
        {
        case TowerLvl::LVL3:
            return basePos;

        case TowerLvl::LVL4:
            return { pos.x - 79, pos.y - 64 };

        case TowerLvl::LVL5:
            return { pos.x - 64, pos.y - 64 };

        case TowerLvl::LVL6:
            return { pos.x - 64, pos.y - 96 };

        case TowerLvl::LVL7:
            return { pos.x - 64, pos.y - 128 };

        default:
            return basePos;
        }
    }

    return basePos;
}

void Tower::SetTarget(Vector2 targetPos)
{

    if (targetPos.x < pos.x)
    {
        facingLeft = true;
    }
    else
    {
        facingLeft = false;
    }
}

void Tower::Draw(const GameAssets& assets) const
{
    Vector2 towerPos = GetAdjustedTowerPos();
    Vector2 upgradeButtonPos = { towerPos.x - 64, towerPos.y - 128 };
    Vector2 unitPos = { pos.x - 50, pos.y - 75 };
    Texture2D towerTexture = assets.GetLvl1ArcherTowerTexture();
    Texture2D unitTexture;

    switch (lvl)
    {
    case TowerLvl::LVL1:
    case TowerLvl::LVL2:
    case TowerLvl::LVL3:
    case TowerLvl::LVL4:
    case TowerLvl::LVL5:
    case TowerLvl::LVL6:
    case TowerLvl::LVL7:
        switch (type)
        {
        case TowerType::ARCHER:
            if (lvl == TowerLvl::LVL1) { towerTexture = assets.GetLvl1ArcherTowerTexture(); }
            else if (lvl == TowerLvl::LVL2) { towerTexture = assets.GetLvl2ArcherTowerTexture(); }
            else if (lvl == TowerLvl::LVL3) { towerTexture = assets.GetLvl3ArcherTowerTexture(); unitPos = { pos.x - 50, pos.y - 100 }; }
            else if (lvl == TowerLvl::LVL4) { towerTexture = assets.GetLvl4ArcherTowerTexture(); unitPos = { pos.x - 50, pos.y - 125 }; }
            else if (lvl == TowerLvl::LVL5) { towerTexture = assets.GetLvl5ArcherTowerTexture(); unitPos = { pos.x - 50, pos.y - 135 }; }
            else if (lvl == TowerLvl::LVL6) { towerTexture = assets.GetLvl6ArcherTowerTexture(); unitPos = { pos.x - 50, pos.y - 135 }; }
            else if (lvl == TowerLvl::LVL7) { towerTexture = assets.GetLvl7ArcherTowerTexture(); unitPos = { pos.x - 50, pos.y - 135 }; }

            unitTexture = assets.GetArcherTexture();
            break;

        case TowerType::WIZARD:
            if (lvl == TowerLvl::LVL1) { towerTexture = assets.GetLvl1WizardTowerTexture(); unitPos = { pos.x - 50, pos.y - 90 }; }
            else if (lvl == TowerLvl::LVL2) { towerTexture = assets.GetLvl2WizardTowerTexture(); unitPos = { pos.x - 50, pos.y - 90 }; }
            else if (lvl == TowerLvl::LVL3) { towerTexture = assets.GetLvl3WizardTowerTexture(); unitPos = { pos.x - 50, pos.y - 90 }; }
            else if (lvl == TowerLvl::LVL4) { towerTexture = assets.GetLvl4WizardTowerTexture(); upgradeButtonPos = { towerPos.x - 64, towerPos.y - 107 }; unitPos = { pos.x - 50, pos.y - 127 }; }
            else if (lvl == TowerLvl::LVL5) { towerTexture = assets.GetLvl5WizardTowerTexture(); upgradeButtonPos = { towerPos.x - 64, towerPos.y - 88 };  unitPos = { pos.x - 50, pos.y - 135 }; }
            else if (lvl == TowerLvl::LVL6) { towerTexture = assets.GetLvl6WizardTowerTexture(); upgradeButtonPos = { towerPos.x - 64, towerPos.y - 85 };  unitPos = { pos.x - 50, pos.y - 143 }; }
            else if (lvl == TowerLvl::LVL7) { towerTexture = assets.GetLvl7WizardTowerTexture(); }

            unitTexture = assets.GetWizardTexture();
            break;

        case TowerType::CATAPULT:
            if (lvl == TowerLvl::LVL1) { towerTexture = assets.GetLvl1CatapultTowerTexture(); unitPos = { pos.x - 30, pos.y - 50 }; upgradeButtonPos = { towerPos.x - 64, towerPos.y - 125 }; }
            else if (lvl == TowerLvl::LVL2) { towerTexture = assets.GetLvl2CatapultTowerTexture(); unitPos = { pos.x - 30, pos.y - 50 }; upgradeButtonPos = { towerPos.x - 64, towerPos.y - 125 }; }
            else if (lvl == TowerLvl::LVL3) { towerTexture = assets.GetLvl3CatapultTowerTexture(); unitPos = { pos.x - 30, pos.y - 55 }; upgradeButtonPos = { towerPos.x - 64, towerPos.y - 125 }; }
            else if (lvl == TowerLvl::LVL4) { towerTexture = assets.GetLvl4CatapultTowerTexture(); upgradeButtonPos = { towerPos.x - 64, towerPos.y - 107 }; unitPos = { pos.x - 30, pos.y - 63 }; upgradeButtonPos = { towerPos.x - 49, towerPos.y - 125 }; }
            else if (lvl == TowerLvl::LVL5) { towerTexture = assets.GetLvl5CatapultTowerTexture(); upgradeButtonPos = { towerPos.x - 64, towerPos.y - 88 };  unitPos = { pos.x - 30, pos.y - 75 }; upgradeButtonPos = { towerPos.x - 64, towerPos.y - 125 }; }
            else if (lvl == TowerLvl::LVL6) { towerTexture = assets.GetLvl6CatapultTowerTexture(); unitPos = { pos.x - 30, pos.y - 100 }; upgradeButtonPos = { towerPos.x - 64, towerPos.y - 125 }; }
            else if (lvl == TowerLvl::LVL7) { towerTexture = assets.GetLvl7CatapultTowerTexture(); unitPos = { pos.x - 30, pos.y - 130 }; upgradeButtonPos = { towerPos.x - 64, towerPos.y - 125 }; }

            unitTexture = assets.GetCatapultTexture();
            break;

        default:
            return;
        }
        break;

    default:
        return;
    }

    DrawCircleLinesV(pos, range, Fade(WHITE, 0.3f));

    DrawTextureEx(towerTexture, towerPos, 0.0f, 2.0f, WHITE);

    if (!(type == TowerType::WIZARD && lvl == TowerLvl::LVL7))
    {
        float scale = (type == TowerType::WIZARD ? 0.8f : 0.75f);

        float sourceWidth = (float)unitTexture.width;
        if (!facingLeft) sourceWidth = -sourceWidth;

        Rectangle sourceRec = { 0.0f, 0.0f, sourceWidth, (float)unitTexture.height };

        Rectangle destRec = {
            unitPos.x,
            unitPos.y,
            (float)unitTexture.width * scale,
            (float)unitTexture.height * scale
        };
        Vector2 origin = { 0.0f, 0.0f };

        DrawTexturePro(unitTexture, sourceRec, destRec, origin, 0.0f, WHITE);
    }

    if (lvl != TowerLvl::LVL7)
    {
        Vector2 mouse = GetMousePosition();
        if (CheckCollisionPointCircle(mouse, pos, range + 20))
        {
            Rectangle upgradeButtonHitbox = GetUpgradeHitbox();

            Vector2 UpgradePrice = { upgradeButtonHitbox.x + 45, upgradeButtonHitbox.y + 10 };
            Vector2 upgradeCoinPos = { UpgradePrice.x + 35, UpgradePrice.y + 14 };
            Vector2 LevelPosition = { upgradeButtonHitbox.x - 70, upgradeButtonHitbox.y + 35 };

            DrawTextureEx(assets.GetAmelorationWithButtonTexture(), upgradeButtonPos, 0.0f, 1.0f, WHITE);

            DrawTextPro(assets.GetMedievalFont(), TextFormat("%i", GetUpgradeCost()), UpgradePrice, { 0.0f, 0.0f }, 20.0f, 20.0f, 2.0f, WHITE);

            DrawTextureEx(assets.GetCoinTexture(), upgradeCoinPos, 20.0f, 1.0f, WHITE);

            DrawTextPro(assets.GetMedievalFont(), TextFormat("Lvl : %i", (int)lvl + 1), LevelPosition, { 0.0f, 0.0f }, -20.0f, 20.0f, 2.0f, WHITE);
        }
    }
}