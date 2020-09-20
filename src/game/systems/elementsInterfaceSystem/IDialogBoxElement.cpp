//
// Created by Battary on 28.05.2020.
//

#include "game/systems/elementsInterfaceSystem/IDialogBoxElement.h"

void IDialogBoxElement::drawBordersOnLayer(const int layer) {
  const int mainLayer = terminal_state(TK_LAYER);
  for (int i = 0; i <= mainLayer + layer; i++) {
    terminal_layer(i);
    terminal_clear_area(elementColumn_ - 1, elementRow_ - 1, elementWidth_ + 2, elementHeight_ + 2);
  }
  terminal_layer((mainLayer + layer));
  // Top border
  for (int x = 0; x < elementWidth_ + 2; x++) {
    terminal_put(elementColumn_ + x - 1, elementRow_ - 1, 0x2593);
  }
  // Bot border
  for (int x = 0; x < elementWidth_ + 2; x++) {
    terminal_put(elementColumn_ + x - 1, elementRow_ + elementHeight_, 0x2593);
  }
  // Left border
  for (int y = 0; y < elementHeight_; y++) {
    terminal_put(elementColumn_ - 1, elementRow_ + y, 0x2593);
  }
  // Right border
  for (int y = 0; y < elementHeight_; y++) {
    terminal_put(elementColumn_ + elementWidth_, elementRow_ + y, 0x2593);
  }
  terminal_layer(mainLayer);
}

void IDialogBoxElement::displayElement() {
  elementData_ +=
      "[bbox=" + std::to_string(elementWidth_) + "x" + std::to_string(elementHeight_ + dialogKeys_.size()) + "]";
  terminal_clear_area(elementColumn_ - 1, elementRow_ - 1, elementWidth_ + 2, elementHeight_ + 2);

  drawBordersOnLayer(10);
  drawOnLayer(10);
}

void IDialogBoxElement::calculateBoxSize(std::string data) {
  size_t lines{1}, maxlength{0}, currlength{0};
  bool stopcount{false};
  for (size_t i = 0; i < data.size(); ++i) {
    if (data[i] == '[') stopcount = true;
    if (data[i] == ']') stopcount = false;
    if (data[i] == '\n') {
      lines++;
      if (currlength > maxlength) {
        maxlength = currlength;
      }
      currlength = 0;
    } else {
      if (!stopcount) currlength++;
    }
  }
  if (currlength > maxlength) {
    maxlength = currlength;
  }
  if (elementColumn_ + maxlength > 79) {
    elementColumn_ = 79 - maxlength;
  }
  if (elementRow_ + lines > 24) {
    elementRow_ = 24 - lines;
  }
  setVariables(elementColumn_, elementRow_, maxlength, lines, "");
}
