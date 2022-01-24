#pragma once

#include "../JsonForward.h"
#include <algorithm>
#include <array>
#include <iomanip>
#include <mutex>
#include <numbers>
#include <numeric>
#include <windows.h>
#include <sstream>
#include <random>

#include "../imgui/imgui.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "../imgui/imgui_internal.h"
#include "../imgui/imgui_stdlib.h"

#include "../ConfigStructs.h"
#include "../InputUtil.h"
#include "../Interfaces.h"
#include "../Memory.h"
#include "../ProtobufReader.h"
#include "../SDK/Prediction.h"
#include "../d3drender.h"
#include "EnginePrediction.h"
#include "Misc.h"
#include "../render.h"
#include "../SDK/ClassId.h"
#include "../SDK/Client.h"
#include "../SDK/ClientClass.h"
#include "../SDK/ClientMode.h"
#include "../SDK/ConVar.h"
#include "../SDK/Cvar.h"
#include "../SDK/Engine.h"
#include "../SDK/EngineTrace.h"
#include "../SDK/Entity.h"
#include "../SDK/EntityList.h"
#include "../SDK/FrameStage.h"
#include "../SDK/GameEvent.h"
#include "../SDK/GlobalVars.h"
#include "../SDK/ItemSchema.h"
#include "../SDK/Localize.h"
#include "../SDK/LocalPlayer.h"
#include "../SDK/NetworkChannel.h"
#include "../SDK/Panorama.h"
#include "../SDK/Platform.h"
#include "../SDK/UserCmd.h"
#include "../SDK/UtlVector.h"
#include "../SDK/Vector.h"
#include "../SDK/WeaponData.h"
#include "../SDK/WeaponId.h"
#include "../SDK/WeaponSystem.h"

#include "../GUI.h"
#include "../Helpers.h"
#include "../Hooks.h"
#include "../GameData.h"

#include "../imguiCustom.h"
#include "../Vmatrix.h"

#include <vector>
#include <deque>

enum class FrameStage;
class GameEvent;
struct ImDrawList;
struct UserCmd;

#define M_PI 3.14159265358979323846
#define PI_F	((float)(M_PI)) 

namespace Misc
{
    void RecorderHooks(UserCmd* cmd);
    void RegionChanger();
    void setup_steam();
    bool shouldRevealMoney() noexcept;
    bool shouldRevealSuspect() noexcept;
    bool shouldDisableModelOcclusion() noexcept;
    bool shouldFixBoneMatrix() noexcept;
    bool isRadarHackOn() noexcept;
    bool isMenuKeyPressed() noexcept;
    float maxAngleDelta() noexcept;
    float aspectRatio() noexcept;
    void Camera();

    void spectatorList2() noexcept;

    void GUIspectatorList() noexcept;

    void PredictEdgebug(UserCmd* cmd);
    void PredictDuckEdge(UserCmd* cmd);
    void PredictDuckEdge2(UserCmd* cmd);
    void AutoDucks(UserCmd* cmd, int preflags, int postflags);
    void DamageIndicator(GameEvent* event);
    void watermark2() noexcept;
    void EdgebugDetect(UserCmd* cmd, float unpredicted_velocity) noexcept;
    void Keystrokes();
    void run_cm();
    void render_bean(Vector start, Vector end, Color4 color);
    void Jumpstats();
    void BlockBot(UserCmd* cmd);
    void edgejump(UserCmd* cmd, int iFlags, int otherflag) noexcept;
    void PostPred(UserCmd* cmd);
    void Duckedge(UserCmd* cmd);
    void EdgeBug(UserCmd* cmd, int iFlags);
    void StrafeOpt(UserCmd* cmd);
    void TeamDamage(GameEvent* event) noexcept;
    void DrawDamage();
    void smartedgebug(UserCmd* pCmd, float unpredicted_velocity, int iFlags);
    void MiniJump(UserCmd* cmd) noexcept;
    void RotateMovement(UserCmd* pCmd, float rotation);
    void autoStrafe(UserCmd* cmd) noexcept;
    void StaminaIndicator();
    void longjump(UserCmd* cmd, int iFlags);
    void ladderlj(UserCmd* cmd, int iFlags);
    void RecorderIndicator();
    void VelocityIndicator();
    void Spotify();
    void MovementRecorder(UserCmd* pCmd);
    void DrawMovementRecorder();
    void VelocityGraph();
    void StaminaGraph();
    void saveToFile();
    void readFromFile();
    void DrawRecorder() noexcept;
    void HookRecorder(UserCmd* cmd) noexcept;
    void VisualizeRecorder() noexcept;
    void NullStrafe(UserCmd* cmd);
    void indicator();
    void Oldedgebug(UserCmd* cmd);
    void jumpbug(UserCmd* cmd) noexcept;
    void slowwalk(UserCmd* cmd) noexcept;
    void updateClanTag(bool = false) noexcept;
    void spectatorList() noexcept;
    void noscopeCrosshair(ImDrawList* drawlist) noexcept;
    void recoilCrosshair(ImDrawList* drawList) noexcept;
    void watermark() noexcept;
    void prepareRevolver(UserCmd*) noexcept;
    void fastPlant(UserCmd*) noexcept;
    void fastStop(UserCmd*) noexcept;
    void drawBombTimer() noexcept;
    void stealNames() noexcept;
    void disablePanoramablur() noexcept;
    void quickReload(UserCmd*) noexcept;
    bool changeName(bool, const char*, float) noexcept;
    void bunnyHop(UserCmd*) noexcept;
    void fakeBan(bool = false) noexcept;
    void nadePredict() noexcept;
    void fixTabletSignal() noexcept;
    void killMessage(GameEvent& event) noexcept;
    void fixMovement(UserCmd* cmd, float yaw) noexcept;
    void antiAfkKick(UserCmd* cmd) noexcept;
    void fixAnimationLOD(FrameStage stage) noexcept;
    float unpredicted_velocity = 0;
    int iFlags = 0;
    void autoPistol(UserCmd* cmd) noexcept;
    void chokePackets(bool& sendPacket) noexcept;
    void autoReload(UserCmd* cmd) noexcept;
    void revealRanks(UserCmd* cmd) noexcept;
    void removeCrouchCooldown(UserCmd* cmd) noexcept;
    void moonwalk(UserCmd* cmd) noexcept;
    void playHitSound(GameEvent& event) noexcept;
    void killSound(GameEvent& event) noexcept;
    void purchaseList(GameEvent* event = nullptr) noexcept;
    void oppositeHandKnife(FrameStage stage) noexcept;
    void runReportbot() noexcept;
    void resetReportbot() noexcept;
    void preserveKillfeed(bool roundStart = false) noexcept;
    void voteRevealer(GameEvent& event) noexcept;
    void onVoteStart(const void* data, int size) noexcept;
    void onVotePass() noexcept;
    void onVoteFailed() noexcept;
    void drawOffscreenEnemies(ImDrawList* drawList) noexcept;
    void Spectatorlist();
    void autoAccept(const char* soundEntry) noexcept;

    void updateEventListeners(bool forceRemove = false) noexcept;
    void updateInput() noexcept;

    // GUI
    void menuBarItem() noexcept;
    void tabItem() noexcept;
    void tabItem2() noexcept;
    void drawGUI(bool contentOnly) noexcept;

    void drawGUI2(bool contentOnly) noexcept;

    // Config
    json toJson() noexcept;
    void fromJson(const json& j) noexcept;
    void resetConfig() noexcept;

    //blm
    inline int teamDamage = 0;
    inline int teamKills = 0;

}

class preto {

public:

    void record(UserCmd* cmd);
    void play(UserCmd* cmd);

private:
    bool recordBool;
    bool playBool;
    bool crossDistBool;
    bool AimToFirstRecord;
    bool recordAfterDonePlaying;

    Vector viewPos;
    Vector lastPos;
    bool tempBool = true;
    bool isPlayingback = false;
    int i = 0;
};

extern preto movementRecorder;

struct nigger {

    struct custom_cmd
    {
        Vector			viewAngles;
        Vector			pos;
        float			forwardmove;
        float			sidemove;
        float			upmove;
        int				buttons;
    };

    std::vector<custom_cmd> CmdFinal;
    custom_cmd tempCmd;

};

inline nigger blm;



