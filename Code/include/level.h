
#pragma once

#include <raylib.h>
#include <vector>
#include "enum.h" 

struct EnemyWave {
    EnemyType enemyType;
    int count;
    float interval;

    EnemyWave(EnemyType type, int c, float i)
        : enemyType(type), count(c), interval(i) {
    }

    EnemyWave() : enemyType(EnemyType::NORMAL), count(0), interval(0.0f) {}
};


struct LevelData {
    CurrentLevel id;
    std::vector<EnemyWave> preBossWaves;
    float bossHpMultiplier;
};

class Level
{
private:
    std::vector<LevelData> allLevelData;
    void LoadAllLevelData();

public:
    Level();

    const LevelData& GetLevelData(CurrentLevel levelId) const;
};

