#include <raylib.h>
#include <string>

#include "Assets.h"
#include "sprites.h"

using namespace std;

void GameAssets::LoadGameAssets()
{
    mouseTexture = LoadTexture("Assets/raymancursormouse.png");
    titleScreenTexture = LoadTexture("Assets/title_screen.png");
    levelSelectionTexture = LoadTexture("Assets/level_selection.png");
    settingsTexture = LoadTexture("Assets/settings.png");
    helpTexture = LoadTexture("Assets/help/help.png");

    greenButtonTexture = LoadTexture("Assets/green_button.png");
    redButtonTexture = LoadTexture("Assets/red_button.png");

    volumeOptionTexture = LoadTexture("Assets/volume/volume_option.png");
    creditsTexture = LoadTexture("Assets/credits.png");
    resetTexture = LoadTexture("Assets/reset.png");

    masterVolume0 = LoadTexture("Assets/volume/master_volume_0%.png");
    masterVolume25 = LoadTexture("Assets/volume/master_volume_25%.png");
    masterVolume50 = LoadTexture("Assets/volume/master_volume_50%.png");
    masterVolume75 = LoadTexture("Assets/volume/master_volume_75%.png");
    masterVolume100 = LoadTexture("Assets/volume/master_volume_100%.png");

    musicVolume0 = LoadTexture("Assets/volume/music_volume_0%.png");
    musicVolume25 = LoadTexture("Assets/volume/music_volume_25%.png");
    musicVolume50 = LoadTexture("Assets/volume/music_volume_50%.png");
    musicVolume75 = LoadTexture("Assets/volume/music_volume_75%.png");
    musicVolume100 = LoadTexture("Assets/volume/music_volume_100%.png");

    sfxVolume0 = LoadTexture("Assets/volume/sfx_volume_0%.png");
    sfxVolume25 = LoadTexture("Assets/volume/sfx_volume_25%.png");
    sfxVolume50 = LoadTexture("Assets/volume/sfx_volume_50%.png");
    sfxVolume75 = LoadTexture("Assets/volume/sfx_volume_75%.png");
    sfxVolume100 = LoadTexture("Assets/volume/sfx_volume_100%.png");

    gameplayHelpTexture = LoadTexture("Assets/help/gameplay_help.png");
    towerHelpTexture = LoadTexture("Assets/help/tower_help.png");
    enemyHelpTexture = LoadTexture("Assets/help/enemy_help.png");

    lvl1BackgroundTexture = LoadTexture("Assets/RandomMaps/map02tdf.png");
    lvl2BackgroundTexture = LoadTexture("Assets/RandomMaps/map01tdf.png");
    lvl3BackgroundTexture = LoadTexture("Assets/RandomMaps/map03tdf.png");

    shopIconTexture = LoadTexture("Assets/shop_icon.png");
    coinIconTexture = LoadTexture("Assets/coin_icon.png");
    coinTexture = LoadTexture("Assets/coin.png");

    for (int i = 0; i < 15; ++i)
    {
        string path = "Assets/life/life_" + to_string(i + 1) + ".png";
        lifeTextures[i] = LoadTexture(path.c_str());
    }
    fullLifeTexture = LoadTexture("Assets/life/full_life.png");

    archerTexture = LoadTexture("Assets/archer_tower/archer.png");
    wizardTexture = LoadTexture("Assets/wizard_tower/wizardRAYMAN.png");
    fireBallTexture = LoadTexture("Assets/wizard_tower/fireBall.png");
    catapultTexture = LoadTexture("Assets/catapult_tower/catapult.png");

    lvl1ArcherTowerTexture = LoadTexture("Assets/archer_tower/archer_tower_lvl1.png");
    lvl2ArcherTowerTexture = LoadTexture("Assets/archer_tower/archer_tower_lvl2.png");
    lvl3ArcherTowerTexture = LoadTexture("Assets/archer_tower/archer_tower_lvl3.png");
	lvl4ArcherTowerTexture = LoadTexture("Assets/archer_tower/archer_tower_lvl4.png");
	lvl5ArcherTowerTexture = LoadTexture("Assets/archer_tower/archer_tower_lvl5.png");
	lvl6ArcherTowerTexture = LoadTexture("Assets/archer_tower/archer_tower_lvl6.png");
	lvl7ArcherTowerTexture = LoadTexture("Assets/archer_tower/archer_tower_lvl7.png");

    lvl1WizardTowerTexture = LoadTexture("Assets/wizard_tower/wizard_tower_lvl1.png");
    lvl2WizardTowerTexture = LoadTexture("Assets/wizard_tower/wizard_tower_lvl2.png");
    lvl3WizardTowerTexture = LoadTexture("Assets/wizard_tower/wizard_tower_lvl3.png");
    lvl4WizardTowerTexture = LoadTexture("Assets/wizard_tower/wizard_tower_lvl4.png");
    lvl5WizardTowerTexture = LoadTexture("Assets/wizard_tower/wizard_tower_lvl5.png");
    lvl6WizardTowerTexture = LoadTexture("Assets/wizard_tower/wizard_tower_lvl6.png");
    lvl7WizardTowerTexture = LoadTexture("Assets/wizard_tower/wizard_tower_lvl7.png");


    lvl1CatapultTowerTexture = LoadTexture("Assets/catapult_tower/catapult_tower_lvl1.png");
	lvl2CatapultTowerTexture = LoadTexture("Assets/catapult_tower/catapult_tower_lvl2.png");
	lvl3CatapultTowerTexture = LoadTexture("Assets/catapult_tower/catapult_tower_lvl3.png");
    lvl4CatapultTowerTexture = LoadTexture("Assets/catapult_tower/catapult_tower_lvl4.png");
    lvl5CatapultTowerTexture = LoadTexture("Assets/catapult_tower/catapult_tower_lvl5.png");
    lvl6CatapultTowerTexture = LoadTexture("Assets/catapult_tower/catapult_tower_lvl6.png");
    lvl7CatapultTowerTexture = LoadTexture("Assets/catapult_tower/catapult_tower_lvl7.png");

    castleTexture = LoadTexture("Assets/castle/castle.png");

	amelorationWithButtonTexture = LoadTexture("Assets/amelioration_with_button.png");


    tankWalkSheet = LoadSpriteSheet("Assets/enemies/TANKRABBIDSWALK.png", 7, 1);
    tankWalkAnimation.Name = "Walk";
    tankWalkAnimation.StartFrame = 0;
    tankWalkAnimation.EndFrame = 6;
    tankWalkAnimation.FPS = 10.0f;
    tankWalkAnimation.Loops = true;

    tankAttackSheet = LoadSpriteSheet("Assets/enemies/TANKRABBIDSATTACK.png", 7, 1);
    tankAttackAnimation.Name = "Attack";
    tankAttackAnimation.StartFrame = 0;
    tankAttackAnimation.EndFrame = 6;
    tankAttackAnimation.FPS = 10.0f;
    tankAttackAnimation.Loops = false;

    bulletTexture = LoadTexture("Assets/castle/Bullet.png");
    boss1Texture = LoadTexture("Assets/enemies/boss_1.png");
    boss2Texture = LoadTexture("Assets/enemies/boss_2.png");
    boss3Texture = LoadTexture("Assets/enemies/boss_3.png");
    boss4Texture = LoadTexture("Assets/enemies/boss_4.png");
	ferretTexture = LoadTexture("Assets/enemies/ferret.png");
	necromancerTexture = LoadTexture("Assets/enemies/normal_enemy.png");

    infiniteGameOverTexture = LoadTexture("Assets/infinite_gameover.png");
    levelGameOverTexture = LoadTexture("Assets/level_gameover.png");
    levelVictoryTexture = LoadTexture("Assets/level_victory.png");

    lockTexture = LoadTexture("Assets/lock.png");

    medievalFont = LoadFont("Assets/font/medieval_font.ttf");

    victoryMusic = LoadMusicStream("Assets/music/victory_music.mp3");
    gameOverMusic = LoadMusicStream("Assets/music/game_over_music.mp3");
    levelMusic = LoadMusicStream("Assets/music/level_music.mp3");
    infiniteMusic = LoadMusicStream("Assets/music/infinite_music.mp3");
    bossMusic = LoadMusicStream("Assets/music/boss_music.mp3");
    titleMusic = LoadMusicStream("Assets/music/title_music.mp3");

    music2 = LoadMusicStream("Assets/music/71-bunnies-can-t-slide.mp3");
    waveBeginMusic = LoadMusicStream("Assets/music/wave_begin.mp3");

    archerShot = LoadSound("Assets/sound/archer_shot.wav");
    catapultShot = LoadSound("Assets/sound/catapult_shot.wav");
    clickSound = LoadSound("Assets/sound/click_sound.wav");
    clickLevel = LoadSound("Assets/sound/click_level.wav");
    death1 = LoadSound("Assets/sound/death_1.wav");
    death2 = LoadSound("Assets/sound/death_2.wav");
    death3 = LoadSound("Assets/sound/death_3.wav");
    enemyAttack = LoadSound("Assets/sound/enemy_attack.wav");
    lockedLevel = LoadSound("Assets/sound/locked_level.wav");
    resetSound = LoadSound("Assets/sound/reset_sound.wav");
    wizardShot = LoadSound("Assets/sound/wizard_shot.wav");
    grabTowerSound = LoadSound("Assets/sound/grab_tower.wav");
    levelUpSound = LoadSound("Assets/sound/level_up.wav");
}

void GameAssets::UnloadGameAssets()
{
    UnloadTexture(mouseTexture);
    UnloadTexture(titleScreenTexture);
    UnloadTexture(levelSelectionTexture);
    UnloadTexture(settingsTexture);
    UnloadTexture(helpTexture);

    UnloadTexture(greenButtonTexture);
    UnloadTexture(redButtonTexture);

    UnloadTexture(volumeOptionTexture);
    UnloadTexture(creditsTexture);
    UnloadTexture(resetTexture);

    UnloadTexture(masterVolume0);
    UnloadTexture(masterVolume25);
    UnloadTexture(masterVolume50);
    UnloadTexture(masterVolume75);
    UnloadTexture(masterVolume100);

    UnloadTexture(musicVolume0);
    UnloadTexture(musicVolume25);
    UnloadTexture(musicVolume50);
    UnloadTexture(musicVolume75);
    UnloadTexture(musicVolume100);

    UnloadTexture(sfxVolume0);
    UnloadTexture(sfxVolume25);
    UnloadTexture(sfxVolume50);
    UnloadTexture(sfxVolume75);
    UnloadTexture(sfxVolume100);

    UnloadTexture(gameplayHelpTexture);
    UnloadTexture(towerHelpTexture);
    UnloadTexture(enemyHelpTexture);

    UnloadTexture(lvl1BackgroundTexture);
    UnloadTexture(lvl2BackgroundTexture);
    UnloadTexture(lvl3BackgroundTexture);

    UnloadTexture(shopIconTexture);
    UnloadTexture(coinIconTexture);
    UnloadTexture(coinTexture);

    for (int i = 0; i < 15; ++i)
    {
        UnloadTexture(lifeTextures[i]);
    }
    UnloadTexture(fullLifeTexture);

    UnloadTexture(castleTexture);
    UnloadTexture(archerTexture);
    UnloadTexture(wizardTexture);
    UnloadTexture(fireBallTexture);
    UnloadTexture(catapultTexture);

    UnloadTexture(lvl1ArcherTowerTexture);
    UnloadTexture(lvl2ArcherTowerTexture);
    UnloadTexture(lvl3ArcherTowerTexture);
    UnloadTexture(lvl4ArcherTowerTexture);
    UnloadTexture(lvl5ArcherTowerTexture);
    UnloadTexture(lvl6ArcherTowerTexture);
    UnloadTexture(lvl7ArcherTowerTexture);

    UnloadTexture(lvl1WizardTowerTexture);
    UnloadTexture(lvl2WizardTowerTexture);
    UnloadTexture(lvl3WizardTowerTexture);
    UnloadTexture(lvl4WizardTowerTexture);
    UnloadTexture(lvl5WizardTowerTexture);
    UnloadTexture(lvl6WizardTowerTexture);
    UnloadTexture(lvl7WizardTowerTexture);


    UnloadTexture(lvl1CatapultTowerTexture);
    UnloadTexture(lvl2CatapultTowerTexture);
	UnloadTexture(lvl3CatapultTowerTexture);
    UnloadTexture(lvl4CatapultTowerTexture);
    UnloadTexture(lvl5CatapultTowerTexture);
    UnloadTexture(lvl6CatapultTowerTexture);
    UnloadTexture(lvl7CatapultTowerTexture);


	UnloadTexture(amelorationWithButtonTexture);

    UnloadTexture(necromancerTexture); 
    UnloadTexture(ferretTexture);
    UnloadTexture(cacodaemonTexture);

    UnloadTexture(boss1Texture);
    UnloadTexture(boss2Texture);
    UnloadTexture(boss3Texture);
    UnloadTexture(boss4Texture);

    UnloadTexture(infiniteGameOverTexture);
    UnloadTexture(levelGameOverTexture);
    UnloadTexture(levelVictoryTexture);

    UnloadTexture(lockTexture);

    UnloadTexture(tankWalkSheet.SheetTexture);
    UnloadTexture(tankAttackSheet.SheetTexture);

    UnloadTexture(bulletTexture);

    UnloadFont(medievalFont);

    UnloadMusicStream(victoryMusic);
    UnloadMusicStream(gameOverMusic);
    UnloadMusicStream(levelMusic);
    UnloadMusicStream(infiniteMusic);
    UnloadMusicStream(bossMusic);
    UnloadMusicStream(titleMusic);

    UnloadMusicStream(music2);
    UnloadMusicStream(waveBeginMusic);
   
    UnloadSound(archerShot);
    UnloadSound(catapultShot);
    UnloadSound(clickSound);
    UnloadSound(clickLevel);
    UnloadSound(death1);
    UnloadSound(death2);
    UnloadSound(death3);
    UnloadSound(enemyAttack);
    UnloadSound(lockedLevel);
    UnloadSound(resetSound);
    UnloadSound(wizardShot);
    UnloadSound(grabTowerSound);
    UnloadSound(levelUpSound);
}

Texture2D GameAssets::GetLifeTexture(float percent) const
{
    if (percent > 93.5f) return fullLifeTexture;
    if (percent > 87.0f) return lifeTextures[0];
    if (percent > 80.5f) return lifeTextures[1];
    if (percent > 74.0f) return lifeTextures[2];
    if (percent > 67.5f) return lifeTextures[3];
    if (percent > 61.0f) return lifeTextures[4];
    if (percent > 54.5f) return lifeTextures[5];
    if (percent > 48.0f) return lifeTextures[6];
    if (percent > 41.5f) return lifeTextures[7];
    if (percent > 35.0f) return lifeTextures[8];
    if (percent > 28.5f) return lifeTextures[9];
    if (percent > 22.0f) return lifeTextures[10];
    if (percent > 15.5f) return lifeTextures[11];
    if (percent > 9.0f)  return lifeTextures[12];
    if (percent > 0.0f)  return lifeTextures[13];
    return lifeTextures[14];
}

