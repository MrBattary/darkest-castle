//
// Created by Battary on 28.04.2020.
//

#include "game/systems/mapFormationSubsystems/constructors/IConstructor.h"

std::tuple<const int, const int> IConstructor::pullCoords(std::string obj) {
  auto xPointer = obj.find("AxisX") + 5;
  std::string xCord = obj.substr(xPointer, 2);
  int x = std::stoi(xCord);

  auto yPointer = obj.find("AxisY") + 5;
  std::string yCord = obj.substr(yPointer, 2);
  int y = std::stoi(yCord);

  return std::make_tuple(x, y);
}

const std::string IConstructor::pullImage(std::string obj) {
  return obj.substr(0, 1);
}
