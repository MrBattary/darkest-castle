//
// Created by Battary on 25.03.2020.
//

#pragma once

#include <memory>
#include <vector>
#include <cstring>
#include <fstream>
#include <string>

#include "BearLibTerminal.h"
#include "game/lib/ECS/ECS.h"
// Components
#include "game/components/LocationComponent.h"
#include "game/components/SymbolComponent.h"

//Система, выводящая символы, которыми отображается сущность в консоль
class EntitiesDisplaySystem : public ecs::System {
 private:
  bool outputTextMod_{true}, outputTextModPrev_{true};
  int spritesLoadOrUnload(std::vector<std::shared_ptr<ecs::Entity>>);

 public:
  EntitiesDisplaySystem();

  void updateSystem(ecs::World&) override;

  void setOutputMod(bool);
  bool getOutputMod();
  void switchMod();

  ~EntitiesDisplaySystem() override = default;
};
