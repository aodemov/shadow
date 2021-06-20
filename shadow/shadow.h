#pragma once

#include "shadow/core/macros.h"
#include "shadow/core/debug/profiling.h"

#include "shadow/core/log/log.h"

#include "shadow/application/application.h"

#include "shadow/events/event_bus.h"
#include "shadow/events/application_events.h"
#include "shadow/events/keyboard_events.h"
#include "shadow/events/mouse_events.h"

#include "shadow/input/key_codes.h"
#include "shadow/input/input.h"

#include "shadow/renderer/render.h"
#include "shadow/renderer/shader.h"
#include "shadow/renderer/vertex_array.h"
#include "shadow/renderer/camera_controller.h"
#include "shadow/renderer/font.h"

#include "shadow/ecs/scene_manager.h"
#include "shadow/ecs/scene.h"
#include "shadow/ecs/entity.h"
#include "shadow/ecs/component.h"
#include "shadow/components/transform.h"
#include "shadow/components/sprite_component.h"
#include "shadow/components/camera_component.h"
#include "shadow/components/script_component.h"
#include "shadow/components/animator_component.h"
#include "shadow/components/ui_component.h"
#include "shadow/components/collider_component.h"
#include "shadow/components/rigidbody_component.h"
#include "shadow/components/trigger_component.h"
#include "shadow/components/tag_component.h"

#include "shadow/components/sprite.h"
#include "shadow/components/texture_atlas.h"
#include "shadow/components/animation.h"
#include "shadow/components/animation_controller.h"

#include "shadow/ui/ui_block.h"
#include "shadow/ui/label.h"
#include "shadow/ui/ui_container.h"

#include "shadow/core/math/random.h"
#include "shadow/core/utils/file.h"

