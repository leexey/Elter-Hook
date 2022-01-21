#pragma once

struct UserCmd;

namespace EnginePrediction
{
    bool inpred = false;
    void run(UserCmd* cmd) noexcept;
    void end() noexcept;
    int getFlags() noexcept;
}
