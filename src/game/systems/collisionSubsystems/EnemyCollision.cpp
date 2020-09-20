//
// Created by Battary on 03.08.2020.
//

#include "game/systems/collisionSubsystems/EnemyCollision.h"

void EnemyCollision::updateData(ecs::World& world, std::shared_ptr<ecs::Entity> first,
                                std::shared_ptr<ecs::Entity> second) {
  auto playerPosComp = first->getComponent<LocationComponent>();
  auto playerPrevPosComp = first->getComponent<PreviousLocationComponent>();
  auto playerDirComp = first->getComponent<DirectionComponent>();
  auto playerInvComp = first->getComponent<InventoryComponent>();
  auto playerStatComp = first->getComponent<StatsComponent>();
  auto interfaceSys = world.getSystem<InterfaceUpdateSystem>();

  auto enemyPosComp = second->getComponent<LocationComponent>();
  auto enemyPrevPosComp = second->getComponent<PreviousLocationComponent>();
  auto enemyInvComp = second->getComponent<InventoryComponent>();
  auto enemyStatComp = second->getComponent<StatsComponent>();

  auto playerDamage = playerStatComp->getStat("+Attack")->value_ - enemyStatComp->getStat("+Defence")->value_;
  if (playerDamage < 1) playerDamage = 1;
  auto enemyDamage = enemyStatComp->getStat("+Attack")->value_ - playerStatComp->getStat("+Defence")->value_;
  if (enemyDamage < 1) enemyDamage = 1;

  int playerDamageTaken{0}, enemyDamageTaken{0};
  if (!interfaceSys->containElement("End level")) {
    playerStatComp->getStat("Damage")->value_ += enemyDamage;
    enemyStatComp->getStat("Damage")->value_ += playerDamage;
    playerDamageTaken = playerStatComp->getStat("Damage")->value_;
    enemyDamageTaken = enemyStatComp->getStat("Damage")->value_;

    auto logBox = interfaceSys->getElement<PlayerRealtimeLogBox>();
    logBox->addData("Damage [color=green]Dealt: " + std::to_string(playerDamage) + "[/color]");
    logBox->addData("[color=red] Received: " + std::to_string(enemyDamage) + "[/color] ");
  }

  if (playerDamageTaken >= playerStatComp->getStat("+Health")->value_) {
    world.purgeEntity(second->getID());
    if (!interfaceSys->containElement("End game")) interfaceSys->createElement<EndGameBox>(world);
    if (!interfaceSys->containElement("Leaderboard")) interfaceSys->createElement<LeaderboardBox>();
  } else {
    if (enemyDamageTaken > enemyStatComp->getStat("+Health")->value_) {
      world.purgeEntity(second->getID());
    } else {
      if (playerDirComp->direction_ == DirectionComponent::NOWHERE) {
        enemyPosComp->column_ = enemyPrevPosComp->columnPrevious_;
        enemyPosComp->row_ = enemyPrevPosComp->rowPrevious_;
      } else {
        if (playerDirComp->direction_ == DirectionComponent::UPWARD ||
            playerDirComp->direction_ == DirectionComponent::DOWNWARD) {
          playerPosComp->row_ = playerPrevPosComp->rowPrevious_;
        }
        if (playerDirComp->direction_ == DirectionComponent::LEFTWARD ||
            playerDirComp->direction_ == DirectionComponent::RIGHTWARD) {
          playerPosComp->column_ = playerPrevPosComp->columnPrevious_;
        }
      }
    }
  }
}

void EnemyCollision::updateSubsystem(ecs::World& world, std::shared_ptr<ecs::Entity> first,
                                     std::shared_ptr<ecs::Entity> second) {
  std::string firstName = first->getEntityName();
  std::string secondName = second->getEntityName();

  if (secondName == "Enemy") {
    updateData(world, first, second);
  } else {
    updateData(world, second, first);
  }
  world.updateWorldList();
}
