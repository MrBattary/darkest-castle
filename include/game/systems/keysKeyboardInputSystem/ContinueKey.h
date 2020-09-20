//
// Created by Battary on 11.06.2020.
//

#pragma once

#include "../InterfaceUpdateSystem.h"
#include "BearLibTerminal.h"
#include "IKey.h"

// Сообщение соответствующей системе,что требуется перейти на следующий уровень
class ContinueKey : public IKey {
 public:
  ContinueKey();

  void execute(ecs::World&) override;

  ~ContinueKey() override = default;
};
