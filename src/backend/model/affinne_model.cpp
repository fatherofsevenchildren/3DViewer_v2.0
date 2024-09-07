#include "affinne_model.h"

namespace s21 {
void Affinne::Moving(enum Axis axis, const double distance) {
  long unsigned int i = 0,
                    j = (axis == Axis::kX) ? 0 : ((axis == Axis::kY) ? 1 : 2);
  while (i < data_->vertexes.size() - 2) {
    data_->vertexes[i + j] += distance;
    i += 3;
  }
}

void Affinne::ModeRotate(enum Axis axis, const double angle) {
  if (axis == Axis::kX)
    this->RotateX(angle);
  else if (axis == Axis::kY)
    this->RotateY(angle);
  else
    this->RotateZ(angle);
}

void Affinne::RotateX(const double angle) {
  for (long unsigned int i = 0; i < data_->vertexes.size() - 2; i += 3) {
    double tempY = data_->vertexes.at(i + 1);
    double tempZ = data_->vertexes.at(i + 2);
    data_->vertexes.at(i + 1) =
        std::cos(angle) * tempY - std::sin(angle) * tempZ;
    data_->vertexes.at(i + 2) =
        std::sin(angle) * tempY + std::cos(angle) * tempZ;
  }
}

void Affinne::RotateY(const double angle) {
  for (long unsigned int i = 0; i < data_->vertexes.size() - 2; i += 3) {
    double tempX = data_->vertexes.at(i);
    double tempZ = data_->vertexes.at(i + 2);
    data_->vertexes.at(i) = std::cos(angle) * tempX - std::sin(angle) * tempZ;
    data_->vertexes.at(i + 2) =
        std::sin(angle) * tempX + std::cos(angle) * tempZ;
  }
}

void Affinne::RotateZ(const double angle) {
  for (long unsigned int i = 0; i < data_->vertexes.size() - 2; i += 3) {
    double tempX = data_->vertexes.at(i);
    double tempY = data_->vertexes.at(i + 1);
    data_->vertexes.at(i) = std::cos(angle) * tempX - std::sin(angle) * tempY;
    data_->vertexes.at(i + 1) =
        std::sin(angle) * tempX + std::cos(angle) * tempY;
  }
}

void Affinne::ModeScale(double koef) {
  // static int i = 0;
  // static double a, b;
  // if (i == 0)
  // {
  //      a = 1;
  //      b = 1;
  // }
  // else
  // {
  // if (koef == 0) koef = 1;
  //     a = koef;
  //     b = b / a;
  // }

  static double old_koef = 0.5;
  double shift = koef / old_koef;
  old_koef = koef;
  for (unsigned long int i = 0; i < data_.get()->vertexes.size(); i++) {
    data_.get()->vertexes[i] *= shift;
  }
  // i++;
}
// double shift = scale_count / prev_scale;
// scaling(&ui->openGLWidget->data.VERTEXES, shift);
// prev_scale = scale_count;
// ui->openGLWidget->update();

}  // namespace s21
