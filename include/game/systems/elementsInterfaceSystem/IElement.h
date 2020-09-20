//
// Created by Battary on 28.05.2020.
//

#pragma once

#include <string>
#include <vector>

#include "BearLibTerminal.h"
#include "game/lib/ECS/ECS.h"

// Шаблон всех элементов интерфейса
class IElement {
 protected:
  int elementColumn_{0}, elementRow_{0}, elementWidth_{0}, elementHeight_{0};
  std::string elementData_{}, name_{};
  bool expendable_{false}, hide_{false};
  std::vector<int> reqUpdNumbers_;

  void drawOnLayer(int);

 public:
  virtual void updateElement(ecs::World&) = 0;

  virtual void displayElement() = 0;

  void setVariables(int, int, int, int, std::string);
  void setVariables(int, int, std::string);
  void setExpendable(bool);
  void setHide(bool);

  std::string getName();
  bool getExpendable() const;
  bool getHide() const;
  bool getReqUpdateNumber(int) const;

  virtual ~IElement() = default;
};
