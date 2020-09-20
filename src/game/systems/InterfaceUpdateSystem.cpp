//
// Created by Battary on 28.05.2020.
//

#include "game/systems/InterfaceUpdateSystem.h"
InterfaceUpdateSystem::InterfaceUpdateSystem() {
  setID(900);
  createElement<PlayerRealtimeStatisticsBox>();
  createElement<PlayerRealtimeLogBox>();
  createElement<PlayerHealthBox>();
  createElement<MenuMiniBox>();
  createElement<HelpMiniBox>();
  createElement<InventoryMiniMox>();
}

void InterfaceUpdateSystem::addElements(ecs::World& world) {
  if (!blockNewWindows_) {
    if (command_ == "Exit" && !containElement("Menu")) {
      createElement<MenuBox>(world);
    }
    if (command_ == "Help" && !containElement("Help")) {
      createElement<HelpBox>(world);
    }
    if (command_ == "Inventory" && !containElement("Inventory")) {
      createElement<InventoryBox>(world);
    }
  }
}

void InterfaceUpdateSystem::freezeEntities(ecs::World& world) {
  auto enemiesLogicSys = world.getSystem<EnemiesLogicSystem>();
  auto playerMoveSys = world.getSystem<PlayerMovementSystem>();
  if (containElement("Menu") || containElement("Help") || containElement("Inventory")) {
    playerMoveSys->setInactive(true);
    enemiesLogicSys->setInactive(true);
  } else {
    playerMoveSys->setInactive(false);
    enemiesLogicSys->setInactive(false);
  }
}

void InterfaceUpdateSystem::updateSystem(ecs::World& world) {
  for (auto& element : elements_) {
    if (element.second->getReqUpdateNumber(1)) elements_.at(element.first)->updateElement(world);
  }
  bool allErased{false};
  do {
    allErased = true;
    for (auto& element : elements_) {
      if (elements_.at(element.first)->getExpendable()) {
        elements_.erase(element.first);
        allErased = false;
        break;
      }
    }
  } while (!allErased);

  addElements(world);
  freezeEntities(world);
  command_.clear();

  for (auto& element : elements_) {
    if (element.second->getReqUpdateNumber(2)) elements_.at(element.first)->updateElement(world);
  }
}

void InterfaceUpdateSystem::deleteElement(std::string name) {
  elements_.erase(name);
}

std::string InterfaceUpdateSystem::getCommand() const {
  return command_;
}

void InterfaceUpdateSystem::setCommand(std::string command) {
  command_ = command;
}

bool InterfaceUpdateSystem::containElement(std::string name) const {
  return elements_.count(name) != 0;
}

void InterfaceUpdateSystem::blockNewWindows() {
  blockNewWindows_ = true;
}

void InterfaceUpdateSystem::unblockNewWindows() {
  blockNewWindows_ = false;
}
bool InterfaceUpdateSystem::getElementExpendableStatus(std::string name) const {
  for (auto& element : elements_) {
    if (element.first == name) {
      return element.second->getExpendable();
    }
  }
  return true;
}
void InterfaceUpdateSystem::hideAllExcept(std::initializer_list<std::string> list) {
  for (auto& element : elements_) {
    for (auto elementFromList : list) {
      if (element.first != elementFromList) {
        element.second->setHide(true);
        break;
      } else {
        element.second->setHide(false);
      }
    }
  }
}
void InterfaceUpdateSystem::unhideAllExcept(std::initializer_list<std::string> list) {
  if (list.size()) {
    for (auto& element : elements_) {
      for (auto elementFromList : list) {
        if (element.first == elementFromList) {
          element.second->setHide(false);
          break;
        } else {
          element.second->setHide(true);
        }
      }
    }
  } else {
    for (auto& element : elements_) {
      element.second->setHide(false);
    }
  }
}
