#include "wave_system.h"
#include "game.h"
#include "enum.h"

WaveSystemClass::WaveSystemClass()
    : int_FAST(0), int_NORMAL(0), int_TANK(0)
{
}

void WaveSystemClass::SetNumOfFAST(int count, CurrentLevel currentLevel)
{
    this->int_FAST = count;
    (void)currentLevel;
}

void WaveSystemClass::SetNumOfNORMAL(int count, CurrentLevel currentLevel)
{
    this->int_NORMAL = count;
    (void)currentLevel;
}

void WaveSystemClass::SetNumOfTANK(int count, Game& game)
{
    this->int_TANK = count;
    (void)game;
}

void WaveSystemClass::ResetWaveCounts()
{
    int_FAST = 0;
    int_NORMAL = 0;
    int_TANK = 0;
}