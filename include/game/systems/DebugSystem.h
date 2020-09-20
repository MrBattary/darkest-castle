//
// Created by Battary on 26.03.2020.
//

#pragma once

#include "BearLibTerminal.h"
#include "game/lib/ECS/ECS.h"

// Components
#include "game/components/ControlComponent.h"
#include "game/components/LocationComponent.h"
#include "game/components/PreviousLocationComponent.h"
// Systems
#include "game/systems/InterfaceUpdateSystem.h"

//Система, непосредственно выводящая значения некоторых компонентов в терминал
class DebugSystem : public ecs::System {
 public:
  DebugSystem();

  void updateSystem(ecs::World&) override;

  ~DebugSystem() override = default;
};
