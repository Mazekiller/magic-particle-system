#include "EnemyBase.hpp"

Enemy::Enemy(const float hitPoints, const float sp)
  :Characters(sp), HitPoints(hitPoints), BeingAttacked(false)
{}

Enemy::~Enemy() {}

float Enemy::getHitPoints() const { return HitPoints; }

bool Enemy::isDead() { if (HitPoints <= EPSILON) return true;  return false; } ///La solucion loca terminaba siendo mas cara al final.



