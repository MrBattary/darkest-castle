//
// Created by Battary on 26.05.2020.
//

#include "game/systems/keysKeyboardInputSystem/playerMovementKeys/PlayerMoveUpKey.h"

void PlayerMoveUpKey::execute(ecs::World& world) {
  auto player = world.getEntity<Player>();
  auto command = player->getComponent<ControlComponent>();
  if (command != nullptr) command->current_ = name_;
}
PlayerMoveUpKey::PlayerMoveUpKey() {
  name_ = "Move up";
}
