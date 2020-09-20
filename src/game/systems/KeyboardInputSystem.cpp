//
// Created by Battary on 26.05.2020.
//

#include "game/systems/KeyboardInputSystem.h"

KeyboardInputSystem::KeyboardInputSystem() {
  setID(0);
  setKeys(TK_ESCAPE, TK_UP, TK_DOWN, TK_LEFT, TK_RIGHT, TK_ENTER, TK_SPACE, TK_H, TK_I);
  setKeysNames();
}

void KeyboardInputSystem::setKeys(int back = 0, int up = 0, int down = 0, int left = 0, int right = 0, int forward = 0,
                                  int stay = 0, int help = 0, int inventory = 0) {
  keys_.insert(std::make_pair(up, std::make_shared<PlayerMoveUpKey>()));
  keys_.insert(std::make_pair(down, std::make_shared<PlayerMoveDownKey>()));
  keys_.insert(std::make_pair(left, std::make_shared<PlayerMoveLeftKey>()));
  keys_.insert(std::make_pair(right, std::make_shared<PlayerMoveRightKey>()));
  keys_.insert(std::make_pair(back, std::make_shared<ExitKey>()));
  keys_.insert(std::make_pair(stay, std::make_shared<StayKey>()));
  keys_.insert(std::make_pair(forward, std::make_shared<ContinueKey>()));
  keys_.insert(std::make_pair(help, std::make_shared<HelpKey>()));
  keys_.insert(std::make_pair(inventory, std::make_shared<InventoryKey>()));
}

void KeyboardInputSystem::setKeysNames() {
  keysNames_.insert(std::make_pair(TK_ESCAPE, "Esc"));
  keysNames_.insert(std::make_pair(TK_UP, "Up"));
  keysNames_.insert(std::make_pair(TK_DOWN, "Down"));
  keysNames_.insert(std::make_pair(TK_LEFT, "Left"));
  keysNames_.insert(std::make_pair(TK_RIGHT, "Right"));
  keysNames_.insert(std::make_pair(TK_ENTER, "Enter"));
  keysNames_.insert(std::make_pair(TK_SPACE, "Space"));
  keysNames_.insert(std::make_pair(TK_H, "H"));
  keysNames_.insert(std::make_pair(TK_I, "I"));
}

std::vector<std::shared_ptr<IKey>> KeyboardInputSystem::findKeysRealisation(const int key) {
  std::vector<std::shared_ptr<IKey>> keysRealisation;
  auto pos = keys_.find(key);
  if (pos == keys_.end()) {
    keysRealisation.push_back(nothing_);
  } else {
    for (auto it = keys_.begin(); it != keys_.end(); ++it) {
      if (it->first == key) {
        keysRealisation.push_back(it->second);
      }
    }
  }
  return keysRealisation;
}

void KeyboardInputSystem::updateSystem(ecs::World& world) {
  if (!inputBuffer_) inputBuffer_ = terminal_read();

  std::vector<std::shared_ptr<IKey>> realisation = findKeysRealisation(inputBuffer_);
  for (auto current : realisation) {
    current->execute(world);
  }
  inputBuffer_ = 0;
}

std::string KeyboardInputSystem::getKeyName(std::string name) {
  for (auto it = keys_.begin(); it != keys_.end(); ++it) {
    if (!it->second->name_.compare(name)) {
      auto keyName = keysNames_.find(it->first);
      return keyName->second;
    }
  }
  return "";
}
void KeyboardInputSystem::skipInput() {
  inputBuffer_ = -1;
}
