#ifndef SRC__BACKEND__VIWER_AFFINE_STRATEGY_H
#define SRC__BACKEND__VIWER_AFFINE_STRATEGY_H

//#include "./../controller/viwer_controller.h"
#include "./../data/data.h"
#include "./../model/affinne_model.h"

namespace s21 {

using shared_ptr_data = std::shared_ptr<ObjectData>;

class Strategy {
 public:
  virtual void Execute(shared_ptr_data& data, enum s21::Mode mode,
                       enum s21::Axis axis, const double val) = 0;

};  // class Strategy

class AffineStrategy : Strategy {
 public:
  void Execute(shared_ptr_data& data, enum s21::Mode mode, enum s21::Axis axis,
               const double val) override;

 private:
};  // class StrategyRotate

class Context {
 protected:
  AffineStrategy* operation_;

 public:
  Context() {}
  virtual ~Context() {}
  virtual void SetStrategy(AffineStrategy* op) = 0;
  virtual void ExecuteStrategy(shared_ptr_data& data, enum s21::Mode mode,
                               enum s21::Axis axis, const double val) = 0;
};

class User : public Context {
 public:
  void ExecuteStrategy(shared_ptr_data& data, enum s21::Mode mode,
                       enum s21::Axis axis, const double val) override {
    if (operation_) {
      operation_->Execute(data, mode, axis, val);
    }
  }

  void SetStrategy(AffineStrategy* op) override { operation_ = op; }
};
}  // namespace s21

#endif  // SRC__BACKEND__VIWER_AFFINE_STRATEGY_H
