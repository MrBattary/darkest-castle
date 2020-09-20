//
// Created by Battary on 26.03.2020.
//

#include "game/systems/EntitiesDisplaySystem.h"

EntitiesDisplaySystem::EntitiesDisplaySystem() {
  setID(1000);
  addProcessedComponents(100, 200);
}

int EntitiesDisplaySystem::spritesLoadOrUnload(std::vector<std::shared_ptr<ecs::Entity>> entities) {
  if (outputTextMod_) {
    for (auto ent : entities) {
      auto symbolComp = ent->getComponent<SymbolComponent>();
      std::string value {std::to_string(symbolComp->symbol_) + ": none"};
      terminal_set(value.c_str());
    }
  } else {
    std::string workingPath {};
    std::string tilePathWindows {"..\\data\\sprites\\"};
    std::string tilePathLinux {"../data/sprites/"};
    std::string tilePathCMake {"data/sprites/"};

    std::ifstream stream;
    stream.open(tilePathWindows + "readme.txt", std::ios::in);
    if (!stream.is_open()) {
      stream.clear();
      stream.open(tilePathLinux + "readme.txt", std::ios::in);
      if (!stream.is_open()) {
        stream.clear();
        stream.open(tilePathCMake + "readme.txt", std::ios::in);
        if (!stream.is_open()) {
          return 1;
        } else {
          workingPath = tilePathCMake;
        }
      } else {
        workingPath = tilePathLinux;
      }
    } else {
      workingPath = tilePathWindows;
    }
    stream.close();

    for (auto ent : entities) {
      auto symbolComp = ent->getComponent<SymbolComponent>();
      std::string value{std::to_string(symbolComp->symbol_) + ": " + workingPath + symbolComp->spriteData_};
      terminal_set(value.c_str());
    }
  }
  return 0;
}

void EntitiesDisplaySystem::updateSystem(ecs::World &world) {
  // TODO(Battary): Доработать отрисовку, чтобы не было каждый раз полной отрисовки заново
  auto entities = world.getListEntities(getID());
  if (outputTextMod_ != outputTextModPrev_) {
    if (spritesLoadOrUnload(entities)) world.terminateApplication();
  }
  for (auto ent : entities) {
    auto locationComp = ent->getComponent<LocationComponent>();
    auto symbolComp = ent->getComponent<SymbolComponent>();
    auto basicLayer = terminal_state(TK_LAYER);
    terminal_layer(symbolComp->layer_);
    terminal_put(locationComp->column_, locationComp->row_, symbolComp->symbol_);
    terminal_layer(basicLayer);
  }
  outputTextModPrev_ = outputTextMod_;
}

void EntitiesDisplaySystem::setOutputMod(bool mod) {
  outputTextMod_ = mod;
}

bool EntitiesDisplaySystem::getOutputMod() {
  return outputTextMod_;
}

void EntitiesDisplaySystem::switchMod() {
  outputTextMod_ = !outputTextMod_;
}
