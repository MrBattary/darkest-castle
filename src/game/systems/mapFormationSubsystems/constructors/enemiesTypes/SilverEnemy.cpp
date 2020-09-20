//
// Created by Battary on 04.08.2020.
//

#include "game/systems/mapFormationSubsystems/constructors/enemiesTypes/SilverEnemy.h"
void SilverEnemy::createEnemy(std::shared_ptr<Enemy>& enemy) {
  enemy->addComponent<SymbolComponent>(0x00ca, "SilKnight12x16.png, align=center", 5);
  enemy->addComponent<EnemyLogicComponent>(5);
  auto hostilesComp = enemy->getComponent<EnemyLogicComponent>();
  hostilesComp->hostiles_.push_back("Player");

  enemy->addComponent<StatsComponent>();
  auto stComp = enemy->getComponent<StatsComponent>();
  stComp->addStat("+Attack", 0);
  stComp->addStat("+Defence", 0);
  stComp->addStat("+Health", 0);
  stComp->addStat("Attack", 1);
  stComp->addStat("Defence", 1);
  stComp->addStat("Health", 50);
  stComp->addStat("Damage", 0);

  auto eliteSword = std::make_shared<Item>();
  eliteSword->setEntityName("Elite sword");
  eliteSword->addComponent<StatsComponent>();
  auto swordStComp = eliteSword->getComponent<StatsComponent>();
  swordStComp->addStat("Attack", 12);

  auto eliteArmor = std::make_shared<Item>();
  eliteArmor->setEntityName("Elite armor");
  eliteArmor->addComponent<StatsComponent>();
  auto armorStComp = eliteArmor->getComponent<StatsComponent>();
  armorStComp->addStat("Attack", -5);
  armorStComp->addStat("Defence", 10);

  enemy->addComponent<InventoryComponent>();
  auto invComp = enemy->getComponent<InventoryComponent>();
  invComp->items_.insert(std::make_pair("Weapon", std::move(eliteSword)));
  invComp->items_.insert(std::make_pair("Armor", std::move(eliteArmor)));
}
