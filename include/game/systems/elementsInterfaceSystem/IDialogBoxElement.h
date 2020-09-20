//
// Created by Battary on 28.05.2020.
//
#pragma once

#include <map>
#include <string>
#include <utility>

#include "IElement.h"

// Шаблон элементов, которые ведут диалог с пользователем
class IDialogBoxElement : public IElement {
 private:
  void drawBordersOnLayer(const int);

 protected:
  void calculateBoxSize(std::string);

 public:
  std::map<int, std::pair<std::string, std::string>> dialogKeys_ {};

  void updateElement(ecs::World &) override = 0;

  void displayElement() override;

  ~IDialogBoxElement() override = default;
};
