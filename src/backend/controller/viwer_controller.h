#ifndef SRC__BACKEND__VIWER_CONTROLLER_H
#define SRC__BACKEND__VIWER_CONTROLLER_H

#include "../model/normalization.h"
#include "../model/viwer_model.h"

// тестовые костыли
template <typename T>
void SetVector(std::vector<T> *vector, T *arr, const int size) {
  size_t size_arr = size;
  for (size_t i = 0; i < size_arr; i++) {
    vector->push_back(arr[i]);
  }
}

// тестовые костыли
template <typename T>
T *GetArrPointer(const std::vector<T> &vector) {
  T *arr = new T[vector.size()];
  for (size_t i = 0; i < vector.size(); i++) {
    // auto s = vector[i];
    // auto s = vector[i];
    arr[i] = vector[i];
  }
  return arr;
}

namespace s21 {

class ViwerController {
  using Model = ViwerModel;

 public:
  // ViwerController() : model_(new Model()) {}
  // ~ViwerController() { delete model_; }

  ViwerController() = default;
  ~ViwerController() = default;
  void SetData(std::string &file_name) {
    model_.resetData();
    model_.setValue(file_name);
    if (!model_.getError()) {
      Normalization norm(model_.getData());
      norm.RunNormalization();
      model_.verts4vecs();
    }
  }
  std::shared_ptr<ObjectData> &GetPointerData() { return model_.getData(); }

  void verts4vecs() { model_.verts4vecs(); }

 private:
  Model model_;

};  // class ViwerController

}  // namespace s21

#endif  // SRC__BACKEND__VIWER_CONTROLLER_H
