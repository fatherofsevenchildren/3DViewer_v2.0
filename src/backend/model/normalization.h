#ifndef SRC__BACKEND__VIWER_MODEL__NORMALIZATION_H
#define SRC__BACKEND__VIWER_MODEL__NORMALIZATION_H

#include "../data/data.h"

namespace s21 {

class Normalization {
 public:
  Normalization() = delete;
  ~Normalization() = default;
  explicit Normalization(std::shared_ptr<ObjectData> data) : data_(data) {}

  void RunNormalization();

 private:
  std::shared_ptr<ObjectData> data_;

  void GetMinMax();
  void Scale(const double koef);
  void Centralization();
  long double MaxDifference();
};

}  // namespace s21

#endif  // SRC__BACKEND__VIWER_MODEL__NORMALIZATION_H