//
// Created by Battary on 29.05.2020.
//

#include "game/systems/elementsInterfaceSystem/dialogBoxes/EndLevelBox.h"
EndLevelBox::EndLevelBox(ecs::World& world, int x, int y, int map) : tpToX_(x), tpToY_(y), nextMap_(map) {
  setVariables(31, 10, 16, 3, "");

  name_ = "End level";
  reqUpdNumbers_ = {1};

  auto keyboardSys = world.getSystem<KeyboardInputSystem>();
  dialogKeys_[1] = std::make_pair("Stay:", keyboardSys->getKeyName("Stay"));
  dialogKeys_[2] = std::make_pair("Move:", keyboardSys->getKeyName("Continue"));
  dialogKeys_[3] = std::make_pair("Exit:", keyboardSys->getKeyName("Exit"));

  auto interfaceSys = world.getSystem<InterfaceUpdateSystem>();
  interfaceSys->hideAllExcept({"End level", "Leaderboard"});

  auto outputSys = world.getSystem<EntitiesDisplaySystem>();
  auto playerMoveSys = world.getSystem<PlayerMovementSystem>();
  auto enemiesLogicSys = world.getSystem<EnemiesLogicSystem>();
  enemiesLogicSys->setInactive(true);
  playerMoveSys->setInactive(true);
  outputSys->setInactive(true);
  auto player = world.getEntity<Player>();
  auto statisticsComp = player->getComponent<StatisticsComponent>();

  elementData_ = "Congratulations!\nSteps: " + std::to_string(statisticsComp->steps_) +
                 "\nCoins: " + std::to_string(statisticsComp->coins_) + "\n";
  for (auto it = dialogKeys_.begin(); it != dialogKeys_.end(); ++it) {
    elementData_ += it->second.first + " " + (it->second.second);
    if (it != std::prev(dialogKeys_.end(), 1)) {
      elementData_ += "\n";
    }
  }

  calculateBoxSize(elementData_);

  interfaceSys->blockNewWindows();
  expendable_ = false;
}

void EndLevelBox::updateElement(ecs::World& world) {
  auto interfaceSys = world.getSystem<InterfaceUpdateSystem>();

  if (interfaceSys->getCommand() == "Exit") {
    world.terminateApplication();
  }
  if (interfaceSys->getCommand() == "Stay" || interfaceSys->getCommand() == "Continue") {
    if (interfaceSys->getCommand() =="Continue") {
      auto playerEnt = world.getEntity<Player>(1);
      auto locationComp = playerEnt->getComponent<LocationComponent>();
      locationComp->column_ = tpToX_;
      locationComp->row_ = tpToY_;

      auto mapSys = world.getSystem<MapFormationSystem>(100);
      mapSys->setNextMap(nextMap_);
      mapSys->updateSystem(world);

      auto locationPrevComp = playerEnt->getComponent<PreviousLocationComponent>();
      locationPrevComp->columnPrevious_ = locationComp->column_;
      locationPrevComp->rowPrevious_ = locationComp->row_;
    }

    expendable_ = true;
    interfaceSys->deleteElement("Leaderboard");
    interfaceSys->unhideAllExcept({});
    interfaceSys->unblockNewWindows();
    interfaceSys->setCommand("");
    auto outputSys = world.getSystem<EntitiesDisplaySystem>();
    auto playerMoveSys = world.getSystem<PlayerMovementSystem>();
    auto enemiesLogicSys = world.getSystem<EnemiesLogicSystem>();
    enemiesLogicSys->setInactive(false);
    playerMoveSys->setInactive(false);
    outputSys->setInactive(false);
  }
}
