//
// Created by Battary on 26.05.2020.
//

#include "game/systems/mapFormationSubsystems/constructors/ExitConstructor.h"

int ExitConstructor::pullData(std::string obj, std::string designation) {
  auto pointer = obj.find(designation);
  if (pointer != std::string::npos) {
    pointer += 3;
    std::string str = obj.substr(pointer, 3);
    return std::stoi(str);
  } else {
    return 1;
  }
}

void ExitConstructor::constructObject(ecs::World& world, std::string obj) {
  size_t exitID = world.createEntityAndReturnID<Exit>();
  auto exit = world.getEntity<Exit>(exitID);
  std::string image = pullImage(obj);
  int imageCode{0};
  if (image == "<") imageCode = 0x3C;
  if (image == ">") imageCode = 0x3E;
  exit->addComponent<SymbolComponent>(imageCode, "Door11x16.png, align=center", 3);

  int x{0}, y{0};
  std::tie(x, y) = pullCoords(obj);
  exit->addComponent<LocationComponent>(x, y);

  int mapNumber = pullData(obj, "Map");
  int toXNumber = pullData(obj, "ToX");
  int toYNumber = pullData(obj, "ToY");
  exit->addComponent<ExitDataComponent>(mapNumber, toXNumber, toYNumber);
}
