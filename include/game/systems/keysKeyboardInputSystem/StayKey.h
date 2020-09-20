//
// Created by Battary on 28.05.2020.
//

#pragma once

#include "BearLibTerminal.h"
#include "../InterfaceUpdateSystem.h"
#include "IKey.h"

// Сообщение соответствующей системе, что игра должна быть продолжена
class StayKey : public IKey{
 public:
  StayKey();

  void execute(ecs::World&) override;

  ~StayKey() override = default;
};
