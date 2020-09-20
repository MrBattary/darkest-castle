//
// Created by Battary on 26.05.2020.
//

#pragma once

#include "BearLibTerminal.h"
#include "../InterfaceUpdateSystem.h"
#include "IKey.h"

// Сообщение, что игра должна быть завершена или поставлена на паузу
class ExitKey : public IKey{
 public:
  ExitKey();

  void execute(ecs::World&) override;

  ~ExitKey() override = default;
};
