#pragma once

#include <raylib.h>
#include <vector>
#include <string>
#include <memory>

#include "enum.h"
#include "castle.h"
#include "tower.h"
#include "assets.h"
#include "pathpoint.h"
#include "level.h"
#include "wave_system.h"

class Enemy;
class Bullet;

typedef struct GameData {
    int masterVolume;
    int musicVolume;
    int sfxVolume;
    int maxUnlockedLevel;
    int bestWave;
} GameData;

class Game
{
private:
    CurrentScreen previousScreen;
    CurrentScreen currentScreen;
    CurrentLevel currentLevel;

    GameAssets assets;
    Castle mainCastle;
    Level level;
    WaveSystemClass waveSystem;
    TowerType currentDragState;

    std::vector<Tower> towers;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<Bullet> bullets;
    std::vector<PathPoint> path;

    Vector2 spawnPoint;
    Vector2 castlePosition;

    float spawnTimer;

    int currentWave;
    float waveSpawnTimer;
    float timeBetweenSpawns;
    float timeBetweenWaves;
    float waveCooldownTimer;
    bool isWaveActive;
    int enemiesSpawnedThisWave;
    int totalEnemiesInWave;
    float waveAnnouncementTimer;
    float currentWaveHealthMultiplier;
    float currentWaveSpeedMultiplier;
    int currentWaveIndex;
    int enemiesSpawned;
    float waveTimer;

    bool lifeBarButton = true;
    bool damageNumberButton = true;
    bool highlightPathButton = false;
    bool buildPauseButton = false;
    bool volumeButton = false;
    bool resetButton = false;
    bool creditsButton = false;

    bool canClickSettings = true;
    bool canClickHelp = true;

    bool gameplayHelpButton = false;
    bool towerHelpButton = false;
    bool enemyHelpButton = false;

    bool pauseGame = false;

    int money;

    int maxUnlockedLevel = 1;

    const Rectangle shopArcherRect;
    const Rectangle shopWizardRect;
    const Rectangle shopCatapultRect;

    const LevelData* currentLevelData = nullptr;
    
    int bestWave = 0;

    bool firstFrameTitleMusic = true;
    bool firstFrameGameplayMusic = false;
    bool firstFrameVictoryMusic = false;
    bool firstFrameGameOverMusic = false;
    bool isBossWaveActive = false;

    int masterVolume = 75;
    int musicVolume = 75;
    int sfxVolume = 75;

    float timeScale = 1.0f;

    bool canTowerBePlaced = true;

    void CreatePath(Vector2 castlePos);

    void LoadMapForLevel(CurrentLevel level);

    void AddEnemy(EnemyType type, float healthMult, float speedMult, bool spawnBehindLastEnemy = false);
    void AddLevelEnemy(EnemyType t);
    bool BuyTower(Vector2 mousePos, TowerType type, int cost);
    void AddTower(Vector2 mousePos, TowerType type);
    void ClearDeadEntities();
    void UpdateWaveSystem(float dt);
    void StartNewWave();
    void CalculateWaveEnemies();

    void SaveGameData();
    void LoadGameData();
    bool IsPositionOnPath(Vector2 position) const;
    void SetupLevel(CurrentLevel levelId);

    void UpdateTitle();
    void UpdateChooseLevel();
    void UpdateSettings();
    void UpdateHelp();
    void UpdateVolumeOptions();
    void UpdateGameplay(float dt);
    void UpdateVictory();
    void UpdateGameOver();

    void ApplySettings();
    void ApplyMasterVolume(float volume);
    void ApplyMusicVolume(float volume);
    void ApplySfxVolume(float volume);

    void DrawTitle() const;
    void DrawChooseLevel() const;
    void DrawSettings() const;
    void DrawHelp() const;

    void DrawLvl1() const;
    void DrawLvl2() const;
    void DrawLvl3() const;
    void DrawLvl4() const;
    void DrawLvl5() const;
    void DrawLvl6() const;
    void DrawLvl7() const;
    void DrawLvl8() const;
    void DrawLvl9() const;
    void DrawLvl10() const;
    void DrawLvl11() const;
    void DrawLvl12() const;
    void DrawLvl13() const;
    void DrawLvl14() const;
    void DrawLvl15() const;

    void DrawGameplay() const;
    void DrawVictory() const;
    void DrawGameOver() const;

public:
    Game();
    ~Game();

    void Init();
    void Update(float dt);
    void Draw();

    void PlayTitleAudio();
    void PlayGameplayAudio();
    void PlayVictoryAudio();
    void PlayGameOverAudio();

    void SetScreen(CurrentScreen newScreen);
    void LoadGame();
    void SaveGame();

    int GetMoney() const { return money; }
    void GainMoney(int amount) { money += amount; }

    bool IsLevelLocked(int levelNumber) const { return levelNumber > maxUnlockedLevel; }
    int GetMaxUnlockedLevel() const { return maxUnlockedLevel; }
    void SetMaxUnlockedLevel(int lvl) { maxUnlockedLevel = lvl; } // <--- Une seule fois !

    bool GetLifeBarButton() const { return lifeBarButton; }
    bool GetDamageNumberButton() const { return damageNumberButton; }
    bool GetHighlightPathButton() const { return highlightPathButton; }
    bool GetBuildPauseButton() const { return buildPauseButton; }
    bool GetVolumeButton() const { return volumeButton; }
    bool GetResetButton() const { return resetButton; }
    bool GetCreditsButton() const { return creditsButton; }

    bool GetCanClickSettings() const { return canClickSettings; }
    bool GetCanClickHelp() const { return canClickHelp; }

    bool GetPauseGame() const { return pauseGame; }
    bool GetCanTowerBePlaced() const { return canTowerBePlaced; }
    const GameAssets& GetAssets() const { return assets; }

    WaveSystemClass& GetWaveSystem() { return waveSystem; }
    int GetCurrentWave() const { return currentWave; }
    void SetTimeBetweenSpawns(float time) { timeBetweenSpawns = time; }
    void SetTimeBetweenWaves(float time) { timeBetweenWaves = time; }
    float GetTimeBetweenSpawns() const { return timeBetweenSpawns; }
    float GetTimeBetweenWaves() const { return timeBetweenWaves; }
    bool IsWaveActive() const { return isWaveActive; }
    int GetEnemiesSpawnedThisWave() const { return enemiesSpawnedThisWave; }
    int GetTotalEnemiesInWave() const { return totalEnemiesInWave; }
    float GetWaveCooldownTimer() const { return waveCooldownTimer; }
    float GetWaveAnnouncementTimer() const { return waveAnnouncementTimer; }

    void UnlockNextLevel(int currentLevelFinished) {
        if (currentLevelFinished == maxUnlockedLevel && maxUnlockedLevel < 15) {
            maxUnlockedLevel++;
            SaveGame();
        }
    }
};