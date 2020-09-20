//
// Created by Battary on 27.03.2020.
//

#include "game/lib/Random/Random.h"

int rnd::RandomBetweenInt(int a, int b) {
  std::random_device rd;                       //Недетерминированный генератор
  std::uniform_int_distribution<> dist(a, b);  //Задание границ генерации числа a <= с <= b
  int c = dist(rd);                            //Генерация
  return c;
}

double rnd::RandomBetweenDouble(double a, double b) {
  std::random_device rd;                        //Недетерминированный генератор
  std::uniform_real_distribution<> dist(a, b);  //Задание границ генерации числа a <= с <= b
  double c = dist(rd);                          //Генерация
  return c;
}

size_t rnd::RandomBetweenSizeT(size_t a, size_t b) {
  std::random_device rd;                             //Недетерминированный генератор
  std::uniform_int_distribution<size_t> dist(a, b);  //Задание границ генерации числа a <= с <= b
  size_t c = dist(rd);                               //Генерация
  return c;
}
