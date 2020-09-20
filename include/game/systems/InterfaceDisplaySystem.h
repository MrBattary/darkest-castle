//
// Created by Battary on 03.07.2020.
//

#pragma once

#include "BearLibTerminal.h"
#include "game/lib/ECS/ECS.h"
// Friend
#include "game/systems/InterfaceUpdateSystem.h"

// Класс отвечает за вывод элементов интерфейса
class InterfaceDisplaySystem : public ecs::System {
 public:
  InterfaceDisplaySystem();

  void updateSystem(ecs::World&) override;

  ~InterfaceDisplaySystem() override = default;
};
