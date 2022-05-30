#if RETRO_REV02

// This is the "dummy" struct, it serves as the base in the event a suitable API isn't loaded (such as in this decomp)
// This struct should never be removed, other structs such as "SteamUserCore" would be added and "userCore" would be set to that instead
struct DummyCore : UserCore {
    void StageLoad();
    bool32 CheckFocusLost();
    int32 GetUserLanguage();
    int32 GetUserRegion();
    int32 GetUserPlatform();
    bool32 GetConfirmButtonFlip();
    void LaunchManual();
    void ExitGame();
    int32 GetDefaultGamepadType();
    bool32 IsOverlayEnabled(uint32 overlay) { return false; }
#if RETRO_VER_EGS
    bool32 CanShowExtensionOverlay(int32 overlay)
    {
        PrintLog(PRINT_POPUP, "Can Show Extension Overlay?: %d", overlay);
        return true;
    }
    bool32 ShowExtensionOverlay(int32 overlay)
    {
        PrintLog(PRINT_POPUP, "Show Extension Overlay: %d", overlay);
        return true;
    }
    bool32 ShowAltExtensionOverlay(int32 overlay)
    {
        PrintLog(PRINT_POPUP, "Show Alternate Extension Overlay: %d", overlay);
        return true;
    }
    bool32 ShowLimitedVideoOptions(int32 overlay)
    {
        PrintLog(PRINT_POPUP, "Show Limited Video Options?");
        return false;
    }
    void InitInputDevices() {}
    void Unknown() {}
#else
    bool32 ShowExtensionOverlay(int32 overlay)
    {
        switch (overlay) {
            default: PrintLog(PRINT_POPUP, "Show Unknown Extension Overlay: %d", overlay); break;
            case 0: PrintLog(PRINT_POPUP, "Show Extension Overlay: %d (Plus Upsell Screen)", overlay); break;
        }

        return false;
    }
#endif

    uint16 field_25;
    uint8 field_27;
};

extern DummyCore *dummyCore;

DummyCore *InitDummyCore();

#endif

// these are rev02 only but keeping em helps organization
uint32 GetAPIValueID(const char *identifier, int32 charIndex);
int32 GetAPIValue(uint32 id);
