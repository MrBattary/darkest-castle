//
// Created by Battary on 26.05.2020.
//

#pragma once

#include "../IKey.h"
// Entities
#include "game/entities/PlayerEntity.h"
#include "game/components/ControlComponent.h"

// Сообщение соответствующей системе, что игроку требуется сдвинуться вниз
class PlayerMoveDownKey : public IKey{
 public:
  PlayerMoveDownKey();

  void execute(ecs::World &) override;

  ~PlayerMoveDownKey() override = default;
};
