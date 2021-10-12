#include "SonicMania.h"

ObjectTMZ1Outro *TMZ1Outro;

void TMZ1Outro_Update(void)
{
    RSDK_THIS(TMZ1Outro);

    if (Zone->actID) {
        void *states[] = { TMZ1Outro_Cutscene2_State1, NULL };
        CutsceneSeq_StartSequence((Entity *)entity, states);
        RSDK.SetLimitedFade(0, 5, 4, entity->alpha, 128, 256);
    }
    else {
        void *states[] = { TMZ1Outro_Cutscene1_State1, TMZ1Outro_Cutscene1_State2, TMZ1Outro_Cutscene1_State3, TMZ1Outro_Cutscene1_State4, NULL };
        CutsceneSeq_StartSequence((Entity *)entity, states);
    }
    if (RSDK_GET_ENTITY(SLOT_CUTSCENESEQ, CutsceneSeq)->objectID)
        RSDK_GET_ENTITY(SLOT_CUTSCENESEQ, CutsceneSeq)->skipType = SKIPTYPE_RELOADSCN;
    entity->active = ACTIVE_NEVER;
}

void TMZ1Outro_LateUpdate(void) {}

void TMZ1Outro_StaticUpdate(void) {}

void TMZ1Outro_Draw(void) {}

void TMZ1Outro_Create(void *data)
{
    RSDK_THIS(TMZ1Outro);
    if (!RSDK_sceneInfo->inEditor) {
        entity->active  = ACTIVE_NORMAL;
        entity->visible = false;
    }
}

void TMZ1Outro_StageLoad(void) {}

bool32 TMZ1Outro_Cutscene1_State1(EntityCutsceneSeq *host)
{
    CutsceneSeq_LockAllPlayerControl();

    foreach_active(Player, player)
    {
        player->state      = Player_State_Ground;
        player->stateInput = StateMachine_None;
    }

    return true;
}

bool32 TMZ1Outro_Cutscene1_State2(EntityCutsceneSeq *host)
{
    if (host->timer == 120) {
        // CrimsonEye_Unknown5(4);
        RSDK.PlaySfx(CrimsonEye->sfxBeep, false, 255);
    }

    if (host->timer == 160) {
        Camera_ShakeScreen(0, 0, 6);
        CrimsonEye->value13                = -0x10000;
        TileLayer *moveLayer               = RSDK.GetSceneLayer(Zone->moveLayer);
        moveLayer->drawLayer[0]            = 0;
        moveLayer->scrollPos               = 0x5000000;
        moveLayer->scrollInfo[0].scrollPos = -0x4D00000;
        RSDK.PlaySfx(CrimsonEye->sfxHullClose, false, 255);
    }

    if (host->timer > 160 && !(host->timer & 0x3F))
        RSDK.PlaySfx(CrimsonEye->sfxElevator, false, 255);

    if (host->timer > 200) {
        if (CrimsonEye->value13) {
            if (RSDK.GetSceneLayer(Zone->moveLayer)->scrollPos < 0x2300000)
                CrimsonEye->value13 = 0;
        }
        else if (!CrimsonEye->value12) {
            Camera_ShakeScreen(0, 0, 6);
            RSDK.PlaySfx(CrimsonEye->sfxHullClose, false, 255);
            return true;
        }
    }

    foreach_active(ItemBox, itembox) { itembox->position.y -= CrimsonEye->value13; }
    foreach_active(SignPost, signPost) { signPost->position.y -= CrimsonEye->value13; }

    return false;
}

bool32 TMZ1Outro_Cutscene1_State3(EntityCutsceneSeq *host)
{
    RSDK_THIS(TMZ1Outro);

    if (host->timer == 30) {
        bool32 flag = true;
        foreach_active(Player, player)
        {
            if (abs(entity->position.x - player->position.x) >= 0x100000) {
                if (player->position.x > entity->position.x) {
                    player->left = true;
                    flag         = false;
                }
                if (player->position.x < entity->position.x) {
                    player->right = true;
                    flag          = false;
                }
            }
            else {
                player->left  = false;
                player->right = false;
                player->groundVel -= player->groundVel >> 3;
                player->velocity.x -= player->velocity.x >> 3;
                player->direction = FLIP_NONE;
            }

            player->jumpPress = false;
            player->jumpHold  = true;
            if (player->playerAnimator.animationID == ANI_PUSH)
                player->jumpPress = true;
            if (!player->onGround || player->velocity.x)
                flag = false;
        }
        return flag;
    }
    return false;
}

bool32 TMZ1Outro_Cutscene1_State4(EntityCutsceneSeq *host)
{
    RSDK_THIS(TMZ1Outro);
    entity->alpha += 4;
    RSDK.SetLimitedFade(0, 3, 5, entity->alpha, 128, 256);

    EntityCamera *camera = RSDK_GET_ENTITY(SLOT_CAMERA1, Camera);
    if (camera->offset.x > 0)
        camera->offset.x -= 0x10000;
    if (entity->alpha == 320) {
        globals->suppressTitlecard = true;
        globals->suppressAutoMusic = true;
        Zone_StoreEntities((RSDK_screens->position.x + RSDK_screens->centerX) << 16, (RSDK_screens->height + RSDK_screens->position.y) << 16);
        RSDK.LoadScene();
        return true;
    }
    return false;
}

bool32 TMZ1Outro_Cutscene2_State1(EntityCutsceneSeq *host)
{
    RSDK_THIS(TMZ1Outro);

    entity->alpha += 4;
    RSDK.SetLimitedFade(0, 5, 4, entity->alpha, 128, 256);
    if (entity->alpha >= 0x100) {
        foreach_all(TitleCard, tCard)
        {
            tCard->active              = ACTIVE_NORMAL;
            tCard->state               = TitleCard_Unknown6;
            tCard->stateDraw           = TitleCard_StateDraw_Default;
            globals->suppressAutoMusic = false;
            Music_PlayTrack(TRACK_STAGE);
            foreach_break;
        }
        return true;
    }
    return false;
}

void TMZ1Outro_EditorDraw(void) {}

void TMZ1Outro_EditorLoad(void) {}

void TMZ1Outro_Serialize(void) { RSDK_EDITABLE_VAR(TMZ1Outro, VAR_VECTOR2, size); }
