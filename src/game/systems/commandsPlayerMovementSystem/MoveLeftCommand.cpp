//
// Created by Battary on 26.03.2020.
//

#include "game/systems/commandsPlayerMovementSystem/MoveLeftCommand.h"

void MoveLeftCommand::execute(std::shared_ptr<LocationComponent> comp,
                              std::shared_ptr<PreviousLocationComponent> compPr,
                              std::shared_ptr<DirectionComponent> dir,
                              std::shared_ptr<StatisticsComponent> stat) {
  stat->steps_ = ++stat->steps_;
  compPr->columnPrevious_ = comp->column_;
  comp->column_ = comp->column_ - 1;
  dir->direction_ = DirectionComponent::LEFTWARD;
}
