//
// Created by Battary on 27.03.2020.
//

#pragma once

#include <random>

namespace rnd {
//Возвращает целое случайное значение, между a и b, a < b
int RandomBetweenInt(int a, int b);

//Возвращает рациональное случайное значение, между a и b, a < b
double RandomBetweenDouble(double a, double b);

//Возвращает целое случайное 64битное значение, между a и b, a < b
size_t RandomBetweenSizeT(size_t a, size_t b);
}  // namespace rnd
