

#include "normalization.h"

#include "affinne_model.h"

namespace s21 {
void Normalization::RunNormalization() {
  GetMinMax();
  Centralization();
  Scale(0.5);
  GetMinMax();
}
void Normalization::GetMinMax() {
  data_.get()->x_max = data_.get()->x_min = data_.get()->vertexes[0];
  data_.get()->y_max = data_.get()->y_min = data_.get()->vertexes[1];
  data_.get()->z_max = data_.get()->z_min = data_.get()->vertexes[2];
  for (unsigned long int i = 3; i < data_.get()->vertexes.size(); i++) {
    if (!(i % 3)) {
      if (data_.get()->vertexes[i] > data_.get()->x_max)
        data_.get()->x_max = data_.get()->vertexes[i];
      if (data_.get()->vertexes[i] < data_.get()->x_min)
        data_.get()->x_min = data_.get()->vertexes[i];
    } else if (i % 3 == 1) {
      if (data_.get()->vertexes[i] > data_.get()->y_max)
        data_.get()->y_max = data_.get()->vertexes[i];
      if (data_.get()->vertexes[i] < data_.get()->y_min)
        data_.get()->y_min = data_.get()->vertexes[i];
    } else {
      if (data_.get()->vertexes[i] > data_.get()->z_max)
        data_.get()->z_max = data_.get()->vertexes[i];
      if (data_.get()->vertexes[i] < data_.get()->z_min)
        data_.get()->z_min = data_.get()->vertexes[i];
    }
  }
}
void Normalization::Scale(const double koef) {
  Affinne affine(data_);
  long double max_dif = MaxDifference();
  long double scal = (koef * 2) / max_dif;
  affine.ModeScale(scal);
}
void Normalization::Centralization() {
  Affinne affine(data_);
  affine.Moving(Axis::kX, 0 - data_.get()->x_max - data_.get()->x_min);
  affine.Moving(Axis::kY, 0 - data_.get()->y_max - data_.get()->y_min);
  affine.Moving(Axis::kZ, 0 - data_.get()->z_max - data_.get()->z_min);
}
long double Normalization::MaxDifference() {
  long double res = data_.get()->x_max - data_.get()->x_min;
  if ((data_.get()->y_max - data_.get()->y_min) > res)
    res = data_.get()->y_max - data_.get()->y_min;
  if ((data_.get()->z_max - data_.get()->z_min) > res)
    res = data_.get()->z_max - data_.get()->z_min;
  return res;
}

}  // namespace s21
