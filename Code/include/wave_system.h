#pragma once

#include "enum.h"

class Game;

class WaveSystemClass
{
private:
    int int_FAST;
    int int_NORMAL;
    int int_TANK;

public:
    WaveSystemClass();

    void SetNumOfFAST(int count, CurrentLevel currentLevel);
    void SetNumOfNORMAL(int count, CurrentLevel currentLevel);
    void SetNumOfTANK(int count, Game& game);

    int GetNumOfFAST() const { return int_FAST; }
    int GetNumOfNORMAL() const { return int_NORMAL; }
    int GetNumOfTANK() const { return int_TANK; }

    void ModifyNumOfFAST(int amount) { int_FAST += amount; if (int_FAST < 0) int_FAST = 0; }
    void ModifyNumOfNORMAL(int amount) { int_NORMAL += amount; if (int_NORMAL < 0) int_NORMAL = 0; }
    void ModifyNumOfTANK(int amount) { int_TANK += amount; if (int_TANK < 0) int_TANK = 0; }

    void ResetWaveCounts();
};