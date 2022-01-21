#include <array>
#include <cstring>
#include <string_view>
#include <utility>
#include <vector>

#include "../imgui/imgui.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "../imgui/imgui_internal.h"

#include "../ConfigStructs.h"
#include "../fnv.h"
#include "../GameData.h"
#include "../Helpers.h"
#include "../Interfaces.h"
#include "../Memory.h"
#include "../imguiCustom.h"
#include "Visuals.h"

#include "../SDK/ConVar.h"
#include "../SDK/Cvar.h"
#include "../SDK/Engine.h"
#include "../SDK/Entity.h"
#include "../SDK/EntityList.h"
#include "../SDK/FrameStage.h"
#include "../SDK/GameEvent.h"
#include "../SDK/GlobalVars.h"
#include "../SDK/Input.h"
#include "../SDK/LocalPlayer.h"
#include "../SDK/Material.h"
#include "../SDK/MaterialSystem.h"
#include "../SDK/ViewRenderBeams.h"

struct BulletTracers : ColorToggle {
    BulletTracers() : ColorToggle{ 0.0f, 0.75f, 1.0f, 1.0f } {}
};

struct VisualsConfig {
    bool disablePostProcessing{ false };
    bool inverseRagdollGravity{ false };
    bool noFog{ false };
    bool FogChanger{ false };
    float fogstart{ 0.0f };
    int FogDist = 0;
    float FogDens = 0.f;
    bool no3dSky{ false };
    bool noAimPunch{ false };
    bool noViewPunch{ false };
    bool noHands{ false };
    bool noSleeves{ false };
    bool noWeapons{ false };
    bool soundesp{ false };
    bool noSmoke{ false };
    bool noBlur{ false };
    bool dlight{ false };
    bool foott{ false };
    bool noScopeOverlay{ false };
    bool noGrass{ false };
    bool noShadows{ false };
    bool fakeprime{ false };
    bool wireframeSmoke{ false };
    bool zoom{ false };
    KeyBindToggle zoomKey;
    bool thirdperson{ false };
    KeyBindToggle thirdpersonKey;
    int thirdpersonDistance{ 0 };
    int viewmodelFov{ 0 };
    int fov{ 0 };
    int farZ{ 0 };
    int flashReduction{ 0 };
    float brightness{ 0.0f };
    int skybox{ 0 };
    ColorToggle3 world;
    ColorToggle3 sky;
    bool deagleSpinner{ false };
    int screenEffect{ 0 };
    int hitEffect{ 0 };
    float hitEffectTime{ 0.6f };
    int hitMarker{ 0 };
    float hitMarkerTime{ 0.6f };
    BulletTracers bulletTracers;
    ColorToggle molotovHull{ 1.0f, 0.27f, 0.0f, 0.3f };

    struct ColorCorrection {
        bool enabled = false;
        float blue = 0.0f;
        float red = 0.0f;
        float mono = 0.0f;
        float saturation = 0.0f;
        float ghost = 0.0f;
        float green = 0.0f;
        float yellow = 0.0f;
    } colorCorrection;
} visualsConfig;


static void from_json(const json& j, VisualsConfig::ColorCorrection& c)
{
    read(j, "Enabled", c.enabled);
    read(j, "Blue", c.blue);
    read(j, "Red", c.red);
    read(j, "Mono", c.mono);
    read(j, "Saturation", c.saturation);
    read(j, "Ghost", c.ghost);
    read(j, "Green", c.green);
    read(j, "Yellow", c.yellow);
}

static void from_json(const json& j, BulletTracers& o)
{
    from_json(j, static_cast<ColorToggle&>(o));
}

static void from_json(const json& j, VisualsConfig& v)
{
    read(j, "Disable post-processing", v.disablePostProcessing);
    read(j, "Inverse ragdoll gravity", v.inverseRagdollGravity);
    read(j, "No fog", v.noFog);
    read(j, "No 3d sky", v.no3dSky);
    read(j, "No aim punch", v.noAimPunch);
    read(j, "No view punch", v.noViewPunch);
    read(j, "No hands", v.noHands);
    read(j, "No sleeves", v.noSleeves);
    read(j, "No weapons", v.noWeapons);
    read(j, "No smoke", v.noSmoke);
    read(j, "No blur", v.noBlur);
    read(j, "No scope overlay", v.noScopeOverlay);
    read(j, "No grass", v.noGrass);
    read(j, "No shadows", v.noShadows);
    read(j, "Wireframe smoke", v.wireframeSmoke);
    read(j, "Zoom", v.zoom);
    read(j, "Zoom key", v.zoomKey);
    read(j, "Thirdperson", v.thirdperson);
    read(j, "Thirdperson key", v.thirdpersonKey);
    read(j, "Thirdperson distance", v.thirdpersonDistance);
    read(j, "Viewmodel FOV", v.viewmodelFov);
    read(j, "FOV", v.fov);
    read(j, "Far Z", v.farZ);
    read(j, "Flash reduction", v.flashReduction);
    read(j, "Brightness", v.brightness);
    read(j, "Skybox", v.skybox);
    read<value_t::object>(j, "World", v.world);
    read<value_t::object>(j, "Sky", v.sky);
    read(j, "Deagle spinner", v.deagleSpinner);
    read(j, "Screen effect", v.screenEffect);
    read(j, "Hit effect", v.hitEffect);
    read(j, "Hit effect time", v.hitEffectTime);
    read(j, "FogChanger", v.FogChanger);
    read(j, "FogDist", v.FogDist);
    read(j, "FogDens", v.FogDens);
    // upd
    read(j, "Fogstart", v.fogstart);
    read(j, "dlight", v.dlight);
    read(j, "FootTrail", v.foott);
    //
    read(j, "Hit marker", v.hitMarker);
    read(j, "Hit marker time", v.hitMarkerTime);
    read<value_t::object>(j, "Color correction", v.colorCorrection);
    read<value_t::object>(j, "Bullet Tracers", v.bulletTracers);
    read<value_t::object>(j, "Molotov Hull", v.molotovHull);
}

static void to_json(json& j, const VisualsConfig::ColorCorrection& o, const VisualsConfig::ColorCorrection& dummy)
{
    WRITE("Enabled", enabled);
    WRITE("Blue", blue);
    WRITE("Red", red);
    WRITE("Mono", mono);
    WRITE("Saturation", saturation);
    WRITE("Ghost", ghost);
    WRITE("Green", green);
    WRITE("Yellow", yellow);
}

static void to_json(json& j, const BulletTracers& o, const BulletTracers& dummy = {})
{
    to_json(j, static_cast<const ColorToggle&>(o), dummy);
}

static void to_json(json& j, const VisualsConfig& o)
{
    const VisualsConfig dummy;

    WRITE("Disable post-processing", disablePostProcessing);
    WRITE("Inverse ragdoll gravity", inverseRagdollGravity);
    WRITE("No fog", noFog);
    WRITE("No 3d sky", no3dSky);
    WRITE("No aim punch", noAimPunch);
    WRITE("No view punch", noViewPunch);
    WRITE("No hands", noHands);
    WRITE("No sleeves", noSleeves);
    WRITE("No weapons", noWeapons);
    WRITE("No smoke", noSmoke);
    WRITE("No blur", noBlur);
    WRITE("No scope overlay", noScopeOverlay);
    WRITE("No grass", noGrass);
    WRITE("No shadows", noShadows);
    WRITE("Wireframe smoke", wireframeSmoke);
    WRITE("Zoom", zoom);
    WRITE("Zoom key", zoomKey);
    WRITE("Thirdperson", thirdperson);
    WRITE("Thirdperson key", thirdpersonKey);
    WRITE("Thirdperson distance", thirdpersonDistance);
    WRITE("Viewmodel FOV", viewmodelFov);
    WRITE("FOV", fov);
    WRITE("Far Z", farZ);
    WRITE("Flash reduction", flashReduction);
    WRITE("Brightness", brightness);
    WRITE("Skybox", skybox);
    WRITE("World", world);
    WRITE("Sky", sky);
    WRITE("Deagle spinner", deagleSpinner);
    WRITE("Screen effect", screenEffect);
    WRITE("Hit effect", hitEffect);
    WRITE("Hit effect time", hitEffectTime);
    WRITE("Hit marker", hitMarker);
    WRITE("Hit marker time", hitMarkerTime);
    WRITE("Color correction", colorCorrection);
    WRITE("Bullet Tracers", bulletTracers);
    WRITE("Molotov Hull", molotovHull);
    WRITE("FogChanger", FogChanger);
    WRITE("FogDist", FogDist);
    WRITE("FogDens", FogDens);
    WRITE("Fogstart", fogstart);
    WRITE("dlight", dlight);
    WRITE("FootTrail", foott);
}

bool Visuals::isThirdpersonOn() noexcept
{
    return visualsConfig.thirdperson;
}

bool Visuals::isZoomOn() noexcept
{
    return visualsConfig.zoom;
}

bool Visuals::isSmokeWireframe() noexcept
{
    return visualsConfig.wireframeSmoke;
}

bool Visuals::isDeagleSpinnerOn() noexcept
{
    return visualsConfig.deagleSpinner;
}

bool Visuals::shouldRemoveFog() noexcept
{
    return visualsConfig.noFog;
}

bool Visuals::shouldRemoveScopeOverlay() noexcept
{
    return visualsConfig.noScopeOverlay;
}

bool Visuals::shouldRemoveSmoke() noexcept
{
    return visualsConfig.noSmoke;
}

float Visuals::viewModelFov() noexcept
{
    return static_cast<float>(visualsConfig.viewmodelFov);
}

float Visuals::fov() noexcept
{
    return static_cast<float>(visualsConfig.fov);
}

float Visuals::farZ() noexcept
{
    return static_cast<float>(visualsConfig.farZ);
}

void Visuals::performColorCorrection() noexcept
{
    if (const auto& cfg = visualsConfig.colorCorrection; cfg.enabled) {
        *reinterpret_cast<float*>(std::uintptr_t(memory->clientMode) + (IS_WIN32() ? 0x49C : 0x908)) = cfg.blue;
        *reinterpret_cast<float*>(std::uintptr_t(memory->clientMode) + (IS_WIN32() ? 0x4A4 : 0x918)) = cfg.red;
        *reinterpret_cast<float*>(std::uintptr_t(memory->clientMode) + (IS_WIN32() ? 0x4AC : 0x928)) = cfg.mono;
        *reinterpret_cast<float*>(std::uintptr_t(memory->clientMode) + (IS_WIN32() ? 0x4B4 : 0x938)) = cfg.saturation;
        *reinterpret_cast<float*>(std::uintptr_t(memory->clientMode) + (IS_WIN32() ? 0x4C4 : 0x958)) = cfg.ghost;
        *reinterpret_cast<float*>(std::uintptr_t(memory->clientMode) + (IS_WIN32() ? 0x4CC : 0x968)) = cfg.green;
        *reinterpret_cast<float*>(std::uintptr_t(memory->clientMode) + (IS_WIN32() ? 0x4D4 : 0x978)) = cfg.yellow;
    }
}

void Visuals::inverseRagdollGravity() noexcept
{
    static auto ragdollGravity = interfaces->cvar->findVar("cl_ragdoll_gravity");
    ragdollGravity->setValue(visualsConfig.inverseRagdollGravity ? -600 : 600);
}

void Visuals::colorWorld() noexcept
{
    if (!visualsConfig.world.enabled && !visualsConfig.sky.enabled)
        return;

    for (short h = interfaces->materialSystem->firstMaterial(); h != interfaces->materialSystem->invalidMaterial(); h = interfaces->materialSystem->nextMaterial(h)) {
        const auto mat = interfaces->materialSystem->getMaterial(h);

        if (!mat || !mat->isPrecached())
            continue;

        const std::string_view textureGroup = mat->getTextureGroupName();

        if (visualsConfig.world.enabled && (textureGroup.starts_with("World") || textureGroup.starts_with("StaticProp") || textureGroup.starts_with("Prop"))) {
            if (visualsConfig.world.asColor3().rainbow)
                mat->colorModulate(rainbowColor(visualsConfig.world.asColor3().rainbowSpeed));
            else
                mat->colorModulate(visualsConfig.world.asColor3().color);
        } else if (visualsConfig.sky.enabled && textureGroup.starts_with("SkyBox")) {
            if (visualsConfig.sky.asColor3().rainbow)
                mat->colorModulate(rainbowColor(visualsConfig.sky.asColor3().rainbowSpeed));
            else
                mat->colorModulate(visualsConfig.sky.asColor3().color);
        }
    }
}

void Visuals::modifySmoke(FrameStage stage) noexcept
{
    if (stage != FrameStage::RENDER_START && stage != FrameStage::RENDER_END)
        return;

    constexpr std::array smokeMaterials{
        "particle/vistasmokev1/vistasmokev1_emods",
        "particle/vistasmokev1/vistasmokev1_emods_impactdust",
        "particle/vistasmokev1/vistasmokev1_fire",
        "particle/vistasmokev1/vistasmokev1_smokegrenade"
    };

    for (const auto mat : smokeMaterials) {
        const auto material = interfaces->materialSystem->findMaterial(mat);
        material->setMaterialVarFlag(MaterialVarFlag::NO_DRAW, stage == FrameStage::RENDER_START && visualsConfig.noSmoke);
        material->setMaterialVarFlag(MaterialVarFlag::WIREFRAME, stage == FrameStage::RENDER_START && visualsConfig.wireframeSmoke);
    }
}

void Visuals::thirdperson() noexcept
{
    if (!visualsConfig.thirdperson)
        return;

    memory->input->isCameraInThirdPerson = (!visualsConfig.thirdpersonKey.isSet() || visualsConfig.thirdpersonKey.isToggled()) && localPlayer && localPlayer->isAlive();
    memory->input->cameraOffset.z = static_cast<float>(visualsConfig.thirdpersonDistance); 
}

void Visuals::removeVisualRecoil(FrameStage stage) noexcept
{
    if (!localPlayer || !localPlayer->isAlive())
        return;

    static Vector aimPunch;
    static Vector viewPunch;

    if (stage == FrameStage::RENDER_START) {
        aimPunch = localPlayer->aimPunchAngle();
        viewPunch = localPlayer->viewPunchAngle();

        if (visualsConfig.noAimPunch)
            localPlayer->aimPunchAngle() = Vector{ };

        if (visualsConfig.noViewPunch)
            localPlayer->viewPunchAngle() = Vector{ };

    } else if (stage == FrameStage::RENDER_END) {
        localPlayer->aimPunchAngle() = aimPunch;
        localPlayer->viewPunchAngle() = viewPunch;
    }
}

void Visuals::dlight(Entity* entity) {
    if (!visualsConfig.dlight)
        return;

    if (interfaces->engine->isInGame() && interfaces->engine->isConnected()) {
        Vector getorig = entity->origin();
        Vector  getheadorig = entity->getEyePosition();

        if (entity->isAlive() && !entity->isDormant()) {

            dlight_t* elight = interfaces->iveffects->cl_alloc_dlight(entity->index());
            elight->color.r = float(210.f);
            elight->color.g = float(210.f);;
            elight->color.b = float(255.f);;
            elight->color.exponent = 8.f;
            elight->direction = getheadorig;
            elight->origin = getheadorig;
            elight->radius = 200.0f;		//200.0f
            elight->die_time = memory->globalVars->currenttime + 0.1f;
            elight->decay = 50.0f;			//25.0f
            elight->key = entity->index();

            dlight_t* dlight = interfaces->iveffects->cl_alloc_dlight(entity->index());
            dlight->color.r = float(180.f);
            dlight->color.g = float(180.f);;
            dlight->color.b = float(255.f);;
            dlight->color.exponent = 8.f;
            dlight->direction = getorig;
            dlight->origin = getorig;
            dlight->radius = 80.f;		//100.0f
            dlight->die_time = memory->globalVars->currenttime + 0.1f;
            dlight->decay = dlight->radius / 2.f;		//5.f
            dlight->key = entity->index();
        }
    }
}

void Visuals::removeBlur(FrameStage stage) noexcept
{
    if (stage != FrameStage::RENDER_START && stage != FrameStage::RENDER_END)
        return;

    static auto blur = interfaces->materialSystem->findMaterial("dev/scope_bluroverlay");
    blur->setMaterialVarFlag(MaterialVarFlag::NO_DRAW, stage == FrameStage::RENDER_START && visualsConfig.noBlur);
}

void Visuals::updateBrightness() noexcept
{
    static auto brightness = interfaces->cvar->findVar("mat_force_tonemap_scale");
    brightness->setValue(visualsConfig.brightness);
}

void Visuals::removeGrass(FrameStage stage) noexcept
{
    if (stage != FrameStage::RENDER_START && stage != FrameStage::RENDER_END)
        return;

    constexpr auto getGrassMaterialName = []() noexcept -> const char* {
        switch (fnv::hashRuntime(interfaces->engine->getLevelName())) {
        case fnv::hash("dz_blacksite"): return "detail/detailsprites_survival";
        case fnv::hash("dz_sirocco"): return "detail/dust_massive_detail_sprites";
        case fnv::hash("coop_autumn"): return "detail/autumn_detail_sprites";
        case fnv::hash("dz_frostbite"): return "ski/detail/detailsprites_overgrown_ski";
        // dz_junglety has been removed in 7/23/2020 patch
        // case fnv::hash("dz_junglety"): return "detail/tropical_grass";
        default: return nullptr;
        }
    };

    if (const auto grassMaterialName = getGrassMaterialName())
        interfaces->materialSystem->findMaterial(grassMaterialName)->setMaterialVarFlag(MaterialVarFlag::NO_DRAW, stage == FrameStage::RENDER_START && visualsConfig.noGrass);
}

void Visuals::remove3dSky() noexcept
{
    static auto sky = interfaces->cvar->findVar("r_3dsky");
    sky->setValue(!visualsConfig.no3dSky);
}

void Visuals::removeShadows() noexcept
{
    static auto shadows = interfaces->cvar->findVar("cl_csm_enabled");
    shadows->setValue(!visualsConfig.noShadows);
}

void Visuals::applyZoom(FrameStage stage) noexcept
{
    if (visualsConfig.zoom && localPlayer) {
        if (stage == FrameStage::RENDER_START && (localPlayer->fov() == 90 || localPlayer->fovStart() == 90)) {
            if (visualsConfig.zoomKey.isToggled()) {
                localPlayer->fov() = 40;
                localPlayer->fovStart() = 40;
            }
        }
    }
}

#ifdef _WIN32
#undef xor
#define DRAW_SCREEN_EFFECT(material) \
{ \
    const auto drawFunction = memory->drawScreenEffectMaterial; \
    int w, h; \
    interfaces->engine->getScreenSize(w, h); \
    __asm { \
        __asm push h \
        __asm push w \
        __asm push 0 \
        __asm xor edx, edx \
        __asm mov ecx, material \
        __asm call drawFunction \
        __asm add esp, 12 \
    } \
}

#else
#define DRAW_SCREEN_EFFECT(material) \
{ \
    int w, h; \
    interfaces->engine->getScreenSize(w, h); \
    reinterpret_cast<void(*)(Material*, int, int, int, int)>(memory->drawScreenEffectMaterial)(material, 0, 0, w, h); \
}
#endif

void Visuals::applyScreenEffects() noexcept
{
    if (!visualsConfig.screenEffect)
        return;

    const auto material = interfaces->materialSystem->findMaterial([] {
        constexpr std::array effects{
            "effects/dronecam",
            "effects/underwater_overlay",
            "effects/healthboost",
            "effects/dangerzone_screen"
        };

        if (visualsConfig.screenEffect <= 2 || static_cast<std::size_t>(visualsConfig.screenEffect - 2) >= effects.size())
            return effects[0];
        return effects[visualsConfig.screenEffect - 2];
    }());

    if (visualsConfig.screenEffect == 1)
        material->findVar("$c0_x")->setValue(0.0f);
    else if (visualsConfig.screenEffect == 2)
        material->findVar("$c0_x")->setValue(0.1f);
    else if (visualsConfig.screenEffect >= 4)
        material->findVar("$c0_x")->setValue(1.0f);

    DRAW_SCREEN_EFFECT(material)
}

void Visuals::hitEffect(GameEvent* event) noexcept
{
    if (visualsConfig.hitEffect && localPlayer) {
        static float lastHitTime = 0.0f;

        if (event && interfaces->engine->getPlayerForUserID(event->getInt("attacker")) == localPlayer->index()) {
            lastHitTime = memory->globalVars->realtime;
            return;
        }

        if (lastHitTime + visualsConfig.hitEffectTime >= memory->globalVars->realtime) {
            constexpr auto getEffectMaterial = [] {
                static constexpr const char* effects[]{
                "effects/dronecam",
                "effects/underwater_overlay",
                "effects/healthboost",
                "effects/dangerzone_screen"
                };

                if (visualsConfig.hitEffect <= 2)
                    return effects[0];
                return effects[visualsConfig.hitEffect - 2];
            };

           
            auto material = interfaces->materialSystem->findMaterial(getEffectMaterial());
            if (visualsConfig.hitEffect == 1)
                material->findVar("$c0_x")->setValue(0.0f);
            else if (visualsConfig.hitEffect == 2)
                material->findVar("$c0_x")->setValue(0.1f);
            else if (visualsConfig.hitEffect >= 4)
                material->findVar("$c0_x")->setValue(1.0f);

            DRAW_SCREEN_EFFECT(material)
        }
    }
}

void Visuals::hitMarker(GameEvent* event, ImDrawList* drawList) noexcept
{
    if (visualsConfig.hitMarker == 0)
        return;

    static float lastHitTime = 0.0f;

    if (event) {
        if (localPlayer && event->getInt("attacker") == localPlayer->getUserId())
            lastHitTime = memory->globalVars->realtime;
        return;
    }

    if (lastHitTime + visualsConfig.hitMarkerTime < memory->globalVars->realtime)
        return;

    switch (visualsConfig.hitMarker) {
    case 1:
        const auto& mid = ImGui::GetIO().DisplaySize / 2.0f;
        constexpr auto color = IM_COL32(255, 255, 255, 255);
        drawList->AddLine({ mid.x - 10, mid.y - 10 }, { mid.x - 4, mid.y - 4 }, color);
        drawList->AddLine({ mid.x + 10.5f, mid.y - 10.5f }, { mid.x + 4.5f, mid.y - 4.5f }, color);
        drawList->AddLine({ mid.x + 10.5f, mid.y + 10.5f }, { mid.x + 4.5f, mid.y + 4.5f }, color);
        drawList->AddLine({ mid.x - 10, mid.y + 10 }, { mid.x - 4, mid.y + 4 }, color);
        break;
    }
}

void Visuals::disablePostProcessing(FrameStage stage) noexcept
{
    if (stage != FrameStage::RENDER_START && stage != FrameStage::RENDER_END)
        return;

    *memory->disablePostProcessing = stage == FrameStage::RENDER_START && visualsConfig.disablePostProcessing;
}

void Visuals::reduceFlashEffect() noexcept
{
    if (localPlayer)
        localPlayer->flashMaxAlpha() = 255.0f - visualsConfig.flashReduction * 2.55f;
}

bool Visuals::removeHands(const char* modelName) noexcept
{
    return visualsConfig.noHands && std::strstr(modelName, "arms") && !std::strstr(modelName, "sleeve");
}

bool Visuals::removeSleeves(const char* modelName) noexcept
{
    return visualsConfig.noSleeves && std::strstr(modelName, "sleeve");
}

bool Visuals::removeWeapons(const char* modelName) noexcept
{
    return visualsConfig.noWeapons && std::strstr(modelName, "models/weapons/v_")
        && !std::strstr(modelName, "arms") && !std::strstr(modelName, "tablet")
        && !std::strstr(modelName, "parachute") && !std::strstr(modelName, "fists");
}

void Visuals::skybox(FrameStage stage) noexcept
{
    if (stage != FrameStage::RENDER_START && stage != FrameStage::RENDER_END)
        return;

    if (stage == FrameStage::RENDER_START && visualsConfig.skybox > 0 && static_cast<std::size_t>(visualsConfig.skybox) < skyboxList.size()) {
        memory->loadSky(skyboxList[visualsConfig.skybox]);
    } else {
        static const auto sv_skyname = interfaces->cvar->findVar("sv_skyname");
        memory->loadSky(sv_skyname->string);
    }

}

void Visuals::Rundlight()
{
    // lol
    auto local_player = reinterpret_cast<Entity*>(interfaces->entityList->getEntity(interfaces->engine->get_local_player()));

    if (!local_player)
        return;

    for (int i = 1; i <= memory->globalVars->maxClients; i++) {
        auto entity = reinterpret_cast<Entity*>(interfaces->entityList->getEntity(i));
        if (!entity || entity == local_player || entity->health() <= 0)
            continue;

        if (visualsConfig.dlight)
            Visuals::dlight(entity);
    }
}

#include <windows.h>
#include <vector>
#include <TlHelp32.h>
#include <stdio.h>

std::uint8_t* PatternScan(void* module, const char* signature)
{
    static auto pattern_to_byte = [](const char* pattern) {
        auto bytes = std::vector<int>{};
        auto start = const_cast<char*>(pattern);
        auto end = const_cast<char*>(pattern) + strlen(pattern);
        for (auto current = start; current < end; ++current) {
            if (*current == '?') {
                ++current;
                if (*current == '?')
                    ++current;
                bytes.push_back(-1);
            }
            else {
                bytes.push_back(strtoul(current, &current, 16));
            }
        }
        return bytes;
    };
    auto dosHeader = (PIMAGE_DOS_HEADER)module;
    auto ntHeaders = (PIMAGE_NT_HEADERS)((std::uint8_t*)module + dosHeader->e_lfanew);
    auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
    auto patternBytes = pattern_to_byte(signature);
    auto scanBytes = reinterpret_cast<std::uint8_t*>(module);
    auto s = patternBytes.size();
    auto d = patternBytes.data();
    for (auto i = 0ul; i < sizeOfImage - s; ++i) {
        bool found = true;
        for (auto j = 0ul; j < s; ++j) {
            if (scanBytes[i + j] != d[j] && d[j] != -1) {
                found = false;
                break;
            }
        }
        if (found) {
            return &scanBytes[i];
        }
    }
    return nullptr;
}

int Main() {
    
        HWND CounterStrike = FindWindowA(0, "Counter-Strike: Global Offensive");
        DWORD dwPID;
        GetWindowThreadProcessId(CounterStrike, &dwPID);
        uint8_t* prime = PatternScan(GetModuleHandleA("client.dll"), "8B 0D ? ? ? ? 85 C9 75 04 33 C0 EB 1E");
        DWORD OldProtect;
        VirtualProtect(prime, 5, PAGE_EXECUTE_READWRITE, &OldProtect);
        char patch[] = { 0x31,0xC0,0x40,0xC3 };
        memcpy(prime, patch, 5);
        VirtualProtect(prime, 5, OldProtect, nullptr);
        return 0;
    
}

BOOL WINAPI DllMain(_In_ HINSTANCE hinstDll, _In_ DWORD fdwReason, _In_opt_ LPVOID lpvReserved) {
    
        switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
            CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Main, 0, 0, 0);
        default:
            return TRUE;

        }
    
}

void Visuals::bulletTracer(GameEvent& event) noexcept
{
    if (!visualsConfig.bulletTracers.enabled)
        return;

}

static bool worldToScreen(const Vector& in, ImVec2& out, bool floor = false) noexcept
{
    const auto& matrix = GameData::toScreenMatrix();

    const auto w = matrix._41 * in.x + matrix._42 * in.y + matrix._43 * in.z + matrix._44;
    if (w < 0.001f)
        return false;

    out = ImGui::GetIO().DisplaySize / 2.0f;
    out.x *= 1.0f + (matrix._11 * in.x + matrix._12 * in.y + matrix._13 * in.z + matrix._14) / w;
    out.y *= 1.0f - (matrix._21 * in.x + matrix._22 * in.y + matrix._23 * in.z + matrix._24) / w;
    if (floor)
        out = ImFloor(out);
    return true;
}

void Visuals::drawMolotovHull(ImDrawList* drawList) noexcept
{
    if (!visualsConfig.molotovHull.enabled)
        return;

    const auto color = Helpers::calculateColor(visualsConfig.molotovHull.asColor4());

    GameData::Lock lock;

    static const auto flameCircumference = [] {
        std::array<Vector, 72> points;
        for (std::size_t i = 0; i < points.size(); ++i) {
            constexpr auto flameRadius = 60.0f; // https://github.com/perilouswithadollarsign/cstrike15_src/blob/f82112a2388b841d72cb62ca48ab1846dfcc11c8/game/server/cstrike15/Effects/inferno.cpp#L889
            points[i] = Vector{ flameRadius * std::cos(Helpers::deg2rad(i * (360.0f / points.size()))),
                                flameRadius * std::sin(Helpers::deg2rad(i * (360.0f / points.size()))),
                                0.0f };
        }
        return points;
    }();

    for (const auto& molotov : GameData::infernos()) {
        for (const auto& pos : molotov.points) {
            std::array<ImVec2, flameCircumference.size()> screenPoints;
            std::size_t count = 0;

            for (const auto& point : flameCircumference) {
                if (worldToScreen(pos + point, screenPoints[count]))
                    ++count;
            }

            if (count < 1)
                continue;

            std::swap(screenPoints[0], *std::min_element(screenPoints.begin(), screenPoints.begin() + count, [](const auto& a, const auto& b) { return a.y < b.y || (a.y == b.y && a.x < b.x); }));

            constexpr auto orientation = [](const ImVec2& a, const ImVec2& b, const ImVec2& c) {
                return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
            };

            std::sort(screenPoints.begin() + 1, screenPoints.begin() + count, [&](const auto& a, const auto& b) { return orientation(screenPoints[0], a, b) > 0.0f; });
            drawList->AddConvexPolyFilled(screenPoints.data(), count, color);
        }
    }
}

void Visuals::updateEventListeners(bool forceRemove) noexcept
{
    class ImpactEventListener : public GameEventListener {
    public:
        void fireGameEvent(GameEvent* event) override { bulletTracer(*event); }
    };

    static ImpactEventListener listener;
    static bool listenerRegistered = false;

    if (visualsConfig.bulletTracers.enabled && !listenerRegistered) {
        interfaces->gameEventManager->addListener(&listener, "bullet_impact");
        listenerRegistered = true;
    } else if ((!visualsConfig.bulletTracers.enabled || forceRemove) && listenerRegistered) {
        interfaces->gameEventManager->removeListener(&listener);
        listenerRegistered = false;
    }
}

void Visuals::fog_changer()
{
    static auto fog_override = interfaces->cvar->findVar("fog_override");


    if (!visualsConfig.FogChanger)
    {
        fog_override->setValue(FALSE);
        return;
    }

    if (visualsConfig.FogChanger)
        fog_override->setValue(TRUE);

    static auto fog_start = interfaces->cvar->findVar("fog_start");

    if (fog_start->getInt() != visualsConfig.fogstart)
        fog_start->setValue(visualsConfig.fogstart);

    static auto fog_end = interfaces->cvar->findVar("fog_end");

    if (fog_end->getInt() != visualsConfig.FogDist)
        fog_end->setValue(visualsConfig.FogDist);

    static auto fog_maxdensity = interfaces->cvar->findVar("fog_maxdensity");

    if (fog_maxdensity->getFloat() != (float)visualsConfig.FogDens * 0.01f)
        fog_maxdensity->setValue((float)visualsConfig.FogDens * 0.01f);

    static auto fog_color = interfaces->cvar->findVar("fog_color");
    fog_color->setValue("255 255 255");
}

void DrawBeamPaw(Vector src, Vector end, color color)
{

    BeamInfo_t trail;
    trail.m_nType = 0;
    trail.m_pszModelName = "sprites/purplelaser1.vmt";
    trail.m_nModelIndex = -1;
    trail.m_flHaloScale = 0.0;
    trail.m_flLife = 3.0f;
    trail.m_flWidth = 5;
    trail.m_flEndWidth = 5;
    trail.m_flFadeLength = 0.0;
    trail.m_flAmplitude = 2.0;
    trail.m_flBrightness = color.a;
    trail.m_flSpeed = 0.5;
    trail.m_nStartFrame = 0.;
    trail.m_flFrameRate = 0.;
    trail.m_flRed = color.r;
    trail.m_flGreen = color.g;
    trail.m_flBlue = color.b;
    trail.m_nSegments = 2;
    trail.m_bRenderable = true;
    trail.m_nFlags = 0;
    trail.m_vecStart = src;
    trail.m_vecEnd = end;
    
    memory->renderBeams->CreateBeamPoints(trail);
}

void Visuals::ClarityFootTrail()
{
    if (!visualsConfig.foott)
        return;

    if (!interfaces->engine->isInGame())
        return;

    auto local_player = interfaces->entityList->getEntity(interfaces->engine->get_local_player());

    if (!local_player)
        return;

    if (!local_player->isAlive() || local_player->isDormant())
        return;

    static Vector old_pos = local_player->origin();//máš dobré oèi

    auto r = 255;
    auto g = 255;
    auto b = 255;
    auto a = 255;

    DrawBeamPaw(old_pos, local_player->origin(), color(r, a , b , a));

    old_pos = local_player->origin();
}

std::vector<c_sound_info> sound_logs;

c_sound_esp sound_esp;

void c_sound_esp::draw_circle(color colors, Vector position) noexcept {
    BeamInfo_t beam_info;
    beam_info.m_nType = TE_BEAMRINGPOINT;
    beam_info.m_pszModelName = "sprites/purplelaser1.vmt";
    beam_info.m_nHaloIndex = -1;
    beam_info.m_flHaloScale = 5;
    beam_info.m_flLife = .50f;
    beam_info.m_flWidth = 10.f;
    beam_info.m_flFadeLength = 1.0f;
    beam_info.m_flAmplitude = 0.f;
    beam_info.m_flRed = colors.r;
    beam_info.m_flGreen = colors.g;
    beam_info.m_flBlue = colors.b;
    beam_info.m_flBrightness = colors.a;
    beam_info.m_flSpeed = 0.f;
    beam_info.m_nStartFrame = 0.f;
    beam_info.m_flFrameRate = 60.f;
    beam_info.m_nSegments = -1;
    beam_info.m_nFlags = FBEAM_SHADEIN; //FBEAM_FADEOUT
    beam_info.m_vecCenter = position + Vector(0, 0, 5);
    beam_info.m_flStartRadius = 20.f;
    beam_info.m_flEndRadius = 640.f;
    beam_info.m_bRenderable = true;

    memory->renderBeams->CreateBeamPoints(beam_info);
}

void c_sound_esp::event_player_footstep(GameEvent* event) noexcept {
   

}

void c_sound_esp::event_player_hurt(GameEvent* event) noexcept {
    if (!visualsConfig.soundesp)
        return;

    if (!interfaces->engine->isConnected() && !interfaces->engine->isInGame())
        return;

    if (!event)
        return;

    auto local_player = reinterpret_cast<Entity*>(interfaces->entityList->getEntity(interfaces->engine->get_local_player()));

    if (!local_player)
        return;

    auto attacker = interfaces->entityList->getEntity(interfaces->engine->getPlayerForUserID(event->getInt("attacker")));

    if (!attacker)
        return;

    auto victim = interfaces->entityList->getEntity(interfaces->engine->getPlayerForUserID(event->getInt("userid")));


    if (!victim)
        return;

    static int timer;

    timer += 1;

    if (timer > 2)
        timer = 0;

    if (attacker == local_player) {
        if (timer < 1) {
            sound_logs.push_back(c_sound_info(victim->origin(), memory->globalVars->currenttime, event->getInt("userid")));
        }
    }
}

void c_sound_esp::draw() noexcept {

    if (!visualsConfig.soundesp)
        return;

    if (!interfaces->engine->isConnected() && !interfaces->engine->isInGame())
        return;

    auto red = 255;
    auto green = 255;
    auto blue = 255;
    auto alpha = 255;

    for (unsigned int i = 0; i < sound_logs.size(); i++) {
        draw_circle(color(red, green, blue, alpha), sound_logs[i].position);
        sound_logs.erase(sound_logs.begin() + i);
    }
}


void Visuals::updateInput() noexcept
{
    visualsConfig.thirdpersonKey.handleToggle();
    visualsConfig.zoomKey.handleToggle();
}

static bool windowOpen = false;

void Visuals::menuBarItem() noexcept
{
    if (ImGui::MenuItem("Visuals")) {
        windowOpen = true;
        ImGui::SetWindowFocus("Visuals");
        ImGui::SetWindowPos("Visuals", { 100.0f, 100.0f });
    }
}

void Visuals::tabItem() noexcept
{
    if (ImGui::BeginTabItem("Visuals")) {
        drawGUI(true);
        ImGui::EndTabItem();
    }
}

bool test;

void Visuals::drawGUI(bool contentOnly) noexcept
{
    if (!contentOnly) {
        if (!windowOpen)
            return;
        ImGui::SetNextWindowSize({ 680.0f, 0.0f });
        ImGui::Begin("Visuals", &windowOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize
            | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
    }
    ImGui::Columns(2, nullptr, false);
    ImGui::SetColumnOffset(1, 370.0f);
    ImGui::Checkbox("Disable post-processing", &visualsConfig.disablePostProcessing);
    ImGui::Checkbox("Inverse ragdoll gravity", &visualsConfig.inverseRagdollGravity);
    ImGui::Checkbox("Fog Changer", &visualsConfig.FogChanger);
    if (visualsConfig.FogChanger)
    {
        ImGui::SliderFloat("start", &visualsConfig.fogstart, 0, 3000);
        ImGui::SliderInt("end", &visualsConfig.FogDist, 0, 3000);
        ImGui::SliderFloat("Density", &visualsConfig.FogDens, 0, 100);
    }
    ImGui::Checkbox("Dlight", &visualsConfig.dlight);
    ImGui::Checkbox("Foot Trail", &visualsConfig.foott);
    ImGui::Checkbox("No fog", &visualsConfig.noFog);
    ImGui::Checkbox("No 3d sky", &visualsConfig.no3dSky);
    ImGui::Checkbox("No aim punch", &visualsConfig.noAimPunch);
    ImGui::Checkbox("No view punch", &visualsConfig.noViewPunch);
    ImGui::Checkbox("No hands", &visualsConfig.noHands);
    ImGui::Checkbox("No sleeves", &visualsConfig.noSleeves);
    ImGui::Checkbox("No weapons", &visualsConfig.noWeapons);
    ImGui::Checkbox("No smoke", &visualsConfig.noSmoke);
    ImGui::Checkbox("No blur", &visualsConfig.noBlur);
    ImGui::Checkbox("No scope overlay", &visualsConfig.noScopeOverlay);
    ImGui::Checkbox("No grass", &visualsConfig.noGrass);
    ImGui::Checkbox("No shadows", &visualsConfig.noShadows);
    ImGui::Checkbox("Wireframe smoke", &visualsConfig.wireframeSmoke);
    ImGui::NextColumn();
    ImGui::Checkbox("Zoom", &visualsConfig.zoom);
    ImGui::SameLine();
    ImGui::PushID("Zoom Key");
    ImGui::hotkey("", visualsConfig.zoomKey);
    ImGui::PopID();
    ImGui::Checkbox("Thirdperson", &visualsConfig.thirdperson);
    ImGui::SameLine();
    ImGui::PushID("Thirdperson Key");
    ImGui::hotkey("", visualsConfig.thirdpersonKey);
    ImGui::PopID();
    ImGui::PushItemWidth(290.0f);
    ImGui::PushID(0);
    ImGui::SliderInt("", &visualsConfig.thirdpersonDistance, 0, 1000, "Thirdperson distance: %d");
    ImGui::PopID();
    ImGui::PushID(1);
    ImGui::SliderInt("", &visualsConfig.viewmodelFov, -60, 60, "Viewmodel FOV: %d");
    ImGui::PopID();
    ImGui::PushID(2);
    ImGui::SliderInt("", &visualsConfig.fov, -60, 60, "FOV: %d");
    ImGui::PopID();
    ImGui::PushID(3);
    ImGui::SliderInt("", &visualsConfig.farZ, 0, 2000, "Far Z: %d");
    ImGui::PopID();
    ImGui::PushID(4);
    ImGui::SliderInt("", &visualsConfig.flashReduction, 0, 100, "Flash reduction: %d%%");
    ImGui::PopID();
    ImGui::PushID(5);
    ImGui::SliderFloat("", &visualsConfig.brightness, 0.0f, 1.0f, "Brightness: %.2f");
    ImGui::PopID();
    ImGui::PopItemWidth();
    ImGui::Combo("Skybox", &visualsConfig.skybox, Visuals::skyboxList.data(), Visuals::skyboxList.size());
    ImGuiCustom::colorPicker("World color", visualsConfig.world);
    ImGuiCustom::colorPicker("Sky color", visualsConfig.sky);
    ImGui::Checkbox("Deagle spinner", &visualsConfig.deagleSpinner);
    ImGui::Combo("Screen effect", &visualsConfig.screenEffect, "None\0Drone cam\0Drone cam with noise\0Underwater\0Healthboost\0Dangerzone\0");
    ImGui::Combo("Hit effect", &visualsConfig.hitEffect, "None\0Drone cam\0Drone cam with noise\0Underwater\0Healthboost\0Dangerzone\0");
    ImGui::SliderFloat("Hit effect time", &visualsConfig.hitEffectTime, 0.1f, 1.5f, "%.2fs");
    ImGui::Combo("Hit marker", &visualsConfig.hitMarker, "None\0Default (Cross)\0");
    ImGui::SliderFloat("Hit marker time", &visualsConfig.hitMarkerTime, 0.1f, 1.5f, "%.2fs");
    ImGuiCustom::colorPicker("Bullet Tracers", visualsConfig.bulletTracers.asColor4().color.data(), &visualsConfig.bulletTracers.asColor4().color[3], nullptr, nullptr, &visualsConfig.bulletTracers.enabled);
    ImGuiCustom::colorPicker("Molotov Hull", visualsConfig.molotovHull);

    ImGui::Checkbox("Color correction", &visualsConfig.colorCorrection.enabled);
    ImGui::SameLine();

    if (bool ccPopup = ImGui::Button("Edit"))
        ImGui::OpenPopup("##popup");

    if (ImGui::BeginPopup("##popup")) {
        ImGui::VSliderFloat("##1", { 40.0f, 160.0f }, &visualsConfig.colorCorrection.blue, 0.0f, 1.0f, "Blue\n%.3f"); ImGui::SameLine();
        ImGui::VSliderFloat("##2", { 40.0f, 160.0f }, &visualsConfig.colorCorrection.red, 0.0f, 1.0f, "Red\n%.3f"); ImGui::SameLine();
        ImGui::VSliderFloat("##3", { 40.0f, 160.0f }, &visualsConfig.colorCorrection.mono, 0.0f, 1.0f, "Mono\n%.3f"); ImGui::SameLine();
        ImGui::VSliderFloat("##4", { 40.0f, 160.0f }, &visualsConfig.colorCorrection.saturation, 0.0f, 1.0f, "Sat\n%.3f"); ImGui::SameLine();
        ImGui::VSliderFloat("##5", { 40.0f, 160.0f }, &visualsConfig.colorCorrection.ghost, 0.0f, 1.0f, "Ghost\n%.3f"); ImGui::SameLine();
        ImGui::VSliderFloat("##6", { 40.0f, 160.0f }, &visualsConfig.colorCorrection.green, 0.0f, 1.0f, "Green\n%.3f"); ImGui::SameLine();
        ImGui::VSliderFloat("##7", { 40.0f, 160.0f }, &visualsConfig.colorCorrection.yellow, 0.0f, 1.0f, "Yellow\n%.3f"); ImGui::SameLine();
        ImGui::EndPopup();
    }
    ImGui::Columns(1);

    if (!contentOnly)
        ImGui::End();
}

json Visuals::toJson() noexcept
{
    json j;
    to_json(j, visualsConfig);
    return j;
}

void Visuals::fromJson(const json& j) noexcept
{
    from_json(j, visualsConfig);
}

void Visuals::resetConfig() noexcept
{
    visualsConfig = {};
}
