#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

#include "game.h"

using namespace std;

Castle castle[1];
Tower towers[10];
Enemy enemies[1000];
Bullet bullets[1000];
TowerType towerTypes[10];

int const MAX_CASTLES = 1;
int const MAX_TOWERS = 10;
int const MAX_ENEMIES = 100;
int const MAX_BULLETS = 1000;

int castleCount = 0;
int towerCount = 0;
int enemyCount = 0;
int bulletCount = 0;

float spawnTimer = 0;

TowerType currentDragState = NONE;

Vector2 path[10];
int pathLength = 0;
Vector2 spawnPoint = { 0, 600 };

CurrentScreen currentScreen = TITLE;

const Rectangle shopArcherRect = { 1410, 1030, 130, 130 };
const Rectangle shopWizardRect = { 1580, 1030, 130, 130 };
const Rectangle shopCatapultRect = { 1750, 1030, 130, 130 };

void LoadGameAssets(GameAssets& assets)
{
    assets.mouseTexture = LoadTexture("assets/mouse_cursor.png");
	assets.titleScreenTexture = LoadTexture("assets/title_screen.png");
    assets.levelSelectionTexture = LoadTexture("assets/level_selection.png");
    assets.shopIconTexture = LoadTexture("assets/shop_icon.png");

    // life
    assets.fullLifeTexture = LoadTexture("Assets/life/full_life.png");
	assets.life1Texture = LoadTexture("Assets/life/life_1.png");
	assets.life2Texture = LoadTexture("Assets/life/life_2.png");
	assets.life3Texture = LoadTexture("Assets/life/life_3.png");
	assets.life4Texture = LoadTexture("Assets/life/life_4.png");
    assets.life5Texture = LoadTexture("Assets/life/life_5.png");
    assets.life6Texture = LoadTexture("Assets/life/life_6.png");
    assets.life7Texture = LoadTexture("Assets/life/life_7.png");
    assets.life8Texture = LoadTexture("Assets/life/life_8.png");
    assets.life9Texture = LoadTexture("Assets/life/life_9.png");
    assets.life10Texture = LoadTexture("Assets/life/life_10.png");
    assets.life11Texture = LoadTexture("Assets/life/life_11.png");
    assets.life12Texture = LoadTexture("Assets/life/life_12.png");
    assets.life13Texture = LoadTexture("Assets/life/life_13.png");
    assets.life14Texture = LoadTexture("Assets/life/life_14.png");
	assets.life15Texture = LoadTexture("Assets/life/life_15.png");

	assets.castleTexture = LoadTexture("Assets/castle/castle.png");
	assets.archerTexture = LoadTexture("Assets/archer_tower/archer.png");
    assets.wizardTexture = LoadTexture("Assets/wizard_tower/wizard.png");
	assets.fireBallTexture = LoadTexture("Assets/wizard_tower/fireBall.png");
	assets.catapultTexture = LoadTexture("Assets/catapult_tower/catapult.png");
	assets.lvl1ArcherTowerTexture = LoadTexture("Assets/archer_tower/archer_tower_lvl1.png");
	assets.lvl1WizardTowerTexture = LoadTexture("Assets/wizard_tower/wizard_tower_lvl1.png");
	assets.lvl1CatapultTowerTexture = LoadTexture("Assets/catapult_tower/catapult_tower_lvl1.png");

    // normal
	assets.necromancerTexture = LoadTexture("Assets/enemies/necromancer.png");
	// fast
	assets.ferretTexture = LoadTexture("Assets/enemies/ferret.png");
	// tank
	assets.cacodaemonTexture = LoadTexture("Assets/enemies/cacodaemon.png");
}

void UnloadGameAssets(GameAssets& assets)
{
    UnloadTexture(assets.mouseTexture);
	UnloadTexture(assets.titleScreenTexture);
    UnloadTexture(assets.levelSelectionTexture);
    UnloadTexture(assets.shopIconTexture);

    // life
	UnloadTexture(assets.fullLifeTexture);
	UnloadTexture(assets.life1Texture);
	UnloadTexture(assets.life2Texture);
    UnloadTexture(assets.life3Texture);
    UnloadTexture(assets.life4Texture);
    UnloadTexture(assets.life5Texture);
    UnloadTexture(assets.life6Texture);
    UnloadTexture(assets.life7Texture);
    UnloadTexture(assets.life8Texture);
    UnloadTexture(assets.life9Texture);
    UnloadTexture(assets.life10Texture);
    UnloadTexture(assets.life11Texture);
    UnloadTexture(assets.life12Texture);
    UnloadTexture(assets.life13Texture);
	UnloadTexture(assets.life14Texture);
	UnloadTexture(assets.life15Texture);

	UnloadTexture(assets.castleTexture);
	UnloadTexture(assets.archerTexture);
    UnloadTexture(assets.wizardTexture);
	UnloadTexture(assets.fireBallTexture);
	UnloadTexture(assets.catapultTexture);
    UnloadTexture(assets.lvl1ArcherTowerTexture);
	UnloadTexture(assets.lvl1WizardTowerTexture);
	UnloadTexture(assets.lvl1CatapultTowerTexture);

	UnloadTexture(assets.necromancerTexture);
	UnloadTexture(assets.ferretTexture);
	UnloadTexture(assets.cacodaemonTexture);
}

void CustomMouse(GameAssets& assets)
{
    Vector2 mousePos = GetMousePosition();

    if (assets.mouseTexture.id > 0)
    {
        float drawX = mousePos.x - assets.mouseTexture.width / 2 + 425;
        float drawY = mousePos.y - assets.mouseTexture.height / 2 + 188;

        DrawTextureEx(assets.mouseTexture, Vector2{ drawX, drawY }, 0.0f, 0.15f, WHITE);
    }
}

void GameUpdate(GameAssets& assets)
{
    switch (currentScreen)
    {
    case TITLE:
        UpdateTitle(assets);
        break;
    case CHOOSE_LEVEL:
        UpdateChooseLevel(assets);
        break;
    case GAMEPLAY:
        UpdateGameplay(assets);
        break;
    case GAMEOVER:
        UpdateGameOver();
        break;
    }
}

void UpdateTitle(const GameAssets& assets)
{
    DrawTexture(assets.titleScreenTexture, 0, 0, WHITE);

    const Rectangle levelsSelectionButton = { 1088, 736, 544, 189 };
    Vector2 mouse = GetMousePosition();
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (CheckCollisionPointRec(mouse, levelsSelectionButton))
        {
            currentScreen = CHOOSE_LEVEL;
        }
    }
}

void UpdateChooseLevel(const GameAssets& assets)
{
    DrawTexture(assets.levelSelectionTexture, 0, 0, WHITE);

	const Rectangle level1Button = { 332, 332, 103, 103 };
	Vector2 mouse = GetMousePosition();
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (CheckCollisionPointRec(mouse, level1Button))
        {
            currentScreen = GAMEPLAY;
        }
    }
}

void UpdateGameplay(const GameAssets& assets)
{
    ClearBackground(DARKGRAY);

    DrawRectangle(0, 0, 1920, 75, DARKGRAY);
    DrawTexture(assets.castleTexture, 0, 0, WHITE);

    GameDraw(assets);
    DrawLifeBar(assets);

    DrawText("1. CLIC: Placer tour (cree le chemin)", 10, 10, 20, WHITE);
    DrawText("2. ESPACE: Spawn ennemi", 10, 35, 20, WHITE);

    CastlePlacement();
    TowersPlacement();

	// manual spawn
    if (IsKeyPressed(KEY_SPACE)) AddEnemy();

	// auto spawn
    if (pathLength > 0) {
        spawnTimer += GetFrameTime();
        if (spawnTimer > 2.0f) {
            AddEnemy();
            spawnTimer = 0;
        }
    }

    MoveEnemies();
    // CastlesShoot();
    TowerShoot();
    MoveBullets();
}

void UpdateGameOver()
{
    // game over
}

void GameInit()
{
    srand(time(NULL));
    castleCount = 0;
    towerCount = 0;
    enemyCount = 0;
    bulletCount = 0;
    spawnTimer = 0;
    pathLength = 0;

    currentDragState = NONE; // Reset drag

    // Reset tableaux
    for (int i = 0; i < MAX_CASTLES; i++) {
        castle[i].exist = false;
        castle[i].life = 0;
        castle[i].maxLife = 0;
    }
    for (int i = 0; i < MAX_TOWERS; i++)
    {
        towers[i].exist = false;
        towerTypes[i] = NONE;
    }
    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies[i].alive = false;
        enemies[i].moving = false;
        enemies[i].attackCooldown = 0.0f;
        enemies[i].type = NORMAL;
        enemies[i].health = 0;
        enemies[i].maxLife = 0;
        enemies[i].damage = 0;
        enemies[i].nextPoint = 0;
    }
    for (int i = 0; i < MAX_BULLETS; i++) bullets[i].active = false;

    cout << "GAME START" << endl;
}

void CreatePath(Vector2 castlePos)
{
    pathLength = 0;
    path[pathLength++] = spawnPoint;
    Vector2 current = spawnPoint;
    Vector2 target = castlePos;
    int numPoints = 3 + (rand() % 3);

    for (int i = 0; i < numPoints; i++) {
        float t = (float)(i + 1) / (float)(numPoints + 1);
        float baseX = current.x + (target.x - current.x) * t;
        float baseY = current.y + (target.y - current.y) * t;
        float randomX = (float)((rand() % 400) - 200);
        float randomY = (float)((rand() % 400) - 200);

        Vector2 newPoint = { baseX + randomX, baseY + randomY };

        if (newPoint.x < 50) newPoint.x = 50;
        if (newPoint.x > 1700) newPoint.x = 1700;
        if (newPoint.y < 100) newPoint.y = 100;
        if (newPoint.y > 1100) newPoint.y = 1100;

        path[pathLength++] = newPoint;
    }
    path[pathLength++] = castlePos;
}

void CastlePlacement()
{
    Vector2 mouse = GetMousePosition();
	// castle placement (only 1st click)
    if (!castle[0].exist && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (mouse.x < 1750 && mouse.y > 100) AddCastle(mouse);
        return;
    }
}


void TowersPlacement()
{
    Vector2 mouse = GetMousePosition();

    // Drag and Drop
    if (castle[0].exist)
    {
        // Drag
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && currentDragState == NONE)
        {
            if (CheckCollisionPointRec(mouse, shopArcherRect)) {
                currentDragState = ARCHER;
            }
            else if (CheckCollisionPointRec(mouse, shopWizardRect)) {
                currentDragState = WIZARD;
            }
            else if (CheckCollisionPointRec(mouse, shopCatapultRect)) {
                currentDragState = CATAPULT;
            }
        }

        // Drop
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && currentDragState != NONE)
        {
			// Verified drop zone
            if (mouse.y < 1000 && mouse.x < 1800 && mouse.y > 100)
            {
                switch (currentDragState)
                {
                case ARCHER: AddArcherTower(mouse); break;
                case WIZARD: AddWizardTower(mouse); break;
                case CATAPULT: AddCatapultTower(mouse); break;
                default: break;
                }
            }
			// Reinitialize drag state
            currentDragState = NONE;
        }
    }
}

void AddCastle(Vector2 mousePos)
{
    if (castleCount >= MAX_CASTLES) return;
    castle[castleCount].pos = mousePos;
    castle[castleCount].exist = true;
	castle[castleCount].life = 100;
	castle[castleCount].maxLife = 100;
    castleCount++;
    CreatePath(mousePos);
}

void AddArcherTower(Vector2 mousePos)
{
    if (towerCount >= MAX_TOWERS) return;
    towers[towerCount].pos = mousePos;
    towers[towerCount].exist = true;
    towers[towerCount].range = 250;
    towerTypes[towerCount] = ARCHER;
	bullets[bulletCount].type = ARCHER;
    towerCount++;
}

void AddWizardTower(Vector2 mousePos)
{
    if (towerCount >= MAX_TOWERS) return;
    towers[towerCount].pos = mousePos;
    towers[towerCount].exist = true;
    towers[towerCount].range = 200;
    towerTypes[towerCount] = WIZARD;
    bullets[bulletCount].type = WIZARD;
    towerCount++;
}

void AddCatapultTower(Vector2 mousePos)
{
    if (towerCount >= MAX_TOWERS) return;
    towers[towerCount].pos = mousePos;
    towers[towerCount].exist = true;
    towers[towerCount].range = 300;
    towerTypes[towerCount] = CATAPULT;
    bullets[bulletCount].type = CATAPULT;
    towerCount++;
}


void AddEnemy() {
    if (enemyCount >= MAX_ENEMIES || pathLength == 0) return;
    
    enemies[enemyCount].pos = path[0];

    // Définir le type au spawn (ici aléatoire entre NORMAL, FAST, TANK)
    int r = GetRandomValue(1, 3);
    if (r == 1) enemies[enemyCount].type = NORMAL;
    else if (r == 2) enemies[enemyCount].type = FAST;
    else enemies[enemyCount].type = TANK;

    // Initialiser la santé et degats selon le type assigné
    switch (enemies[enemyCount].type)
    {
    case NORMAL:
        enemies[enemyCount].health = 100;
        enemies[enemyCount].maxLife = 100;
		enemies[enemyCount].damage = 50;
        break;
    case FAST:
        enemies[enemyCount].health = 70;
        enemies[enemyCount].maxLife = 70;
        enemies[enemyCount].damage = 25;
        break;
    case TANK:
        enemies[enemyCount].health = 200;
		enemies[enemyCount].maxLife = 200;
        enemies[enemyCount].damage = 100;
        break;
    default:
        enemies[enemyCount].health = 100;
		enemies[enemyCount].maxLife = 100;
        break;
    }

    enemies[enemyCount].nextPoint = 1;
    enemies[enemyCount].alive = true;
	enemies[enemyCount].moving = true;
    enemies[enemyCount].attackCooldown = 0.0f;

    enemyCount++;

}

void MoveEnemies()
{
    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        if (!enemies[i].alive) continue;

        // If enemy reached the final point, stop moving (will attack castle)
        if (enemies[i].nextPoint >= pathLength)
        {
            enemies[i].moving = false;
            continue;
        }

        // Move along path
        Vector2 target = path[enemies[i].nextPoint];
        float dx = target.x - enemies[i].pos.x;
        float dy = target.y - enemies[i].pos.y;
        float dist = sqrt(dx * dx + dy * dy);
        if (dist < 10)
        {
            enemies[i].nextPoint++;
            // if nextPoint now equals pathLength, enemy will stop next frame and attack
            if (enemies[i].nextPoint >= pathLength) enemies[i].moving = false;
        }
        else
        {
            // Utiliser le type stocké dans l'ennemi pour définir sa vitesse
            float speedMultiplier = 1.0f;
            switch (enemies[i].type)
            {
            case NORMAL:
                speedMultiplier = 2.0f;
                break;
            case FAST:
                speedMultiplier = 4.0f;
                break;
            case TANK:
                speedMultiplier = 1.25f;
                break;
            default:
                speedMultiplier = 2.0f;
                break;
            }

            enemies[i].pos.x += (dx / dist) * speedMultiplier;
            enemies[i].pos.y += (dy / dist) * speedMultiplier;
            enemies[i].moving = true;
        }
    }
}
void EnemiesAttack()
{
    if (!castle[0].exist) return;

    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        if (!enemies[i].alive) continue;

        // If enemy still moving, skip attack logic for this enemy
        if (enemies[i].moving) continue;

        // Enemy reached castle (or stopped): handle attack cooldown & damage
        switch (enemies[i].type)
        {
        case NORMAL:
            enemies[i].attackCooldown += GetFrameTime();
            if (enemies[i].attackCooldown >= 1.0f)
            {
                castle[0].life -= enemies[i].damage;
                enemies[i].attackCooldown = 0.0f;
            }
            break;
        case FAST:
            enemies[i].attackCooldown += GetFrameTime();
            if (enemies[i].attackCooldown >= 0.5f)
            {
                castle[0].life -= enemies[i].damage;
                enemies[i].attackCooldown = 0.0f;
            }
            break;
        case TANK:
            enemies[i].attackCooldown += GetFrameTime();
            if (enemies[i].attackCooldown >= 2.0f)
            {
                castle[0].life -= enemies[i].damage;
                enemies[i].attackCooldown = 0.0f;
            }
            break;
        default:
            enemies[i].attackCooldown += GetFrameTime();
            if (enemies[i].attackCooldown >= 1.0f)
            {
                castle[0].life -= enemies[i].damage;
                enemies[i].attackCooldown = 0.0f;
            }
            break;
        }
    }
}

void ShootBullet(Vector2 from, Vector2 to, TowerType type)
{
    if (bulletCount >= MAX_BULLETS) return;
    float dx = to.x - from.x; float dy = to.y - from.y; float dist = sqrt(dx * dx + dy * dy);
    bullets[bulletCount].pos = from;
    bullets[bulletCount].speed = { (dx / dist) * 8.0f, (dy / dist) * 8.0f };
    bullets[bulletCount].active = true;
    bullets[bulletCount].type = type;
    bulletCount++;
}
/*
void CastlesShoot() {
    static float cooldown[MAX_CASTLES] = { 0 };
    for (int t = 0; t < MAX_CASTLES; t++)
    {
        if (!castle[t].exist) continue;
        cooldown[t] += GetFrameTime();

        if (cooldown[t] < 0.8f) continue;
        for (int e = 0; e < MAX_ENEMIES; e++)
        {
            if (!enemies[e].alive) continue;

            if (CheckCollisionCircles(enemies[e].pos, 30, castle[t].pos, 325))
            {
                ShootBullet(castle[t].pos, enemies[e].pos);
                cooldown[t] = 0;
                break;
            }
        }
    }
}
*/
void TowerShoot()
{
    static float cooldown[MAX_TOWERS] = { 0 };
    for (int t = 0; t < MAX_TOWERS; t++)
    {
        if (!towers[t].exist) continue;
        cooldown[t] += GetFrameTime();

        // cooldown
        if (towerTypes[t] == ARCHER)
        {
            if (cooldown[t] < 0.5f) continue;
        }

        if (towerTypes[t] == WIZARD)
        {
            if (cooldown[t] < 1.5f) continue;
        }

        if (towerTypes[t] == CATAPULT)
        {
            if (cooldown[t] < 3.0f) continue;
        }

        for (int e = 0; e < MAX_ENEMIES; e++)
        {
            if (!enemies[e].alive) continue;
            if (CheckCollisionCircles(enemies[e].pos, 30, towers[t].pos, towers[t].range))
            {
                ShootBullet(towers[t].pos, enemies[e].pos, towerTypes[t]);
                cooldown[t] = 0;
                break;
            }
        }
    }
}

void MoveBullets()
{
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (!bullets[i].active) continue;

		// bullet movement
        bullets[i].pos.x += bullets[i].speed.x;
        bullets[i].pos.y += bullets[i].speed.y;

		// left screen
        if (bullets[i].pos.x < 0 || bullets[i].pos.x > 1920 || bullets[i].pos.y < 0)
        {
            bullets[i].active = false;
            continue;
        }

		// collision with enemies
        for (int e = 0; e < MAX_ENEMIES; e++)
        {
			// Only check alive enemies
            if (enemies[e].alive && CheckCollisionCircles(bullets[i].pos, 10, enemies[e].pos, 30))
            {
				// Different behavior based on bullet type
                if (bullets[i].type == ARCHER)
                {
                    // 1 hit
                    enemies[e].health -= 20;
                    if (enemies[e].health <= 0) enemies[e].alive = false;
                }
                else if (bullets[i].type == WIZARD || bullets[i].type == CATAPULT)
                {
					// Zone damage
                    float explosionRadius = 0;
                    int damageAmount = 0;

                    if (bullets[i].type == WIZARD) {
                        explosionRadius = 35.0f; // Radius
                        damageAmount = 60;      // Damage
                    }
                    else { // CATAPULT
                        explosionRadius = 50.0f;
                        damageAmount = 100;
                    }

					// Apply damage to all enemies within the explosion radius
                    for (int j = 0; j < MAX_ENEMIES; j++) {
                        if (!enemies[j].alive) continue;

						// Check collision with explosion radius
                        if (CheckCollisionCircles(bullets[i].pos, explosionRadius, enemies[j].pos, 30)) {
                            enemies[j].health -= damageAmount;
                            if (enemies[j].health <= 0) enemies[j].alive = false;
                        }
                    }
                    // Visual Effect
                }
                // destoy bullet after impact
                bullets[i].active = false;
                break;
            }
        }
    }
}

void DrawVectorLines() {
}

void GameDraw(const GameAssets& assets)
{
    // Path
    if (pathLength > 0) {
        for (int i = 0; i < pathLength - 1; i++) DrawLineEx(path[i], path[i + 1], 3.0f, Fade(RED, 0.4f));
        for (int i = 0; i < pathLength; i++) DrawCircleV(path[i], 8, Fade(GREEN, 0.6f));
    }

    // Shop UI (Fond des boutons)
    DrawTexture(assets.shopIconTexture, (int)shopArcherRect.x, (int)shopArcherRect.y, WHITE);
    DrawTexture(assets.shopIconTexture, (int)shopWizardRect.x, (int)shopWizardRect.y, WHITE);
    DrawTexture(assets.shopIconTexture, (int)shopCatapultRect.x, (int)shopCatapultRect.y, WHITE);

    // castle
    for (int i = 0; i < MAX_CASTLES; i++)
        if (castle[i].exist) {
            DrawCircleV(castle[i].pos, 60, BLUE);
            DrawCircleLinesV(castle[i].pos, 325, Fade(ORANGE, 0.3f));
        }

    // Placement Château (Ghost)
    if (!castle[0].exist) {
        Vector2 mouse = GetMousePosition();
        if (mouse.x < 1750 && mouse.y > 100) DrawCircleV(mouse, 60, Fade(BLUE, 0.3f));
    }

    // --- Dessin des Tours Existantes ---
    for (int i = 0; i < MAX_TOWERS; i++)
    {
        if (towers[i].exist)
        {
            // On centre l'image (offset 64 car scale 2.0 * 64px width / 2 = 64)
            Vector2 towerPos = { towers[i].pos.x - 64, towers[i].pos.y - 64 };
			Vector2 archerPos = { towers[i].pos.x - 50, towers[i].pos.y - 75 };
			Vector2 wizardPos = { towers[i].pos.x - 64, towers[i].pos.y - 105 };
			Vector2 catapultPos = { towers[i].pos.x - 40, towers[i].pos.y - 65 };

            // On utilise le tableau towerTypes pour savoir quelle texture dessiner
            if (towerTypes[i] == ARCHER) {
                DrawTextureEx(assets.lvl1ArcherTowerTexture, towerPos, 0, 2, WHITE);
                DrawTextureEx(assets.archerTexture, archerPos, 0, 0.75, WHITE);
                DrawCircleLinesV(towers[i].pos, 250, Fade(WHITE, 0.3f));
            }
            else if (towerTypes[i] == WIZARD) {
                DrawTextureEx(assets.lvl1WizardTowerTexture, towerPos, 0, 2, WHITE);
                DrawTextureEx(assets.wizardTexture, wizardPos, 0, 1, WHITE);
                DrawCircleLinesV(towers[i].pos, 200, Fade(WHITE, 0.3f));
            }
            else if (towerTypes[i] == CATAPULT) {
                DrawTextureEx(assets.lvl1CatapultTowerTexture, towerPos, 0, 2, WHITE);
				DrawTextureEx(assets.catapultTexture, catapultPos, 0, 1, WHITE);
                DrawCircleLinesV(towers[i].pos, 300, Fade(WHITE, 0.3f));
            }
            
        }
    }

    // --- Dessin du Drag & Drop (Ghost Tower sous la souris) ---
    if (currentDragState != NONE)
    {
        Vector2 mouse = GetMousePosition();
		Vector2 archerDragPos = { mouse.x - 50, mouse.y - 55 }; // Centrage
        Vector2 wizardDragPos = { mouse.x - 64, mouse.y - 70 }; // Centrage
		Vector2 catapultDragPos = { mouse.x - 40, mouse.y - 45 }; // Centrage

        // On dessine la tour correspondant à ce qu'on drag, avec transparence
        switch (currentDragState)
        {
        case ARCHER:
            DrawTextureEx(assets.archerTexture, archerDragPos, 0, 0.80f, Fade(WHITE, 0.6f));
            DrawCircleLinesV(mouse, 250, Fade(WHITE, 0.3f)); // Portée prévisionnelle
            break;
        case WIZARD:
            DrawTextureEx(assets.wizardTexture/*lvl1WizardTowerTexture*/, wizardDragPos, 0, 1, Fade(WHITE, 0.6f));
            DrawCircleLinesV(mouse, 200, Fade(WHITE, 0.3f));
            break;
        case CATAPULT:
            DrawTextureEx(assets.catapultTexture, catapultDragPos, 0, 0.90f, Fade(WHITE, 0.6f));
            DrawCircleLinesV(mouse, 300, Fade(WHITE, 0.3f));
            break;
        default: break;
        }
    }

    // Ennemies
    for (int i = 0; i < MAX_ENEMIES; i++) if (enemies[i].alive)
    {
        switch (enemies[i].type)
        {
        case NORMAL:
            DrawTextureEx(assets.necromancerTexture, Vector2{ enemies[i].pos.x - 48, enemies[i].pos.y - 48 }, 0, 3, WHITE);
            break;
        case FAST:
            DrawTextureEx(assets.ferretTexture, Vector2{ enemies[i].pos.x - 48, enemies[i].pos.y - 48 }, 0, 3, WHITE);
            break;
        case TANK:
            DrawTextureEx(assets.cacodaemonTexture, Vector2{ enemies[i].pos.x - 48, enemies[i].pos.y - 48 }, 0, 2, WHITE);
            break;
        }
    }

	// Bullets
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (bullets[i].active)
        {
            switch (bullets[i].type)
            {
            case ARCHER:
                DrawCircleV(bullets[i].pos, 10, LIGHTGRAY);
                break;
            case WIZARD:
                DrawTextureEx(assets.fireBallTexture, Vector2{ bullets[i].pos.x - 16, bullets[i].pos.y - 16 }, 0, 1, ORANGE);
                break;
            case CATAPULT:
                DrawCircleV(bullets[i].pos, 15, BROWN);
                break;
            default:
                break;
            }
        }
    }

    // Spawn point
    DrawCircleV(spawnPoint, 15, GREEN);
    DrawText("SPAWN", 20, 580, 20, WHITE);

    // Icônes du magasin (Overlay final pour être sûr qu'elles sont au dessus)
    // Archer
    if (currentDragState != ARCHER)
    {
        DrawTextureEx(assets.archerTexture, Vector2{ 1410 + 25, 1030 + 18 }, 0, 0.80f, WHITE);
    }
    DrawText("$100", 1410 + 13 + 50 - MeasureText("$100", 20) / 2, 1030 + 13 + 85, 20, YELLOW);

    // Wizard
    if (currentDragState != WIZARD)
    {
        DrawTextureEx(assets.wizardTexture, Vector2{ 1580 + 13, 1030 + 5 }, 0, 1, WHITE);
	}
    DrawText("$150", 1580 + 13 + 50 - MeasureText("$150", 20) / 2, 1030 + 13 + 85, 20, YELLOW);

    // Catapult
    if (currentDragState != CATAPULT)
    {
        DrawTextureEx(assets.catapultTexture, Vector2{ 1750 + 40, 1030 + 30 }, 0, 0.90f, WHITE);
	}
    DrawText("$200", 1750 + 13 + 50 - MeasureText("$200", 20) / 2, 1030 + 13 + 85, 20, YELLOW);
}

void DrawLifeBar(const GameAssets& assets)
{

    // Life UI
    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        if (enemies[i].alive)
        {
            Vector2 enemyLifePos;
            switch (enemies[i].type)
            {
            case NORMAL:
                enemyLifePos = { enemies[i].pos.x - 50, enemies[i].pos.y - 70 };
                break;
            case FAST:
                enemyLifePos = { enemies[i].pos.x - 40, enemies[i].pos.y - 55 };
                break;
            case TANK:
                enemyLifePos = { enemies[i].pos.x - 30, enemies[i].pos.y - 70 };
                break;
            }

			float enemylifePercent = (enemies[i].health * 100) / enemies[i].maxLife;

            if (enemylifePercent == 100)
            {
                DrawTextureEx(assets.fullLifeTexture, enemyLifePos, 0, 1.5f, WHITE);
            }
            else if (enemylifePercent >= 93.5)
            {
                DrawTextureEx(assets.life1Texture, enemyLifePos, 0, 1.5f, WHITE);
            }
            else if (enemylifePercent >= 87)
            {
                DrawTextureEx(assets.life2Texture, enemyLifePos, 0, 1.5f, WHITE);
            }
            else if (enemylifePercent >= 80.5)
            {
                DrawTextureEx(assets.life3Texture, enemyLifePos, 0, 1.5f, WHITE);
            }
            else if (enemylifePercent >= 74)
            {
                DrawTextureEx(assets.life4Texture, enemyLifePos, 0, 1.5f, WHITE);
            }
            else if (enemylifePercent >= 67.5)
            {
                DrawTextureEx(assets.life5Texture, enemyLifePos, 0, 1.5f, WHITE);
            }
            else if (enemylifePercent >= 61)
            {
                DrawTextureEx(assets.life6Texture, enemyLifePos, 0, 1.5f, WHITE);
            }
            else if (enemylifePercent >= 54.5)
            {
                DrawTextureEx(assets.life7Texture, enemyLifePos, 0, 1.5f, WHITE);
            }
            else if (enemylifePercent >= 48)
            {
                DrawTextureEx(assets.life8Texture, enemyLifePos, 0, 1.5f, WHITE);
            }
            else if (enemylifePercent >= 41.5)
            {
                DrawTextureEx(assets.life9Texture, enemyLifePos, 0, 1.5f, WHITE);
            }
            else if (enemylifePercent >= 35)
            {
                DrawTextureEx(assets.life10Texture, enemyLifePos, 0, 1.5f, WHITE);
            }
            else if (enemylifePercent >= 28.5)
            {
                DrawTextureEx(assets.life11Texture, enemyLifePos, 0, 1.5f, WHITE);
            }
            else if (enemylifePercent >= 22)
            {
                DrawTextureEx(assets.life12Texture, enemyLifePos, 0, 1.5f, WHITE);
            }
            else if (enemylifePercent >= 15.5)
            {
                DrawTextureEx(assets.life13Texture, enemyLifePos, 0, 1.5f, WHITE);
            }
            else if (enemylifePercent >= 9)
            {
                DrawTextureEx(assets.life14Texture, enemyLifePos, 0, 1.5f, WHITE);
            }
            else if (enemylifePercent > 0)
            {
                DrawTextureEx(assets.life15Texture, enemyLifePos, 0, 1.5f, WHITE);
            }
        }
    }

	Vector2 castleLifePos = { castle[0].pos.x - 100, castle[0].pos.y - 175 };
	// castle life
    if (castle[0].exist)
    {
		float castleLifePercent = (castle[0].life * 100) / castle[0].maxLife;

        if (castleLifePercent == 100)
        {
            DrawTextureEx(assets.fullLifeTexture, castleLifePos, 0, 3.0f, WHITE);
        }
        else if (castleLifePercent >= 93.5)
        {
            DrawTextureEx(assets.life1Texture, castleLifePos, 0, 3.0f, WHITE);
        }
        else if (castleLifePercent >= 87)
        {
            DrawTextureEx(assets.life2Texture, castleLifePos, 0, 3.0f, WHITE);
        }
        else if (castleLifePercent >= 80.5)
        {
            DrawTextureEx(assets.life3Texture, castleLifePos, 0, 3.0f, WHITE);
        }
        else if (castleLifePercent >= 74)
        {
            DrawTextureEx(assets.life4Texture, castleLifePos, 0, 3.0f, WHITE);
        }
        else if (castleLifePercent >= 67.5)
        {
            DrawTextureEx(assets.life5Texture, castleLifePos, 0, 3.0f, WHITE);
        }
        else if (castleLifePercent >= 61)
        {
            DrawTextureEx(assets.life6Texture, castleLifePos, 0, 3.0f, WHITE);
        }
        else if (castleLifePercent >= 54.5)
        {
            DrawTextureEx(assets.life7Texture, castleLifePos, 0, 3.0f, WHITE);
        }
        else if (castleLifePercent >= 48)
        {
            DrawTextureEx(assets.life8Texture, castleLifePos, 0, 3.0f, WHITE);
        }
        else if (castleLifePercent >= 41.5)
        {
            DrawTextureEx(assets.life9Texture, castleLifePos, 0, 3.0f, WHITE);
        }
        else if (castleLifePercent >= 35)
        {
            DrawTextureEx(assets.life10Texture, castleLifePos, 0, 3.0f, WHITE);
        }
        else if (castleLifePercent >= 28.5)
        {
            DrawTextureEx(assets.life11Texture, castleLifePos, 0, 3.0f, WHITE);
        }
        else if (castleLifePercent >= 22)
        {
            DrawTextureEx(assets.life12Texture, castleLifePos, 0, 3.0f, WHITE);
        }
        else if (castleLifePercent >= 15.5)
        {
            DrawTextureEx(assets.life13Texture, castleLifePos, 0, 3.0f, WHITE);
        }
        else if (castleLifePercent >= 9)
        {
            DrawTextureEx(assets.life14Texture, castleLifePos, 0, 3.0f, WHITE);
        }
        else if (castleLifePercent > 0)
        {
            DrawTextureEx(assets.life15Texture, castleLifePos, 0, 3.0f, WHITE);
        }
	}
}
