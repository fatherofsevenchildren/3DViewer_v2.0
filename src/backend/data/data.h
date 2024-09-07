#ifndef SRC__BACKEND__DATA__DATA_H
#define SRC__BACKEND__DATA__DATA_H

#include <stdio.h>

#include <iostream>
#include <memory>
#include <vector>

#include "math.h"

namespace s21 {

enum Axis { kX, kY, kZ };
enum Mode { kMove, kRotate, kScale };

struct ObjectData {
  std::vector<double> vertexes;  // Вершины
  std::vector<int> vectors;
  std::vector<double> vecs;  // Координаты
  double x_min;
  double x_max;
  double y_min;
  double y_max;
  double z_min;
  double z_max;
};

}  // namespace s21

#endif  // SRC__BACKEND__DATA__DATA_H
