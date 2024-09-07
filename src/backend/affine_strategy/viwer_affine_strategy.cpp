#include "viwer_affine_strategy.h"

namespace s21 {
void AffineStrategy::Execute(shared_ptr_data& data, enum s21::Mode mode,
                             enum s21::Axis axis, const double val) {
  Affinne User(data);
  if (mode == s21::Mode::kMove)
    User.Moving(axis, val);
  else if (mode == s21::Mode::kRotate)
    User.ModeRotate(axis, val);
  else
    User.ModeScale(val);
}
}  // namespace s21
