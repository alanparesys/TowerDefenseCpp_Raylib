#pragma once

#include <raylib.h>
#include "sprites.h"

class GameAssets
{
private:
    Texture2D mouseTexture;
    Texture2D titleScreenTexture;
    Texture2D levelSelectionTexture;
    Texture2D settingsTexture;
    Texture2D helpTexture;

    Texture2D greenButtonTexture;
    Texture2D redButtonTexture;

    Texture2D volumeOptionTexture;
    Texture2D creditsTexture;
    Texture2D resetTexture;

    Texture2D masterVolume0;
    Texture2D masterVolume25;
    Texture2D masterVolume50;
    Texture2D masterVolume75;
    Texture2D masterVolume100;

    Texture2D musicVolume0;
    Texture2D musicVolume25;
    Texture2D musicVolume50;
    Texture2D musicVolume75;
    Texture2D musicVolume100;

    Texture2D sfxVolume0;
    Texture2D sfxVolume25;
    Texture2D sfxVolume50;
    Texture2D sfxVolume75;
    Texture2D sfxVolume100;

    Texture2D gameplayHelpTexture;
    Texture2D towerHelpTexture;
    Texture2D enemyHelpTexture;

    Texture2D lvl1BackgroundTexture;
    Texture2D lvl2BackgroundTexture;
    Texture2D lvl3BackgroundTexture;

    Texture2D infiniteGameOverTexture;
    Texture2D levelGameOverTexture;
    Texture2D levelVictoryTexture;

    Texture2D shopIconTexture;
    Texture2D coinIconTexture;
    Texture2D coinTexture;
    Texture2D lockTexture;

    Texture2D fullLifeTexture;
    Texture2D lifeTextures[15];

    Texture2D castleTexture;
    Texture2D archerTexture;
    Texture2D wizardTexture;
    Texture2D fireBallTexture;
    Texture2D catapultTexture;
    Texture2D bulletTexture;
    Texture2D amelorationWithButtonTexture;

    Texture2D lvl1ArcherTowerTexture;
    Texture2D lvl2ArcherTowerTexture;
    Texture2D lvl3ArcherTowerTexture;
    Texture2D lvl4ArcherTowerTexture;
    Texture2D lvl5ArcherTowerTexture;
    Texture2D lvl6ArcherTowerTexture;
    Texture2D lvl7ArcherTowerTexture;

    Texture2D lvl1WizardTowerTexture;
    Texture2D lvl2WizardTowerTexture;
    Texture2D lvl3WizardTowerTexture;
    Texture2D lvl4WizardTowerTexture;
    Texture2D lvl5WizardTowerTexture;
    Texture2D lvl6WizardTowerTexture;
    Texture2D lvl7WizardTowerTexture;

    Texture2D lvl1CatapultTowerTexture;
    Texture2D lvl2CatapultTowerTexture;
    Texture2D lvl3CatapultTowerTexture;
    Texture2D lvl4CatapultTowerTexture;
    Texture2D lvl5CatapultTowerTexture;
    Texture2D lvl6CatapultTowerTexture;
    Texture2D lvl7CatapultTowerTexture;

    Texture2D necromancerTexture;
    Texture2D ferretTexture;
    Texture2D cacodaemonTexture;

    Texture2D boss1Texture;
    Texture2D boss2Texture;
    Texture2D boss3Texture;
    Texture2D boss4Texture;

    SpriteSheet tankWalkSheet;
    SpriteAnimation tankWalkAnimation;
    SpriteSheet tankAttackSheet;
    SpriteAnimation tankAttackAnimation;

    Font medievalFont;

    Music music2;
    Music waveBeginMusic;

    Music titleMusic;
    Music levelMusic;
    Music infiniteMusic;
    Music bossMusic;
    Music victoryMusic;
    Music gameOverMusic;

    Sound archerShot;
    Sound catapultShot;
    Sound clickSound;
    Sound clickLevel;
    Sound death1;
    Sound death2;
    Sound death3;
    Sound enemyAttack;
    Sound lockedLevel;
    Sound resetSound;
    Sound wizardShot;
    Sound grabTowerSound;
    Sound levelUpSound;


public:
    void LoadGameAssets();
    void UnloadGameAssets();
    Texture2D GetLifeTexture(float percent) const;


    const Music& GetTitleMusic() const { return titleMusic; }
    const Music& GetLevelMusic() const { return levelMusic; }
    const Music& GetInfiniteMusic() const { return infiniteMusic; }
    const Music& GetBossMusic() const { return bossMusic; }
    const Music& GetVictoryMusic() const { return victoryMusic; }
    const Music& GetGameOverMusic() const { return gameOverMusic; }
    Music& GetWaveBeginMusic() { return waveBeginMusic; }

    const Sound& GetArcherShot() const { return archerShot; }
    const Sound& GetWizardShot() const { return wizardShot; }
    const Sound& GetCatapultShot() const { return catapultShot; }
    const Sound& GetClickSound() const { return clickSound; }
    const Sound& GetClickLevel() const { return clickLevel; }
    const Sound& GetLockedLevel() const { return lockedLevel; }
    const Sound& GetResetSound() const { return resetSound; }
    const Sound& GetGrabTowerSound() const { return grabTowerSound; }
    const Sound& GetLevelUpSound() const { return levelUpSound; }
    const Sound& GetDeath1() const { return death1; }
    const Sound& GetDeath2() const { return death2; }
    const Sound& GetDeath3() const { return death3; }

    const Texture2D& GetMouseTexture() const { return mouseTexture; }
    const Texture2D& GetTitleScreenTexture() const { return titleScreenTexture; }
    const Texture2D& GetLevelSelectionTexture() const { return levelSelectionTexture; }
    const Texture2D& GetSettingsTexture() const { return settingsTexture; }
    const Texture2D& GetHelpTexture() const { return helpTexture; }
    const Texture2D& GetGreenButtonTexture() const { return greenButtonTexture; }
    const Texture2D& GetRedButtonTexture() const { return redButtonTexture; }
    const Texture2D& GetVolumeOptionTexture() const { return volumeOptionTexture; }
    const Texture2D& GetCreditsTexture() const { return creditsTexture; }
    const Texture2D& GetResetTexture() const { return resetTexture; }

    const Texture2D& GetGameplayHelpTexture() const { return gameplayHelpTexture; }
    const Texture2D& GetTowerHelpTexture() const { return towerHelpTexture; }
    const Texture2D& GetEnemyHelpTexture() const { return enemyHelpTexture; }

    const Texture2D& GetLvl1BackgroundTexture() const { return lvl1BackgroundTexture; }
    const Texture2D& GetLvl2BackgroundTexture() const { return lvl2BackgroundTexture; }
    const Texture2D& GetLvl3BackgroundTexture() const { return lvl3BackgroundTexture; }

    const Texture2D& GetInfiniteGameOverTexture() const { return infiniteGameOverTexture; }
    const Texture2D& GetLevelGameOverTexture() const { return levelGameOverTexture; }
    const Texture2D& GetLevelVictoryTexture() const { return levelVictoryTexture; }

    const Texture2D& GetMasterVolume0() const { return masterVolume0; }
    const Texture2D& GetMasterVolume25() const { return masterVolume25; }
    const Texture2D& GetMasterVolume50() const { return masterVolume50; }
    const Texture2D& GetMasterVolume75() const { return masterVolume75; }
    const Texture2D& GetMasterVolume100() const { return masterVolume100; }

    const Texture2D& GetMusicVolume0() const { return musicVolume0; }
    const Texture2D& GetMusicVolume25() const { return musicVolume25; }
    const Texture2D& GetMusicVolume50() const { return musicVolume50; }
    const Texture2D& GetMusicVolume75() const { return musicVolume75; }
    const Texture2D& GetMusicVolume100() const { return musicVolume100; }

    const Texture2D& GetSfxVolume0() const { return sfxVolume0; }
    const Texture2D& GetSfxVolume25() const { return sfxVolume25; }
    const Texture2D& GetSfxVolume50() const { return sfxVolume50; }
    const Texture2D& GetSfxVolume75() const { return sfxVolume75; }
    const Texture2D& GetSfxVolume100() const { return sfxVolume100; }

    const Texture2D& GetShopIconTexture() const { return shopIconTexture; }
    const Texture2D& GetCoinIconTexture() const { return coinIconTexture; }
    const Texture2D& GetCoinTexture() const { return coinTexture; }
    const Texture2D& GetLockTexture() const { return lockTexture; }
    const Texture2D& GetCastleTexture() const { return castleTexture; }

    const Texture2D& GetArcherTexture() const { return archerTexture; }
    const Texture2D& GetWizardTexture() const { return wizardTexture; }
    const Texture2D& GetFireBallTexture() const { return fireBallTexture; }
    const Texture2D& GetCatapultTexture() const { return catapultTexture; }
    const Texture2D& GetBulletTexture() const { return bulletTexture; }
    const Texture2D& GetAmelorationWithButtonTexture() const { return amelorationWithButtonTexture; }

    const Texture2D& GetLvl1ArcherTowerTexture() const { return lvl1ArcherTowerTexture; }
    const Texture2D& GetLvl2ArcherTowerTexture() const { return lvl2ArcherTowerTexture; }
    const Texture2D& GetLvl3ArcherTowerTexture() const { return lvl3ArcherTowerTexture; }
    const Texture2D& GetLvl4ArcherTowerTexture() const { return lvl4ArcherTowerTexture; }
    const Texture2D& GetLvl5ArcherTowerTexture() const { return lvl5ArcherTowerTexture; }
    const Texture2D& GetLvl6ArcherTowerTexture() const { return lvl6ArcherTowerTexture; }
    const Texture2D& GetLvl7ArcherTowerTexture() const { return lvl7ArcherTowerTexture; }

    const Texture2D& GetLvl1WizardTowerTexture() const { return lvl1WizardTowerTexture; }
    const Texture2D& GetLvl2WizardTowerTexture() const { return lvl2WizardTowerTexture; }
    const Texture2D& GetLvl3WizardTowerTexture() const { return lvl3WizardTowerTexture; }
    const Texture2D& GetLvl4WizardTowerTexture() const { return lvl4WizardTowerTexture; }
    const Texture2D& GetLvl5WizardTowerTexture() const { return lvl5WizardTowerTexture; }
    const Texture2D& GetLvl6WizardTowerTexture() const { return lvl6WizardTowerTexture; }
    const Texture2D& GetLvl7WizardTowerTexture() const { return lvl7WizardTowerTexture; }

    const Texture2D& GetLvl1CatapultTowerTexture() const { return lvl1CatapultTowerTexture; }
    const Texture2D& GetLvl2CatapultTowerTexture() const { return lvl2CatapultTowerTexture; }
    const Texture2D& GetLvl3CatapultTowerTexture() const { return lvl3CatapultTowerTexture; }
    const Texture2D& GetLvl4CatapultTowerTexture() const { return lvl4CatapultTowerTexture; }
    const Texture2D& GetLvl5CatapultTowerTexture() const { return lvl5CatapultTowerTexture; }
    const Texture2D& GetLvl6CatapultTowerTexture() const { return lvl6CatapultTowerTexture; }
    const Texture2D& GetLvl7CatapultTowerTexture() const { return lvl7CatapultTowerTexture; }

    const Texture2D& GetNecromancerTexture() const { return necromancerTexture; }
    const Texture2D& GetFerretTexture() const { return ferretTexture; }
    const Texture2D& GetCacodaemonTexture() const { return cacodaemonTexture; }
    const Texture2D& GetBoss1Texture() const { return boss1Texture; }
    const Texture2D& GetBoss2Texture() const { return boss2Texture; }
    const Texture2D& GetBoss3Texture() const { return boss3Texture; }
    const Texture2D& GetBoss4Texture() const { return boss4Texture; }

    const SpriteSheet& GetTankWalkSheet() const { return tankWalkSheet; }
    const SpriteAnimation& GetTankWalkAnimation() const { return tankWalkAnimation; }
    const SpriteSheet& GetTankAttackSheet() const { return tankAttackSheet; }
    const SpriteAnimation& GetTankAttackAnimation() const { return tankAttackAnimation; }

    const Font& GetMedievalFont() const { return medievalFont; }
};