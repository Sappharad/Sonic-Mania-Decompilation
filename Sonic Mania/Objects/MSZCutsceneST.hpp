#ifndef OBJ_MSZCUTSCENEST_H
#define OBJ_MSZCUTSCENEST_H

#include "../SonicMania.hpp"

// Object Class
struct ObjectMSZCutsceneST : Object {
    int value1[6]; //= { -65536, -65536, 0, 0, 0, -65536 };
    ushort value2;
    ushort value3;
    TextInfo value4;
    byte value5;
    bool32 value6;
    bool32 value7;
    bool32 value8;
    bool32 value9;
    bool32 value10;
    bool32 value11;
    bool32 value12;
    byte value13;
    byte value14;
    ushort value15;
    ushort value16;
    ushort value17;
    byte value18;
};

// Entity Class
struct EntityMSZCutsceneST : Entity {

};

// Object Struct
extern ObjectMSZCutsceneST *MSZCutsceneST;

// Standard Entity Events
void MSZCutsceneST_Update();
void MSZCutsceneST_LateUpdate();
void MSZCutsceneST_StaticUpdate();
void MSZCutsceneST_Draw();
void MSZCutsceneST_Create(void* data);
void MSZCutsceneST_StageLoad();
void MSZCutsceneST_EditorDraw();
void MSZCutsceneST_EditorLoad();
void MSZCutsceneST_Serialize();

// Extra Entity Functions


#endif //!OBJ_MSZCUTSCENEST_H