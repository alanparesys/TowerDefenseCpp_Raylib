#pragma once

enum class CurrentScreen
{
    LOADING = 0,
    TITLE,
    CHOOSE_LEVEL,
    SETTINGS,
    HELP,
    GAMEPLAY,
    VICTORY,
    GAMEOVER
};

enum class CurrentLevel
{
    NONE = 0,
    LEVEL1 = 1,
    LEVEL2,
    LEVEL3,
    LEVEL4,
    LEVEL5,
    LEVEL6,
    LEVEL7,
    LEVEL8,
    LEVEL9,
    LEVEL10,
    LEVEL11,
    LEVEL12,
    LEVEL13,
    LEVEL14,
    LEVEL15,

    INFINITE = 99
};

enum class TowerType
{
    NONE = 0,
    ARCHER,
    WIZARD,
    CATAPULT
};

enum class TowerLvl
{
    LVL1 = 0,
    LVL2,
    LVL3,
    LVL4,
    LVL5,
    LVL6,
    LVL7
};


enum class EnemyType
{
    NORMAL = 0,
    FAST,
    TANK,
    BOSS
};

