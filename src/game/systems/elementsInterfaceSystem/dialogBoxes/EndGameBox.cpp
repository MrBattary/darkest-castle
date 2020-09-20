//
// Created by Battary on 04.08.2020.
//

#include "game/systems/elementsInterfaceSystem/dialogBoxes/EndGameBox.h"
EndGameBox::EndGameBox(ecs::World & world) {
  setVariables(31, 10, 16, 3, "");

  name_ = "Game over";
  reqUpdNumbers_ = {1};

  auto keyboardSys = world.getSystem<KeyboardInputSystem>();
  dialogKeys_[1] = std::make_pair("Repeat:", keyboardSys->getKeyName("Continue"));
  dialogKeys_[2] = std::make_pair("Exit:", keyboardSys->getKeyName("Exit"));

  auto interfaceSys = world.getSystem<InterfaceUpdateSystem>();
  interfaceSys->hideAllExcept({"End level", "Leaderboard"});

  auto outputSys = world.getSystem<EntitiesDisplaySystem>();
  auto playerMoveSys = world.getSystem<PlayerMovementSystem>();
  auto enemiesLogicSys = world.getSystem<EnemiesLogicSystem>();
  enemiesLogicSys->setInactive(true);
  playerMoveSys->setInactive(true);
  outputSys->setInactive(true);

  auto player = world.getEntity<Player>();
  auto statisticsComp = player->getComponent<StatisticsComponent>();

  elementData_ = "Game over\nSteps: " + std::to_string(statisticsComp->steps_) +
                 "\nCoins: " + std::to_string(statisticsComp->coins_) + "\n";
  for (auto it = dialogKeys_.begin(); it != dialogKeys_.end(); ++it) {
    elementData_ += it->second.first + " " + (it->second.second);
    if (it != std::prev(dialogKeys_.end(), 1)) {
      elementData_ += "\n";
    }
  }

  calculateBoxSize(elementData_);

  interfaceSys->blockNewWindows();
  expendable_ = false;
}

void EndGameBox::updateElement(ecs::World & world) {
  auto interfaceSys = world.getSystem<InterfaceUpdateSystem>();
  if (interfaceSys->getCommand() == "Exit") {
    world.terminateApplication();
  }
  if (interfaceSys->getCommand() =="Continue") {
    expendable_ = true;
    interfaceSys->deleteElement("Leaderboard");
    interfaceSys->unhideAllExcept({});
    interfaceSys->unblockNewWindows();
    interfaceSys->setCommand("");
    auto inputSys = world.getSystem<KeyboardInputSystem>();
    inputSys->skipInput();

    world.clearEntities();
    world.resetLastEntityID();
    world.purgeSystem(2);
    world.purgeSystem(100);
    world.purgeSystem(200);
    world.purgeSystem(300);
    world.purgeSystem(500);
    world.purgeSystem(1000);
    world.updateWorldList();

    // Создаем персонажа
    world.createEntity<Player>();
    auto player = world.getEntity<Player>();
    player->addComponent<SymbolComponent>(0x40, "PrimaryKnight12x16.png, align=center", 5);
    player->addComponent<LocationComponent>(2, 2);
    player->addComponent<PreviousLocationComponent>();
    player->addComponent<DirectionComponent>();
    player->addComponent<ControlComponent>();
    player->addComponent<StatisticsComponent>();
    player->addComponent<StatsComponent>();
    auto chComp = player->getComponent<StatsComponent>();
    chComp->addStat("+Attack", 0);
    chComp->addStat("+Defence", 0);
    chComp->addStat("+Health", 0);
    chComp->addStat("Attack", 1);
    chComp->addStat("Defence", 1);
    chComp->addStat("Health", 30);
    chComp->addStat("Damage", 0);

    // Создаем базовые предметы персонажу
    // Оружие
    auto knightsSword = std::make_shared<Item>();
    knightsSword->setEntityName("Knight's sword");
    knightsSword->addComponent<StatsComponent>();
    auto swordStComp = knightsSword->getComponent<StatsComponent>();
    swordStComp->addStat("Attack", 5);
    // Броня
    auto knightsArmor = std::make_shared<Item>();
    knightsArmor->setEntityName("Knight's armor");
    knightsArmor->addComponent<StatsComponent>();
    auto armorStComp = knightsArmor->getComponent<StatsComponent>();
    armorStComp->addStat("Attack", -1);
    armorStComp->addStat("Defence", 4);
    // Выдаем базовые предметы персонажу
    player->addComponent<InventoryComponent>();
    auto invComp = player->getComponent<InventoryComponent>();
    invComp->items_.insert(std::make_pair("Weapon", std::move(knightsSword)));
    invComp->items_.insert(std::make_pair("Armor", std::move(knightsArmor)));

    world.createSystem<PlayerMovementSystem>();
    world.createSystem<EntitiesDisplaySystem>();
    world.createSystem<CollisionSystem>();
    world.createSystem<MapFormationSystem>(0);
    world.createSystem<EnemiesLogicSystem>();
    world.createSystem<InventoryStatsSystem>();

    world.updateWorldList();
  }
}
