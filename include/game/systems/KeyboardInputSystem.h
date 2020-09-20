//
// Created by Battary on 26.05.2020.
//

#pragma once

#include <map>
#include <vector>
#include <memory>
#include <string>

#include "BearLibTerminal.h"
#include "game/lib/ECS/ECS.h"
// Keys
#include "keysKeyboardInputSystem/ContinueKey.h"
#include "keysKeyboardInputSystem/ExitKey.h"
#include "keysKeyboardInputSystem/IKey.h"
#include "keysKeyboardInputSystem/NothingKey.h"
#include "keysKeyboardInputSystem/StayKey.h"
#include "keysKeyboardInputSystem/interfaceKeys/HelpKey.h"
#include "keysKeyboardInputSystem/interfaceKeys/InventoryKey.h"
#include "keysKeyboardInputSystem/playerMovementKeys/PlayerMoveDownKey.h"
#include "keysKeyboardInputSystem/playerMovementKeys/PlayerMoveLeftKey.h"
#include "keysKeyboardInputSystem/playerMovementKeys/PlayerMoveRightKey.h"
#include "keysKeyboardInputSystem/playerMovementKeys/PlayerMoveUpKey.h"

// Система отвечающая за конфигурацию и ввод с клавитатуры
class KeyboardInputSystem : public ecs::System {
 private:
  std::map<int, std::string> keysNames_ {};
  std::multimap<int, std::shared_ptr<IKey>> keys_ {};
  std::shared_ptr<NothingKey> nothing_ = std::make_shared<NothingKey>();

  bool changed_{true};
  int inputBuffer_{0};

  void setKeys(int, int, int, int, int, int, int, int, int);
  void setKeysNames();
  std::vector<std::shared_ptr<IKey>> findKeysRealisation(const int);

 public:
  KeyboardInputSystem();

  void updateSystem(ecs::World&) override;

  std::string getKeyName(std::string);

  void skipInput();

  ~KeyboardInputSystem() override = default;
};
