//
// Created by Battary on 27.07.2020.
//

#include "game/systems/elementsInterfaceSystem/dialogBoxes/InventoryBox.h"
InventoryBox::InventoryBox(ecs::World& world) {
  setVariables(61, 2, 20, 11, "");

  name_ = "Inventory";
  reqUpdNumbers_ = {1};

  auto keyboardSys = world.getSystem<KeyboardInputSystem>();
  dialogKeys_[1] = std::make_pair("Close inventory:", keyboardSys->getKeyName("Inventory"));

  auto player = world.getEntity<Player>();
  auto playerStatComp = player->getComponent<StatsComponent>();
  auto playerInvComp = player->getComponent<InventoryComponent>();
  elementData_ += "[color=orange]Player[/color]\n";
  for (auto it = playerStatComp->stats_.begin(); it != playerStatComp->stats_.end(); ++it) {
    if (it->first.substr(0, 1) != "+" && it->first != "Damage") {
      auto currStatFromItems{0};
      for (auto lt = playerInvComp->items_.begin(); lt != playerInvComp->items_.end(); ++lt) {
        auto itemStatComp = lt->second->getComponent<StatsComponent>();
        for (auto jt = itemStatComp->stats_.begin(); jt != itemStatComp->stats_.end(); ++jt) {
          if (it->second->name_ == jt->second->name_) currStatFromItems += jt->second->value_;
        }
      }

      elementData_ += it->second->name_ + ": " + std::to_string(it->second->value_) + " + ";
      paintStat(currStatFromItems);
    }
  }
  for (auto it = playerInvComp->items_.begin(); it != playerInvComp->items_.end(); ++it) {
    elementData_ += "\n[color=orange]" + it->second->getEntityName() + "[/color]\n";
    auto itemStatComp = it->second->getComponent<StatsComponent>();
    for (auto jt = itemStatComp->stats_.begin(); jt != itemStatComp->stats_.end(); ++jt) {
      elementData_ += jt->second->name_ + ": ";
      paintStat(jt->second->value_);
    }
  }
  elementData_ += "\n";
  for (auto it = dialogKeys_.begin(); it != dialogKeys_.end(); ++it) {
    elementData_ += it->second.first + " " + (it->second.second);
    if (it != std::prev(dialogKeys_.end(), 1)) {
      elementData_ += "\n";
    }
  }
  calculateBoxSize(elementData_);

  expendable_ = false;
}
void InventoryBox::updateElement(ecs::World& world) {
  auto interfaceSys = world.getSystem<InterfaceUpdateSystem>();

  if (interfaceSys->getCommand() == "Inventory") {
    expendable_ = true;
    interfaceSys->setCommand("");
  }
}

void InventoryBox::paintStat(const int value) {
  if (value < 0) {
    elementData_ += "[color=red]" + std::to_string(value) + "[/color]\n";
  }
  if (value > 0) {
    elementData_ += "[color=green]" + std::to_string(value) + "[/color]\n";
  }
  if (value == 0) {
    elementData_ += std::to_string(value) + "\n";
  }
}
