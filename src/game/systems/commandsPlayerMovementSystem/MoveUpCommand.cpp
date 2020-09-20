//
// Created by Battary on 26.03.2020.
//

#include "game/systems/commandsPlayerMovementSystem/MoveUpCommand.h"

void MoveUpCommand::execute(std::shared_ptr<LocationComponent> comp,
                            std::shared_ptr<PreviousLocationComponent> compPr,
                            std::shared_ptr<DirectionComponent> dir,
                            std::shared_ptr<StatisticsComponent> stat) {
  stat->steps_ = ++stat->steps_;
  compPr->rowPrevious_ = comp->row_;
  comp->row_ = comp->row_ - 1;
  dir->direction_ = DirectionComponent::UPWARD;
}
