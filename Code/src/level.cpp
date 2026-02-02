
#include "level.h"
#include "game.h"
#include <stdexcept>
#include <iostream>

Level::Level()
{
    LoadAllLevelData();
}

const LevelData& Level::GetLevelData(CurrentLevel levelId) const
{
    size_t index = static_cast<size_t>(levelId) - 1;

    if (levelId == CurrentLevel::NONE || index >= allLevelData.size())
    {
        throw std::runtime_error("Level data not found or invalid level ID!");
    }

    return allLevelData[index];
}

void Level::LoadAllLevelData()
{
    allLevelData.clear();
    allLevelData.reserve(15);

    LevelData lvl1 = { CurrentLevel::LEVEL1, {
        { EnemyType::NORMAL, 5, 1.0f },
        { EnemyType::BOSS, 1, 1.0f}
    }, 1.0f };
    allLevelData.push_back(lvl1);

    LevelData lvl2 = { CurrentLevel::LEVEL2, {
        { EnemyType::NORMAL, 8, 1.2f },
        { EnemyType::FAST, 3, 1.5f },
        { EnemyType::BOSS, 1, 1.2f }
    }, 1.2f };
    allLevelData.push_back(lvl2);

    LevelData lvl3 = { CurrentLevel::LEVEL3, {
        { EnemyType::NORMAL, 15, 1.0f },
        { EnemyType::FAST, 5, 1.0f },
        { EnemyType::BOSS, 1, 1.5f}
    }, 1.5f };
    allLevelData.push_back(lvl3);

    LevelData lvl4 = { CurrentLevel::LEVEL4, {
        { EnemyType::NORMAL, 10, 1.0f },
        { EnemyType::TANK, 1, 3.0f },
        { EnemyType::BOSS, 1, 1.0f}
    }, 2.0f };
    allLevelData.push_back(lvl4);

    LevelData lvl5 = { CurrentLevel::LEVEL5, {
        { EnemyType::FAST, 15, 0.8f },
        { EnemyType::TANK, 2, 4.0f },
        { EnemyType::BOSS, 1, 2.5f}
    }, 2.5f };
    allLevelData.push_back(lvl5);

    LevelData lvl6 = { CurrentLevel::LEVEL6, {
        { EnemyType::TANK, 1, 0.5f },
        { EnemyType::FAST, 5, 0.8f },
        { EnemyType::NORMAL, 10, 1.0f },
        { EnemyType::BOSS, 1, 1.0f}
    }, 3.0f };
    allLevelData.push_back(lvl6);

    LevelData lvl7 = { CurrentLevel::LEVEL7, {
        { EnemyType::NORMAL, 30, 0.6f },
        { EnemyType::FAST, 5, 0.8f },
        { EnemyType::BOSS, 1, 3.5f}
    }, 3.5f };
    allLevelData.push_back(lvl7);

    LevelData lvl8 = { CurrentLevel::LEVEL8, {
        { EnemyType::TANK, 3, 3.0f },
        { EnemyType::FAST, 10, 0.8f },
        { EnemyType::BOSS, 1, 1.0f}
    }, 4.0f };
    allLevelData.push_back(lvl8);

    LevelData lvl9 = { CurrentLevel::LEVEL9, {
        { EnemyType::FAST, 40, 0.5f },
        { EnemyType::BOSS, 1, 4.2f}
    }, 4.2f };
    allLevelData.push_back(lvl9);

    LevelData lvl10 = { CurrentLevel::LEVEL10, {
        { EnemyType::TANK, 2, 4.0f },
        { EnemyType::NORMAL, 20, 0.8f },
        { EnemyType::FAST, 15, 0.8f },
        { EnemyType::BOSS, 1, 5.0f}
    }, 5.0f };
    allLevelData.push_back(lvl10);

    LevelData lvl11 = { CurrentLevel::LEVEL11, {
        { EnemyType::NORMAL, 15, 0.7f },
        { EnemyType::TANK, 8, 2.0f },
        { EnemyType::BOSS, 1, 6.0f}
    }, 6.0f };
    allLevelData.push_back(lvl11);

    LevelData lvl12 = { CurrentLevel::LEVEL12, {
        { EnemyType::FAST, 20, 0.5f },
        { EnemyType::TANK, 5, 3.0f },
        { EnemyType::NORMAL, 20, 0.6f },
        { EnemyType::BOSS, 1, 7.0f}
    }, 7.0f };
    allLevelData.push_back(lvl12);

    LevelData lvl13 = { CurrentLevel::LEVEL13, {
        { EnemyType::NORMAL, 60, 0.5f },
        { EnemyType::BOSS, 1, 8.0f}
    }, 8.0f };
    allLevelData.push_back(lvl13);

    LevelData lvl14 = { CurrentLevel::LEVEL14, {
        { EnemyType::TANK, 15, 1.5f },
        { EnemyType::FAST, 25, 0.5f },
        { EnemyType::BOSS, 1, 10.0f}
    }, 10.0f };
    allLevelData.push_back(lvl14);

    LevelData lvl15 = { CurrentLevel::LEVEL15, {
        { EnemyType::FAST, 20, 0.5f },
        { EnemyType::TANK, 10, 1.0f },
        { EnemyType::NORMAL, 30, 0.5f },
        { EnemyType::BOSS, 1, 15.0f}
    }, 15.0f };
    allLevelData.push_back(lvl15);
}