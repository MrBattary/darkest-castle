//
// Created by Battary on 28.05.2020.
//

#include "game/systems/elementsInterfaceSystem/IElement.h"

std::string IElement::getName() {
  return name_;
}
void IElement::setVariables(int column, int row, int width, int height, std::string data) {
  elementColumn_ = column;
  elementRow_ = row;
  elementHeight_ = height;
  elementWidth_ = width;
  elementData_ += data;
}

void IElement::setVariables(int column, int row, std::string data) {
  elementColumn_ = column;
  elementRow_ = row;
  elementData_ += data;
}

void IElement::setExpendable(bool value) {
  expendable_ = value;
}

bool IElement::getExpendable() const {
  return expendable_;
}

void IElement::drawOnLayer(const int layer) {
  const int mainLayer = terminal_state(TK_LAYER);
  for (int i = 0; i <= mainLayer + layer; i++) {
    terminal_layer(i);
    terminal_clear_area(elementColumn_, elementRow_, elementWidth_, elementHeight_);
  }
  terminal_layer((mainLayer + layer));
  terminal_printf(elementColumn_, elementRow_, elementData_.c_str());
  terminal_layer(mainLayer);
}

void IElement::setHide(bool value) {
  hide_ = value;
}

bool IElement::getHide() const {
  return hide_;
}

bool IElement::getReqUpdateNumber(int value) const {
  return std::find(reqUpdNumbers_.begin(), reqUpdNumbers_.end(), value) != reqUpdNumbers_.end();
}
