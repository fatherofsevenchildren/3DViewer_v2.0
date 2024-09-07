#ifndef SRC__BACKEND__MODEL__AFFINNE_MODEL_H
#define SRC__BACKEND__MODEL__AFFINNE_MODEL_H

#include "../data/data.h"

namespace s21 {

class Affinne {
 public:
  Affinne() = delete;
  ~Affinne() = default;
  explicit Affinne(std::shared_ptr<ObjectData> data) : data_(data) {}

  void Moving(enum Axis axis, const double distance);
  void ModeRotate(enum Axis axis, const double angle);
  void RotateX(const double angle);
  void RotateY(const double angle);
  void RotateZ(const double angle);
  void ModeScale(double koef);

 private:
  std::shared_ptr<ObjectData> data_;
};

}  // namespace s21

#endif  // SRC__BACKEND__MODEL__AFFINNE_MODEL_H