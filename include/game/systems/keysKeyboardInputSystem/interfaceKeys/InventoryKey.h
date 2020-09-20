//
// Created by Battary on 27.07.2020.
//

#pragma once

#include "BearLibTerminal.h"
#include "game/systems/InterfaceUpdateSystem.h"
#include "game/systems/keysKeyboardInputSystem/IKey.h"

// Сообщение необходимости открытия/закрытия окна инвентаря
class InventoryKey : public IKey {
 public:
  InventoryKey();

  void execute(ecs::World&) override;

  ~InventoryKey() override = default;
};
