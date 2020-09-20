//
// Created by Battary on 27.07.2020.
//

#pragma once

#include "BearLibTerminal.h"
#include "game/systems/InterfaceUpdateSystem.h"
#include "game/systems/keysKeyboardInputSystem/IKey.h"

// Сообщение необходимости открытия/закрытия окна справки
class HelpKey : public IKey {
 public:
  HelpKey();

  void execute(ecs::World&) override;

  ~HelpKey() override = default;
};
