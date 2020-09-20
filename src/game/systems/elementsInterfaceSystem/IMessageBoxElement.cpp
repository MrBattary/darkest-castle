//
// Created by Battary on 28.05.2020.
//

#include "game/systems/elementsInterfaceSystem/IMessageBoxElement.h"

void IMessageBoxElement::displayElement() {
  elementData_ += "[bbox=" + std::to_string(elementWidth_) + "x" + std::to_string(elementHeight_)+"]";
  terminal_clear_area(elementColumn_, elementRow_, elementWidth_, elementHeight_);

  drawOnLayer(10);
}
