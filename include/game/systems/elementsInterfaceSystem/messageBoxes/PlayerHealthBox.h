//
// Created by Battary on 03.08.2020.
//

#pragma once
// Internal templates
#include "../IMessageBoxElement.h"
// Entities
#include "game/entities/PlayerEntity.h"
#include "game/components/StatsComponent.h"

class PlayerHealthBox : public IMessageBoxElement {
 public:
  PlayerHealthBox();

  void updateElement(ecs::World &) override;

  ~PlayerHealthBox() override = default;
};
