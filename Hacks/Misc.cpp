#include "Misc.h"

inline int oldflags = 0;
int flagsb;
bool bugou;

struct PreserveKillfeed {
    bool enabled = false;
    bool onlyHeadshots = false;
};

struct OffscreenEnemies : ColorToggle {
    OffscreenEnemies() : ColorToggle{ 1.0f, 0.26f, 0.21f, 1.0f } {}
    HealthBar healthBar;
};

struct PurchaseList {
    bool enabled = false;
    bool onlyDuringFreezeTime = false;
    bool showPrices = false;
    bool noTitleBar = false;

    enum Mode {
        Details = 0,
        Summary
    };
    int mode = Details;
};

struct MiscConfig {
    MiscConfig() { clanTag[0] = '\0'; }

    KeyBind menuKey{ KeyBind::INSERT };
    //
    bool rainbowvel{ false };
    bool ebtest{ false };
    bool jumpbug{ false };
    bool edgebug{ false };
    bool edgebug3{ false };
    bool longjump{ false };
    bool minijump{ false };
    int longjumpkey{ false };
    bool edgebug2{ false };
    int edgestyle{ 0 };
    bool velocityGraph{ false };
    bool staminaGraph{ false };
    bool autoduck{ false };
    bool lj{ false };
    bool rageamm{ false };
    bool bb{ false };
    bool damageIndicator{ false };
    bool ladderlj{ false };
    bool spotify{ false };
    bool jumpstats{ false };
    bool Velocity{ false };
    bool strafeopt{ false };
    float Strafespeed{ 0.0f };
    bool Stamina{ false };
    bool edgebugsound{ false };
    bool customebsound{ false };
    bool edgebugeffect{ false };
    bool lockedge{ false };
    int forceRelayCluster = 0;
    bool Fadecolor{ false };
    bool nulls{ false };
    bool VFadecolor{ false };
    bool detectedge{ false };
    bool ImGuiSpec{ false };
    bool footstep{ false };
    int VelocityHeight = 0;
    int savedticks = 3;
    int savedticks2 = 1;
    int edgebugtime{ false };
    int duckticks{ false };
    int staminaheight{ false };
    bool camera{ false };
    bool disableduck{ false };
    bool FakeB{ false };
    bool FakeBI{ false };
    float recoverspeed = 0.f;
    float turnspeed = 0.f;
    bool manual{ false };   
    bool always{ false };
    bool keystrokes{ false };
    float duration = 0.f;
    bool surfacewatermark{ false };
    float VelocityGHeight = { 0.f };
    float StaminaGHeight = { 0.f };
    int waterstyle{ 0 };
    Trails trail;
    KeyBind jumpbugkey;
    KeyBind edgebugkey;
    KeyBind edgebugkey2;
    KeyBind edgebugkey3;
    KeyBind ebtestkey;
    KeyBind ljkey;
    KeyBind FBKEY;
    KeyBind bbkey;
    KeyBind mjkey;
    KeyBind askey;
    // movement recorder things

    bool MovementRecorder{ false };

    KeyBind Recorder;
    KeyBind Playing;

    bool Recorder2 = false;
    bool Player2 = false;

    int showcircle;

    int smooth = 10;

    bool showpath;
    bool show3dcircle;
    bool showfirstpath;
    bool indicators;
   
    //
    bool antiAfkKick{ false };
    bool autoStrafe{ false };
    bool bunnyHop{ false };
    bool customClanTag{ false };
    bool clocktag{ false };
    bool animatedClanTag{ false };
    bool fastDuck{ false };
    bool moonwalk{ false };
    bool edgejump{ false };
    bool slowwalk{ false };
    bool autoPistol{ false };
    bool autoReload{ false };
    bool autoAccept{ false };
    bool radarHack{ false };
    bool revealRanks{ false };
    bool ragemode{ false };
    bool revealMoney{ false };
    bool revealSuspect{ false };
    float wasdheight = 0.f;
    int specstyle = 0;
    bool revealVotes{ false };
    bool fixAnimationLOD{ false };
    bool fixBoneMatrix{ false };
    bool Indicators{ false };
    bool fixMovement{ false };
    bool disableModelOcclusion{ false };
    bool nameStealer{ false };
    bool damage{ false };
    bool disablePanoramablur{ false };
    bool killMessage{ false };
    bool nadePredict{ false };
    bool fixTabletSignal{ false };
    bool fastPlant{ false };
    bool fastStop{ false };
    bool quickReload{ false };
    bool prepareRevolver{ false };
    bool oppositeHandKnife = false;
    PreserveKillfeed preserveKillfeed;
    char clanTag[16];
    KeyBind edgejumpkey;
    KeyBind slowwalkKey;
    ColorToggleThickness noscopeCrosshair;
    ColorToggleThickness recoilCrosshair;
    bool spectatorlist{ false };
    struct Watermark {
        bool enabled = false;
    };
    Watermark watermark;
    float aspectratio{ 0 };
    std::string killMessageString{ "Gotcha!" };
    int banColor{ 6 };
    std::string banText{ "Cheater has been permanently banned from official CS:GO servers." };
    ColorToggle3 bombTimer{ 1.0f, 0.55f, 0.0f };
    KeyBind prepareRevolverKey;
    int hitSound{ 0 };
    int chokedPackets{ 0 };
    KeyBind chokedPacketsKey;
    int quickHealthshotKey{ 0 };
    float maxAngleDelta{ 255.0f };
    int killSound{ 0 };
    std::string customKillSound;
    std::string customHitSound;
    PurchaseList purchaseList;

    struct Reportbot {
        bool enabled = false;
        bool textAbuse = false;
        bool griefing = false;
        bool wallhack = true;
        bool aimbot = true;
        bool other = true;
        int target = 0;
        int delay = 1;
        int rounds = 1;
    } reportbot;

    OffscreenEnemies offscreenEnemies;
} miscConfig;


void VectorSubtract(const Vector& a, const Vector& b, Vector& c)
{
    CHECK_VALID(a);
    CHECK_VALID(b);
    c.x = a.x - b.x;
    c.y = a.y - b.y;
    c.z = a.z - b.z;
}

float VectorDistances(const Vector& v1, const Vector& v2)
{
    return FASTSQRT(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2) + pow(v1.z - v2.z, 2));
}

void normalize_angles(Vector& angles)
{
    while (angles.x > 89.0f)
        angles.x -= 180.0f;

    while (angles.x < -89.0f)
        angles.x += 180.0f;

    while (angles.y < -180.0f)
        angles.y += 360.0f;

    while (angles.y > 180.0f)
        angles.y -= 360.0f;

    angles.z = 0.0f;
}

void clamp_angles(Vector& angles)
{
    if (angles.x > 89.0f)
        angles.x = 89.0f;
    else if (angles.x < -89.0f)
        angles.x = -89.0f;

    if (angles.y > 180.0f)
        angles.y = 180.0f;
    else if (angles.y < -180.0f)
        angles.y = -180.0f;

    angles.z = 0;
}

void angle_vectors(const Vector& angles, Vector& forward)
{
    float sp, sy, cp, cy;

    sy = sin(DEG2RAD(angles[1]));
    cy = cos(DEG2RAD(angles[1]));

    sp = sin(DEG2RAD(angles[0]));
    cp = cos(DEG2RAD(angles[0]));

    forward.x = cp * cy;
    forward.y = cp * sy;
    forward.z = -sp;
}

void angle_vectors(const Vector& angles, Vector* forward, Vector* right, Vector* up)
{
    auto sin_cos = [](float radian, float* sin, float* cos)
    {
        *sin = std::sin(radian);
        *cos = std::cos(radian);
    };

    float sp, sy, sr, cp, cy, cr;

    sin_cos(M_PI / 180.0f * angles.x, &sp, &cp);
    sin_cos(M_PI / 180.0f * angles.y, &sy, &cy);
    sin_cos(M_PI / 180.0f * angles.z, &sr, &cr);

    if (forward)
    {
        forward->x = cp * cy;
        forward->y = cp * sy;
        forward->z = -sp;
    }

    if (right)
    {
        right->x = -1.0f * sr * sp * cy + -1.0f * cr * -sy;
        right->y = -1.0f * sr * sp * sy + -1.0f * cr * cy;
        right->z = -1.0f * sr * cp;
    }

    if (up)
    {
        up->x = cr * sp * cy + -sr * -sy;
        up->y = cr * sp * sy + -sr * cy;
        up->z = cr * cp;
    }
}

static bool WorldToScreen(const Vector& in, Vector& out)
{
    const auto& matrix = interfaces->engine->worldToScreenMatrix();
    float w = matrix._41 * in.x + matrix._42 * in.y + matrix._43 * in.z + matrix._44;

    if (w > 0.001f) {
        const auto [width, height] = interfaces->surface->getScreenSize();
        out.x = width / 2 * (1 + (matrix._11 * in.x + matrix._12 * in.y + matrix._13 * in.z + matrix._14) / w);
        out.y = height / 2 * (1 - (matrix._21 * in.x + matrix._22 * in.y + matrix._23 * in.z + matrix._24) / w);
        out.z = 0.0f;
        return true;
    }
    return false;
}

float VectorLength(const Vector& v)
{
    CHECK_VALID(v);
    return FASTSQRT(v.x * v.x + v.y * v.y + v.z * v.z);
}

void preto::record(UserCmd* cmd)
{
    if (!miscConfig.MovementRecorder)
        return;

    
}

void preto::play(UserCmd* cmd)
{
    if (!miscConfig.MovementRecorder)
        return;
}

#include "../preto.h"
#include "../Config2.h"

Config3 konfig{ "files" };

Config3::Config3(const char* name) noexcept
{
    if (PWSTR pathToDocuments; SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Documents, 0, nullptr, &pathToDocuments))) {
        path2 = pathToDocuments;
        path2 /= name;
        CoTaskMemFree(pathToDocuments);
    }

    if (!std::filesystem::is_directory(path2))
    {
        std::filesystem::remove(path2);
        std::filesystem::create_directory(path2);
    }
}

void Config3::load(size_t id) noexcept
{
    if (!std::filesystem::is_directory(path2))
        std::filesystem::create_directory(path2);

    std::ifstream in{ path2 / configs2[id] };

    if (!in.good())
        return;

    ArchiveX<std::ifstream>{ in } >> blm.CmdFinal;
    
    in.close();
}

void Config3::save(size_t id) const noexcept
{
    if (!std::filesystem::is_directory(path2))
        std::filesystem::create_directory(path2);

    std::ofstream out{ path2 / configs2[id] };

    if (!out.good())
        return;

    ArchiveX<std::ofstream>{ out } << blm.CmdFinal;

    out.close();
}

void Config3::add(const char* name) noexcept
{
    if (*name && std::find(std::cbegin(configs2), std::cend(configs2), name) == std::cend(configs2))
        configs2.emplace_back(name);
}

void Config3::remove(size_t id) noexcept
{
    std::filesystem::remove(path2 / configs2[id]);
    configs2.erase(configs2.cbegin() + id);
}

void Config3::rename(size_t item, const char* newName) noexcept
{
    std::filesystem::rename(path2 / configs2[item], path2 / newName);
    configs2[item] = newName;
}

void Config3::reset() noexcept
{
    blm.CmdFinal = {};
}

void Config3::listConfigs() noexcept
{
    configs2.clear();

    std::error_code ec;
    std::transform(std::filesystem::directory_iterator{ path2, ec },
        std::filesystem::directory_iterator{ },
        std::back_inserter(configs2),
        [](const auto& entry) { return std::string{ (const char*)entry.path().filename().u8string().c_str() }; });
}

#include <Psapi.h>

template <typename T>
static constexpr auto relativeToAbsolute(uintptr_t address) noexcept
{
    return (T)(address + 4 + *reinterpret_cast<std::int32_t*>(address));
}

static std::pair<void*, std::size_t> getModuleInformation(const char* name) noexcept
{
#ifdef _WIN32
    if (HMODULE handle = GetModuleHandleA(name)) {
        if (MODULEINFO moduleInfo; GetModuleInformation(GetCurrentProcess(), handle, &moduleInfo, sizeof(moduleInfo)))
            return std::make_pair(moduleInfo.lpBaseOfDll, moduleInfo.SizeOfImage);
    }
    return {};
#elif __linux__
    struct ModuleInfo {
        const char* name;
        void* base = nullptr;
        std::size_t size = 0;
    } moduleInfo;

    moduleInfo.name = name;

    dl_iterate_phdr([](struct dl_phdr_info* info, std::size_t, void* data) {
        const auto moduleInfo = reinterpret_cast<ModuleInfo*>(data);
        if (!std::string_view{ info->dlpi_name }.ends_with(moduleInfo->name))
            return 0;

        if (const auto fd = open(info->dlpi_name, O_RDONLY); fd >= 0) {
            if (struct stat st; fstat(fd, &st) == 0) {
                if (const auto map = mmap(nullptr, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0); map != MAP_FAILED) {
                    const auto ehdr = (ElfW(Ehdr)*)map;
                    const auto shdrs = (ElfW(Shdr)*)(std::uintptr_t(ehdr) + ehdr->e_shoff);
                    const auto strTab = (const char*)(std::uintptr_t(ehdr) + shdrs[ehdr->e_shstrndx].sh_offset);

                    for (auto i = 0; i < ehdr->e_shnum; ++i) {
                        const auto shdr = (ElfW(Shdr)*)(std::uintptr_t(shdrs) + i * ehdr->e_shentsize);

                        if (std::strcmp(strTab + shdr->sh_name, ".text") != 0)
                            continue;

                        moduleInfo->base = (void*)(info->dlpi_addr + shdr->sh_offset);
                        moduleInfo->size = shdr->sh_size;
                        munmap(map, st.st_size);
                        close(fd);
                        return 1;
                    }
                    munmap(map, st.st_size);
                }
            }
            close(fd);
        }

        moduleInfo->base = (void*)(info->dlpi_addr + info->dlpi_phdr[0].p_vaddr);
        moduleInfo->size = info->dlpi_phdr[0].p_memsz;
        return 1;
}, &moduleInfo);

    return std::make_pair(moduleInfo.base, moduleInfo.size);
#endif
}

[[nodiscard]] static auto generateBadCharTable(std::string_view pattern) noexcept
{
    assert(!pattern.empty());

    std::array<std::size_t, (std::numeric_limits<std::uint8_t>::max)() + 1> table;

    auto lastWildcard = pattern.rfind('?');
    if (lastWildcard == std::string_view::npos)
        lastWildcard = 0;

    const auto defaultShift = (std::max)(std::size_t(1), pattern.length() - 1 - lastWildcard);
    table.fill(defaultShift);

    for (auto i = lastWildcard; i < pattern.length() - 1; ++i)
        table[static_cast<std::uint8_t>(pattern[i])] = pattern.length() - 1 - i;

    return table;
}

static std::uintptr_t findPattern(const char* moduleName, std::string_view pattern, bool reportNotFound = true) noexcept
{
    static auto id = 0;
    ++id;

    const auto [moduleBase, moduleSize] = getModuleInformation(moduleName);

    if (moduleBase && moduleSize) {
        const auto lastIdx = pattern.length() - 1;
        const auto badCharTable = generateBadCharTable(pattern);

        auto start = static_cast<const char*>(moduleBase);
        const auto end = start + moduleSize - pattern.length();

        while (start <= end) {
            int i = lastIdx;
            while (i >= 0 && (pattern[i] == '?' || start[i] == pattern[i]))
                --i;

            if (i < 0)
                return reinterpret_cast<std::uintptr_t>(start);

            start += badCharTable[static_cast<std::uint8_t>(start[lastIdx])];
        }
    }

    assert(false);
#ifdef _WIN32
    if (reportNotFound)
        MessageBoxA(nullptr, ("Failed to find pattern #" + std::to_string(id) + '!').c_str(), "Osiris", MB_OK | MB_ICONWARNING);
#endif
    return 0;
}

void Misc::RegionChanger()
{
    static std::string data_centers[]
    {
        "", "syd", "vie", "gru", "scl", "dxb", "par", "fra", "hkg",
        "maa", "bom", "tyo", "lux", "ams", "limc", "man", "waw", "sgp",
        "jnb", "mad", "sto", "lhr", "atl", "eat", "ord", "lax", "mwh",
        "okc", "sea", "iad"
    };
    static auto relay_cluster = *reinterpret_cast<std::string**>(findPattern(("steamnetworkingsockets"), "\xB8????\xB9????\x0F\x43") + 1);

    if (miscConfig.forceRelayCluster != 0 && miscConfig.forceRelayCluster < 30)
        *relay_cluster = data_centers[miscConfig.forceRelayCluster];

    if (interfaces->engine->isConnected())
    {
        miscConfig.forceRelayCluster = 0;
    }
}

#include "../steam-sdk/steam_api.h"

void Misc::setup_steam()
{
    /*some steam interfaces*/
    typedef uint32_t SteamPipeHandle;
    typedef uint32_t SteamUserHandle;
    SteamUserHandle hSteamUser = ((SteamUserHandle(__cdecl*)(void))GetProcAddress(GetModuleHandleA("steam_api.dll"), "SteamAPI_GetHSteamUser"))();
    SteamPipeHandle hSteamPipe = ((SteamPipeHandle(__cdecl*)(void))GetProcAddress(GetModuleHandleA("steam_api.dll"), "SteamAPI_GetHSteamPipe"))();
    SteamClient = ((ISteamClient * (__cdecl*)(void))GetProcAddress(GetModuleHandleA("steam_api.dll"), "SteamClient"))();
    SteamGameCoordinator = (ISteamGameCoordinator*)SteamClient->GetISteamGenericInterface(hSteamUser, hSteamPipe, "SteamGameCoordinator001");
    SteamUser = (ISteamUser*)SteamClient->GetISteamUser(hSteamUser, hSteamPipe, "SteamUser019");
    SteamUserStats = SteamClient->GetISteamUserStats(hSteamUser, hSteamPipe, "STEAMUSERSTATS_INTERFACE_VERSION011");

    SteamFriends = SteamClient->GetISteamFriends(hSteamUser, hSteamPipe, "SteamFriends015");
    static auto SteamInventory = SteamClient->GetISteamInventory(hSteamUser, hSteamPipe, "STEAMINVENTORY_INTERFACE_V002");
    auto _ = SteamFriends->GetLargeFriendAvatar(SteamUser->GetSteamID());
    SteamUtils = SteamClient->GetISteamUtils(hSteamPipe, "SteamUtils009");
}

bool Misc::shouldRevealMoney() noexcept
{
    return miscConfig.revealMoney;
}

bool Misc::shouldRevealSuspect() noexcept
{
    return miscConfig.revealSuspect;
}

bool Misc::shouldDisableModelOcclusion() noexcept
{
    return miscConfig.disableModelOcclusion;
}

bool Misc::shouldFixBoneMatrix() noexcept
{
    return miscConfig.fixBoneMatrix;
}

bool Misc::isRadarHackOn() noexcept
{
    return miscConfig.radarHack;
}

bool Misc::isMenuKeyPressed() noexcept
{
    return miscConfig.menuKey.isPressed();
}

float Misc::maxAngleDelta() noexcept
{
    return miscConfig.maxAngleDelta;
}

float Misc::aspectRatio() noexcept
{
    return miscConfig.aspectratio;
}

void Misc::Camera()
{
    static auto up = interfaces->cvar->findVar("cl_pitchup");
    up->setValue(miscConfig.camera && localPlayer && !localPlayer->isScoped() ? 999 : 89);
    static auto down = interfaces->cvar->findVar("cl_pitchdown");
    down->setValue(miscConfig.camera && localPlayer && !localPlayer->isScoped() ? 999 : 89);
}

void Misc::PostPred(UserCmd* cmd)
{
    if (!localPlayer)
        return;

    int iFlags = localPlayer->flags();
}
  
void Misc::EdgeBug(UserCmd* cmd, int iFlags)
{
  // antigo edgebug
  // removi pq ficava detectando edge em uns lugar aleatorio
}

void Misc::Duckedge(UserCmd* cmd)
{
    if (!miscConfig.edgebug || !miscConfig.edgebugkey.isDown())
        return;

}

void Misc::StrafeOpt(UserCmd* cmd)
{
    if (!miscConfig.strafeopt || !localPlayer || localPlayer->flags() & 1)
        return;

    constexpr float cfg_max_gain = 100.f;
    constexpr float cfg_pull_amnt = 100.f;

    static float old_yaw = cmd->viewangles.y;
    static auto  sensitivity = interfaces->cvar->findVar("sensitivity");

    auto  velocity = localPlayer->velocity();
    float speed = velocity.length2D();

    float ideal_speed = (speed > 0.f) ? rad_to_deg(std::asin(cfg_max_gain * 0.01f) * 30.f) / speed : 0.f;
    float yaw_delta = std::remainderf(cmd->viewangles.y - old_yaw, 360.f); // 360.f ?
    float abs_yaw_delta = std::fabsf(yaw_delta);
    float ideal_yaw = std::copysignf(ideal_speed, yaw_delta);

    if (cmd->buttons & UserCmd::IN_JUMP && abs_yaw_delta > std::fabsf(ideal_speed * 0.1f) && speed > 45.f)
    {
        float error_margin = ideal_yaw - yaw_delta;
        float target_yaw = old_yaw + yaw_delta + error_margin * cfg_pull_amnt * 0.01f;

        yaw_delta = target_yaw - old_yaw;

        auto moused_x = std::floorf(std::floorf((yaw_delta / sensitivity->getFloat()) / 0.022f));
        auto humanized_angle = moused_x * sensitivity->getFloat() * 0.022f;

        cmd->viewangles.y = humanized_angle + old_yaw;
    }

    interfaces->engine->setViewAngles(cmd->viewangles);

    old_yaw = cmd->viewangles.y;
}

void Misc::StaminaIndicator()
{
    if (!interfaces->engine->isConnected() || !interfaces->engine->isInGame() || !localPlayer->isAlive())
        return;

    if (!miscConfig.Stamina)
        return;

    int x, y;
    interfaces->engine->getScreenSize(x, y);

    // refazer dps
    
}
 

PlayerInfo GetInfo(int Index) {
    PlayerInfo Info;
    interfaces->engine->getPlayerInfo(Index, Info);
    return Info;
}

const char* hitgroup_nameq(int hitgroupa) {
    switch (hitgroupa) {
    case HitGroupz::Head:
        return "head";
    case HitGroupz::LeftLeg:
        return "left leg";
    case HitGroupz::RightLeg:
        return "right leg";
    case HitGroupz::Stomach:
        return "stomach";
    case HitGroupz::LeftArm:
        return "left arm";
    case HitGroupz::RightArm:
        return "right arm";
    default:
        return "body";
    }
}

void Misc::DamageIndicator(GameEvent* event)
{
    if (miscConfig.damageIndicator)
    {
        if (!interfaces->engine->isInGame())
            return;

        if (!interfaces->engine->isConnected())
            return;

        auto localplayer = interfaces->entityList->getEntity(interfaces->engine->get_local_player());

        if (!localplayer)
            return;

        if (!localplayer->isAlive())
            return;


        if (!strcmp(event->getName(), ("player_hurt")))
        {
            std::string event_name = event->getName();
            int attackerid = event->getInt("attacker");
            int entityid = interfaces->engine->getPlayerForUserID(attackerid);

            if (entityid == interfaces->engine->get_local_player())
            {
                int nUserID = event->getInt(("attacker"));
                int nDead = event->getInt(("userid"));
                auto nHitgroup = event->getInt(("hitgroup"));
  

                if (nUserID || nDead)
                {
                    PlayerInfo killed_info = GetInfo(interfaces->engine->getPlayerForUserID(nDead));
                    PlayerInfo killer_info = GetInfo(interfaces->engine->getPlayerForUserID(nUserID));
                    PlayerInfo hitbox =      GetInfo(interfaces->engine->getPlayerForUserID(nHitgroup));
                    auto hitgroup = hitgroup_nameq(nHitgroup);

                    std::string one = (" \x0B elterhook \x01|");
                    std::string two = (" hit ");
                    std::string three = killed_info.name;
                    std::string foura = (" for ");
                    std::string fivea = event->getString(("dmg_health")); 
                    std::string inthe = (" in the ");

                  

                    memory->clientMode->getHudChat()->printf(0, (one + two + three + foura + fivea + inthe + hitgroup).c_str());
                }
            }
        }
    }
}

void Misc::watermark2() noexcept {
    if (!miscConfig.surfacewatermark)
        return;

    int width, height;
    interfaces->engine->getScreenSize(width, height);
    
    static unsigned int last_time;
    last_time = memory->globalVars->tickCount;
    color rainbow;
    rainbow.FromHSV(fmod(last_time * 0.0002f, 1.f), 1.f, 0.5f);

    static auto frameRate = 1.0f;
    frameRate = 0.9f * frameRate + 0.1f * memory->globalVars->absoluteFrameTime;
    const auto [screenWidth, screenHeight] = interfaces->surface->getScreenSize();
    std::wstring fps{ std::to_wstring(frameRate)};

    render::text(width - 65, 8, render::fonts::watermark_font, "elterhook", false, color::white(255));

}

void Misc::EdgebugDetect(UserCmd* cmd, float unpredicted_velocity) noexcept
{
    if (!localPlayer || !localPlayer->isAlive() || localPlayer->moveType() == MoveType::LADDER || localPlayer->moveType() == MoveType::NOCLIP)
        return;

    float cooldown = 0.f;

    auto predicted_velocity = std::floor(localPlayer->velocity().z);
    bool did_edgebug;
    bool did_edgebugducking;

    int counter = 0;


    if (unpredicted_velocity >= -7 || predicted_velocity != -7 || localPlayer->flags() & 1) {
        did_edgebug = false;
    }
    else {

        if (!miscConfig.edgebug || !miscConfig.edgebugkey.isDown() || memory->globalVars->realtime > cooldown) {
            if (miscConfig.detectedge)
                memory->clientMode->getHudChat()->printf(0, std::string("").append(" \x0B").append("elterhook").append(" \x01").append("| edgebug").c_str());
            cooldown = memory->globalVars->realtime + 0.5;
            did_edgebug = true;
            if (miscConfig.edgebugsound)
                interfaces->engine->clientCmdUnrestricted("play ui/beep07.wav");     
            if (miscConfig.edgebugeffect)
                localPlayer->m_flHealthShotBoostExpirationTime() = memory->globalVars->currenttime + 0.5f;
        }
    }
}

void Misc::Keystrokes()
{
    if (!interfaces->engine->isConnected() || !interfaces->engine->isInGame() || !localPlayer->isAlive())
        return;

    if (!miscConfig.keystrokes)
        return;

    int x, y;
    interfaces->engine->getScreenSize(x, y);

    color c2 = color(220, 220, 220, 255);

    //W

    if (GetAsyncKeyState(0X57)) {
        render::text(x / 2, y - 300 - miscConfig.wasdheight, render::fonts::Keystrokes, "W", true, c2);
    }

        render::text(x / 2, y - 300 - miscConfig.wasdheight, render::fonts::Keystrokes, "_", true, c2);
    

    //A

    if (GetAsyncKeyState(0X41)) {
        render::text(x / 2.1, y - 280 - miscConfig.wasdheight, render::fonts::Keystrokes, "A", true, c2);
    }

        render::text(x / 2.1, y - 280 - miscConfig.wasdheight, render::fonts::Keystrokes, "_", true, c2);
    

    //D

    if (GetAsyncKeyState(0x44)) {
        render::text(x / 1.9, y - 280 - miscConfig.wasdheight, render::fonts::Keystrokes, "D", true, c2);
    }

        render::text(x / 1.9, y - 280 - miscConfig.wasdheight, render::fonts::Keystrokes, "_", true, c2);
    

    //S

    if (GetAsyncKeyState(0x53)) {
        render::text(x / 2, y - 280 - miscConfig.wasdheight, render::fonts::Keystrokes, "S", true, c2);
    }

        render::text(x / 2, y - 280 - miscConfig.wasdheight, render::fonts::Keystrokes, "_", true, c2);
  

    //J

    if (GetAsyncKeyState(VK_SPACE)) {
        render::text(x / 1.9, y - 300 - miscConfig.wasdheight, render::fonts::Keystrokes, "J", true, c2);
    }

    render::text(x / 1.9, y - 300 - miscConfig.wasdheight, render::fonts::Keystrokes, "_", true, c2);

    //C

    if (GetAsyncKeyState(VK_CONTROL)) {
        render::text(x / 2.1, y - 300 - miscConfig.wasdheight, render::fonts::Keystrokes, "C", true, c2);
    }

        render::text(x / 2.1, y - 300 - miscConfig.wasdheight, render::fonts::Keystrokes, "_", true, c2);
 
}


#include "../SDK/ViewRenderBeams.h"

void Misc::Jumpstats()
{
    if (!miscConfig.jumpstats)
        return;

    static auto sv_airaccelerate = interfaces->cvar->findVar("sv_airaccelerate");
    static bool was_onground = localPlayer->flags() & 1;
    static Vector last_origin{ };
    static float ground_vel{ };
    static float last_jump_max_speed{ };
    static float last_height{ };
    static float last_dist{ };

    const float lj_threshold = sv_airaccelerate->getFloat() < 15.f ? 190.f : 240.f;

    bool on_ground = localPlayer->flags() & 1;
    bool ducking = localPlayer->flags() & 1;

    char jump_string[250] = { };

    if (on_ground) {
        int vertical = 0;

        if (!was_onground) {
            Vector cur_origin = localPlayer->origin();
            last_dist = cur_origin.distTo(last_origin);

            if (std::abs(cur_origin.z - last_origin.z) >= (ducking ? 10.f : 5.f)) {
                vertical = cur_origin.z > last_origin.z ? 1 : -1;
            }

            if (ground_vel > 210.f && last_jump_max_speed > 285.f && std::abs(last_height) > 30.f) {
                if (vertical) {
                    sprintf_s(jump_string, 250, "pre: %0.2f | max vel: %0.2f | height: %0.2f | duck: %d | \2%s\n",
                        ground_vel, last_jump_max_speed, last_height, ducking, vertical == 1 ? "vertical" : "dropjump");
                }
                else {
                    bool is_lj = last_dist > lj_threshold;
                   sprintf_s(jump_string, 250, "pre: %0.2f | max vel: %0.2f | height: %0.2f | duck: %d | dist: %c%0.2f\n",
                        ground_vel, last_jump_max_speed, last_height, ducking, is_lj ? 4 : 1, last_dist);
                }

                memory->clientMode->getHudChat()->printf(0, jump_string);
            }
        }
        last_origin = localPlayer->origin();
        last_jump_max_speed = 0.f;
        last_height = 0.f;
        ground_vel = localPlayer->velocity().length2D();

        was_onground = true;
    }
    else {
        was_onground = false;
        float vel = localPlayer->velocity().length2D();
        if (vel > last_jump_max_speed) {
            last_jump_max_speed = vel;
        }
        float delta = localPlayer->origin().z - last_origin.z;
        if (std::abs(delta) > std::abs(last_height)) {
            last_height = delta;
        }
    }
}

void Misc::BlockBot(UserCmd* cmd)
{
    if (!miscConfig.bb || !miscConfig.bbkey.isDown())
        return;

    float bestdist = 250.f;
    int index = -1;
    for (int i = 1; i <= interfaces->engine->getMaxClients(); i++) {
        auto entity = interfaces->entityList->getEntity(i);

        if (!entity)
            continue;

        if (!entity->isAlive() || entity->isDormant() || entity == localPlayer.get())
            continue;

        float dist;

        double distance;
        distance = sqrt(((int)localPlayer->origin().x - (int)entity->origin().x) * ((int)localPlayer->origin().x - (int)entity->origin().x) +
            ((int)localPlayer->origin().y - (int)entity->origin().y) * ((int)localPlayer->origin().y - (int)entity->origin().y) +
            ((int)localPlayer->origin().z - (int)entity->origin().z) * ((int)localPlayer->origin().z - (int)entity->origin().z));
        dist = (float)abs(round(distance));

        if (dist < bestdist)
        {
            bestdist = dist;
            index = i;
        }
    }

    if (index == -1)
        return;

    auto target = interfaces->entityList->getEntity(index);

    if (!target)
        return;

    Vector delta = target->origin() - localPlayer->origin();
    Vector2 angles{ radiansToDegrees(atan2f(-delta.z, std::hypotf(delta.x, delta.y))), radiansToDegrees(atan2f(delta.y, delta.x)) };
    angles.normalize2();

    angles.y -= localPlayer->eyeAngles().y;
    angles.normalize2();
    angles.y = std::clamp(angles.y, -180.f, 180.f);

    if (angles.y < -1.0f)
        cmd->sidemove = 450.f;
    else if (angles.y > 1.0f)
        cmd->sidemove = -450.f;

}

void Misc::edgejump(UserCmd* cmd, int iFlags, int otherflag) noexcept
{
    if (!miscConfig.edgejump || !miscConfig.edgejumpkey.isDown())
        return;

    if (!localPlayer || !localPlayer->isAlive())
        return;

    if (const auto mt = localPlayer->moveType(); mt == MoveType::LADDER || mt == MoveType::NOCLIP)
        return;

    if (!(localPlayer->flags() & 1) && (iFlags & 1)) {
        cmd->buttons |= UserCmd::IN_JUMP;
    }
}

static int saved_tick_count;
static int mjtick;
bool get_tick_count;
bool do_lj;
bool do_mj;

void Misc::longjump(UserCmd* cmd, int iFlags)
{

}

void Misc::ladderlj(UserCmd* cmd, int iFlags)
{
    if (!miscConfig.ladderlj || !miscConfig.edgejumpkey.isDown())
        return;

    if (!(localPlayer->flags() & 1) || (iFlags & 1) || localPlayer->moveType() == MoveType::LADDER || localPlayer->moveType() != MoveType::LADDER)
        cmd->buttons |= UserCmd::IN_JUMP;  
}

         
void Misc::VelocityIndicator()
{
    static color velo_ctr = color(0, 0, 0, 255);

    int velocity;

    static int lastvelocity, saved_tick, saved_tick2, savedvelo;

    static bool lol;

    int lasttick = 0;

    static int last_vel_updated = 0;

    if (!interfaces->engine->isConnected() || !interfaces->engine->isInGame() || !localPlayer->isAlive() || !localPlayer)
    {
        saved_tick = 0;
        saved_tick2 = 0;
        lastvelocity = 0;
        velocity = 0;
        savedvelo = 0;
        lasttick = 0;
        last_vel_updated = 0;
        return;
    }

    if (!miscConfig.Velocity)
        return;

    static unsigned int last_time;
    last_time = memory->globalVars->tickCount;
    color rainbow;
    rainbow.FromHSV(fmod(last_time * 0.0002f, 1.f), 1.f, 0.5f);

    velocity = round(localPlayer->velocity().length2D());

    auto cspeed = localPlayer->velocity().length2D();
    int x, y;
    interfaces->engine->getScreenSize(x, y);

    if (localPlayer->flags() & 1) {

        if (lol)
            lol = false;

    }
    else
    {
        saved_tick2 = memory->globalVars->tickCount;
        if (!lol) {
            lol = true;
            savedvelo = velocity;
        }
    }
  
        render::text(x / 1.9935, y - 49 - (miscConfig.VelocityHeight), render::fonts::Velocity2, saved_tick2 + 20 > memory->globalVars->tickCount ? std::to_string(velocity) + " (" + std::to_string(savedvelo) + ")" : std::to_string(velocity), true, color(0, 0, 0, 240));
        render::text(x / 2, y - 50 - (miscConfig.VelocityHeight), render::fonts::Velocity, saved_tick2 + 20 > memory->globalVars->tickCount ? std::to_string(velocity) + " (" + std::to_string(savedvelo) + ")" : std::to_string(velocity), true, velo_ctr);

    if (saved_tick + 2 < memory->globalVars->tickCount)
    {
        lastvelocity == velocity ? velo_ctr = color(255, 199, 89) : lastvelocity < velocity ? velo_ctr = color(30, 255, 109) : velo_ctr = color(255, 119, 119);
        lastvelocity = velocity;
        saved_tick = memory->globalVars->tickCount;
    }
}

void Misc::Spotify()
{
    if (!miscConfig.spotify)
        return;

   
}

void Misc::TeamDamage(GameEvent* event) noexcept {
    if (!event || !interfaces->engine->isInGame())
        return;

    if (!miscConfig.damage)
        return;

}

void Misc::DrawDamage()
{
    if (!miscConfig.damage)
        return;

    if (!interfaces->engine->isConnected() || !interfaces->engine->isInGame() || !localPlayer->isAlive())
        return;

    color c2 = color(240, 240, 240, 240);

    int x, y;
    interfaces->surface->getScreenSize(x, y);
}

static bool worldToScreen(const Vector& in, Vector& out)
{
    const auto& matrix = interfaces->engine->worldToScreenMatrix();
    float w = matrix._41 * in.x + matrix._42 * in.y + matrix._43 * in.z + matrix._44;

    if (w > 0.001f) {
        const auto [width, height] = interfaces->surface->getScreenSize();
        out.x = width / 2 * (1 + (matrix._11 * in.x + matrix._12 * in.y + matrix._13 * in.z + matrix._14) / w);
        out.y = height / 2 * (1 - (matrix._21 * in.x + matrix._22 * in.y + matrix._23 * in.z + matrix._24) / w);
        out.z = 0.0f;
        return true;
    }
    return false;
}


void Misc::autoStrafe(UserCmd* cmd) noexcept
{
}

static bool in_edgebug = false;

void Misc::smartedgebug(UserCmd* pCmd, float unpredicted_velocity, int iFlags)
{
    // Edgebug do yougame.biz 

    if (!miscConfig.edgebug || !miscConfig.edgebugkey.isDown())
        return;
 
    static bool edgebugging = false;
    static int edgebugging_tick = 0;

    if (!edgebugging) {

        for (int i = 0; i < 64; i++) {
            // Run prediction

            unpredicted_velocity = std::floor(localPlayer->velocity().z);
            iFlags = localPlayer->flags();

            EnginePrediction::run(pCmd);
            {

                // Check for edgebug
                if (unpredicted_velocity < -7 && floor(localPlayer->velocity().z) == -7 && !(iFlags & 1) && localPlayer->moveType() != MoveType::NOCLIP) {
                    edgebugging = true;
                    edgebugging_tick = pCmd->tickCount + i;
                    break;
                }
                else
                {
                    unpredicted_velocity = std::floor(localPlayer->velocity().z);
                    iFlags = localPlayer->flags();
                }

            }

            // End prediciton
            EnginePrediction::end();
        }
    }
    else {
        // Lock the movement however you want
        pCmd->sidemove = 0.f;
        pCmd->forwardmove = 0.f;
        pCmd->upmove = 0.f;
        pCmd->mousedx = 0.f;
        in_edgebug = false;

        // Check if edgebug over
        if (pCmd->tickCount > edgebugging_tick) {
            edgebugging = false;
            edgebugging_tick = 0;
        }
    }
}

void Misc::VelocityGraph()  // podre
{
    if (!interfaces->engine->isInGame() || !localPlayer)
        return;  

    if (!miscConfig.velocityGraph)
        return;

    static std::vector<float> velData(110, 0);

    Vector vecVelocity = localPlayer->velocity();
    float currentVelocity = sqrt(vecVelocity.x * vecVelocity.x + vecVelocity.y * vecVelocity.y);

    velData.erase(velData.begin());
    velData.push_back(currentVelocity);

    int vel = localPlayer->velocity().length2D();

    int width, height;
    interfaces->engine->getScreenSize(width, height);

    for (auto i = 0; i < velData.size() - 1; i++)
    {
        int cur = velData.at(i);
        int next = velData.at(i + 1);


        float max_val = (int)velData.size() - 1;
        float val = (int)i;

        int alpha = fabs(max_val - fabs(val - max_val / 2) * 2.f);

        render::draw_line(
            width / 2 + (velData.size() * 3 / 2) - (i - 1) * 3.f,
            height / 1 - miscConfig.VelocityGHeight - (std::clamp(cur, 0, 450) * .2f),
            width / 2 + (velData.size() * 3 / 2) - i * 3.f,
            height / 1 - miscConfig.VelocityGHeight -(std::clamp(next, 0, 450) * .2f), color(255, 255, 255, alpha)
        );
    }
}

void Misc::StaminaGraph()
{
    if (!interfaces->engine->isInGame() || !localPlayer)
        return;

    if (!miscConfig.staminaGraph)
        return;

    static std::vector<float> velData(110, 0);

    Vector vecVelocity = localPlayer->stamina();
    float currentVelocity = sqrt(vecVelocity.x * vecVelocity.x + vecVelocity.y * vecVelocity.y);

    velData.erase(velData.begin());
    velData.push_back(currentVelocity);

    int vel = localPlayer->stamina().length2D();

    int width, height;
    interfaces->engine->getScreenSize(width, height);

    for (auto i = 0; i < velData.size() - 1; i++)
    {
        int cur = velData.at(i);
        int next = velData.at(i + 1);


        float max_val = (int)velData.size() - 1;
        float val = (int)i;

        int alpha = fabs(max_val - fabs(val - max_val / 2) * 2.f);

        render::draw_line(
            width / 2 + (velData.size() * 3 / 2) - (i - 1) * 3.f,
            height / 1 - miscConfig.StaminaGHeight - (std::clamp(cur, 0, 450) * .2f),
            width / 2 + (velData.size() * 3 / 2) - i * 3.f,
            height / 1 - miscConfig.StaminaGHeight - (std::clamp(next, 0, 450) * .2f), color(163, 5, 255, alpha)
        );
    }
}

#include "../Config2.h"

#include "../Config2.h"

Vector MCalculateRelativeAngle(const Vector& source, const Vector& destination, const Vector& viewAngles) noexcept
{
    Vector delta = destination - source;
    Vector angles{ radiansToDegrees(atan2f(-delta.z, std::hypotf(delta.x, delta.y))) - viewAngles.x,
                   radiansToDegrees(atan2f(delta.y, delta.x)) - viewAngles.y };
    angles.normalize();
    return angles;
}

static bool WTS(const Vector& in, ImVec2& out) noexcept
{
    const auto& matrix = GameData::toScreenMatrix();

    const auto w = matrix._41 * in.x + matrix._42 * in.y + matrix._43 * in.z + matrix._44;
    if (w < 0.001f)
        return false;

    out = ImGui::GetIO().DisplaySize / 2.0f;
    out.x *= 1.0f + (matrix._11 * in.x + matrix._12 * in.y + matrix._13 * in.z + matrix._14) / w;
    out.y *= 1.0f - (matrix._21 * in.x + matrix._22 * in.y + matrix._23 * in.z + matrix._24) / w;
    return true;
}

//Movement Recorder
//Movement Recorder
//Movement Recorder

void Misc::NullStrafe(UserCmd* cmd)
{
    if (!miscConfig.nulls || !localPlayer ||
        localPlayer->flags() & 1)
        return;

    if (cmd->mousedx > 0 && cmd->buttons & UserCmd::IN_MOVERIGHT && cmd->buttons & UserCmd::IN_MOVELEFT)
        cmd->sidemove = -450.f;
    else if (cmd->mousedx < 0 && cmd->buttons & UserCmd::IN_MOVELEFT && cmd->buttons & UserCmd::IN_MOVERIGHT)
        cmd->sidemove = 450.f;
}

void Misc::indicator()
{
    if (!interfaces->engine->isConnected() || !interfaces->engine->isInGame() || !localPlayer->isAlive())
        return;

    if (!miscConfig.Indicators)
        return;

        float fade = 255;

        int x, y;

    interfaces->surface->getScreenSize(x, y);

    if (miscConfig.edgejump && miscConfig.edgejumpkey.isDown()) {

        render::text(x / 2, y - 255, render::fonts::Velocity2, "ej", true, color(255, 255, 255, fade));
    }
    if (miscConfig.jumpbug && miscConfig.jumpbugkey.isDown()) {

        render::text(x / 2, y - 225, render::fonts::Velocity2, "jb", true, color(255, 255, 255, fade));
    }
    if (miscConfig.edgebug && miscConfig.edgebugkey.isDown()) {

        render::text(x / 2, y - 195, render::fonts::Velocity2, "eb", true, color(255,255,255,fade));
    }
    if (miscConfig.edgebug2 && miscConfig.edgebugkey2.isDown()) {

        render::text(x / 2, y - 195, render::fonts::Velocity2, "eb", true, color(255, 255, 255, fade));
    }
}

void Misc::Oldedgebug(UserCmd* cmd)
{
    if (!miscConfig.edgebug || !miscConfig.edgebugkey.isDown())
        return;

    if (in_edgebug)
        return;

    if (localPlayer->flags() & 1)
    {
        if (!(EnginePrediction::getFlags() & 1))
            cmd->buttons |= UserCmd::IN_DUCK;
    }

}


void Misc::jumpbug(UserCmd* cmd) noexcept
{
    bool assist = false;

    bugou = false;

    if (!miscConfig.jumpbug || !miscConfig.jumpbugkey.isDown())
        return;

    if (!localPlayer || !localPlayer->isAlive())
        return;

    if (assist)
    {
        if (localPlayer->flags() & 1)
            cmd->buttons |= UserCmd::IN_DUCK;

    }

    bugou = true;
    if (localPlayer->flags() & 1)
    {
        cmd->buttons &= ~UserCmd::IN_JUMP;
        if (!(EnginePrediction::getFlags() & 1))
            cmd->buttons |= UserCmd::IN_DUCK;
        assist = true;

    }
}

bool sim = true;

void Misc::slowwalk(UserCmd* cmd) noexcept
{
    if (!miscConfig.slowwalk || !miscConfig.slowwalkKey.isDown())
        return;

    if (!localPlayer || !localPlayer->isAlive())
        return;

    const auto activeWeapon = localPlayer->getActiveWeapon();
    if (!activeWeapon)
        return;

    const auto weaponData = activeWeapon->getWeaponData();
    if (!weaponData)
        return;

    const float maxSpeed = (localPlayer->isScoped() ? weaponData->maxSpeedAlt : weaponData->maxSpeed) / 3;

    if (cmd->forwardmove && cmd->sidemove) {
        const float maxSpeedRoot = maxSpeed * static_cast<float>(M_SQRT1_2);
        cmd->forwardmove = cmd->forwardmove < 0.0f ? -maxSpeedRoot : maxSpeedRoot;
        cmd->sidemove = cmd->sidemove < 0.0f ? -maxSpeedRoot : maxSpeedRoot;
    }
    else if (cmd->forwardmove) {
        cmd->forwardmove = cmd->forwardmove < 0.0f ? -maxSpeed : maxSpeed;
    }
    else if (cmd->sidemove) {
        cmd->sidemove = cmd->sidemove < 0.0f ? -maxSpeed : maxSpeed;
    }
}

void Misc::updateClanTag(bool tagChanged) noexcept
{
    static std::string clanTag;

    if (tagChanged) {
        clanTag = miscConfig.clanTag;
        if (!clanTag.empty() && clanTag.front() != ' ' && clanTag.back() != ' ')
            clanTag.push_back(' ');
        return;
    }

    static auto lastTime = 0.0f;

    if (miscConfig.clocktag) {
        if (memory->globalVars->realtime - lastTime < 1.0f)
            return;

        const auto time = std::time(nullptr);
        const auto localTime = std::localtime(&time);
        char s[11];
        s[0] = '\0';
        snprintf(s, sizeof(s), "[%02d:%02d:%02d]", localTime->tm_hour, localTime->tm_min, localTime->tm_sec);
        lastTime = memory->globalVars->realtime;
        memory->setClanTag(s, s);
    }
    else if (miscConfig.customClanTag) {
        if (memory->globalVars->realtime - lastTime < 0.6f)
            return;

        if (miscConfig.animatedClanTag && !clanTag.empty()) {
            const auto offset = Helpers::utf8SeqLen(clanTag[0]);
            if (offset != -1 && static_cast<std::size_t>(offset) <= clanTag.length())
                std::rotate(clanTag.begin(), clanTag.begin() + offset, clanTag.end());
        }
        lastTime = memory->globalVars->realtime;
        memory->setClanTag(clanTag.c_str(), clanTag.c_str());
    }
}

void Misc::spectatorList() noexcept
{
    if (!miscConfig.spectatorlist || !miscConfig.specstyle == 0)
        return;

    if (!localPlayer || !localPlayer->isAlive())
        return;

    interfaces->surface->setTextFont(render::fonts::watermark_font);

    interfaces->surface->setTextColor(255, 255, 255);

    const auto [width, height] = interfaces->surface->getScreenSize();

    auto textPositionY = static_cast<int>(0.5f * height);

    for (int i = 1; i <= interfaces->engine->getMaxClients(); ++i) {
        const auto entity = interfaces->entityList->getEntity(i);
        if (!entity || entity->isDormant() || entity->isAlive() || entity->getObserverTarget() != localPlayer.get())
            continue;

        PlayerInfo playerInfo;

        if (!interfaces->engine->getPlayerInfo(i, playerInfo))
            continue;

        if (wchar_t name[128]; MultiByteToWideChar(CP_UTF8, 0, playerInfo.name, -1, name, 128)) {
            const auto [textWidth, textHeight] = interfaces->surface->getTextSize(render::fonts::watermark_font, name);
            interfaces->surface->setTextPosition(width - textWidth - 5, textPositionY);
            textPositionY -= textHeight;
            interfaces->surface->printText(name);
        }
    }
}


static void drawCrosshair(ImDrawList* drawList, const ImVec2& pos, ImU32 color) noexcept
{
    // dot
    drawList->AddRectFilled(pos - ImVec2{ 1, 1 }, pos + ImVec2{ 2, 2 }, color & IM_COL32_A_MASK);

    // left
    drawList->AddRectFilled(ImVec2{ pos.x - 11, pos.y - 1 }, ImVec2{ pos.x - 3, pos.y + 2 }, color & IM_COL32_A_MASK);

    // right
    drawList->AddRectFilled(ImVec2{ pos.x + 4, pos.y - 1 }, ImVec2{ pos.x + 12, pos.y + 2 }, color & IM_COL32_A_MASK);

    // top (left with swapped x/y offsets)
    drawList->AddRectFilled(ImVec2{ pos.x - 1, pos.y - 11 }, ImVec2{ pos.x + 2, pos.y - 3 }, color & IM_COL32_A_MASK);

    // bottom (right with swapped x/y offsets)
    drawList->AddRectFilled(ImVec2{ pos.x - 1, pos.y + 4 }, ImVec2{ pos.x + 2, pos.y + 12 }, color & IM_COL32_A_MASK);

}

void Misc::noscopeCrosshair(ImDrawList* drawList) noexcept
{
    if (!miscConfig.noscopeCrosshair.asColorToggle().enabled)
        return;

    {
        GameData::Lock lock;
        if (const auto& local = GameData::local(); !local.exists || !local.alive || !local.noScope)
            return;
    }

    drawCrosshair(drawList, ImGui::GetIO().DisplaySize / 2, Helpers::calculateColor(miscConfig.noscopeCrosshair.asColorToggle().asColor4()));
}


static bool worldToScreen2(const Vector& in, ImVec2& out) noexcept
{
    const auto& matrix = GameData::toScreenMatrix();

    const auto w = matrix._41 * in.x + matrix._42 * in.y + matrix._43 * in.z + matrix._44;
    if (w < 0.001f)
        return false;

    out = ImGui::GetIO().DisplaySize / 2.0f;
    out.x *= 1.0f + (matrix._11 * in.x + matrix._12 * in.y + matrix._13 * in.z + matrix._14) / w;
    out.y *= 1.0f - (matrix._21 * in.x + matrix._22 * in.y + matrix._23 * in.z + matrix._24) / w;
    out = ImFloor(out);
    return true;
}


void Misc::recoilCrosshair(ImDrawList* drawList) noexcept
{
    if (!miscConfig.recoilCrosshair.asColorToggle().enabled)
        return;

    GameData::Lock lock;
    const auto& localPlayerData = GameData::local();

    if (!localPlayerData.exists || !localPlayerData.alive)
        return;

    if (!localPlayerData.shooting)
        return;

    if (ImVec2 pos; worldToScreen2(localPlayerData.aimPunch, pos))
        drawCrosshair(drawList, pos, Helpers::calculateColor(miscConfig.recoilCrosshair.asColorToggle().asColor4()));
}

void Misc::watermark() noexcept
{
    if (!miscConfig.watermark.enabled)
        return;

    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize;
    if (!gui->isOpen())
        windowFlags |= ImGuiWindowFlags_NoInputs;

    ImGui::SetNextWindowBgAlpha(0.3f);
    ImGui::Begin("Watermark", nullptr, windowFlags);

    static auto frameRate = 1.0f;
    frameRate = 0.9f * frameRate + 0.1f * memory->globalVars->absoluteFrameTime;

    ImGui::Text("Osiris | %d fps | %d ms", frameRate != 0.0f ? static_cast<int>(1 / frameRate) : 0, GameData::getNetOutgoingLatency());
    ImGui::End();
}

void Misc::prepareRevolver(UserCmd* cmd) noexcept
{
    constexpr auto timeToTicks = [](float time) {  return static_cast<int>(0.5f + time / memory->globalVars->intervalPerTick); };
    constexpr float revolverPrepareTime{ 0.234375f };

    static float readyTime;
    if (miscConfig.prepareRevolver && localPlayer && (!miscConfig.prepareRevolverKey.isSet() || miscConfig.prepareRevolverKey.isDown())) {
        const auto activeWeapon = localPlayer->getActiveWeapon();
        if (activeWeapon && activeWeapon->itemDefinitionIndex() == WeaponId::Revolver) {
            if (!readyTime) readyTime = memory->globalVars->serverTime() + revolverPrepareTime;
            auto ticksToReady = timeToTicks(readyTime - memory->globalVars->serverTime() - interfaces->engine->getNetworkChannel()->getLatency(0));
            if (ticksToReady > 0 && ticksToReady <= timeToTicks(revolverPrepareTime))
                cmd->buttons |= UserCmd::IN_ATTACK;
            else
                readyTime = 0.0f;
        }
    }
}

void Misc::fastPlant(UserCmd* cmd) noexcept
{
    if (!miscConfig.fastPlant)
        return;

    if (static auto plantAnywhere = interfaces->cvar->findVar("mp_plant_c4_anywhere"); plantAnywhere->getInt())
        return;

    if (!localPlayer || !localPlayer->isAlive() || (localPlayer->inBombZone() && localPlayer->flags() & 1))
        return;

    if (const auto activeWeapon = localPlayer->getActiveWeapon(); !activeWeapon || activeWeapon->getClientClass()->classId != ClassId::C4)
        return;

    cmd->buttons &= ~UserCmd::IN_ATTACK;

    constexpr auto doorRange = 200.0f;

    Trace trace;
    const auto startPos = localPlayer->getEyePosition();
    const auto endPos = startPos + Vector::fromAngle(cmd->viewangles) * doorRange;
    interfaces->engineTrace->traceRay({ startPos, endPos }, 0x46004009, localPlayer.get(), trace);

    if (!trace.entity || trace.entity->getClientClass()->classId != ClassId::PropDoorRotating)
        cmd->buttons &= ~UserCmd::IN_USE;
}

void Misc::fastStop(UserCmd* cmd) noexcept
{
    if (!miscConfig.fastStop)
        return;

    if (!localPlayer || !localPlayer->isAlive())
        return;

    if (localPlayer->moveType() == MoveType::NOCLIP || localPlayer->moveType() == MoveType::LADDER || !(localPlayer->flags() & 1) || cmd->buttons & UserCmd::IN_JUMP)
        return;

    if (cmd->buttons & (UserCmd::IN_MOVELEFT | UserCmd::IN_MOVERIGHT | UserCmd::IN_FORWARD | UserCmd::IN_BACK))
        return;

    const auto velocity = localPlayer->velocity();
    const auto speed = velocity.length2D();
    if (speed < 15.0f)
        return;

    Vector direction = velocity.toAngle();
    direction.y = cmd->viewangles.y - direction.y;

    const auto negatedDirection = Vector::fromAngle(direction) * -speed;
    cmd->forwardmove = negatedDirection.x;
    cmd->sidemove = negatedDirection.y;
}

void Misc::drawBombTimer() noexcept
{
    if (!miscConfig.bombTimer.enabled)
        return;

    GameData::Lock lock;

    const auto& plantedC4 = GameData::plantedC4();
    if (plantedC4.blowTime == 0.0f && !gui->isOpen())
        return;

    if (!gui->isOpen()) {
        ImGui::SetNextWindowBgAlpha(0.3f);
    }

    static float windowWidth = 200.0f;
    ImGui::SetNextWindowPos({ (ImGui::GetIO().DisplaySize.x - 200.0f) / 2.0f, 60.0f }, ImGuiCond_Once);
    ImGui::SetNextWindowSize({ windowWidth, 0 }, ImGuiCond_Once);

    if (!gui->isOpen())
        ImGui::SetNextWindowSize({ windowWidth, 0 });

    ImGui::SetNextWindowSizeConstraints({ 0, -1 }, { FLT_MAX, -1 });
    ImGui::Begin("Bomb Timer", nullptr, ImGuiWindowFlags_NoTitleBar | (gui->isOpen() ? 0 : ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoDecoration));

    std::ostringstream ss; ss << "Bomb on " << (!plantedC4.bombsite ? 'A' : 'B') << " : " << std::fixed << std::showpoint << std::setprecision(3) << (std::max)(plantedC4.blowTime - memory->globalVars->currenttime, 0.0f) << " s";

    ImGui::textUnformattedCentered(ss.str().c_str());

    ImGui::PushStyleColor(ImGuiCol_PlotHistogram, Helpers::calculateColor(miscConfig.bombTimer.asColor3()));
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4{ 0.2f, 0.2f, 0.2f, 1.0f });
    ImGui::progressBarFullWidth((plantedC4.blowTime - memory->globalVars->currenttime) / plantedC4.timerLength, 5.0f);

    if (plantedC4.defuserHandle != -1) {
        const bool canDefuse = plantedC4.blowTime >= plantedC4.defuseCountDown;

        if (plantedC4.defuserHandle == GameData::local().handle) {
            if (canDefuse) {
                ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 0, 255));
                ImGui::textUnformattedCentered("You can defuse!");
            }
            else {
                ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 0, 0, 255));
                ImGui::textUnformattedCentered("You can not defuse!");
            }
            ImGui::PopStyleColor();
        }
        else if (const auto defusingPlayer = GameData::playerByHandle(plantedC4.defuserHandle)) {
            std::ostringstream ss; ss << defusingPlayer->name << " is defusing: " << std::fixed << std::showpoint << std::setprecision(3) << (std::max)(plantedC4.defuseCountDown - memory->globalVars->currenttime, 0.0f) << " s";

            ImGui::textUnformattedCentered(ss.str().c_str());

            ImGui::PushStyleColor(ImGuiCol_PlotHistogram, canDefuse ? IM_COL32(0, 255, 0, 255) : IM_COL32(255, 0, 0, 255));
            ImGui::progressBarFullWidth((plantedC4.defuseCountDown - memory->globalVars->currenttime) / plantedC4.defuseLength, 5.0f);
            ImGui::PopStyleColor();
        }
    }

    windowWidth = ImGui::GetCurrentWindow()->SizeFull.x;

    ImGui::PopStyleColor(2);
    ImGui::End();
}

void Misc::stealNames() noexcept
{
    if (!miscConfig.nameStealer)
        return;

    if (!localPlayer)
        return;

    static std::vector<int> stolenIds;

    for (int i = 1; i <= memory->globalVars->maxClients; ++i) {
        const auto entity = interfaces->entityList->getEntity(i);

        if (!entity || entity == localPlayer.get())
            continue;

        PlayerInfo playerInfo;
        if (!interfaces->engine->getPlayerInfo(entity->index(), playerInfo))
            continue;

        if (playerInfo.fakeplayer || std::ranges::find(stolenIds, playerInfo.userId) != stolenIds.cend())
            continue;

        if (changeName(false, (std::string{ playerInfo.name } + '\x1').c_str(), 1.0f))
            stolenIds.push_back(playerInfo.userId);

        return;
    }
    stolenIds.clear();
}

void Misc::disablePanoramablur() noexcept
{
    static auto blur = interfaces->cvar->findVar("@panorama_disable_blur");
    blur->setValue(miscConfig.disablePanoramablur);
}

void Misc::quickReload(UserCmd* cmd) noexcept
{
    if (miscConfig.quickReload) {
        static Entity* reloadedWeapon{ nullptr };

        if (reloadedWeapon) {
            for (auto weaponHandle : localPlayer->weapons()) {
                if (weaponHandle == -1)
                    break;

                if (interfaces->entityList->getEntityFromHandle(weaponHandle) == reloadedWeapon) {
                    cmd->weaponselect = reloadedWeapon->index();
                    cmd->weaponsubtype = reloadedWeapon->getWeaponSubType();
                    break;
                }
            }
            reloadedWeapon = nullptr;
        }

        if (auto activeWeapon{ localPlayer->getActiveWeapon() }; activeWeapon && activeWeapon->isInReload() && activeWeapon->clip() == activeWeapon->getWeaponData()->maxClip) {
            reloadedWeapon = activeWeapon;

            for (auto weaponHandle : localPlayer->weapons()) {
                if (weaponHandle == -1)
                    break;

                if (auto weapon{ interfaces->entityList->getEntityFromHandle(weaponHandle) }; weapon && weapon != reloadedWeapon) {
                    cmd->weaponselect = weapon->index();
                    cmd->weaponsubtype = weapon->getWeaponSubType();
                    break;
                }
            }
        }
    }
}

bool Misc::changeName(bool reconnect, const char* newName, float delay) noexcept
{
    static auto exploitInitialized{ false };

    static auto name{ interfaces->cvar->findVar("name") };

    if (reconnect) {
        exploitInitialized = false;
        return false;
    }

    if (!exploitInitialized && interfaces->engine->isInGame()) {
        if (PlayerInfo playerInfo; localPlayer && interfaces->engine->getPlayerInfo(localPlayer->index(), playerInfo) && (!strcmp(playerInfo.name, "?empty") || !strcmp(playerInfo.name, "\n\xAD\xAD\xAD"))) {
            exploitInitialized = true;
        }
        else {
            name->onChangeCallbacks.size = 0;
            name->setValue("\n\xAD\xAD\xAD");
            return false;
        }
    }

    if (static auto nextChangeTime = 0.0f; nextChangeTime <= memory->globalVars->realtime) {
        name->setValue(newName);
        nextChangeTime = memory->globalVars->realtime + delay;
        return true;
    }
    return false;
}

void Misc::bunnyHop(UserCmd* cmd) noexcept
{
    if (!localPlayer)
        return;

    if (bugou)
        return;

    static auto wasLastTimeOnGround{ localPlayer->flags() & 1 };

    if (miscConfig.bunnyHop && !(localPlayer->flags() & 1) && localPlayer->moveType() != MoveType::LADDER && !wasLastTimeOnGround)
        cmd->buttons &= ~UserCmd::IN_JUMP;

    wasLastTimeOnGround = localPlayer->flags() & 1;
}

void Misc::fakeBan(bool set) noexcept
{
    static bool shouldSet = false;

    if (set)
        shouldSet = set;

    if (shouldSet && interfaces->engine->isInGame() && changeName(false, std::string{ "\x1\xB" }.append(std::string{ static_cast<char>(miscConfig.banColor + 1) }).append(miscConfig.banText).append("\x1").c_str(), 5.0f))
        shouldSet = false;
}

void Misc::nadePredict() noexcept
{
    static auto nadeVar{ interfaces->cvar->findVar("cl_grenadepreview") };

    nadeVar->onChangeCallbacks.size = 0;
    nadeVar->setValue(miscConfig.nadePredict);
}

void Misc::fixTabletSignal() noexcept
{
    if (miscConfig.fixTabletSignal && localPlayer) {
        if (auto activeWeapon{ localPlayer->getActiveWeapon() }; activeWeapon && activeWeapon->getClientClass()->classId == ClassId::Tablet)
            activeWeapon->tabletReceptionIsBlocked() = false;
    }
}

void Misc::killMessage(GameEvent& event) noexcept
{
    if (!miscConfig.killMessage)
        return;

    if (!localPlayer || !localPlayer->isAlive())
        return;

    if (const auto localUserId = localPlayer->getUserId(); event.getInt("attacker") != localUserId || event.getInt("userid") == localUserId)
        return;

    std::string cmd = "say \"";
    cmd += miscConfig.killMessageString;
    cmd += '"';
    interfaces->engine->clientCmdUnrestricted(cmd.c_str());
}

void Misc::fixMovement(UserCmd* cmd, float yaw) noexcept
{
    if (miscConfig.fixMovement) {
        float oldYaw = yaw + (yaw < 0.0f ? 360.0f : 0.0f);
        float newYaw = cmd->viewangles.y + (cmd->viewangles.y < 0.0f ? 360.0f : 0.0f);
        float yawDelta = newYaw < oldYaw ? fabsf(newYaw - oldYaw) : 360.0f - fabsf(newYaw - oldYaw);
        yawDelta = 360.0f - yawDelta;

        const float forwardmove = cmd->forwardmove;
        const float sidemove = cmd->sidemove;
        cmd->forwardmove = std::cos(Helpers::deg2rad(yawDelta)) * forwardmove + std::cos(Helpers::deg2rad(yawDelta + 90.0f)) * sidemove;
        cmd->sidemove = std::sin(Helpers::deg2rad(yawDelta)) * forwardmove + std::sin(Helpers::deg2rad(yawDelta + 90.0f)) * sidemove;
    }
}

void Misc::antiAfkKick(UserCmd* cmd) noexcept
{
    if (miscConfig.antiAfkKick && cmd->commandNumber % 2)
        cmd->buttons |= 1 << 26;
}

void Misc::fixAnimationLOD(FrameStage stage) noexcept
{
#ifdef _WIN32
    if (miscConfig.fixAnimationLOD && stage == FrameStage::RENDER_START) {
        if (!localPlayer)
            return;

        for (int i = 1; i <= interfaces->engine->getMaxClients(); i++) {
            Entity* entity = interfaces->entityList->getEntity(i);
            if (!entity || entity == localPlayer.get() || entity->isDormant() || !entity->isAlive()) continue;
            *reinterpret_cast<int*>(entity + 0xA28) = 0;
            *reinterpret_cast<int*>(entity + 0xA30) = memory->globalVars->framecount;
        }
    }
#endif
}

void Misc::autoPistol(UserCmd* cmd) noexcept
{
    if (miscConfig.autoPistol && localPlayer) {
        const auto activeWeapon = localPlayer->getActiveWeapon();
        if (activeWeapon && activeWeapon->isPistol() && activeWeapon->nextPrimaryAttack() > memory->globalVars->serverTime()) {
            if (activeWeapon->itemDefinitionIndex() == WeaponId::Revolver)
                cmd->buttons &= ~UserCmd::IN_ATTACK2;
            else
                cmd->buttons &= ~UserCmd::IN_ATTACK;
        }
    }
}

void Misc::chokePackets(bool& sendPacket) noexcept
{
    if (!miscConfig.chokedPacketsKey.isSet() || miscConfig.chokedPacketsKey.isDown())
        sendPacket = interfaces->engine->getNetworkChannel()->chokedPackets >= miscConfig.chokedPackets;
}

void Misc::autoReload(UserCmd* cmd) noexcept
{
    if (miscConfig.autoReload && localPlayer) {
        const auto activeWeapon = localPlayer->getActiveWeapon();
        if (activeWeapon && getWeaponIndex(activeWeapon->itemDefinitionIndex()) && !activeWeapon->clip())
            cmd->buttons &= ~(UserCmd::IN_ATTACK | UserCmd::IN_ATTACK2);
    }
}

void Misc::revealRanks(UserCmd* cmd) noexcept
{
    if (miscConfig.revealRanks && cmd->buttons & UserCmd::IN_SCORE)
        interfaces->client->dispatchUserMessage(50, 0, 0, nullptr);
}

void Misc::removeCrouchCooldown(UserCmd* cmd) noexcept
{
    if (miscConfig.fastDuck)
        cmd->buttons |= UserCmd::IN_BULLRUSH;
}

void Misc::moonwalk(UserCmd* cmd) noexcept
{
    if (miscConfig.moonwalk && localPlayer && localPlayer->moveType() != MoveType::LADDER)
        cmd->buttons ^= UserCmd::IN_FORWARD | UserCmd::IN_BACK | UserCmd::IN_MOVELEFT | UserCmd::IN_MOVERIGHT;
}

void Misc::playHitSound(GameEvent& event) noexcept
{
    if (!miscConfig.hitSound)
        return;

    if (!localPlayer)
        return;

    if (const auto localUserId = localPlayer->getUserId(); event.getInt("attacker") != localUserId || event.getInt("userid") == localUserId)
        return;

    constexpr std::array hitSounds{
        "play ui/beep07",
        "play buttons/arena_switch_press_02",
        "play training/timer_bell",
        "play physics/glass/glass_impact_bullet1"
    };

    if (static_cast<std::size_t>(miscConfig.hitSound - 1) < hitSounds.size())
        interfaces->engine->clientCmdUnrestricted(hitSounds[miscConfig.hitSound - 1]);
    else if (miscConfig.hitSound == 5)
        interfaces->engine->clientCmdUnrestricted(("play " + miscConfig.customHitSound).c_str());
}

void Misc::killSound(GameEvent& event) noexcept
{
    if (!miscConfig.killSound)
        return;

    if (!localPlayer || !localPlayer->isAlive())
        return;

    if (const auto localUserId = localPlayer->getUserId(); event.getInt("attacker") != localUserId || event.getInt("userid") == localUserId)
        return;

    constexpr std::array killSounds{
        "play ui/beep07",
        "play buttons/arena_switch_press_02",
        "play training/timer_bell",
        "play physics/glass/glass_impact_bullet1"
    };

    if (static_cast<std::size_t>(miscConfig.killSound - 1) < killSounds.size())
        interfaces->engine->clientCmdUnrestricted(killSounds[miscConfig.killSound - 1]);
    else if (miscConfig.killSound == 5)
        interfaces->engine->clientCmdUnrestricted(("play " + miscConfig.customKillSound).c_str());
}

void Misc::purchaseList(GameEvent* event) noexcept
{
    static std::mutex mtx;
    std::scoped_lock _{ mtx };

    struct PlayerPurchases {
        int totalCost;
        std::unordered_map<std::string, int> items;
    };

    static std::unordered_map<int, PlayerPurchases> playerPurchases;
    static std::unordered_map<std::string, int> purchaseTotal;
    static int totalCost;

    static auto freezeEnd = 0.0f;

    if (event) {
        switch (fnv::hashRuntime(event->getName())) {
        case fnv::hash("item_purchase"): {
            if (const auto player = interfaces->entityList->getEntity(interfaces->engine->getPlayerForUserID(event->getInt("userid"))); player && localPlayer && localPlayer->isOtherEnemy(player)) {
                if (const auto definition = memory->itemSystem()->getItemSchema()->getItemDefinitionByName(event->getString("weapon"))) {
                    auto& purchase = playerPurchases[player->handle()];
                    if (const auto weaponInfo = memory->weaponSystem->getWeaponInfo(definition->getWeaponId())) {
                        purchase.totalCost += weaponInfo->price;
                        totalCost += weaponInfo->price;
                    }
                    const std::string weapon = interfaces->localize->findAsUTF8(definition->getItemBaseName());
                    ++purchaseTotal[weapon];
                    ++purchase.items[weapon];
                }
            }
            break;
        }
        case fnv::hash("round_start"):
            freezeEnd = 0.0f;
            playerPurchases.clear();
            purchaseTotal.clear();
            totalCost = 0;
            break;
        case fnv::hash("round_freeze_end"):
            freezeEnd = memory->globalVars->realtime;
            break;
        }
    }
    else {
        if (!miscConfig.purchaseList.enabled)
            return;

        if (static const auto mp_buytime = interfaces->cvar->findVar("mp_buytime"); (!interfaces->engine->isInGame() || freezeEnd != 0.0f && memory->globalVars->realtime > freezeEnd + (!miscConfig.purchaseList.onlyDuringFreezeTime ? mp_buytime->getFloat() : 0.0f) || playerPurchases.empty() || purchaseTotal.empty()) && !gui->isOpen())
            return;

        ImGui::SetNextWindowSize({ 200.0f, 200.0f }, ImGuiCond_Once);

        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse;
        if (!gui->isOpen())
            windowFlags |= ImGuiWindowFlags_NoInputs;
        if (miscConfig.purchaseList.noTitleBar)
            windowFlags |= ImGuiWindowFlags_NoTitleBar;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowTitleAlign, { 0.5f, 0.5f });
        ImGui::Begin("Purchases", nullptr, windowFlags);
        ImGui::PopStyleVar();

        if (miscConfig.purchaseList.mode == PurchaseList::Details) {
            GameData::Lock lock;

            for (const auto& [handle, purchases] : playerPurchases) {
                std::string s;
                s.reserve(std::accumulate(purchases.items.begin(), purchases.items.end(), 0, [](int length, const auto& p) { return length + p.first.length() + 2; }));
                for (const auto& purchasedItem : purchases.items) {
                    if (purchasedItem.second > 1)
                        s += std::to_string(purchasedItem.second) + "x ";
                    s += purchasedItem.first + ", ";
                }

                if (s.length() >= 2)
                    s.erase(s.length() - 2);

                if (const auto player = GameData::playerByHandle(handle)) {
                    if (miscConfig.purchaseList.showPrices)
                        ImGui::TextWrapped("%s $%d: %s", player->name.c_str(), purchases.totalCost, s.c_str());
                    else
                        ImGui::TextWrapped("%s: %s", player->name.c_str(), s.c_str());
                }
            }
        }
        else if (miscConfig.purchaseList.mode == PurchaseList::Summary) {
            for (const auto& purchase : purchaseTotal)
                ImGui::TextWrapped("%d x %s", purchase.second, purchase.first.c_str());

            if (miscConfig.purchaseList.showPrices && totalCost > 0) {
                ImGui::Separator();
                ImGui::TextWrapped("Total: $%d", totalCost);
            }
        }
        ImGui::End();
    }
}

void Misc::oppositeHandKnife(FrameStage stage) noexcept
{
    if (!miscConfig.oppositeHandKnife)
        return;

    if (!localPlayer)
        return;

    if (stage != FrameStage::RENDER_START && stage != FrameStage::RENDER_END)
        return;

    static const auto cl_righthand = interfaces->cvar->findVar("cl_righthand");
    static bool original;

    if (stage == FrameStage::RENDER_START) {
        original = cl_righthand->getInt();

        if (const auto activeWeapon = localPlayer->getActiveWeapon()) {
            if (const auto classId = activeWeapon->getClientClass()->classId; classId == ClassId::Knife || classId == ClassId::KnifeGG)
                cl_righthand->setValue(!original);
        }
    }
    else {
        cl_righthand->setValue(original);
    }
}



static std::vector<std::uint64_t> reportedPlayers;
static int reportbotRound;

void Misc::runReportbot() noexcept
{
    if (!miscConfig.reportbot.enabled)
        return;

    if (!localPlayer)
        return;

    static auto lastReportTime = 0.0f;

    if (lastReportTime + miscConfig.reportbot.delay > memory->globalVars->realtime)
        return;

    if (reportbotRound >= miscConfig.reportbot.rounds)
        return;

    for (int i = 1; i <= interfaces->engine->getMaxClients(); ++i) {
        const auto entity = interfaces->entityList->getEntity(i);

        if (!entity || entity == localPlayer.get())
            continue;

        if (miscConfig.reportbot.target != 2 && (localPlayer->isOtherEnemy(entity) ? miscConfig.reportbot.target != 0 : miscConfig.reportbot.target != 1))
            continue;

        PlayerInfo playerInfo;
        if (!interfaces->engine->getPlayerInfo(i, playerInfo))
            continue;

        if (playerInfo.fakeplayer || std::ranges::find(reportedPlayers, playerInfo.xuid) != reportedPlayers.cend())
            continue;

        std::string report;

        if (miscConfig.reportbot.textAbuse)
            report += "textabuse,";
        if (miscConfig.reportbot.griefing)
            report += "grief,";
        if (miscConfig.reportbot.wallhack)
            report += "wallhack,";
        if (miscConfig.reportbot.aimbot)
            report += "aimbot,";
        if (miscConfig.reportbot.other)
            report += "speedhack,";

        if (!report.empty()) {
            memory->submitReport(std::to_string(playerInfo.xuid).c_str(), report.c_str());
            lastReportTime = memory->globalVars->realtime;
            reportedPlayers.push_back(playerInfo.xuid);
        }
        return;
    }

    reportedPlayers.clear();
    ++reportbotRound;
}

void Misc::resetReportbot() noexcept
{
    reportbotRound = 0;
    reportedPlayers.clear();
}

void Misc::preserveKillfeed(bool roundStart) noexcept
{
    if (!miscConfig.preserveKillfeed.enabled)
        return;

    static auto nextUpdate = 0.0f;

    if (roundStart) {
        nextUpdate = memory->globalVars->realtime + 10.0f;
        return;
    }

    if (nextUpdate > memory->globalVars->realtime)
        return;

    nextUpdate = memory->globalVars->realtime + 2.0f;

    const auto deathNotice = std::uintptr_t(memory->findHudElement(memory->hud, "CCSGO_HudDeathNotice"));
    if (!deathNotice)
        return;

    const auto deathNoticePanel = (*(UIPanel**)(*reinterpret_cast<std::uintptr_t*>(deathNotice WIN32_LINUX(-20 + 88, -32 + 128)) + sizeof(std::uintptr_t)));

    const auto childPanelCount = deathNoticePanel->getChildCount();

    for (int i = 0; i < childPanelCount; ++i) {
        const auto child = deathNoticePanel->getChild(i);
        if (!child)
            continue;

        if (child->hasClass("DeathNotice_Killer") && (!miscConfig.preserveKillfeed.onlyHeadshots || child->hasClass("DeathNoticeHeadShot")))
            child->setAttributeFloat("SpawnTime", memory->globalVars->currenttime);
    }
}

void Misc::voteRevealer(GameEvent& event) noexcept
{
    if (!miscConfig.revealVotes)
        return;

    const auto entity = interfaces->entityList->getEntity(event.getInt("entityid"));
    if (!entity || !entity->isPlayer())
        return;

    const auto votedYes = event.getInt("vote_option") == 0;
    const auto isLocal = localPlayer && entity == localPlayer.get();
    const char color = votedYes ? '\x06' : '\x07';

    memory->clientMode->getHudChat()->printf(0, " \x0C\u2022Osiris\u2022 %c%s\x01 voted %c%s\x01", isLocal ? '\x01' : color, isLocal ? "You" : entity->getPlayerName().c_str(), color, votedYes ? "Yes" : "No");
}

void Misc::onVoteStart(const void* data, int size) noexcept
{
    if (!miscConfig.revealVotes)
        return;

    constexpr auto voteName = [](int index) {
        switch (index)
        {
        case 0: return "Kick";
        case 1: return "Change Level";
        case 6: return "Surrender";
        case 13: return "Start TimeOut";
        default: return "";
        }
    };

    const auto reader = ProtobufReader{ static_cast<const std::uint8_t*>(data), size };
    const auto ent_idx = reader.readInt32(2);

    if (ent_idx) {
        const auto vote_type = reader.readInt32(3);
        const auto entity = interfaces->entityList->getEntity(ent_idx);
        const auto isLocal = localPlayer && entity == localPlayer.get();

        memory->clientMode->getHudChat()->printf(0, " \x0C\u2022elter\u2022 %c%s\x01 call vote (\x06%s\x01)", isLocal ? '\x01' : '\x06', isLocal ? "You" : entity->getPlayerName().c_str(), voteName(vote_type));
    }
}

void Misc::onVotePass() noexcept
{
    if (miscConfig.revealVotes)
        memory->clientMode->getHudChat()->printf(0, " \x0C\u2022elter\u2022\x01 Vote\x06 PASSED");
}

void Misc::onVoteFailed() noexcept
{
    if (miscConfig.revealVotes)
        memory->clientMode->getHudChat()->printf(0, " \x0C\u2022elter\u2022\x01 Vote\x07 FAILED");
}

// ImGui::ShadeVertsLinearColorGradientKeepAlpha() modified to do interpolation in HSV
static void shadeVertsHSVColorGradientKeepAlpha(ImDrawList* draw_list, int vert_start_idx, int vert_end_idx, ImVec2 gradient_p0, ImVec2 gradient_p1, ImU32 col0, ImU32 col1)
{
    ImVec2 gradient_extent = gradient_p1 - gradient_p0;
    float gradient_inv_length2 = 1.0f / ImLengthSqr(gradient_extent);
    ImDrawVert* vert_start = draw_list->VtxBuffer.Data + vert_start_idx;
    ImDrawVert* vert_end = draw_list->VtxBuffer.Data + vert_end_idx;

    ImVec4 col0HSV = ImGui::ColorConvertU32ToFloat4(col0);
    ImVec4 col1HSV = ImGui::ColorConvertU32ToFloat4(col1);
    ImGui::ColorConvertRGBtoHSV(col0HSV.x, col0HSV.y, col0HSV.z, col0HSV.x, col0HSV.y, col0HSV.z);
    ImGui::ColorConvertRGBtoHSV(col1HSV.x, col1HSV.y, col1HSV.z, col1HSV.x, col1HSV.y, col1HSV.z);
    ImVec4 colDelta = col1HSV - col0HSV;

    for (ImDrawVert* vert = vert_start; vert < vert_end; vert++)
    {
        float d = ImDot(vert->pos - gradient_p0, gradient_extent);
        float t = ImClamp(d * gradient_inv_length2, 0.0f, 1.0f);

        float h = col0HSV.x + colDelta.x * t;
        float s = col0HSV.y + colDelta.y * t;
        float v = col0HSV.z + colDelta.z * t;

        ImVec4 rgb;
        ImGui::ColorConvertHSVtoRGB(h, s, v, rgb.x, rgb.y, rgb.z);
        vert->col = (ImGui::ColorConvertFloat4ToU32(rgb) & ~IM_COL32_A_MASK) | (vert->col & IM_COL32_A_MASK);
    }
}

void Misc::drawOffscreenEnemies(ImDrawList* drawList) noexcept
{
    if (!miscConfig.offscreenEnemies.enabled)
        return;

    const auto yaw = Helpers::deg2rad(interfaces->engine->getViewAngles().y);

    GameData::Lock lock;
    for (auto& player : GameData::players()) {
        if ((player.dormant && player.fadingAlpha() == 0.0f) || !player.alive || !player.enemy || player.inViewFrustum)
            continue;

        const auto positionDiff = GameData::local().origin - player.origin;

        auto x = std::cos(yaw) * positionDiff.y - std::sin(yaw) * positionDiff.x;
        auto y = std::cos(yaw) * positionDiff.x + std::sin(yaw) * positionDiff.y;
        if (const auto len = std::sqrt(x * x + y * y); len != 0.0f) {
            x /= len;
            y /= len;
        }

        constexpr auto avatarRadius = 13.0f;
        constexpr auto triangleSize = 10.0f;

        const auto pos = ImGui::GetIO().DisplaySize / 2 + ImVec2{ x, y } *200;
        const auto trianglePos = pos + ImVec2{ x, y } *(avatarRadius + (miscConfig.offscreenEnemies.healthBar.enabled ? 5 : 3));

        Helpers::setAlphaFactor(player.fadingAlpha());
        const auto white = Helpers::calculateColor(255, 255, 255, 255);
        const auto background = Helpers::calculateColor(0, 0, 0, 80);
        const auto color = Helpers::calculateColor(miscConfig.offscreenEnemies.asColor4());
        const auto healthBarColor = miscConfig.offscreenEnemies.healthBar.type == HealthBar::HealthBased ? Helpers::healthColor(std::clamp(player.health / 100.0f, 0.0f, 1.0f)) : Helpers::calculateColor(miscConfig.offscreenEnemies.healthBar.asColor4());
        Helpers::setAlphaFactor(1.0f);

        const ImVec2 trianglePoints[]{
            trianglePos + ImVec2{  0.4f * y, -0.4f * x } *triangleSize,
            trianglePos + ImVec2{  1.0f * x,  1.0f * y } *triangleSize,
            trianglePos + ImVec2{ -0.4f * y,  0.4f * x } *triangleSize
        };

        drawList->AddConvexPolyFilled(trianglePoints, 3, color);
        drawList->AddCircleFilled(pos, avatarRadius + 1, white & IM_COL32_A_MASK, 40);

        const auto texture = player.getAvatarTexture();

        const bool pushTextureId = drawList->_TextureIdStack.empty() || texture != drawList->_TextureIdStack.back();
        if (pushTextureId)
            drawList->PushTextureID(texture);

        const int vertStartIdx = drawList->VtxBuffer.Size;
        drawList->AddCircleFilled(pos, avatarRadius, white, 40);
        const int vertEndIdx = drawList->VtxBuffer.Size;
        ImGui::ShadeVertsLinearUV(drawList, vertStartIdx, vertEndIdx, pos - ImVec2{ avatarRadius, avatarRadius }, pos + ImVec2{ avatarRadius, avatarRadius }, { 0, 0 }, { 1, 1 }, true);

        if (pushTextureId)
            drawList->PopTextureID();

        if (miscConfig.offscreenEnemies.healthBar.enabled) {
            const auto radius = avatarRadius + 2;
            const auto healthFraction = std::clamp(player.health / 100.0f, 0.0f, 1.0f);

            drawList->AddCircle(pos, radius, background, 40, 3.0f);

            const int vertStartIdx = drawList->VtxBuffer.Size;
            if (healthFraction == 1.0f) { // sometimes PathArcTo is missing one top pixel when drawing a full circle, so draw it with AddCircle
                drawList->AddCircle(pos, radius, healthBarColor, 40, 2.0f);
            }
            else {
                constexpr float pi = std::numbers::pi_v<float>;
                drawList->PathArcTo(pos, radius - 0.5f, pi / 2 - pi * healthFraction, pi / 2 + pi * healthFraction, 40);
                drawList->PathStroke(healthBarColor, false, 2.0f);
            }
            const int vertEndIdx = drawList->VtxBuffer.Size;

            if (miscConfig.offscreenEnemies.healthBar.type == HealthBar::Gradient)
                shadeVertsHSVColorGradientKeepAlpha(drawList, vertStartIdx, vertEndIdx, pos - ImVec2{ 0.0f, radius }, pos + ImVec2{ 0.0f, radius }, IM_COL32(0, 255, 0, 255), IM_COL32(255, 0, 0, 255));
        }
    }
}

void Misc::Spectatorlist()
{
    if (!miscConfig.spectatorlist || !miscConfig.specstyle == 1)
        return;
}

void Misc::autoAccept(const char* soundEntry) noexcept
{
    if (!miscConfig.autoAccept)
        return;

    if (std::strcmp(soundEntry, "UIPanorama.popup_accept_match_beep"))
        return;

    if (const auto idx = memory->registeredPanoramaEvents->find(memory->makePanoramaSymbol("MatchAssistedAccept")); idx != -1) {
        if (const auto eventPtr = memory->registeredPanoramaEvents->memory[idx].value.makeEvent(nullptr))
            interfaces->panoramaUIEngine->accessUIEngine()->dispatchEvent(eventPtr);
    }

#ifdef _WIN32
    auto window = FindWindowW(L"Valve001", NULL);
    FLASHWINFO flash{ sizeof(FLASHWINFO), window, FLASHW_TRAY | FLASHW_TIMERNOFG, 0, 0 };
    FlashWindowEx(&flash);
    ShowWindow(window, SW_RESTORE);
#endif
}

void Misc::updateEventListeners(bool forceRemove) noexcept
{
    class PurchaseEventListener : public GameEventListener {
    public:
        void fireGameEvent(GameEvent* event) override { purchaseList(event); }
    };

    static PurchaseEventListener listener;
    static bool listenerRegistered = false;

    if (miscConfig.purchaseList.enabled && !listenerRegistered) {
        interfaces->gameEventManager->addListener(&listener, "item_purchase");
        listenerRegistered = true;
    }
    else if ((!miscConfig.purchaseList.enabled || forceRemove) && listenerRegistered) {
        interfaces->gameEventManager->removeListener(&listener);
        listenerRegistered = false;
    }
}

void Misc::updateInput() noexcept
{

}

static bool windowOpen = false;

void Misc::menuBarItem() noexcept
{
    if (ImGui::MenuItem("Misc")) {
        windowOpen = true;
        ImGui::SetWindowFocus("Misc");
        ImGui::SetWindowPos("Misc", { 100.0f, 100.0f });
    }
}

void Misc::tabItem() noexcept
{
    if (ImGui::BeginTabItem("Misc")) {
        drawGUI(true);
        ImGui::EndTabItem();
    }
}
void Misc::tabItem2() noexcept
{
    if (ImGui::BeginTabItem("Misc")) {
        drawGUI2(true);
        ImGui::EndTabItem();
    }
}

void Misc::drawGUI(bool contentOnly) noexcept
{
    if (!contentOnly) {
        if (!windowOpen)
            return;
        ImGui::SetNextWindowSize({ 580.0f, 0.0f });
        ImGui::Begin("Misce", &windowOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize
            | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
    }
    
    ImGui::Columns(2, nullptr, false);
    ImGui::SetColumnOffset(1, 480.0f);
    ImGui::hotkey("Menu Key", miscConfig.menuKey);
    if (ImGui::Button("Unlock All Achievements"))
    {
        SteamUserStats->RequestCurrentStats();
        for (uint32 i = 0; i < SteamUserStats->GetNumAchievements(); i++)
            SteamUserStats->SetAchievement(SteamUserStats->GetAchievementName(i));
        SteamUserStats->StoreStats();
    }
    ImGui::SetNextItemWidth(140);
    ImGui::Combo("Region Changer", &miscConfig.forceRelayCluster, "Off\0Australia\0Austria\0Brazil\0Chile\0Dubai\0France\0Germany\0Hong Kong\0India (Chennai)\0India (Mumbai)\0Japan\0Luxembourg\0Netherlands\0Peru\0Philipines\0Poland\0Singapore\0South Africa\0Spain\0Sweden\0UK\0USA (Atlanta)\0USA (Seattle)\0USA (Chicago)\0USA (Los Angeles)\0USA (Moses Lake)\0USA (Oklahoma)\0USA (Seattle)\0USA (Washington DC)\0");
    ImGui::Checkbox("Watermark", &miscConfig.surfacewatermark);

    ImGui::Checkbox("Damage Indicator", &miscConfig.damageIndicator);
    ImGui::Checkbox("Spotify Indicator", &miscConfig.spotify);
    ImGui::Checkbox("Blockbot", &miscConfig.bb);
    ImGui::SameLine();
    ImGui::PushID("blockbot key");
    ImGui::hotkey("", miscConfig.bbkey);
    ImGui::PopID();
    ImGui::Checkbox("360 camera", &miscConfig.camera);
    ImGuiCustom::colorPicker("Noscope crosshair", miscConfig.noscopeCrosshair);
    ImGuiCustom::colorPicker("Recoil crosshair", miscConfig.recoilCrosshair);
    ImGui::Checkbox("Auto pistol", &miscConfig.autoPistol);
    ImGui::Checkbox("Auto accept", &miscConfig.autoAccept);
    ImGui::Checkbox("Radar hack", &miscConfig.radarHack);
    ImGui::Checkbox("Reveal ranks", &miscConfig.revealRanks);
    ImGui::Checkbox("Reveal suspect", &miscConfig.revealSuspect);
    ImGui::Checkbox("Reveal votes", &miscConfig.revealVotes);

    ImGui::Checkbox("Spectators List", &miscConfig.spectatorlist);

    ImGuiCustom::colorPicker("Offscreen Enemies", miscConfig.offscreenEnemies.asColor4(), &miscConfig.offscreenEnemies.enabled);
    ImGui::SameLine();
    ImGui::PushID("Offscreen Enemies");
    if (ImGui::Button("..."))
        ImGui::OpenPopup("");

    if (ImGui::BeginPopup("")) {
        ImGui::Checkbox("Health Bar", &miscConfig.offscreenEnemies.healthBar.enabled);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(95.0f);
        ImGui::Combo("Type", &miscConfig.offscreenEnemies.healthBar.type, "Gradient\0Solid\0Health-based\0");
        if (miscConfig.offscreenEnemies.healthBar.type == HealthBar::Solid) {
            ImGui::SameLine();
            ImGuiCustom::colorPicker("", miscConfig.offscreenEnemies.healthBar.asColor4());
        }
        ImGui::EndPopup();
    }
    ImGui::PopID();
    ImGui::Checkbox("Disable model occlusion", &miscConfig.disableModelOcclusion);
    ImGui::SliderFloat("Aspect Ratio", &miscConfig.aspectratio, 0.0f, 5.0f, "%.2f");
    ImGui::Checkbox("Disable HUD blur", &miscConfig.disablePanoramablur);
    ImGui::Checkbox("Animated clan tag", &miscConfig.animatedClanTag);
    ImGui::Checkbox("Custom clantag", &miscConfig.customClanTag);
    ImGui::SameLine();
    ImGui::PushItemWidth(120.0f);
    ImGui::PushID(0);

    if (ImGui::InputText("", miscConfig.clanTag, sizeof(miscConfig.clanTag)))
        Misc::updateClanTag(true);
    ImGui::PopID();
    ImGui::Checkbox("Kill message", &miscConfig.killMessage);
    ImGui::SameLine();
    ImGui::PushItemWidth(120.0f);
    ImGui::PushID(1);
    ImGui::InputText("", &miscConfig.killMessageString);
    ImGui::PopID();
    ImGui::Checkbox("Name stealer", &miscConfig.nameStealer);
    ImGui::PushID(3);
    ImGui::SetNextItemWidth(100.0f);
    ImGui::Combo("", &miscConfig.banColor, "White\0Red\0Purple\0Green\0Light green\0Turquoise\0Light red\0Gray\0Yellow\0Gray 2\0Light blue\0Gray/Purple\0Blue\0Pink\0Dark orange\0Orange\0");
    ImGui::PopID();
    ImGui::SameLine();
    ImGui::PushID(4);
    ImGui::InputText("", &miscConfig.banText);
    ImGui::PopID();
    ImGui::SameLine();
    if (ImGui::Button("Setup fake ban"))
        Misc::fakeBan(true);
    ImGui::Checkbox("Fast plant", &miscConfig.fastPlant);
    ImGui::Checkbox("Fast Stop", &miscConfig.fastStop);
    ImGuiCustom::colorPicker("Bomb timer", miscConfig.bombTimer);
    ImGui::Checkbox("Quick reload", &miscConfig.quickReload);
    ImGui::Checkbox("Prepare revolver", &miscConfig.prepareRevolver);
    ImGui::SameLine();
    ImGui::PushID("Prepare revolver Key");
    ImGui::hotkey("", miscConfig.prepareRevolverKey);
    ImGui::PopID();
    ImGui::Combo("Hit Sound", &miscConfig.hitSound, "None\0Iwebz\0Gamesense\0Bell\0Glass\0Custom\0");
    if (miscConfig.hitSound == 5) {
        ImGui::InputText("Hit Sound filename", &miscConfig.customHitSound);
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("audio file must be put in csgo/sound/ directory");
    }
    ImGui::PushID(5);
    ImGui::Combo("Kill Sound", &miscConfig.killSound, "None\0Iwebz\0Gamesense\0Bell\0Glass\0Custom\0");
    if (miscConfig.killSound == 5) {
        ImGui::InputText("Kill Sound filename", &miscConfig.customKillSound);
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("audio file must be put in csgo/sound/ directory");
    }
    ImGui::PopID();
    ImGui::SetNextItemWidth(90.0f);
    ImGui::InputInt("Choked packets", &miscConfig.chokedPackets, 1, 5);
    miscConfig.chokedPackets = std::clamp(miscConfig.chokedPackets, 0, 64);
    ImGui::SameLine();
    ImGui::PushID("Choked packets Key");
    ImGui::hotkey("", miscConfig.chokedPacketsKey);
    ImGui::PopID();
    /*
    ImGui::Text("Quick healthshot");
    ImGui::SameLine();
    hotkey(miscConfig.quickHealthshotKey);
    */
    ImGui::Checkbox("Grenade Prediction", &miscConfig.nadePredict);
    ImGui::Checkbox("Fix tablet signal", &miscConfig.fixTabletSignal);
    ImGui::SetNextItemWidth(120.0f);
    ImGui::SliderFloat("Max angle delta", &miscConfig.maxAngleDelta, 0.0f, 255.0f, "%.2f");
    ImGui::Checkbox("Opposite Hand Knife", &miscConfig.oppositeHandKnife);
    ImGui::Checkbox("Preserve Killfeed", &miscConfig.preserveKillfeed.enabled);
    ImGui::SameLine();

    ImGui::PushID("Preserve Killfeed");
    if (ImGui::Button("..."))
        ImGui::OpenPopup("");

    if (ImGui::BeginPopup("")) {
        ImGui::Checkbox("Only Headshots", &miscConfig.preserveKillfeed.onlyHeadshots);
        ImGui::EndPopup();
    }
    ImGui::PopID();

    ImGui::Checkbox("Purchase List", &miscConfig.purchaseList.enabled);
    ImGui::SameLine();

    ImGui::PushID("Purchase List");
    if (ImGui::Button("..."))
        ImGui::OpenPopup("");

    if (ImGui::BeginPopup("")) {
        ImGui::SetNextItemWidth(75.0f);
        ImGui::Combo("Mode", &miscConfig.purchaseList.mode, "Details\0Summary\0");
        ImGui::Checkbox("Only During Freeze Time", &miscConfig.purchaseList.onlyDuringFreezeTime);
        ImGui::Checkbox("Show Prices", &miscConfig.purchaseList.showPrices);
        ImGui::Checkbox("No Title Bar", &miscConfig.purchaseList.noTitleBar);
        ImGui::EndPopup();
    }
    ImGui::PopID();

    ImGui::Checkbox("Reportbot", &miscConfig.reportbot.enabled);
    ImGui::SameLine();
    ImGui::PushID("Reportbot");

    if (ImGui::Button("..."))
        ImGui::OpenPopup("");

    if (ImGui::BeginPopup("")) {
        ImGui::PushItemWidth(80.0f);
        ImGui::Combo("Target", &miscConfig.reportbot.target, "Enemies\0Allies\0All\0");
        ImGui::InputInt("Delay (s)", &miscConfig.reportbot.delay);
        miscConfig.reportbot.delay = (std::max)(miscConfig.reportbot.delay, 1);
        ImGui::InputInt("Rounds", &miscConfig.reportbot.rounds);
        miscConfig.reportbot.rounds = (std::max)(miscConfig.reportbot.rounds, 1);
        ImGui::PopItemWidth();
        ImGui::Checkbox("Abusive Communications", &miscConfig.reportbot.textAbuse);
        ImGui::Checkbox("Griefing", &miscConfig.reportbot.griefing);
        ImGui::Checkbox("Wall Hacking", &miscConfig.reportbot.wallhack);
        ImGui::Checkbox("Aim Hacking", &miscConfig.reportbot.aimbot);
        ImGui::Checkbox("Other Hacking", &miscConfig.reportbot.other);
        if (ImGui::Button("Reset"))
            Misc::resetReportbot();
        ImGui::EndPopup();
    }
    ImGui::PopID();

    if (ImGui::Button("Unhook"))
        hooks->uninstall();

    ImGui::Columns(1);
    if (!contentOnly)
        ImGui::End();
}


void Misc::drawGUI2(bool contentOnly) noexcept
{
    if (!contentOnly) {
        if (!windowOpen)
            return;
        ImGui::SetNextWindowSize({ 580.0f, 0.0f });
        ImGui::Begin("Misc", &windowOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize
            | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
    }
    ImGui::Columns(2, nullptr, false);
    ImGui::SetColumnOffset(1, 480.0f);
    ImGui::Checkbox("Bunny hop", &miscConfig.bunnyHop);
    ImGui::Checkbox("Fast duck [desativar]", &miscConfig.fastDuck);
    ImGui::Checkbox("Nulls", &miscConfig.nulls);
   // ImGui::Checkbox("Strafe Optimizer", &miscConfig.strafeopt);
    ImGui::Checkbox("Edge Jump", &miscConfig.edgejump);
    ImGui::SameLine();
    ImGui::PushID("Edge Jump Key");
    ImGui::hotkey("", miscConfig.edgejumpkey);
    ImGui::PopID();
    ImGui::Checkbox("LongJump on ej", &miscConfig.longjump);
    ImGui::Checkbox("Jumpbug", &miscConfig.jumpbug);
    ImGui::SameLine();
    ImGui::PushID("JB KEY");
    ImGui::hotkey("", miscConfig.jumpbugkey);
    ImGui::PopID();
    ImGui::Checkbox("Edgebug", &miscConfig.edgebug);
    ImGui::SameLine();
    ImGui::PushID("EB KEY");
    ImGui::hotkey("", miscConfig.edgebugkey);
    ImGui::PopID();
    ImGui::Checkbox("Indicators", &miscConfig.Indicators);
    ImGui::Checkbox("Jumpstats", &miscConfig.jumpstats);
    ImGui::Checkbox("Edgebug Detect", &miscConfig.detectedge);
    ImGui::Checkbox("Edgebug Sound", &miscConfig.edgebugsound);
    ImGui::Checkbox("Edgebug Effect", &miscConfig.edgebugeffect);
    ImGui::Checkbox("Velocity Graph", &miscConfig.velocityGraph);
    if (miscConfig.velocityGraph)
    {
        ImGui::SliderFloat("Graph Height", &miscConfig.VelocityGHeight, 0 , 250);
    }
    ImGui::Checkbox("Stamina Graph", &miscConfig.staminaGraph);
    if (miscConfig.staminaGraph)
    {
        ImGui::SliderFloat("S_Graph Height", &miscConfig.StaminaGHeight, 0, 250);
    }
    ImGui::Checkbox("Velocity Indicator", &miscConfig.Velocity);
    if (miscConfig.Velocity)
    {
        ImGui::Checkbox("Fade Color", &miscConfig.VFadecolor);
        ImGui::SliderInt("Velocity Height", &miscConfig.VelocityHeight, 0, 120);
    }
    ImGui::Checkbox("Stamina Indicator", &miscConfig.Stamina);
    if (miscConfig.Stamina)
    {
        ImGui::Checkbox("Fade Color ", &miscConfig.Fadecolor);
        ImGui::SliderInt("Stamina Height", &miscConfig.staminaheight, 0, 120);
    }
    ImGui::Checkbox("Keystrokes", &miscConfig.keystrokes);
    if (miscConfig.keystrokes)
    {
        ImGui::SliderFloat("KHeight", &miscConfig.wasdheight, 0, 500);
    }
 
    ImGui::Columns(1);
    if (!contentOnly)
        ImGui::End();
}

static void from_json(const json& j, ImVec2& v)
{
    read(j, "X", v.x);
    read(j, "Y", v.y);
}

static void from_json(const json& j, PurchaseList& pl)
{
    read(j, "Enabled", pl.enabled);
    read(j, "Only During Freeze Time", pl.onlyDuringFreezeTime);
    read(j, "Show Prices", pl.showPrices);
    read(j, "No Title Bar", pl.noTitleBar);
    read(j, "Mode", pl.mode);
}

static void from_json(const json& j, OffscreenEnemies& o)
{
    from_json(j, static_cast<ColorToggle&>(o));

    read<value_t::object>(j, "Health Bar", o.healthBar);
}

static void from_json(const json& j, MiscConfig::Watermark& o)
{
    read(j, "Enabled", o.enabled);
}

static void from_json(const json& j, PreserveKillfeed& o)
{
    read(j, "Enabled", o.enabled);
    read(j, "Only Headshots", o.onlyHeadshots);
}

static void from_json(const json& j, MiscConfig& m)
{
    read(j, "Menu key", m.menuKey);
    read(j, "Anti AFK kick", m.antiAfkKick);
    read(j, "Auto strafe", m.autoStrafe);
    read(j, "Bunny hop", m.bunnyHop);
    read(j, "Custom clan tag", m.customClanTag);
    read(j, "Clock tag", m.clocktag);
    read(j, "Clan tag", m.clanTag, sizeof(m.clanTag));
    read(j, "Animated clan tag", m.animatedClanTag);
    read(j, "Fast duck", m.fastDuck);
    read(j, "Moonwalk", m.moonwalk);
    read(j, "Edge Jump", m.edgejump);
    read(j, "Edge Jump Key", m.edgejumpkey);
    read(j, "Slowwalk", m.slowwalk);
    read(j, "Slowwalk key", m.slowwalkKey);
    read<value_t::object>(j, "Noscope crosshair", m.noscopeCrosshair);
    read<value_t::object>(j, "Recoil crosshair", m.recoilCrosshair);
    read(j, "Auto pistol", m.autoPistol);
    read(j, "Auto reload", m.autoReload);
    read(j, "Auto accept", m.autoAccept);
    read(j, "Radar hack", m.radarHack);
    read(j, "Reveal ranks", m.revealRanks);
    read(j, "Reveal money", m.revealMoney);
    read(j, "Reveal suspect", m.revealSuspect);
    read(j, "Reveal votes", m.revealVotes);
    read(j, "Spectator list", m.spectatorlist);
    read<value_t::object>(j, "Watermark", m.watermark);
    read<value_t::object>(j, "Offscreen Enemies", m.offscreenEnemies);
    read(j, "Fix animation LOD", m.fixAnimationLOD);
    read(j, "Fix bone matrix", m.fixBoneMatrix);
    read(j, "Fix movement", m.fixMovement);
    read(j, "Disable model occlusion", m.disableModelOcclusion);
    read(j, "Aspect Ratio", m.aspectratio);
    read(j, "Kill message", m.killMessage);
    read<value_t::string>(j, "Kill message string", m.killMessageString);
    read(j, "Name stealer", m.nameStealer);
    read(j, "Disable HUD blur", m.disablePanoramablur);
    read(j, "Ban color", m.banColor);
    read<value_t::string>(j, "Ban text", m.banText);
    read(j, "Fast plant", m.fastPlant);
    read(j, "Fast Stop", m.fastStop);
    read<value_t::object>(j, "Bomb timer", m.bombTimer);
    read(j, "Quick reload", m.quickReload);
    read(j, "Prepare revolver", m.prepareRevolver);
    read(j, "Prepare revolver key", m.prepareRevolverKey);
    read(j, "Hit sound", m.hitSound);
    read(j, "Choked packets", m.chokedPackets);
    read(j, "Choked packets key", m.chokedPacketsKey);
    read(j, "Quick healthshot key", m.quickHealthshotKey);
    read(j, "Grenade predict", m.nadePredict);
    read(j, "Fix tablet signal", m.fixTabletSignal);
    read(j, "Max angle delta", m.maxAngleDelta);
    read(j, "Fix tablet signal", m.fixTabletSignal);
    read<value_t::string>(j, "Custom Hit Sound", m.customHitSound);
    read(j, "Kill sound", m.killSound);
    read<value_t::string>(j, "Custom Kill Sound", m.customKillSound);
    read<value_t::object>(j, "Purchase List", m.purchaseList);
    read<value_t::object>(j, "Reportbot", m.reportbot);
    read(j, "Opposite Hand Knife", m.oppositeHandKnife);
    read<value_t::object>(j, "Preserve Killfeed", m.preserveKillfeed);

    read(j, "Jumpbug", m.jumpbug);
    read(j, "Jumpbugkey", m.jumpbugkey);
    read(j, "Edgebug", m.edgebug);
    read(j, "Edgebugtime", m.edgebugtime);
    read(j, "Edgebugkey", m.edgebugkey);
    read(j, "Longjump", m.lj);
    read(j, "Longjumpkey", m.ljkey);
    read(j, "Blockbot", m.bb);
    read(j, "Blockbotkey", m.bbkey);
    read(j, "Velocity", m.Velocity);
    read(j, "VelocityH", m.VelocityHeight);
    read(j, "Edgebugsound", m.edgebugsound);
    read(j, "Detectedge", m.detectedge);
    read(j, "Lockedge", m.lockedge);
    read(j, "Jumpstats", m.jumpstats);
    read(j, "Camera", m.camera);
    read(j, "disableduck", m.disableduck);
    read(j, "Indicators", m.Indicators);
    read(j, "rainbowvel", m.rainbowvel);
    read(j, "Fadecolor", m.Fadecolor);
    read(j, "VFadecolor", m.VFadecolor);
    read(j, "Stamina", m.Stamina);
    read(j, "staminaheight", m.staminaheight);
    // dps
    read(j, "Kheight", m.wasdheight);
    read(j, "Keystrokes", m.keystrokes);
    read(j, "DamageIndicator", m.damageIndicator);
    read(j, "Watermark", m.surfacewatermark);
    read(j, "Spotify", m.spotify);
    read(j, "Strafeopt", m.strafeopt);
    read(j, "Velocitygraph", m.velocityGraph);
    read(j, "Velocitygraphh", m.VelocityGHeight);
    read(j, "Staminagraph", m.staminaGraph);
    read(j, "Staminagraphh", m.StaminaGHeight);
}

static void from_json(const json& j, MiscConfig::Reportbot& r)
{
    read(j, "Enabled", r.enabled);
    read(j, "Target", r.target);
    read(j, "Delay", r.delay);
    read(j, "Rounds", r.rounds);
    read(j, "Abusive Communications", r.textAbuse);
    read(j, "Griefing", r.griefing);
    read(j, "Wall Hacking", r.wallhack);
    read(j, "Aim Hacking", r.aimbot);
    read(j, "Other Hacking", r.other);
}

static void to_json(json& j, const MiscConfig::Reportbot& o, const MiscConfig::Reportbot& dummy = {})
{
    WRITE("Enabled", enabled);
    WRITE("Target", target);
    WRITE("Delay", delay);
    WRITE("Rounds", rounds);
    WRITE("Abusive Communications", textAbuse);
    WRITE("Griefing", griefing);
    WRITE("Wall Hacking", wallhack);
    WRITE("Aim Hacking", aimbot);
    WRITE("Other Hacking", other);
}

static void to_json(json& j, const PurchaseList& o, const PurchaseList& dummy = {})
{
    WRITE("Enabled", enabled);
    WRITE("Only During Freeze Time", onlyDuringFreezeTime);
    WRITE("Show Prices", showPrices);
    WRITE("No Title Bar", noTitleBar);
    WRITE("Mode", mode);
}

static void to_json(json& j, const ImVec2& o, const ImVec2& dummy = {})
{
    WRITE("X", x);
    WRITE("Y", y);
}

static void to_json(json& j, const OffscreenEnemies& o, const OffscreenEnemies& dummy = {})
{
    to_json(j, static_cast<const ColorToggle&>(o), dummy);

    WRITE("Health Bar", healthBar);
}

static void to_json(json& j, const MiscConfig::Watermark& o, const MiscConfig::Watermark& dummy = {})
{
    WRITE("Enabled", enabled);
}

static void to_json(json& j, const PreserveKillfeed& o, const PreserveKillfeed& dummy = {})
{
    WRITE("Enabled", enabled);
    WRITE("Only Headshots", onlyHeadshots);
}

static void to_json(json& j, const MiscConfig& o)
{
    const MiscConfig dummy;

    WRITE("Menu key", menuKey);
    WRITE("Anti AFK kick", antiAfkKick);
    WRITE("Auto strafe", autoStrafe);
    WRITE("Bunny hop", bunnyHop);
    WRITE("Custom clan tag", customClanTag);
    WRITE("Clock tag", clocktag);

    if (o.clanTag[0])
        j["Clan tag"] = o.clanTag;

    WRITE("Animated clan tag", animatedClanTag);
    WRITE("Fast duck", fastDuck);
    WRITE("Moonwalk", moonwalk);
    WRITE("Edge Jump", edgejump);
    WRITE("Edge Jump Key", edgejumpkey);
    WRITE("Slowwalk", slowwalk);
    WRITE("Slowwalk key", slowwalkKey);
    WRITE("Noscope crosshair", noscopeCrosshair);
    WRITE("Recoil crosshair", recoilCrosshair);
    WRITE("Auto pistol", autoPistol);
    WRITE("Auto reload", autoReload);
    WRITE("Auto accept", autoAccept);
    WRITE("Radar hack", radarHack);
    WRITE("Reveal ranks", revealRanks);
    WRITE("Reveal money", revealMoney);
    WRITE("Reveal suspect", revealSuspect);
    WRITE("Reveal votes", revealVotes);
    WRITE("Spectator list", spectatorlist);
    WRITE("Watermark", watermark);
    WRITE("Offscreen Enemies", offscreenEnemies);
    WRITE("Fix animation LOD", fixAnimationLOD);
    WRITE("Fix bone matrix", fixBoneMatrix);
    WRITE("Fix movement", fixMovement);
    WRITE("Disable model occlusion", disableModelOcclusion);
    WRITE("Aspect Ratio", aspectratio);
    WRITE("Kill message", killMessage);
    WRITE("Kill message string", killMessageString);
    WRITE("Name stealer", nameStealer);
    WRITE("Disable HUD blur", disablePanoramablur);
    WRITE("Ban color", banColor);
    WRITE("Ban text", banText);
    WRITE("Fast plant", fastPlant);
    WRITE("Fast Stop", fastStop);
    WRITE("Bomb timer", bombTimer);
    WRITE("Quick reload", quickReload);
    WRITE("Prepare revolver", prepareRevolver);
    WRITE("Prepare revolver key", prepareRevolverKey);
    WRITE("Hit sound", hitSound);
    WRITE("Choked packets", chokedPackets);
    WRITE("Choked packets key", chokedPacketsKey);
    WRITE("Quick healthshot key", quickHealthshotKey);
    WRITE("Grenade predict", nadePredict);
    WRITE("Fix tablet signal", fixTabletSignal);
    WRITE("Max angle delta", maxAngleDelta);
    WRITE("Fix tablet signal", fixTabletSignal);
    WRITE("Custom Hit Sound", customHitSound);
    WRITE("Kill sound", killSound);
    WRITE("Custom Kill Sound", customKillSound);
    WRITE("Purchase List", purchaseList);
    WRITE("Reportbot", reportbot);
    WRITE("Opposite Hand Knife", oppositeHandKnife);
    WRITE("Preserve Killfeed", preserveKillfeed);

    WRITE("Camera", camera);
    WRITE("disableduck", disableduck);
    WRITE("Jumpbug", jumpbug);
    WRITE("Jumpbugkey", jumpbugkey);
    WRITE("Edgebug", edgebug);
    WRITE("Edgebugkey", edgebugkey);
    WRITE("Edgebugtime", edgebugtime);
    WRITE("Longjump", lj);
    WRITE("Longjumpkey", ljkey);
    WRITE("Longjump", lj);
    WRITE("Longjumpkey", ljkey);
    WRITE("Blockbot", bb);
    WRITE("Blockbot", bbkey);
    WRITE("Velocity", Velocity);
    WRITE("VelocityH", VelocityHeight);
    WRITE("Edgebugsound", edgebugsound);
    WRITE("Detectedge", detectedge);
    WRITE("Lockedge", lockedge);
    WRITE("Jumpstats", jumpstats);
    WRITE("Indicators", Indicators);
    WRITE("rainbowvel", rainbowvel);
    WRITE("Fadecolor", Fadecolor);
    WRITE("VFadecolor", VFadecolor);
    WRITE("Stamina", Stamina);
    WRITE("staminaheight", staminaheight);
    WRITE("Kheight", wasdheight);
    WRITE("Keystrokes", keystrokes);
    WRITE("DamageIndicator", damageIndicator);
    WRITE("Watermark", surfacewatermark);
    WRITE("Spotify", spotify);
    WRITE("Strafeopt", strafeopt);
    WRITE("Velocitygraph", velocityGraph);
    WRITE("Velocitygraphh", VelocityGHeight);
    WRITE("Staminagraph", staminaGraph);
    WRITE("Staminagraphh", StaminaGHeight);
}

json Misc::toJson() noexcept
{
    json j;
    to_json(j, miscConfig);
    return j;
}

void Misc::fromJson(const json& j) noexcept
{
    from_json(j, miscConfig);
}

void Misc::resetConfig() noexcept
{
    miscConfig = {};
}
