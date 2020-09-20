//
// Created by Battary on 30.07.2020.
//

#include "game/systems/mapFormationSubsystems/constructors/enemiesTypes/RedEnemy.h"

void RedEnemy::createEnemy(std::shared_ptr<Enemy>& enemy) {
  enemy->addComponent<SymbolComponent>(0x00c8, "RedKnight12x16.png, align=center", 4);
  enemy->addComponent<EnemyLogicComponent>(3);
  auto hostilesComp = enemy->getComponent<EnemyLogicComponent>();
  hostilesComp->hostiles_.push_back("Player");

  enemy->addComponent<StatsComponent>();
  auto stComp = enemy->getComponent<StatsComponent>();
  stComp->addStat("+Attack", 0);
  stComp->addStat("+Defence", 0);
  stComp->addStat("+Health", 0);
  stComp->addStat("Attack", 1);
  stComp->addStat("Defence", 1);
  stComp->addStat("Health", 5);
  stComp->addStat("Damage", 0);

  auto poorSword = std::make_shared<Item>();
  poorSword->setEntityName("Poor sword");
  poorSword->addComponent<StatsComponent>();
  auto swordStComp = poorSword->getComponent<StatsComponent>();
  swordStComp->addStat("Attack", 1);

  enemy->addComponent<InventoryComponent>();
  auto invComp = enemy->getComponent<InventoryComponent>();
  invComp->items_.insert(std::make_pair("Weapon", std::move(poorSword)));
}
