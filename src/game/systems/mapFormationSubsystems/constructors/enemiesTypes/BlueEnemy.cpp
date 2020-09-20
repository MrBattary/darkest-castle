//
// Created by Battary on 04.08.2020.
//

#include "game/systems/mapFormationSubsystems/constructors/enemiesTypes/BlueEnemy.h"
void BlueEnemy::createEnemy(std::shared_ptr<Enemy>& enemy) {
  enemy->addComponent<SymbolComponent>(0x00c9, "BluKnight12x16.png, align=center", 5);
  enemy->addComponent<EnemyLogicComponent>(4);
  auto hostilesComp = enemy->getComponent<EnemyLogicComponent>();
  hostilesComp->hostiles_.push_back("Player");

  enemy->addComponent<StatsComponent>();
  auto stComp = enemy->getComponent<StatsComponent>();
  stComp->addStat("+Attack", 0);
  stComp->addStat("+Defence", 0);
  stComp->addStat("+Health", 0);
  stComp->addStat("Attack", 1);
  stComp->addStat("Defence", 1);
  stComp->addStat("Health", 10);
  stComp->addStat("Damage", 0);

  auto regularSword = std::make_shared<Item>();
  regularSword->setEntityName("Regular sword");
  regularSword->addComponent<StatsComponent>();
  auto swordStComp = regularSword->getComponent<StatsComponent>();
  swordStComp->addStat("Attack", 3);

  auto regularArmor = std::make_shared<Item>();
  regularArmor->setEntityName("Regular armor");
  regularArmor->addComponent<StatsComponent>();
  auto armorStComp = regularArmor->getComponent<StatsComponent>();
  armorStComp->addStat("Attack", -1);
  armorStComp->addStat("Defence", 2);

  enemy->addComponent<InventoryComponent>();
  auto invComp = enemy->getComponent<InventoryComponent>();
  invComp->items_.insert(std::make_pair("Weapon", std::move(regularSword)));
  invComp->items_.insert(std::make_pair("Armor", std::move(regularArmor)));
}
