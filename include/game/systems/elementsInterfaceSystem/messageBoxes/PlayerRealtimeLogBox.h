//
// Created by Battary on 05.08.2020.
//

#pragma once
#include <string>
// Internal templates
#include "../IMessageBoxElement.h"

class PlayerRealtimeLogBox : public IMessageBoxElement {
 private:
  bool messageDisplayed_{false};

 public:
  PlayerRealtimeLogBox();

  void updateElement(ecs::World &) override;

  void addData(std::string);
  void displayRequired();

  ~PlayerRealtimeLogBox() override = default;
};
