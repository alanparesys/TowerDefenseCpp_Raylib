#ifndef GAME_H
#define GAME_H

#include <raylib.h>

// --- 1. ENUMS (Doivent être déclarés en premier) ---
enum CurrentScreen
{
    TITLE,
    CHOOSE_LEVEL,
    GAMEPLAY,
    GAMEOVER
};

enum TowerType
{
    NONE = 0,
    ARCHER,
    WIZARD,
    CATAPULT
};

enum EnemyType
{
    NORMAL = 0,
    FAST,
	TANK,
    BOSS
};

// --- 2. STRUCTS (Utilisent les Enums) ---
struct Tower {
    Vector2 pos;
    int range;
    bool exist;
};

struct Castle {
    Vector2 pos;
	int life;
	int maxLife;
    bool exist;
};

struct Enemy {
    Vector2 pos;
    int health;
	int maxLife;
	int damage;
	float attackCooldown;
    int nextPoint;
	bool moving;
    bool alive;
	EnemyType type;
};

struct Bullet {
    Vector2 pos;
    Vector2 speed;
    bool active;
    TowerType type; // Maintenant TowerType est reconnu car déclaré au-dessus
};

struct GameAssets
{
    Texture2D mouseTexture;
    Texture2D titleScreenTexture;
    Texture2D levelSelectionTexture;
    Texture2D shopIconTexture;
    
    // life
	Texture2D fullLifeTexture;
	Texture2D life1Texture;
	Texture2D life2Texture;
	Texture2D life3Texture;
    Texture2D life4Texture;
    Texture2D life5Texture;
    Texture2D life6Texture;
    Texture2D life7Texture;
    Texture2D life8Texture;
    Texture2D life9Texture;
    Texture2D life10Texture;
    Texture2D life11Texture;
    Texture2D life12Texture;
    Texture2D life13Texture;
    Texture2D life14Texture;
    Texture2D life15Texture;

    Texture2D castleTexture;
    Texture2D archerTexture;
    Texture2D wizardTexture;
	Texture2D fireBallTexture;
    Texture2D catapultTexture;
    Texture2D lvl1ArcherTowerTexture;
    Texture2D lvl1WizardTowerTexture;
    Texture2D lvl1CatapultTowerTexture;

    Texture2D necromancerTexture;
	Texture2D ferretTexture;
    Texture2D cacodaemonTexture;
};

// --- 3. PROTOTYPES DE FONCTIONS ---

void GameInit();

void LoadGameAssets(GameAssets& assets);
void UnloadGameAssets(GameAssets& assets);

void GameUpdate(GameAssets& assets);
void CustomMouse(GameAssets& assets);
void GameDraw(const GameAssets& assets);
void DrawLifeBar(const GameAssets& assets);

void UpdateTitle(const GameAssets& assets);
void UpdateChooseLevel(const GameAssets& assets);
void UpdateGameplay(const GameAssets& assets);
void UpdateGameOver();

void CastlePlacement();
void TowersPlacement();

void AddCastle(Vector2 mousePos);
void AddArcherTower(Vector2 mousePos);
void AddWizardTower(Vector2 mousePos);
void AddCatapultTower(Vector2 mousePos);
void AddEnemy();
void MoveEnemies();
void EnemiesAttack();


// J'ai ajouté le point-virgule manquant ici
void ShootBullet(Vector2 from, Vector2 to, TowerType type);

void CastlesShoot();
void TowerShoot();
void MoveBullets();
void DrawVectorLines();
void CreatePath(Vector2 castlePos);

#endif // Fin du fichier