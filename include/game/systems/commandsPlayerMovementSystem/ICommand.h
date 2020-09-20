//
// Created by Battary on 26.03.2020.
//

#pragma once

#include <memory>

#include "game/components/DirectionComponent.h"
#include "game/components/LocationComponent.h"
#include "game/components/PreviousLocationComponent.h"
#include "game/components/StatisticsComponent.h"

//Класс шаблон команды
class ICommand {
 public:
  virtual void execute(std::shared_ptr<LocationComponent>, std::shared_ptr<PreviousLocationComponent>,
                       std::shared_ptr<DirectionComponent>, std::shared_ptr<StatisticsComponent>) = 0;

  virtual ~ICommand() = default;
};
