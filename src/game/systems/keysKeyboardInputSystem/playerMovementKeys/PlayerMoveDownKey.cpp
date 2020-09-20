//
// Created by Battary on 26.05.2020.
//

#include "game/systems/keysKeyboardInputSystem/playerMovementKeys/PlayerMoveDownKey.h"

void PlayerMoveDownKey::execute(ecs::World& world) {
  auto player = world.getEntity<Player>();
  auto command = player->getComponent<ControlComponent>();
  if (command != nullptr) command->current_ = name_;
}

PlayerMoveDownKey::PlayerMoveDownKey() {
  name_ = "Move down";
}
