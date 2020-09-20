//
// Created by Battary on 25.03.2020.
//
#include "game/GameInit.h"

#include "BearLibTerminal.h"

std::unique_ptr<ecs::World> GameInit() {
  std::unique_ptr<ecs::World> world(new ecs::World(true));

  // Создаем персонажа
  world->createEntity<Player>();
  auto player = world->getEntity<Player>();
  player->addComponent<SymbolComponent>(0x40, "PrimaryKnight12x16.png, align=center", 6);
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

  world->createSystem<PlayerMovementSystem>();
  world->createSystem<EntitiesDisplaySystem>();
  world->createSystem<CollisionSystem>();
  world->createSystem<MapFormationSystem>(0);
  world->createSystem<KeyboardInputSystem>();
  world->createSystem<InterfaceUpdateSystem>();
  world->createSystem<InterfaceDisplaySystem>();
  world->createSystem<EnemiesLogicSystem>();
  world->createSystem<InventoryStatsSystem>();
  // Deprecated system
  // world->createSystem<CoinGenerationSystem>(1, 1, 2);

  // gcc doesn't support preprocessor directives. If you want to use DebugSystem, you'll need to uncomment the 64 str.
  // #if _DEBUG
  // world->createSystem<DebugSystem>();
  // #endif

  world->updateWorldList();

  return world;
}
