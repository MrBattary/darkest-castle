//
// Created by Battary on 26.03.2020.
//

#include "game/systems/commandsPlayerMovementSystem/NothingCommand.h"

void NothingCommand::execute(std::shared_ptr<LocationComponent> comp,
                             std::shared_ptr<PreviousLocationComponent> compPr,
                             std::shared_ptr<DirectionComponent> dir,
                             std::shared_ptr<StatisticsComponent> stat) {
  dir->direction_ = DirectionComponent::NOWHERE;
}
