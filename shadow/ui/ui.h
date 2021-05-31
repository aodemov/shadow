#pragma once

#include "shadow/renderer/camera.h"
#include "shadow/ui/ui_block.h"


namespace Shadow {
class UI {
public:
    static void Init();
    static void Shutdown();

    static void Begin();
    static void End();

    static void Add(Ref<UiBlock> block);
};
}
