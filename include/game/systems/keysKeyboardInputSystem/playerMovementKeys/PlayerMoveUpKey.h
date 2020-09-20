//
// Created by Battary on 26.05.2020.
//

#pragma once

#include "../IKey.h"
// Entities
#include "game/entities/PlayerEntity.h"
#include "game/components/ControlComponent.h"

// Сообщение соответствующей системе, что игроку требуется сдвинуться вверх
class PlayerMoveUpKey : public IKey{
 public:
  PlayerMoveUpKey();

  void execute(ecs::World &) override;

  ~PlayerMoveUpKey() override = default;
};
