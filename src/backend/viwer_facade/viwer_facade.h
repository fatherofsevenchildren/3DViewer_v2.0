#ifndef SRC__BACKEND__VIWER_FACADE_H
#define SRC__BACKEND__VIWER_FACADE_H

#include "./../controller/viwer_controller.h"
#include "./../model/viwer_model.h"
#include "./../viwer_command/viwer_command.h"

namespace s21 {

class ViwerFacade {
 public:
  ViwerFacade()
      : com_move_x_(&user_),
        com_move_y_(&user_),
        com_move_z_(&user_),
        com_rotate_x_(&user_),
        com_rotate_y_(&user_),
        com_rotate_z_(&user_),
        com_scale_(&user_) {
    user_.SetStrategy(&strategy_);
  }
  ~ViwerFacade() = default;

  std::shared_ptr<ObjectData> GetData() { return controller_.GetPointerData(); }

  void LoadObject(std::string &file_name) {
    controller_.SetData(file_name);
    invoker_.ClearHistory();
  }

  void Move(enum s21::Axis axis, const double val) {
    if (axis == s21::Axis::kX) {
      invoker_.SetCommand(&com_move_x_);
    } else if (axis == s21::Axis::kY) {
      invoker_.SetCommand(&com_move_y_);
    } else if (axis == s21::Axis::kZ) {
      invoker_.SetCommand(&com_move_z_);
    }
    invoker_.ExecCommand(controller_, val);
  }

  void Rotate(enum s21::Axis axis, const double val) {
    if (axis == s21::Axis::kX) {
      invoker_.SetCommand(&com_rotate_x_);
    } else if (axis == s21::Axis::kY) {
      invoker_.SetCommand(&com_rotate_y_);
    } else if (axis == s21::Axis::kZ) {
      invoker_.SetCommand(&com_rotate_z_);
    }
    invoker_.ExecCommand(controller_, val);
  }

  void Scale(const double koef) {
    invoker_.SetCommand(&com_scale_);
    invoker_.ExecCommand(controller_, koef);
  }

  void UndoCommand() { invoker_.UndoCommand(controller_.GetPointerData()); }

  // void Color();
  // void Projection();
  // void PointType();
  // void PointSize();
  // void LineType();
  // void LineSize();
  // void ColorBackground();
  // void ColorPoint();
  // void ColorLine();

  // void Screenshot();
  // void Screencast();

 private:
  ViwerController controller_;
  CommandInvoker invoker_;
  User user_;

  AffineStrategy strategy_;

  CommandMoveX com_move_x_;
  CommandMoveY com_move_y_;
  CommandMoveZ com_move_z_;

  CommandRotateX com_rotate_x_;
  CommandRotateY com_rotate_y_;
  CommandRotateZ com_rotate_z_;

  CommandScale com_scale_;

};  // class ViwerFacade

}  // namespace s21

#endif  // SRC__BACKEND__VIWER_FACADE_H
