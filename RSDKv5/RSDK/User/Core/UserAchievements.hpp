#ifndef USER_ACHIEVEMENTS_H
#define USER_ACHIEVEMENTS_H

#include <vector>
#include <string>

namespace RSDK
{

namespace SKU
{

#if RETRO_REV02
// This is the base struct, it serves as the base for any API-specific stats
// This struct should never be removed
struct UserAchievements {
    UserAchievements() {}

    virtual void FrameInit() {}
    virtual void StageLoad() { enabled = true; }
    virtual void OnUnknownEvent() {}
#if RETRO_VER_EGS || RETRO_USE_DUMMY_ACHIEVEMENTS
    virtual bool32 CheckAchievementsEnabled() { return false; }
    virtual void GetAchievementNames(String *names, int32 count) {}
    virtual String *GetAchievementString(String *string)
    {
        string->chars  = NULL;
        string->length = 0;
        string->size   = 0;
        return string;
    }
    virtual String *GetAchievementName(String *name, uint32 id)
    {
        name->chars  = NULL;
        name->length = 0;
        name->size   = 0;
        return name;
    }
    virtual bool32 CheckAchievementPopupEnabled() { return false; }
    virtual int32 GetNextAchievementID() { return 0; }
    virtual void RemoveLastAchievementID() {}
#endif
    virtual void TryUnlockAchievement(const char *name) { PrintLog(PRINT_POPUP, "Achievement Unlocked: %s", name); }

    bool32 enabled = false;
};

#endif

#if RETRO_REV02
extern UserAchievements *achievements;


// ====================
// API Cores
// ====================

// Dummy API
#if RETRO_USERCORE_DUMMY
#include "RSDK/User/Dummy/DummyAchievements.hpp"
#endif

// Steam API
#if RETRO_USERCORE_STEAM
#include "RSDK/User/Steam/SteamAchievements.hpp"
#endif

// Epic Games API
#if RETRO_USERCORE_EOS
#include "RSDK/User/EOS/EOSAchievements.hpp"
#endif

// Switch API
#if RETRO_USERCORE_NX
#include "RSDK/User/NX/NXAchievements.hpp"
#endif

inline bool32 GetAchievementsEnabled() { return achievements->enabled; }
inline void SetAchievementsEnabled(bool32 enabled) { achievements->enabled = enabled; }
#endif

#if RETRO_VER_EGS || RETRO_USE_DUMMY_ACHIEVEMENTS
inline bool32 CheckAchievementsEnabled() { return achievements->CheckAchievementsEnabled(); }
inline void GetAchievementNames(String *names, int32 count) { achievements->GetAchievementNames(names, count); }
#endif

#if RETRO_REV02
inline void TryUnlockAchievement(const char *name) { achievements->TryUnlockAchievement(name); }
#else
void TryUnlockAchievement(const char *name);
#endif
void ClearAchievements();

#if RETRO_VER_EGS || RETRO_USE_DUMMY_ACHIEVEMENTS
extern bool32 achievementsEnabled;
extern uint16 achievementAniFrames[2];
extern Animator achievementAnimator[2];
extern String achievementStrings[2];
extern int32 achievementStringWidth[2];
extern int32 achievementID;
extern int32 achievementDisplayDuration;
extern int32 achievementsDrawn;
extern int32 achievementStrW;
extern int32 achievementStrX;
extern bool32 achievementsLoaded;
extern bool32 achievementDrawReady;
extern bool32 achievementForceReset;

void LoadAchievementAssets();
void ProcessAchievements();
void DrawAchievements();
#endif

} // namespace SKU

} // namespace RSDK

#endif // USER_ACHIEVEMENTS_H
