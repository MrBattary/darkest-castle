//
// Created by Battary on 26.03.2020.
//

#pragma once

#include <map>
#include <memory>
#include <string>

#include "game/lib/ECS/ECS.h"
// Components
#include "game/components/ControlComponent.h"
#include "game/components/LocationComponent.h"
#include "game/components/PreviousLocationComponent.h"
#include "game/components/DirectionComponent.h"
#include "game/components/StatisticsComponent.h"
// Commands
#include "commandsPlayerMovementSystem/MoveDownCommand.h"
#include "commandsPlayerMovementSystem/MoveLeftCommand.h"
#include "commandsPlayerMovementSystem/MoveRightCommand.h"
#include "commandsPlayerMovementSystem/MoveUpCommand.h"
#include "commandsPlayerMovementSystem/NothingCommand.h"

//Система, контролирующая передвижение относительно нажатых клавиш на клавиатуре
class PlayerMovementSystem : public ecs::System {
 private:
  std::map<std::string, std::shared_ptr<ICommand>> storage_ {};
  std::shared_ptr<NothingCommand> nothing_ = std::make_shared<NothingCommand>();

  void fillStorage();
  std::shared_ptr<ICommand> findCommand(const std::string);

 public:
  PlayerMovementSystem();

  void updateSystem(ecs::World&) override;

  ~PlayerMovementSystem() override {
    storage_.clear();
  }
};
