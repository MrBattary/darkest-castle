//
// Created by Battary on 05.08.2020.
//

#include "game/systems/elementsInterfaceSystem/messageBoxes/PlayerRealtimeLogBox.h"

PlayerRealtimeLogBox::PlayerRealtimeLogBox() {
  setVariables(0, 24, 65, 1, "");
  name_ = "PlayerRealtimeLog";
  reqUpdNumbers_ = {1};
  expendable_ = false;
}

void PlayerRealtimeLogBox::updateElement(ecs::World& world) {
  if (!messageDisplayed_) {
    messageDisplayed_ = true;
  } else {
    elementData_.clear();
  }
}

void PlayerRealtimeLogBox::displayRequired() {
  messageDisplayed_ = false;
}

void PlayerRealtimeLogBox::addData(std::string data) {
  if (messageDisplayed_) elementData_.clear();
  elementData_ += data;
  displayRequired();
}
