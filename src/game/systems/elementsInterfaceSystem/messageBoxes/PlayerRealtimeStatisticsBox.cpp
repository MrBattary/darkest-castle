//
// Created by Battary on 28.05.2020.
//

#include "game/systems/elementsInterfaceSystem/messageBoxes/PlayerRealtimeStatisticsBox.h"

PlayerRealtimeStatisticsBox::PlayerRealtimeStatisticsBox() {
  setVariables(0, 0, 20, 1, "");
  name_ = "PlayerRealtimeStatistics";
  reqUpdNumbers_ = {1};
  expendable_ = false;
}

void PlayerRealtimeStatisticsBox::updateElement(ecs::World& world) {
  auto playerEnt = world.getEntity<Player>();
  auto statisticsComp = playerEnt->getComponent<StatisticsComponent>();
  elementData_ =
      "Steps: " + std::to_string(statisticsComp->steps_) + " Coins: " + std::to_string(statisticsComp->coins_);
}
