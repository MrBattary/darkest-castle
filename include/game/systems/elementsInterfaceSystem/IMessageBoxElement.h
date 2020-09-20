//
// Created by Battary on 28.05.2020.
//

#pragma once

#include "IElement.h"

// Шаблон элементов-сообщений, отображающих информацию
class IMessageBoxElement : public IElement {
 public:
  void updateElement(ecs::World &) override = 0;

  void displayElement() override;

  ~IMessageBoxElement() override = default;
};
