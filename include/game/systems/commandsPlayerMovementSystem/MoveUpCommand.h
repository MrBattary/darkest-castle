//
// Created by Battary on 26.03.2020.
//

#pragma once

#include <memory>

#include "ICommand.h"

//Класс команды движения вверх
class MoveUpCommand : public ICommand {
 public:
  MoveUpCommand() = default;

  void execute(std::shared_ptr<LocationComponent>, std::shared_ptr<PreviousLocationComponent>,
               std::shared_ptr<DirectionComponent>, std::shared_ptr<StatisticsComponent>) override;

  ~MoveUpCommand() override = default;
};
