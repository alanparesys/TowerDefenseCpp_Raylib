#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <raylib.h>
#include <fstream>

#include "game.h"
#include "enum.h"
#include "castle.h"
#include "tower.h"
#include "enemy.h"
#include "bullet.h"
#include "assets.h"
#include "pathpoint.h"
#include "level.h"
#include "wave_system.h"

using namespace std;

const char* SAVE_FILE_NAME = "gamedata.sav";

#include <string>
namespace {
    struct RandomMapData {
        std::string filePath;
        std::vector<Vector2> pathPoints;
        Vector2 castlePos{ 0.0f, 0.0f };
        Texture2D texture{ {0} };
        bool loaded = false;
    };

    static std::vector<RandomMapData> g_randomMaps;
    static int g_currentRandomMapIndex = -1;

    static const float g_pathPointRadius = 25.0f;
    static int g_mapChangeInterval = 1;

    static void RegisterRandomMaps()
    {
        g_randomMaps.clear();
        // Map 01 (Index 0)
        {
            RandomMapData m;
            m.filePath = "Assets/RandomMaps/map01tdf.png";
            m.pathPoints = {
                {0.0f, 620.0f},{200.0f, 620.0f},{360.0f, 670.0f},{470.0f, 790.0f},{640.0f, 860.0f},
                {1000.0f, 850.0f},{1137.0f, 780.0f},{1291.0f, 570.0f},{1396.0f, 475.0f},
                {1520.0f, 455.0f}
            };
            m.castlePos = { 1670.0f, 470.0f };
            g_randomMaps.push_back(std::move(m));
        }

        // Map 02 (Index 1)
        {
            RandomMapData m;
            m.filePath = "Assets/RandomMaps/map02tdf.png";
            m.pathPoints = {
                {165.0f, 85.0f},{167.0f, 881.0f},{541.0f, 881.0f},{532.0f, 98.0f},
                {923.0f, 94.0f},{927.0f, 881.0f},{1295.0f, 881.0f},{1287.0f, 463.0f},
                {1483.0f, 463.0f}
            };
            m.castlePos = { 1483.0f, 463.0f };
            g_randomMaps.push_back(std::move(m));
        }

        // Map 03 (Index 2)
        {
            RandomMapData m;
            m.filePath = "Assets/RandomMaps/Map03tdf.png";
            m.pathPoints = {
                {0.0f, 374.0f},{167.0f, 378.0f},{347.0f, 341.0f},{625.0f, 118.0f},{785.0f, 55.0f},
                {982.0f, 55.0f},{1157.0f, 130.0f},{1260.0f, 264.0f},{1295.0f, 419.0f},
                {1244.0f, 580.0f},{1101.0f, 640.0f},{945.0f, 645.0f},{643.0f, 463.0f},
                {488.0f, 511.0f},{354.0f, 611.0f},{291.0f, 735.0f},{306.0f, 883.0f},
                {433.0f, 972.0f},{606.0f, 974.0f},{770.0f, 926.0f},{938.0f, 890.0f},
                {1301.0f, 883.0f},{1444.0f, 798.0f},{1563.0f, 688.0f},{1598.0f, 516.0f},
                {1598.0f, 359.0f},{1591.0f, 203.0f}
            };
            m.castlePos = { 1591.0f, 203.0f };
            g_randomMaps.push_back(std::move(m));
        }
    }

    static void EnsureTextureLoaded(RandomMapData& m)
    {
        if (!m.loaded && !m.filePath.empty())
        {
            m.texture = LoadTexture(m.filePath.c_str());
            m.loaded = (m.texture.id > 0);
        }
    }

    static int GetRandomMapIndex(bool avoidCurrent)
    {
        if (g_randomMaps.empty()) return -1;
        if (g_randomMaps.size() == 1) return 0;

        int next = GetRandomValue(0, g_randomMaps.size() - 1);

        if (avoidCurrent) {
            int attempts = 0;
            while (next == g_currentRandomMapIndex && attempts < 12)
            {
                next = GetRandomValue(0, g_randomMaps.size() - 1);
                ++attempts;
            }
        }
        return next;
    }
}

void Game::LoadMapForLevel(CurrentLevel level)
{
    int mapIndex = -1;

    if (g_randomMaps.empty())
    {
        RegisterRandomMaps();
    }

    switch (level)
    {
    case CurrentLevel::LEVEL1: mapIndex = 1; break;
    case CurrentLevel::LEVEL2: mapIndex = 0; break;
    case CurrentLevel::LEVEL3: mapIndex = 2; break;
    case CurrentLevel::LEVEL4: mapIndex = 1; break;
    case CurrentLevel::LEVEL5: mapIndex = 0; break;
    case CurrentLevel::LEVEL7: mapIndex = 2; break;
    case CurrentLevel::LEVEL8: mapIndex = 1; break;
    case CurrentLevel::LEVEL9: mapIndex = 0; break;
    case CurrentLevel::LEVEL10: mapIndex = 2; break;
    case CurrentLevel::LEVEL11: mapIndex = 1; break;
    case CurrentLevel::LEVEL12: mapIndex = 0; break;
    case CurrentLevel::LEVEL13: mapIndex = 2; break;
    case CurrentLevel::LEVEL14: mapIndex = 1; break;
    case CurrentLevel::LEVEL15: mapIndex = 0; break;

    case CurrentLevel::INFINITE:
        mapIndex = GetRandomMapIndex(true);
        break;

    default:
        mapIndex = g_randomMaps.empty() ? -1 : 0;
        break;
    }

    if (mapIndex >= 0 && mapIndex < g_randomMaps.size())
    {
        g_currentRandomMapIndex = mapIndex;

        RandomMapData& activeMap = g_randomMaps[g_currentRandomMapIndex];

        EnsureTextureLoaded(activeMap);

        this->spawnPoint = activeMap.pathPoints.front();
        this->castlePosition = activeMap.castlePos;

        CreatePath(this->castlePosition);
    }
    else
    {
        cout << "ERROR: Could not load map for level " << (int)level << endl;
    }
}

Game::Game() :
    previousScreen(CurrentScreen::LOADING),
    currentScreen(CurrentScreen::TITLE),
    currentLevel(CurrentLevel::NONE),
    assets(),
    money(300),
    spawnTimer(0.0f),
    spawnPoint{ 0.0f, 0.0f },
    castlePosition{ 0.0f, 0.0f },
    currentDragState(TowerType::NONE),
    shopArcherRect{ 1410, 1030, 130, 130 },
    shopWizardRect{ 1580, 1030, 130, 130 },
    shopCatapultRect{ 1750, 1030, 130, 130 },
    currentWave(0),
    waveSpawnTimer(0.0f),
    timeBetweenSpawns(0.8f),
    timeBetweenWaves(5.0f),
    waveCooldownTimer(0.0f),
    isWaveActive(false),
    enemiesSpawnedThisWave(0),
    totalEnemiesInWave(0),
    waveAnnouncementTimer(0.0f),
    currentWaveHealthMultiplier(1.0f),
    currentWaveSpeedMultiplier(1.0f)
{
    LoadGame();
}

Game::~Game()
{
    assets.UnloadGameAssets();
}



void Game::SaveGameData()
{
    GameData data = {
        masterVolume,
        musicVolume,
        sfxVolume,
        maxUnlockedLevel,
        bestWave
    };

    SaveFileData(SAVE_FILE_NAME, &data, sizeof(GameData));
}

void Game::LoadGameData()
{
    GameData data = {};
    int bytesRead = 0;

    unsigned char* fileData = LoadFileData(SAVE_FILE_NAME, &bytesRead);

    if (fileData != NULL && bytesRead == sizeof(GameData))
    {
        data = *(GameData*)fileData;

        masterVolume = data.masterVolume;
        musicVolume = data.musicVolume;
        sfxVolume = data.sfxVolume;
        maxUnlockedLevel = data.maxUnlockedLevel;
        bestWave = data.bestWave;
    }
    else
    {
        masterVolume = 75;
        musicVolume = 75;
        sfxVolume = 75;
        maxUnlockedLevel = 0;
        bestWave = 0;

        SaveGameData();
    }

    if (fileData != NULL) UnloadFileData(fileData);
}
void Game::SaveGame()
{
    std::ofstream outFile("save.txt");

    if (outFile.is_open())
    {
        outFile << maxUnlockedLevel << std::endl;
        outFile << bestWave << std::endl;

        outFile << masterVolume << std::endl;
        outFile << musicVolume << std::endl;
        outFile << sfxVolume << std::endl;

        outFile << lifeBarButton << std::endl;
        outFile << damageNumberButton << std::endl;
        outFile << highlightPathButton << std::endl;
        outFile << buildPauseButton << std::endl;

        outFile.close();
    }
}


void Game::LoadGame()
{
    std::ifstream inFile("save.txt");

    if (inFile.is_open())
    {
        int savedLvl, savedWave;
        int savedMasterVol, savedMusicVol, savedSfxVol;
        bool savedLifeBar, savedDamageNum, savedHighlight, savedBuildPause;

        if (!(inFile >> savedLvl)) return;
        if (!(inFile >> savedWave)) return;

        if (!(inFile >> savedMasterVol)) return;
        if (!(inFile >> savedMusicVol)) return;
        if (!(inFile >> savedSfxVol)) return;

        if (!(inFile >> savedLifeBar)) return;
        if (!(inFile >> savedDamageNum)) return;
        if (!(inFile >> savedHighlight)) return;
        if (!(inFile >> savedBuildPause)) return;


        this->maxUnlockedLevel = savedLvl;
        this->bestWave = savedWave;
        this->masterVolume = savedMasterVol;
        this->musicVolume = savedMusicVol;
        this->sfxVolume = savedSfxVol;
        this->lifeBarButton = savedLifeBar;
        this->damageNumberButton = savedDamageNum;
        this->highlightPathButton = savedHighlight;
        this->buildPauseButton = savedBuildPause;

        inFile.close();

        ApplySettings();
        ApplyMasterVolume((float)masterVolume / 100.0f);
        ApplyMusicVolume((float)musicVolume / 100.0f);
        ApplySfxVolume((float)sfxVolume / 100.0f);
    }
 
    else
    {
        ApplySettings();
        ApplyMasterVolume((float)masterVolume / 100.0f);
        ApplyMusicVolume((float)musicVolume / 100.0f);
        ApplySfxVolume((float)sfxVolume / 100.0f);
    }

}

void Game::Init()
{
    LoadGame();
    srand((unsigned int)time(NULL));
    assets.LoadGameAssets();

    RegisterRandomMaps();

    towers.clear();
    enemies.clear();
    bullets.clear();
    path.clear();

    money = 300;

    spawnTimer = 0.0f;
    currentDragState = TowerType::NONE;
    currentScreen = CurrentScreen::TITLE;

    LoadMapForLevel(CurrentLevel::LEVEL1);

    mainCastle = Castle();

    cout << "GAME START" << endl;
}

void Game::CreatePath(Vector2 castlePosition)
{
    path.clear();

    if (g_currentRandomMapIndex < 0 || g_currentRandomMapIndex >= g_randomMaps.size())
    {
        cout << "ERROR: Cannot create path, no map loaded." << endl;
        return;
    }

    const float PATH_POINT_RADIUS = g_pathPointRadius;

    const std::vector<Vector2>& mapPoints = g_randomMaps[g_currentRandomMapIndex].pathPoints;

    path.reserve(mapPoints.size());
    for (const auto& pos : mapPoints)
    {
        path.push_back(PathPoint{ pos, PATH_POINT_RADIUS });
    }
}

bool Game::BuyTower(Vector2 mousePos, TowerType type, int cost)
{
    if (money < cost) {
        return false;
    }
    if (towers.size() >= 10) return false;
    
    if (IsPositionOnPath(mousePos)) {
        return false;
    }

    money -= cost;

    towers.emplace_back(mousePos, type);
    return true;
}

void Game::AddTower(Vector2 mousePos, TowerType type)
{
    if (towers.size() >= 10) return;
    towers.emplace_back(mousePos, type);
}

void Game::AddEnemy(EnemyType t, float healthMultiplier, float speedMultiplier, bool spawnBehindLastEnemy)
{
    Vector2 finalSpawnPosition = spawnPoint;

    if (spawnBehindLastEnemy && !enemies.empty())
    {
        const auto& lastSpawned = enemies.back();
        Vector2 lastPos = lastSpawned->GetPosition();

        if (path.size() > 1)
        {
            float dx = path[1].position.x - path[0].position.x;
            float dy = path[1].position.y - path[0].position.y;
            float magnitude = sqrtf(dx * dx + dy * dy);

            if (magnitude > 0.0f)
            {
                float dir_x = dx / magnitude;
                float dir_y = dy / magnitude;

                float offsetDistance = 30.0f;

                finalSpawnPosition.x = lastPos.x - dir_x * offsetDistance;
                finalSpawnPosition.y = lastPos.y - dir_y * offsetDistance;
            }
        }
    }

    auto newEnemy = CreateEnemy(t, finalSpawnPosition, *this, healthMultiplier, speedMultiplier);

    if (path.size() > 1)
    {
        newEnemy->InitializeTarget(path[1].position, path[1].radius);
    }

    enemies.push_back(std::move(newEnemy));
}

void Game::AddLevelEnemy(EnemyType t)
{
    std::unique_ptr<Enemy> newEnemyPtr = CreateEnemy(t, spawnPoint, *this, 1.0f, 1.0f);

    if (!newEnemyPtr) return;

    if (path.size() > 1)
    {
        newEnemyPtr->InitializeTarget(path[1].position, path[1].radius);
    }

    enemies.push_back(std::move(newEnemyPtr));
}

void Game::SetupLevel(CurrentLevel levelId)
{
    mainCastle.ResetLife();
    enemies.clear();
    bullets.clear();
    towers.clear();
    money = 500;

    LoadMapForLevel(levelId);

    mainCastle.Init(castlePosition, 1500);

    if (path.empty())
    {
        std::cerr << "Erreur fatale: Le chemin pour le niveau " << static_cast<int>(levelId) << " est vide." << std::endl;
        currentLevelData = nullptr;
        currentLevel = CurrentLevel::NONE;
        return;
    }

    currentLevel = levelId;


    if (levelId == CurrentLevel::INFINITE)
    {
        currentLevelData = nullptr;

        currentWave = 0;
        waveSpawnTimer = 0.0f;
        waveCooldownTimer = 0.0f;
        isWaveActive = false;
        enemiesSpawnedThisWave = 0;
        totalEnemiesInWave = 0;
        waveAnnouncementTimer = 0.0f;
        currentWaveHealthMultiplier = 1.0f;
        currentWaveSpeedMultiplier = 1.0f;
        waveSystem.ResetWaveCounts();

        waveCooldownTimer = 3.0f;
        std::cout << "Mode Infini lanc." << std::endl;
    }
    else
    {
        spawnTimer = 0.0f;
        currentWaveIndex = 0;
        enemiesSpawned = 0;
        waveTimer = 0.0f;

        try
        {
            const LevelData& data = level.GetLevelData(levelId);
            currentLevelData = &data;
            cout << "Level " << static_cast<int>(levelId) << " data loaded successfully." << std::endl;
        }
        catch (const std::runtime_error& e) {
            std::cerr << "Erreur de chargement des données de niveau: " << e.what() << std::endl;
            currentLevelData = nullptr;
            currentLevel = CurrentLevel::NONE;
            return;
        }
    }

    SetScreen(CurrentScreen::GAMEPLAY);
}

void Game::ClearDeadEntities()
{
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
        [](const Bullet& b) { return !b.IsActive(); }), bullets.end());

    enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
        [](const std::unique_ptr<Enemy>& e) { return !e->IsAlive(); }), enemies.end());
}

bool Game::IsPositionOnPath(Vector2 position) const
{
    const float PATH_PROTECTION_RADIUS = 120.0f;
    
    for (const auto& pathPoint : path)
    {
        if (CheckCollisionPointCircle(position, pathPoint.position, PATH_PROTECTION_RADIUS))
        {
            return true;
        }
    }
    
    for (size_t i = 0; i < path.size() - 1; i++)
    {
        Vector2 p1 = path[i].position;
        Vector2 p2 = path[i + 1].position;
        
        if (CheckCollisionPointLine(position, p1, p2, (int)PATH_PROTECTION_RADIUS))
        {
            return true;
        }
    }
    
    return false;
}

void Game::Update(float dt)
{
    if (IsKeyPressed(KEY_F)) ToggleFullscreen();

    switch (currentScreen)
    {
    case CurrentScreen::TITLE: UpdateTitle(); break;
    case CurrentScreen::CHOOSE_LEVEL: UpdateChooseLevel(); break;
    case CurrentScreen::SETTINGS: UpdateSettings(); break;
    case CurrentScreen::HELP: UpdateHelp(); break;
    case CurrentScreen::GAMEPLAY: UpdateGameplay(dt); break;
    case CurrentScreen::VICTORY: UpdateVictory(); break;
    case CurrentScreen::GAMEOVER: UpdateGameOver(); break;
    }
}

void Game::SetScreen(CurrentScreen newScreen)
{
    previousScreen = currentScreen;
    currentScreen = newScreen;


    if (previousScreen == CurrentScreen::TITLE)
    {
        firstFrameTitleMusic = false;
    }

    if (previousScreen == CurrentScreen::GAMEPLAY)
    {
        StopMusicStream(assets.GetLevelMusic());
        StopMusicStream(assets.GetInfiniteMusic());
        StopMusicStream(assets.GetBossMusic());

        isBossWaveActive = false;
        firstFrameGameplayMusic = false;
    }

    if (previousScreen == CurrentScreen::VICTORY)
    {
        StopMusicStream(assets.GetVictoryMusic());
        firstFrameVictoryMusic = false;
    }

    if (previousScreen == CurrentScreen::GAMEOVER)
    {
        StopMusicStream(assets.GetGameOverMusic());
        firstFrameGameOverMusic = false;
    }

    if (currentScreen == CurrentScreen::TITLE)
    {
        firstFrameTitleMusic = true;
    }

    if (currentScreen == CurrentScreen::GAMEPLAY)
    {
        StopMusicStream(assets.GetTitleMusic());

        firstFrameGameplayMusic = true;
    }

    if (currentScreen == CurrentScreen::VICTORY)
    {
        firstFrameVictoryMusic = true;
    }

    if (currentScreen == CurrentScreen::GAMEOVER)
    {
        firstFrameGameOverMusic = true;
    }
}

void Game::PlayTitleAudio()
{

    Music titleMusic = assets.GetTitleMusic(); 

    if (firstFrameTitleMusic)
    {
        StopMusicStream(assets.GetVictoryMusic());
        StopMusicStream(assets.GetGameOverMusic());

        titleMusic.looping = true;
        PlayMusicStream(titleMusic);

        firstFrameTitleMusic = false;
    }

    UpdateMusicStream(titleMusic);

}

void Game::PlayGameplayAudio()
{
    if (currentLevel == CurrentLevel::INFINITE)
    {
        Music music = assets.GetInfiniteMusic();

        if (isBossWaveActive)
        {
            StopMusicStream(assets.GetBossMusic());
            isBossWaveActive = false;
            firstFrameGameplayMusic = true;
        }

        if (firstFrameGameplayMusic)
        {
            music.looping = true;
            PlayMusicStream(music);
            SetMusicVolume(music, 0.3);
            firstFrameGameplayMusic = false;
        }
        UpdateMusicStream(music);
    }
    else
    {
        if (isBossWaveActive)
        {
           

            if (firstFrameGameplayMusic)
            {
                StopMusicStream(assets.GetLevelMusic());

                Music bossMusic = assets.GetBossMusic();
                bossMusic.looping = true;
                PlayMusicStream(bossMusic);

                firstFrameGameplayMusic = false;
            }
            UpdateMusicStream(assets.GetBossMusic());
        }
        else
        {

            Music music = assets.GetLevelMusic();

            if (!firstFrameGameplayMusic) {
                StopMusicStream(assets.GetBossMusic());
            }

            if (firstFrameGameplayMusic)
            {
                StopMusicStream(assets.GetInfiniteMusic());

                music.looping = true;
                PlayMusicStream(music);
                firstFrameGameplayMusic = false;
            }
            UpdateMusicStream(music);
        }
    }
}

void Game::PlayVictoryAudio()
{
    Music music = assets.GetVictoryMusic();

    if (firstFrameVictoryMusic)
    {
        StopMusicStream(assets.GetLevelMusic());
        StopMusicStream(assets.GetBossMusic());

        music.looping = true;
        PlayMusicStream(music);

        firstFrameVictoryMusic = false;
    }

    UpdateMusicStream(music);
}

void Game::PlayGameOverAudio()
{
    Music music = assets.GetGameOverMusic();

    if (firstFrameGameOverMusic)
    {
        StopMusicStream(assets.GetLevelMusic());
        StopMusicStream(assets.GetInfiniteMusic());
        StopMusicStream(assets.GetBossMusic());

        music.looping = true;
        PlayMusicStream(music);
        SetMusicVolume(music, 2);
        firstFrameGameOverMusic = false;
    }

    UpdateMusicStream(music);
}

void Game::UpdateTitle()
{
    const Rectangle levelsSelectionButton = { 1088, 736, 544, 189 };
    const Rectangle settingsButton = { 384, 416, 352, 128 };
    const Rectangle helpButton = { 1184, 416, 352, 128 };

    const Rectangle infiniteLevelRect = { 288, 736, 544, 189 };

    Vector2 origin{ 0, 0 };

    Vector2 mouse = GetMousePosition();

    PlayTitleAudio();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
        CheckCollisionPointRec(mouse, levelsSelectionButton))
    {
        SetScreen(CurrentScreen::CHOOSE_LEVEL);
        PlaySound(assets.GetClickSound());
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
        CheckCollisionPointRec(mouse, settingsButton))
    {
        SetScreen(CurrentScreen::SETTINGS);
        PlaySound(assets.GetClickSound());

    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
        CheckCollisionPointRec(mouse, helpButton))
    {
        SetScreen(CurrentScreen::HELP);
        PlaySound(assets.GetClickSound());

    }


    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
        CheckCollisionPointRec(mouse, infiniteLevelRect))
    {

        currentLevel = CurrentLevel::INFINITE;

        SetupLevel(currentLevel);
        PlaySound(assets.GetClickLevel());

        currentScreen = CurrentScreen::GAMEPLAY;
    }
}

void Game::UpdateChooseLevel()
{

    const float BUTTON_SIZE = 103.0f;

    const float X_SPACING = 288.0f;
    const float Y_SPACING = 288.0f;

    const Vector2 START_POS = { 332.0f, 332.0f };

    Rectangle levelButtons[15];

    for (int i = 0; i < 15; ++i)
    {
        int col = i % 5;
        int row = i / 5;

        levelButtons[i].x = START_POS.x + (float)col * X_SPACING;
        levelButtons[i].y = START_POS.y + (float)row * Y_SPACING;
        levelButtons[i].width = BUTTON_SIZE;
        levelButtons[i].height = BUTTON_SIZE;
    }

    Vector2 mouse = GetMousePosition();
    PlayTitleAudio();

    Vector2 returnTitleCenter = { 1692 + 128 / 2.0f, 972 + 128 / 2.0f };
    float returnTitleRadius = 128 / 2.0f;

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
        CheckCollisionPointCircle(mouse, returnTitleCenter, returnTitleRadius))
    {
        currentScreen = CurrentScreen::TITLE;
        PlaySound(assets.GetClickSound());

    }
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        for (int i = 0; i < 15; ++i)
        {
            int levelNum = i + 1;

            if (!IsLevelLocked(levelNum))
            {
                if (CheckCollisionPointRec(mouse, levelButtons[i]))
                {
                    CurrentLevel selectedLevel = (CurrentLevel)levelNum;
                    currentLevel = selectedLevel;
                    SetupLevel(selectedLevel);
                    PlaySound(assets.GetClickLevel());
                    currentScreen = CurrentScreen::GAMEPLAY;
                    break;
                }
            }
            else
            {
                if (CheckCollisionPointRec(mouse, levelButtons[i]))
                {
                    PlaySound(assets.GetLockedLevel());
                    SetSoundVolume(assets.GetLockedLevel(), 4.0f);
                }
            }
        }
    }
}

void Game::UpdateSettings()
{
    PlayTitleAudio();
    Vector2 mouse = GetMousePosition();

    bool mouseClicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    const Rectangle lifeBarButtonRect = { 244, 345, 407, 140 };
    const Rectangle damageNumberButtonRect = { 244, 580, 407, 140 };
    const Rectangle highlightPathButtonRect = { 756, 345, 407, 140 };
    const Rectangle buildPauseButtonRect = { 756, 580, 407, 140 };
    const Rectangle volumeButtonRect = { 1269, 332, 407, 140 };
    const Rectangle resetButtonRect = { 1269, 580, 407, 140 };
    const Rectangle creditsButtonRect = { 756, 815, 407, 140 };

    Vector2 returnTitleCenter = { 1692 + 128 / 2.0f, 972 + 128 / 2.0f };
    float returnTitleRadius = 128 / 2.0f;

    Vector2 returnSettingsCenter = { 1366 + 64 / 2.0f, 319 + 64 / 2.0f };
    float returnSettingsRadius = 64 / 2.0f;

    if (volumeButton)
    {
        UpdateVolumeOptions();

        if (mouseClicked &&
            CheckCollisionPointCircle(mouse, returnSettingsCenter, returnSettingsRadius))
        {
            volumeButton = false;
            PlaySound(assets.GetClickSound());
        }
        return;
    }

    if (resetButton)
    {
        Rectangle yesRect{ 608, 602, 257, 92 };
        Rectangle noRect{ 1055, 602, 257, 92 };


        if (mouseClicked)
        {

            if (mouseClicked &&
                CheckCollisionPointCircle(mouse, returnSettingsCenter, returnSettingsRadius))
            {
                volumeButton = false;
                PlaySound(assets.GetClickSound());
            }
            return;

            if (CheckCollisionPointRec(mouse, noRect))
            {
                resetButton = false;
                PlaySound(assets.GetClickSound());
                return; 
            }

            if (CheckCollisionPointRec(mouse, yesRect))
            {
                masterVolume = 75;
                musicVolume = 75;
                sfxVolume = 75;
                maxUnlockedLevel = 1;
                bestWave = 0;
                lifeBarButton = true;
                damageNumberButton = true;
                highlightPathButton = false;
                buildPauseButton = false;
                ApplyMasterVolume(0.75f);
                ApplyMusicVolume(0.75f);
                ApplySfxVolume(0.75f);

                ApplySettings();
                SaveGame();
                PlaySound(assets.GetResetSound());
                resetButton = false;
                return;
            }
        }

        return;
    }

    if (creditsButton)
    {
        if (mouseClicked &&
            CheckCollisionPointCircle(mouse, returnSettingsCenter, returnSettingsRadius))
        {
            creditsButton = false;
            PlaySound(assets.GetClickSound());
        }


        return;
    }


    if (mouseClicked)
    {
        if (CheckCollisionPointCircle(mouse, returnTitleCenter, returnTitleRadius))
        {
            SetScreen(CurrentScreen::TITLE);
            PlaySound(assets.GetClickSound());
        }

        else if (CheckCollisionPointRec(mouse, lifeBarButtonRect))
        {
            lifeBarButton = !lifeBarButton;
            PlaySound(assets.GetClickSound());
        }

        else if (CheckCollisionPointRec(mouse, damageNumberButtonRect))
        {
            damageNumberButton = !damageNumberButton;
            PlaySound(assets.GetClickSound());
        }

        else if (CheckCollisionPointRec(mouse, highlightPathButtonRect))
        {
            highlightPathButton = !highlightPathButton;
            PlaySound(assets.GetClickSound());
        }

        else if (CheckCollisionPointRec(mouse, buildPauseButtonRect))
        {
            buildPauseButton = !buildPauseButton;
            PlaySound(assets.GetClickSound());
        }

        // --- Boutons d'Ouverture de Sous-Menu ---
        else if (CheckCollisionPointRec(mouse, volumeButtonRect))
        {
            volumeButton = true;
            PlaySound(assets.GetClickSound());
        }

        else if (CheckCollisionPointRec(mouse, resetButtonRect))
        {
            resetButton = true;
            PlaySound(assets.GetClickSound());
        }

        else if (CheckCollisionPointRec(mouse, creditsButtonRect))
        {
            creditsButton = true;
            PlaySound(assets.GetClickSound());
        }
    }
}

void Game::UpdateHelp()
{
    PlayTitleAudio();
    Vector2 mouse = GetMousePosition();

    Rectangle gameplayHelpButtonRect = { 256, 256, 1408, 256 };
    Rectangle towerHelpButtonRect = { 256, 544, 1408, 256 };
    Rectangle enemyHelpButtonRect = { 256, 832, 1408, 256 };

    Vector2 returnTitleCenter = { 1692 + 128 / 2.0f, 972 + 128 / 2.0f };
    float returnTitleRadius = 128 / 2.0f;

    Vector2 returnHelpButton = { 1647 + 64 / 2.0f, 265 + 64 / 2.0f };
    float returnHelpRadius = 64 / 2.0f;

    if (gameplayHelpButton || towerHelpButton || enemyHelpButton)
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
            CheckCollisionPointCircle(mouse, returnHelpButton, returnHelpRadius))
        {
            gameplayHelpButton = false;
            towerHelpButton = false;
            enemyHelpButton = false;
            PlaySound(assets.GetClickSound());

        }
        return;
    }

    if (!canClickHelp) return;


    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
        CheckCollisionPointCircle(mouse, returnTitleCenter, returnTitleRadius))
    {
        currentScreen = CurrentScreen::TITLE;
        PlaySound(assets.GetClickSound());

    }

    else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
        CheckCollisionPointRec(mouse, gameplayHelpButtonRect))
    {
        gameplayHelpButton = true;
        PlaySound(assets.GetClickSound());

         
    }

    else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
        CheckCollisionPointRec(mouse, towerHelpButtonRect))
    {
        towerHelpButton = true;
        PlaySound(assets.GetClickSound());

         
    }

    else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
        CheckCollisionPointRec(mouse, enemyHelpButtonRect))
    {
        enemyHelpButton = true;
        PlaySound(assets.GetClickSound());

         
    }
}

void Game::UpdateGameplay(float dt)
{
 
    PlayGameplayAudio();

    Vector2 mouse = GetMousePosition();

    Rectangle speed1Rect = { (int)shopArcherRect.x - 950, (int)shopArcherRect.y + 50 , 150, 150 };
    Rectangle speed2Rect = { (int)shopArcherRect.x - 775, (int)shopArcherRect.y + 50, 150, 150 };
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, speed2Rect))
    {
        timeScale = 2.0f;
    }
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, speed1Rect))
    {
        timeScale = 1.0f;
    }

    float scaled_dt = dt * timeScale;

    PlayTitleAudio();

    if (!mainCastle.Exists())
    {
        mainCastle.Init(castlePosition, 1500);
        CreatePath(castlePosition);
    }

    if (mainCastle.Exists())
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && currentDragState == TowerType::NONE)
        {
            if (CheckCollisionPointRec(mouse, shopArcherRect)) currentDragState = TowerType::ARCHER;
            else if (CheckCollisionPointRec(mouse, shopWizardRect)) currentDragState = TowerType::WIZARD;
            else if (CheckCollisionPointRec(mouse, shopCatapultRect)) currentDragState = TowerType::CATAPULT;
            PlaySound(assets.GetGrabTowerSound());
            if (currentDragState != TowerType::NONE && buildPauseButton) pauseGame = true;
        }

        if (currentDragState != TowerType::NONE)
        {
            if (mouse.y < 1000 && mouse.x < 1800 && mouse.y > 100)
            {
                canTowerBePlaced = true;
            }
            else
            {
                canTowerBePlaced = false;
            }
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && currentDragState != TowerType::NONE)
        {
            int cost = 0;
            if (currentDragState == TowerType::ARCHER) cost = 150;
            else if (currentDragState == TowerType::WIZARD) cost = 250;
            else if (currentDragState == TowerType::CATAPULT) cost = 400;
            PlaySound(assets.GetGrabTowerSound());
            if (canTowerBePlaced == true)
            {
                BuyTower(mouse, currentDragState, cost);
            }

            currentDragState = TowerType::NONE;
            canTowerBePlaced = true;

            if (buildPauseButton) pauseGame = false;
        }
    }

    if (mainCastle.Exists() && !path.empty())
    {
        if (!pauseGame)
        {
            if (currentLevel == CurrentLevel::INFINITE)
            {
                UpdateWaveSystem(scaled_dt);
                isBossWaveActive = false;
            }
            else
            {
                if (currentLevelData && currentWaveIndex < currentLevelData->preBossWaves.size())
                {
                    if (currentWaveIndex == currentLevelData->preBossWaves.size() - 1 && !isBossWaveActive)
                    {
                        isBossWaveActive = true;
                        firstFrameGameplayMusic = true;
                        std::cout << "Attention ! La musique de Boss est déclenchée !" << std::endl;
                    }

                    const EnemyWave& currentWave = currentLevelData->preBossWaves[currentWaveIndex];

                    if (enemiesSpawned < currentWave.count)
                    {
                        waveTimer += scaled_dt;
                        if (waveTimer >= currentWave.interval)
                        {
                            AddLevelEnemy(currentWave.enemyType);
                            enemiesSpawned++;
                            waveTimer = 0.0f;
                        }
                    }
                    else if (enemies.empty())
                    {
                        currentWaveIndex++;
                        enemiesSpawned = 0;
                        waveTimer = 0.0f;

                        if (currentWaveIndex >= currentLevelData->preBossWaves.size())
                        {
                            std::cout << "VICTOIRE FINALE ! Niveau " << static_cast<int>(currentLevel) << " termine." << std::endl;

                            UnlockNextLevel((int)currentLevel);

                            isBossWaveActive = false;
                            firstFrameVictoryMusic = true;

                            SetScreen(CurrentScreen::VICTORY);
                        }
                        else
                        {
                            std::cout << "Vague suivante : " << currentWaveIndex + 1 << std::endl;
                        }
                    }
                }
            }
        }

    }

    for (size_t i = 0; i < enemies.size(); i++) {
        if (enemies[i]->IsAlive()) {
            bool wasAlive = enemies[i]->IsAlive();

            enemies[i]->Update(scaled_dt, path, mainCastle.GetLifeRef(), assets);

            if (wasAlive && !enemies[i]->IsAlive()) {
                GainMoney(enemies[i]->GetReward());
            }
        }
    }
    for (Tower& tower : towers) {
        tower.Update(scaled_dt);

        if (tower.CanAttack()) {

            Enemy* targetEnemy = nullptr;

            int targetIndex = tower.GetTargetIndex();

            if (targetIndex != -1 && targetIndex < (int)enemies.size()) {
                Enemy* potentialTarget = enemies[targetIndex].get();

                float dx = potentialTarget->GetPosition().x - tower.GetPosition().x;
                float dy = potentialTarget->GetPosition().y - tower.GetPosition().y;
                float distance = sqrt(dx * dx + dy * dy);

                if (potentialTarget->IsAlive() && distance <= tower.GetRange()) {
                    targetEnemy = potentialTarget;
                }
                else {
                    tower.SetTargetIndex(-1);
                }
            }

            if (targetEnemy == nullptr) {
                for (size_t i = 0; i < enemies.size(); ++i) {
                    Enemy* enemy = enemies[i].get();
                    if (enemy->IsAlive()) {
                        float dx = enemy->GetPosition().x - tower.GetPosition().x;
                        float dy = enemy->GetPosition().y - tower.GetPosition().y;
                        float distance = sqrt(dx * dx + dy * dy);

                        if (distance <= tower.GetRange())
                        {
                            targetEnemy = enemy;
                            tower.SetTargetIndex((int)i);
                            break;
                        }
                    }
                }
            }

            if (targetEnemy != nullptr) {
                tower.SetTarget(targetEnemy->GetPosition());

                int damage = tower.GetDamage();
                Bullet newBullet;
                newBullet.Init(tower.GetPosition(), targetEnemy->GetPosition(), tower.GetType(), damage);
                newBullet.SetGamePtr(this);

                bullets.push_back(newBullet);
                tower.ResetAttackTimer();
            }
        }
    }

    for (Bullet& bullet : bullets) {
        bullet.Update(scaled_dt, assets);
        bullet.CheckCollision(scaled_dt, enemies, assets);
    }

    for (Tower& tower : towers) {
        Rectangle upgradeButtonHitbox = tower.GetUpgradeHitbox();
        Vector2 mouse = GetMousePosition();

        if (CheckCollisionPointRec(mouse, upgradeButtonHitbox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && tower.GetLvl() != TowerLvl::LVL7)
        {
            int cost = tower.GetUpgradeCost();
            if (money >= cost) {
                money -= cost;
                tower.UpgradeLvl(assets);
            }
        }
    }
    
    int totalReward = 0;
    for (const auto& enemy : enemies) {
        if (!enemy->IsAlive()) {
            totalReward += enemy->GetReward();
        }
    }

    if (totalReward > 0) {
        GainMoney(totalReward);
    }
    


    ClearDeadEntities();

    if (mainCastle.Exists() && !mainCastle.IsAlive()) {
        firstFrameGameOverMusic = true;
        SetScreen(CurrentScreen::GAMEOVER);
        currentDragState = TowerType::NONE;
    }
}



void Game::UpdateVictory()
{
    PlayVictoryAudio();

    Vector2 mouse = GetMousePosition();
    Rectangle titleRect { 266, 831, 544, 189 };
    Rectangle retryRect { 1110, 831, 544, 189 };
    Rectangle nextLevelRect { 681, 572, 544, 189 };

    currentDragState = TowerType::NONE;
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, titleRect)) {
        SetScreen(CurrentScreen::TITLE);
        PlaySound(assets.GetClickSound());

    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, retryRect)) {
        SetScreen(CurrentScreen::GAMEPLAY);
        SetupLevel(currentLevel);
        PlaySound(assets.GetClickLevel());

    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, nextLevelRect)) {

        int nextLevelNum = (int)currentLevel + 1;

        const int MAX_STANDARD_LEVEL = (int)CurrentLevel::LEVEL15;

        if (nextLevelNum <= MAX_STANDARD_LEVEL)
        {
            currentLevel = (CurrentLevel)nextLevelNum;

            SetupLevel(currentLevel);
            SetScreen(CurrentScreen::GAMEPLAY);
            PlaySound(assets.GetClickLevel());
        }
        else
        {
            SetScreen(CurrentScreen::TITLE);
            PlaySound(assets.GetClickSound());

        }
    }
}

void Game::UpdateGameOver()
{
    PlayGameOverAudio();

    Vector2 mouse = GetMousePosition();
    Rectangle titleRect{ 266, 831, 544, 189 };
    Rectangle retryRect{ 1110, 831, 544, 189 };

    currentDragState = TowerType::NONE;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, titleRect)) {
            SetScreen(CurrentScreen::TITLE);
            PlaySound(assets.GetClickSound());

        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, retryRect)) {
            SetScreen(CurrentScreen::GAMEPLAY);
            SetupLevel(currentLevel);
            PlaySound(assets.GetClickLevel());

        }
    }



void Game::ApplySettings()
{
    PlayGameOverAudio();

    Vector2 mouse = GetMousePosition();
    Vector2 origin = { 0, 0 };

    if (creditsButton)
    {
        DrawTextureEx(assets.GetCreditsTexture(), origin, 0, 1, WHITE);
    }

    if (resetButton)
    {
        DrawTextureEx(assets.GetResetTexture(), origin, 0, 1, WHITE);
    }

    if (volumeButton)
    {
        Rectangle masterVolume0Rec = { 935, 463 , 43, 32 };
        Rectangle masterVolume25Rec = { 978, 463, 87, 32 };

        DrawTextureEx(assets.GetVolumeOptionTexture(), origin, 0, 1, WHITE);

        if (masterVolume == 0)
        {
            DrawTextureEx(assets.GetMasterVolume0(), origin, 0, 1, WHITE);
            ApplyMasterVolume(0);
        }
        else if (masterVolume == 25)
        {
            DrawTextureEx(assets.GetMasterVolume25(), origin, 0, 1, WHITE);
            ApplyMasterVolume(0.25f);
        }
        else if (masterVolume == 50)
        {
            DrawTextureEx(assets.GetMasterVolume50(), origin, 0, 1, WHITE);
            ApplyMasterVolume(0.50f);
        }
        else if (masterVolume == 75)
        {
            DrawTextureEx(assets.GetMasterVolume75(), origin, 0, 1, WHITE);
            ApplyMasterVolume(0.75f);
        }
        else if (masterVolume == 100)
        {
            DrawTextureEx(assets.GetMasterVolume100(), origin, 0, 1, WHITE);
            ApplyMasterVolume(1.00f);
        }
        if (musicVolume == 0)
        {
            DrawTextureEx(assets.GetMusicVolume0(), origin, 0, 1, WHITE);
            ApplyMusicVolume(0);
        }
        else if (musicVolume == 25)
        {
            DrawTextureEx(assets.GetMusicVolume25(), origin, 0, 1, WHITE);
            ApplyMusicVolume(0.25f);
        }
        else if (musicVolume == 50)
        {
            DrawTextureEx(assets.GetMusicVolume50(), origin, 0, 1, WHITE);
            ApplyMusicVolume(0.50f);
        }
        else if (musicVolume == 75)
        {
            DrawTextureEx(assets.GetMusicVolume75(), origin, 0, 1, WHITE);
            ApplyMusicVolume(0.75f);
        }
        else if (musicVolume == 100)
        {
            DrawTextureEx(assets.GetMusicVolume100(), origin, 0, 1, WHITE);
            ApplyMusicVolume(1.00f);
        }
        if (sfxVolume == 0)
        {
            DrawTextureEx(assets.GetSfxVolume0(), origin, 0, 1, WHITE);
            ApplySfxVolume(0);
        }
        else if (sfxVolume == 25)
        {
            DrawTextureEx(assets.GetSfxVolume25(), origin, 0, 1, WHITE);
            ApplySfxVolume(0.25f);
        }
        else if (sfxVolume == 50)
        {
            DrawTextureEx(assets.GetSfxVolume50(), origin, 0, 1, WHITE);
            ApplySfxVolume(0.50f);
        }
        else if (sfxVolume == 75)
        {
            DrawTextureEx(assets.GetSfxVolume75(), origin, 0, 1, WHITE);
            ApplySfxVolume(0.75f);
        }
        else if (sfxVolume == 100)
        {
            DrawTextureEx(assets.GetSfxVolume100(), origin, 0, 1, WHITE);
            ApplySfxVolume(1.00f);
        }
    }
}

void Game::UpdateVolumeOptions()
{
    Vector2 mouse = GetMousePosition();
    bool mousePressed = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    bool volumeChanged = false;

    Rectangle masterVolume0Rec = { 935, 463 , 43, 32 };
    Rectangle masterVolume25Rec = { 978, 463, 87, 32 };
    Rectangle masterVolume50Rec = { 1065, 463, 86, 32 };
    Rectangle masterVolume75Rec = { 1151, 463, 87, 32 };
    Rectangle masterVolume100Rec = { 1238, 463, 43, 32 };

    Rectangle musicVolume0Rec = { 935, 565 , 43, 32 };
    Rectangle musicVolume25Rec = { 978, 565, 87, 32 };
    Rectangle musicVolume50Rec = { 1065, 565, 86, 32 };
    Rectangle musicVolume75Rec = { 1151, 565, 87, 32 };
    Rectangle musicVolume100Rec = { 1238, 565, 43, 32 };

    Rectangle sfxVolume0Rec = { 935, 667 , 43, 32 };
    Rectangle sfxVolume25Rec = { 978, 667, 87, 32 };
    Rectangle sfxVolume50Rec = { 1065, 667, 86, 32 };
    Rectangle sfxVolume75Rec = { 1151, 667, 87, 32 };
    Rectangle sfxVolume100Rec = { 1238, 667, 43, 32 };

    if (mousePressed)
    {
        if (CheckCollisionPointRec(mouse, masterVolume0Rec)) {
            masterVolume = 0;  
        }
        else if (CheckCollisionPointRec(mouse, masterVolume25Rec)) {
            masterVolume = 25;  
        }
        else if (CheckCollisionPointRec(mouse, masterVolume50Rec)) {
            masterVolume = 50;  
        }
        else if (CheckCollisionPointRec(mouse, masterVolume75Rec)) {
            masterVolume = 75;  
        }
        else if (CheckCollisionPointRec(mouse, masterVolume100Rec)) {
            masterVolume = 100;  
        }
        else if (CheckCollisionPointRec(mouse, musicVolume0Rec)) {
            musicVolume = 0;  
        }
        else if (CheckCollisionPointRec(mouse, musicVolume25Rec)) {
            musicVolume = 25;  
        }
        else if (CheckCollisionPointRec(mouse, musicVolume50Rec)) {
            musicVolume = 50;  
        }
        else if (CheckCollisionPointRec(mouse, musicVolume75Rec)) {
            musicVolume = 75;  
        }
        else if (CheckCollisionPointRec(mouse, musicVolume100Rec)) {
            musicVolume = 100;  
        }
        else if (CheckCollisionPointRec(mouse, sfxVolume0Rec)) {
            sfxVolume = 0;  
        }
        else if (CheckCollisionPointRec(mouse, sfxVolume25Rec)) {
            sfxVolume = 25;  
        }
        else if (CheckCollisionPointRec(mouse, sfxVolume50Rec)) {
            sfxVolume = 50;  
        }
        else if (CheckCollisionPointRec(mouse, sfxVolume75Rec)) {
            sfxVolume = 75;  
        }
        else if (CheckCollisionPointRec(mouse, sfxVolume100Rec)) {
            sfxVolume = 100;  
        }
    }


}

void Game::ApplyMasterVolume(float volume)
{
    SetMasterVolume(volume);
}

void Game::ApplyMusicVolume(float volume)
{
    SetMusicVolume(assets.GetVictoryMusic(), volume);
    SetMusicVolume(assets.GetGameOverMusic(), volume);
    SetMusicVolume(assets.GetLevelMusic(), volume);
    SetMusicVolume(assets.GetInfiniteMusic(), volume);
    SetMusicVolume(assets.GetBossMusic(), volume);
    SetMusicVolume(assets.GetTitleMusic(), volume);

    SetMusicVolume(assets.GetWaveBeginMusic(), volume);
}

void Game::ApplySfxVolume(float volume)
{
    SetSoundVolume(assets.GetArcherShot(), volume);
    SetSoundVolume(assets.GetWizardShot(), volume);
    SetSoundVolume(assets.GetCatapultShot(), volume);

    SetSoundVolume(assets.GetClickSound(), volume);
    SetSoundVolume(assets.GetClickLevel(), volume);
    SetSoundVolume(assets.GetLockedLevel(), volume);
    SetSoundVolume(assets.GetResetSound(), volume);
    SetSoundVolume(assets.GetGrabTowerSound(), volume);
    SetSoundVolume(assets.GetLevelUpSound(), volume);

    SetSoundVolume(assets.GetDeath1(), volume);
    SetSoundVolume(assets.GetDeath2(), volume);
    SetSoundVolume(assets.GetDeath3(), volume);

}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(DARKGRAY);

    switch (currentScreen) {
    case CurrentScreen::TITLE: DrawTitle(); break;
    case CurrentScreen::CHOOSE_LEVEL: DrawChooseLevel(); break;
    case CurrentScreen::SETTINGS:
    {
        DrawSettings();
        ApplySettings();
        break;
    }
    case CurrentScreen::HELP:
    {
        DrawHelp();
        break;
    }

    case CurrentScreen::GAMEPLAY: DrawGameplay(); break;
    case CurrentScreen::VICTORY: DrawVictory(); break;
    case CurrentScreen::GAMEOVER: DrawGameOver(); break;
    }
  
    Vector2 mouse = GetMousePosition();
    if (assets.GetMouseTexture().id > 0) {
        float drawX = mouse.x - assets.GetMouseTexture().width / 2 + 425;
        float drawY = mouse.y - assets.GetMouseTexture().height / 2 + 188;
        DrawTextureEx(assets.GetMouseTexture(), Vector2{ drawX, drawY }, 0.0f, 0.15f, WHITE);
    }
    EndDrawing();
}

void Game::DrawTitle() const
{
    DrawTexture(assets.GetTitleScreenTexture(), 0, 0, WHITE);

}

void Game::DrawChooseLevel() const
{
    DrawTexture(assets.GetLevelSelectionTexture(), 0, 0, WHITE);

    const float BUTTON_SIZE = 103.0f;
    const float X_SPACING = 288.0f;
    const float Y_SPACING = 288.0f;
    const Vector2 START_POS = { 332.0f, 332.0f };

    for (int i = 0; i < 15; i++)
    {
        int col = i % 5;
        int row = i / 5;

        Vector2 buttonPos;
        buttonPos.x = START_POS.x + (float)col * X_SPACING;
        buttonPos.y = START_POS.y + (float)row * Y_SPACING;

        if (IsLevelLocked(i + 1))
        {
            DrawTextureEx(assets.GetLockTexture(), buttonPos, 0, 1, WHITE);
        }

    }
}

void Game::DrawSettings() const
{
    DrawTexture(assets.GetSettingsTexture(), 0, 0, WHITE);

    Vector2 mouse = GetMousePosition();

    Vector2 lifeBarButtonPos = { 486, 402 };
    Vector2 damageNumberButtonPos = { 554, 637 };
    Vector2 highlightPathButtonPos = { 1045, 402 };
    Vector2 buildPauseButtonPos = { 1030, 637 };
    Vector2 origin = { 0, 0 };

    if (Game::lifeBarButton) DrawTextureEx(assets.GetGreenButtonTexture(), lifeBarButtonPos, 0, 1, WHITE);
    else DrawTextureEx(assets.GetRedButtonTexture(), lifeBarButtonPos, 0, 1, WHITE);

    if (Game::damageNumberButton) DrawTextureEx(assets.GetGreenButtonTexture(), damageNumberButtonPos, 0, 1, WHITE);
    else DrawTextureEx(assets.GetRedButtonTexture(), damageNumberButtonPos, 0, 1, WHITE);

    if (Game::highlightPathButton) DrawTextureEx(assets.GetGreenButtonTexture(), highlightPathButtonPos, 0, 1, WHITE);
    else DrawTextureEx(assets.GetRedButtonTexture(), highlightPathButtonPos, 0, 1, WHITE);

    if (Game::buildPauseButton) DrawTextureEx(assets.GetGreenButtonTexture(), buildPauseButtonPos, 0, 1, WHITE);
    else DrawTextureEx(assets.GetRedButtonTexture(), buildPauseButtonPos, 0, 1, WHITE);
}

void Game::DrawHelp() const
{
    DrawTexture(assets.GetHelpTexture(), 0, 0, WHITE);

    if (gameplayHelpButton)
    {
        DrawTexture(assets.GetGameplayHelpTexture(), 0, 0, WHITE);
    }
    else if (towerHelpButton)
    {
        DrawTexture(assets.GetTowerHelpTexture(), 0, 0, WHITE);
    }
    else if (enemyHelpButton)
    {
        DrawTexture(assets.GetEnemyHelpTexture(), 0, 0, WHITE);
    }
}


void Game::DrawLvl1() const
{
    DrawTexture(assets.GetLvl1BackgroundTexture(), 0, 0, WHITE);
}

void Game::DrawLvl2() const
{
    DrawTexture(assets.GetLvl2BackgroundTexture(), 0, 0, WHITE);
}

void Game::DrawLvl3() const
{
    DrawTexture(assets.GetLvl3BackgroundTexture(), 0, 0, WHITE);
}

void Game::DrawLvl4() const
{
    DrawTexture(assets.GetLvl1BackgroundTexture(), 0, 0, WHITE);
}

void Game::DrawLvl5() const
{
    DrawTexture(assets.GetLvl2BackgroundTexture(), 0, 0, WHITE);
}

void Game::DrawLvl6() const
{
    DrawTexture(assets.GetLvl2BackgroundTexture(), 0, 0, WHITE);
}

void Game::DrawLvl7() const
{
    DrawTexture(assets.GetLvl3BackgroundTexture(), 0, 0, WHITE);
}

void Game::DrawLvl8() const
{
    DrawTexture(assets.GetLvl1BackgroundTexture(), 0, 0, WHITE);
}

void Game::DrawLvl9() const
{
    DrawTexture(assets.GetLvl2BackgroundTexture(), 0, 0, WHITE);
}

void Game::DrawLvl10() const
{
    DrawTexture(assets.GetLvl3BackgroundTexture(), 0, 0, WHITE);
}

void Game::DrawLvl11() const
{
    DrawTexture(assets.GetLvl1BackgroundTexture(), 0, 0, WHITE);
}

void Game::DrawLvl12() const
{
    DrawTexture(assets.GetLvl2BackgroundTexture(), 0, 0, WHITE);
}

void Game::DrawLvl13() const
{
    DrawTexture(assets.GetLvl3BackgroundTexture(), 0, 0, WHITE);
}

void Game::DrawLvl14() const
{
    DrawTexture(assets.GetLvl1BackgroundTexture(), 0, 0, WHITE);
}

void Game::DrawLvl15() const
{
    DrawTexture(assets.GetLvl2BackgroundTexture(), 0, 0, WHITE);
}

void Game::DrawGameplay() const
{

    if (currentLevel == CurrentLevel::INFINITE && g_currentRandomMapIndex >= 0 && g_currentRandomMapIndex < (int)g_randomMaps.size())
    {
        const auto& m = g_randomMaps[g_currentRandomMapIndex];
        if (m.loaded && m.texture.id > 0) DrawTexture(m.texture, 0, 0, WHITE);
        else DrawTexture(assets.GetCastleTexture(), 0, 0, WHITE);
    }
    else
    {
        switch (currentLevel)
        {
        case CurrentLevel::LEVEL1: DrawLvl1(); break;
        case CurrentLevel::LEVEL2: DrawLvl2(); break;
        case CurrentLevel::LEVEL3: DrawLvl3(); break;
        case CurrentLevel::LEVEL4: DrawLvl4(); break;
        case CurrentLevel::LEVEL5: DrawLvl5(); break;
        case CurrentLevel::LEVEL6: DrawLvl6(); break;
        case CurrentLevel::LEVEL7: DrawLvl7(); break;
        case CurrentLevel::LEVEL8: DrawLvl8(); break;
        case CurrentLevel::LEVEL9: DrawLvl9(); break;
        case CurrentLevel::LEVEL10: DrawLvl10(); break;
        case CurrentLevel::LEVEL11: DrawLvl11(); break;
        case CurrentLevel::LEVEL12: DrawLvl12(); break;
        case CurrentLevel::LEVEL13: DrawLvl13(); break;
        case CurrentLevel::LEVEL14: DrawLvl14(); break;
        case CurrentLevel::LEVEL15: DrawLvl15(); break;
        }

    }

    Vector2 mouse = GetMousePosition();

    if (currentLevel == CurrentLevel::INFINITE)
    {
        

        if (GetWaveAnnouncementTimer() > 0.0f)
        {
            const char* waveText = TextFormat("WAVE %i", GetCurrentWave());
            int fontSize = 120;
            int textWidth = MeasureText(waveText, fontSize);
            int textX = 1920 / 2 - textWidth / 2;
            int textY = 1200 / 2 - fontSize / 2;

            DrawRectangle(0, 0, 1920, 1200, Fade(BLACK, 0.5f));

            DrawText(waveText, textX + 4, textY + 4, fontSize, BLACK);
            DrawText(waveText, textX, textY, fontSize, YELLOW);
        }
    }

    if (highlightPathButton)
    {
        if (!path.empty())
        {
            if (path.size() > 1)
            {
                for (size_t i = 1; i < path.size(); i++)
                {
                    Vector2 startPos = path[i - 1].position;
                    Vector2 endPos = path[i].position;
                    DrawLineEx(startPos, endPos, 10.0f, Fade(RED, 0.6f));
                }
            }

            for (const auto& p : path)
            {
                DrawCircle((int)p.position.x, (int)p.position.y, p.radius, Fade(GREEN, 0.6f));
            }
        }
    }

    if (mainCastle.Exists())
    {
        mainCastle.Draw(assets);
    }
    else
    {
        Vector2 mouseLocal = GetMousePosition();
        if (mouseLocal.x < 1750 && mouseLocal.y > 100) {
            DrawCircleV(mouseLocal, 60, Fade(BLUE, 0.3f));
        }
    }

    for (const auto& enemy : enemies) {
        enemy->Draw(assets);
    }

    for (const auto& bullet : bullets) {
        bullet.Draw(assets);
    }

    for (const auto& tower : towers) {
        tower.Draw(assets);
    }

    if (mainCastle.Exists()) {
        Vector2 pos = mainCastle.GetPosition();
        int currentLife = mainCastle.GetLife();
        int maxLife = mainCastle.GetMaxLife();
        float lifePercent = (float)currentLife / (float)maxLife * 100.0f;
        Vector2 castleLifePos = { pos.x - 100, pos.y - 250 };
        DrawTextureEx(assets.GetLifeTexture(lifePercent), castleLifePos, 0, 3.0f, WHITE);
    }

    DrawCircleV(spawnPoint, 15, GREEN);

    Vector2 coinPos = { (int)shopArcherRect.x - 300, (int)shopArcherRect.y + 50 };
    Vector2 wavePos = { (int)shopArcherRect.x - 1325, (int)shopArcherRect.y + 60 };
    Vector2 x1Pos = { (int)shopArcherRect.x - 950, (int)shopArcherRect.y + 50 };
    Vector2 x2Pos = { (int)shopArcherRect.x - 775, (int)shopArcherRect.y + 50 };

    DrawTexture(assets.GetShopIconTexture(), (int)shopArcherRect.x, (int)shopArcherRect.y, WHITE);
    DrawTexture(assets.GetShopIconTexture(), (int)shopWizardRect.x, (int)shopWizardRect.y, WHITE);
    DrawTexture(assets.GetShopIconTexture(), (int)shopCatapultRect.x, (int)shopCatapultRect.y, WHITE);
    DrawTexture(assets.GetCoinIconTexture(), (int)shopArcherRect.x - 325, (int)shopArcherRect.y, WHITE);
    DrawTexture(assets.GetCoinIconTexture(), (int)shopArcherRect.x - 1375, (int)shopArcherRect.y, WHITE);
    DrawTextPro(assets.GetMedievalFont(), TextFormat("Coins : %i", money), coinPos, { 0.0f, 0.0f }, 0, 45.0f, 2.0f, BLACK);
    if (currentLevel == CurrentLevel::INFINITE)
    {
     DrawTextPro(assets.GetMedievalFont(), TextFormat("Wave : %i", currentWave), wavePos, { 0.0f, 0.0f }, 0, 45.0f, 2.0f, BLACK);

    }
    else
    {
        int nextLevelNum = (int)currentLevel;
        DrawTextPro(assets.GetMedievalFont(), TextFormat("Level : %i", nextLevelNum), wavePos, { 0.0f, 0.0f }, 0, 45.0f, 2.0f, BLACK);
    }

    DrawTexture(assets.GetShopIconTexture(), (int)shopArcherRect.x - 1000, (int)shopArcherRect.y, WHITE);
    DrawTexture(assets.GetShopIconTexture(), (int)shopArcherRect.x - 825, (int)shopArcherRect.y, WHITE);
    DrawTextPro(assets.GetMedievalFont(), TextFormat("X1", currentWave), x1Pos, { 0.0f, 0.0f }, 0, 60.0f, 2.0f, BLACK);
    DrawTextPro(assets.GetMedievalFont(), TextFormat("X2", currentWave), x2Pos, { 0.0f, 0.0f }, 0, 60.0f, 2.0f, BLACK);

    if (currentDragState != TowerType::NONE)
    {
        Vector2 archerDragPos = { mouse.x - 50, mouse.y - 55 };
        Vector2 wizardDragPos = { mouse.x - 64, mouse.y - 70 };
        Vector2 catapultDragPos = { mouse.x - 40, mouse.y - 45 };
        Color red = RED;
        Color white = WHITE;

        if (!canTowerBePlaced || IsPositionOnPath(mouse))
        {
            switch (currentDragState)
            {
            case TowerType::ARCHER:
                DrawTextureEx(assets.GetArcherTexture(), archerDragPos, 0, 0.80f, Fade(red, 0.6f));
                DrawCircleLinesV(mouse, 150, Fade(WHITE, 0.3f));
                break;
            case TowerType::WIZARD:
                DrawTextureEx(assets.GetWizardTexture(), wizardDragPos, 0, 1, Fade(red, 0.6f));
                DrawCircleLinesV(mouse, 200, Fade(WHITE, 0.3f));
                break;
            case TowerType::CATAPULT:
                DrawTextureEx(assets.GetCatapultTexture(), catapultDragPos, 0, 0.75f, Fade(red, 0.6f));
                DrawCircleLinesV(mouse, 250, Fade(WHITE, 0.3f));
                break;
            default: break;
            }
        }
        else
        {
            switch (currentDragState)
            {
            case TowerType::ARCHER:
                DrawTextureEx(assets.GetArcherTexture(), archerDragPos, 0, 0.80f, Fade(white, 0.6f));
                DrawCircleLinesV(mouse, 150, Fade(WHITE, 0.3f));
                break;
            case TowerType::WIZARD:
                DrawTextureEx(assets.GetWizardTexture(), wizardDragPos, 0, 1, Fade(white, 0.6f));
                DrawCircleLinesV(mouse, 200, Fade(WHITE, 0.3f));
                break;
            case TowerType::CATAPULT:
                DrawTextureEx(assets.GetCatapultTexture(), catapultDragPos, 0, 0.75f, Fade(white, 0.6f));
                DrawCircleLinesV(mouse, 250, Fade(WHITE, 0.3f));
                break;
            default: break;
            }
        }
    }

    if (currentDragState != TowerType::ARCHER)
    {
        DrawTextureEx(assets.GetArcherTexture(), Vector2{ 1410 + 25, 1030 + 18 }, 0, 0.80f, WHITE);
    }
    DrawText("$150", 1410 + 13 + 50 - MeasureText("$100", 20) / 2, 900 + 13 + 85, 20, YELLOW);

    if (currentDragState != TowerType::WIZARD)
    {
        DrawTextureEx(assets.GetWizardTexture(), Vector2{ 1580 + 13, 1030 + 5 }, 0, 1, WHITE);
    }
    DrawText("$250", 1580 + 13 + 50 - MeasureText("$150", 20) / 2, 900 + 13 + 85, 20, YELLOW);

    if (currentDragState != TowerType::CATAPULT)
    {
        DrawTextureEx(assets.GetCatapultTexture(), Vector2{ 1750 + 40, 1030 + 30 }, 0, 0.90f, WHITE);
    }
    DrawText("$400", 1750 + 13 + 50 - MeasureText("$200", 20) / 2, 900 + 13 + 85, 20, YELLOW);
}

void Game::DrawVictory() const
{
    DrawTexture(assets.GetLevelVictoryTexture(), 0, 0, WHITE);
    
}

void Game::DrawGameOver() const
{
    if (currentLevel == CurrentLevel::INFINITE)
    {
        Vector2 currentWavePos{ 975, 410 };
        Vector2 bestWavePos{ 975, 654 };
        DrawTexture(assets.GetInfiniteGameOverTexture(), 0, 0, WHITE);
        DrawTextEx(assets.GetMedievalFont(), TextFormat("%i", currentWave), currentWavePos, 100.0f, 10.0f, BLACK);
        DrawTextEx(assets.GetMedievalFont(), TextFormat("%i", bestWave), bestWavePos, 100.0f, 10.0f, BLACK);
    }
    else
    {
        DrawTexture(assets.GetLevelGameOverTexture(), 0, 0, WHITE);

    }

}


void Game::UpdateWaveSystem(float dt)
{
    if (waveAnnouncementTimer > 0.0f)
    {
        waveAnnouncementTimer -= dt;
    }
    if (IsMusicStreamPlaying(assets.GetWaveBeginMusic()))
    {
        UpdateMusicStream(assets.GetWaveBeginMusic());
    }

    if (!isWaveActive && waveCooldownTimer > 0.0f)
    {
        waveCooldownTimer -= dt;
        if (waveCooldownTimer <= 0.0f) StartNewWave();
    }
    else if (isWaveActive)
    {
        if (enemiesSpawnedThisWave >= totalEnemiesInWave)
        {
            if (enemies.empty())
            {
                isWaveActive = false;
                waveCooldownTimer = timeBetweenWaves;
            }
        }
        else 
        {
            waveSpawnTimer += dt;
            if (waveSpawnTimer >= timeBetweenSpawns)
            {
                EnemyType typeToSpawn = EnemyType::NORMAL;

                bool foundType = false;
                while (!foundType)
                {
                    int numFAST = waveSystem.GetNumOfFAST();
                    int numNORMAL = waveSystem.GetNumOfNORMAL();
                    int numTANK = waveSystem.GetNumOfTANK();

                    int totalAvailableTypes = (numFAST > 0 ? 1 : 0) +
                        (numNORMAL > 0 ? 1 : 0) +
                        (numTANK > 0 ? 1 : 0);

                    if (totalAvailableTypes == 0) return; // Quota épuisé

                    int randomChoice = rand() % 3;

                    if (randomChoice == 0 && numFAST > 0)
                    {
                        typeToSpawn = EnemyType::FAST;
                        waveSystem.ModifyNumOfFAST(-1);
                        foundType = true;
                    }
                    else if (randomChoice == 1 && numNORMAL > 0)
                    {
                        typeToSpawn = EnemyType::NORMAL;
                        waveSystem.ModifyNumOfNORMAL(-1);
                        foundType = true;
                    }
                    else if (randomChoice == 2 && numTANK > 0)
                    {
                        typeToSpawn = EnemyType::TANK;
                        waveSystem.ModifyNumOfTANK(-1);
                        foundType = true;
                    }
                }

                if (typeToSpawn == EnemyType::TANK)
                {
                    if (waveSystem.GetNumOfFAST() > 0)
                    {
                        AddEnemy(typeToSpawn, currentWaveHealthMultiplier, currentWaveSpeedMultiplier);
                        enemiesSpawnedThisWave++;
                        waveSpawnTimer = 0.0f;

                        EnemyType typeFAST = EnemyType::FAST;
                        waveSystem.ModifyNumOfFAST(-1);

                        AddEnemy(typeFAST, currentWaveHealthMultiplier, currentWaveSpeedMultiplier, true);
                        enemiesSpawnedThisWave++;

                        return;
                    }
                }

                AddEnemy(typeToSpawn, currentWaveHealthMultiplier, currentWaveSpeedMultiplier);
                enemiesSpawnedThisWave++;
                waveSpawnTimer = 0.0f;
            }
        }
    }

    if (currentWave > bestWave) bestWave = currentWave;
}

void Game::StartNewWave()
{
    currentWave = (currentWave == 0) ? 1 : currentWave + 1;

    waveSystem.ResetWaveCounts();

    CalculateWaveEnemies();

    if (currentLevel == CurrentLevel::INFINITE && !g_randomMaps.empty())
    {
        if ((currentWave - 1) % g_mapChangeInterval == 0)
        {
           
            LoadMapForLevel(CurrentLevel::INFINITE);

            mainCastle.Init(castlePosition, mainCastle.GetMaxLife());

        }
    }

    isWaveActive = true;
    enemiesSpawnedThisWave = 0;
    waveSpawnTimer = 0.0f;
    waveCooldownTimer = 0.0f;
    waveAnnouncementTimer = 3.0f;

    Music& waveMusic = assets.GetWaveBeginMusic();
    waveMusic.looping = false;
    StopMusicStream(waveMusic);
    PlayMusicStream(waveMusic);
}

void Game::CalculateWaveEnemies()
{
    int current = currentWave;

    int totalBaseEnemies = 10;
    float growthFactor = 0.5f;

    int totalEnemies = (int)(totalBaseEnemies + (current * current * growthFactor));

    if (current <= 3)
    {
        totalEnemies = 5 + current * 2;
    }

    int numFAST = 0;
    int numNORMAL = 0;
    int numTANK = 0;

    float ratioFAST = 0.0f;
    float ratioNORMAL = 0.0f;
    float ratioTANK = 0.0f;

    if (current >= 5 && current % 5 == 0)
    {
        ratioFAST = 0.30f;
        ratioNORMAL = 0.50f;
        ratioTANK = 0.20f;
        totalEnemies = (int)(totalEnemies * 1.5f);
    }
    else if (current < 5)
    {
        ratioFAST = 0.60f;
        ratioNORMAL = 0.40f;
        ratioTANK = 0.00f;
    }
    else
    {
        ratioFAST = 0.50f;
        ratioNORMAL = 0.40f;
        ratioTANK = 0.10f;
    }

    numFAST = (int)(totalEnemies * ratioFAST);
    numNORMAL = (int)(totalEnemies * ratioNORMAL);

    numTANK = totalEnemies - numFAST - numNORMAL;

    waveSystem.SetNumOfFAST(numFAST, currentLevel);
    waveSystem.SetNumOfNORMAL(numNORMAL, currentLevel);
    waveSystem.SetNumOfTANK(numTANK, *this);

    totalEnemiesInWave = totalEnemies;

    currentWaveHealthMultiplier = 1.0f + (current - 1) * 0.1f;

    int speedBoostWaves = (current - 1) / 5;
    currentWaveSpeedMultiplier = 1.0f + speedBoostWaves * 0.05f;
}