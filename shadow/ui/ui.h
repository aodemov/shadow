#pragma once

#include "shadow/renderer/camera.h"

namespace Shadow {
class UI {
public:
    static void Init();
    static void Shutdown();

    static void Begin();
    static void End();
};
}
