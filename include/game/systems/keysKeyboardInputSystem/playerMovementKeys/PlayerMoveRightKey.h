//
// Created by Battary on 26.05.2020.
//

#pragma once

#include "../IKey.h"
// Entities
#include "game/entities/PlayerEntity.h"
#include "game/components/ControlComponent.h"

// Сообщение соответствующей системе,, что игроку требуется сдвинуться вправо
class PlayerMoveRightKey : public IKey{
 public:
  PlayerMoveRightKey();

  void execute(ecs::World &) override;

  ~PlayerMoveRightKey() override = default;
};
