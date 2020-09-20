//
// Created by Battary on 03.08.2020.
//

#include "game/systems/elementsInterfaceSystem/messageBoxes/PlayerHealthBox.h"
PlayerHealthBox::PlayerHealthBox() {
  setVariables(25, 0, 10, 1, "");
  name_ = "PlayerHealth";
  reqUpdNumbers_ = {1};
  expendable_ = false;
}

void PlayerHealthBox::updateElement(ecs::World& world) {
  auto playerEnt = world.getEntity<Player>();
  auto statsComp = playerEnt->getComponent<StatsComponent>();
  auto health =  statsComp->getStat("+Health");
  auto damage = statsComp->getStat("Damage");
  elementData_ = "Health: " + std::to_string(health->value_ - damage->value_);
}
