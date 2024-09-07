#ifndef SRC__BACKEND__VIWER_COMMAND_H
#define SRC__BACKEND__VIWER_COMMAND_H

#include <list>

#include "../affine_strategy/viwer_affine_strategy.h"
#include "../controller/viwer_controller.h"

namespace s21 {

const short int kMaxOldDataSize = 15;
using shared_ptr_data = std::shared_ptr<struct ObjectData>;

class ViwerCommand {
 public:
  virtual ~ViwerCommand() = default;
  virtual void Execute(ViwerController &cont, const double angle) = 0;
  virtual void UnExecute(shared_ptr_data data) = 0;
  virtual void ClearHistory() = 0;

 protected:
  std::list<struct ObjectData> list_data_;

};  // class ViewCommand

class CommandRotateX : public ViwerCommand {
 public:
  CommandRotateX(User *context) : context_(context) {}
  void Execute(ViwerController &cont, const double val) override {
    if (list_data_.size() == kMaxOldDataSize) list_data_.pop_front();
    list_data_.push_back(*(cont.GetPointerData().get()));
    context_->ExecuteStrategy(cont.GetPointerData(), s21::kRotate, s21::kX,
                              val);
    cont.verts4vecs();
  }

  void UnExecute(shared_ptr_data data) override {
    if (!list_data_.empty()) {
      *data.get() = list_data_.back();
      list_data_.pop_back();
    }
  }
  void ClearHistory() override { list_data_.clear(); }

 private:
  User *context_;

};  // class CommandRotateX

class CommandRotateY : public ViwerCommand {
 public:
  CommandRotateY(User *context) : context_(context) {}
  void Execute(ViwerController &cont, const double val) override {
    if (list_data_.size() == kMaxOldDataSize) list_data_.pop_front();
    list_data_.push_back(*(cont.GetPointerData().get()));
    context_->ExecuteStrategy(cont.GetPointerData(), s21::kRotate, s21::kY,
                              val);
    cont.verts4vecs();
  }
  void UnExecute(shared_ptr_data data) override {
    if (!list_data_.empty()) {
      *data.get() = list_data_.back();
      list_data_.pop_back();
    }
  }
  void ClearHistory() override { list_data_.clear(); }

 private:
  User *context_;

};  // class CommandRotateY

class CommandRotateZ : public ViwerCommand {
 public:
  CommandRotateZ(User *context) : context_(context) {}
  void Execute(ViwerController &cont, const double val) override {
    if (list_data_.size() == kMaxOldDataSize) list_data_.pop_front();
    list_data_.push_back(*(cont.GetPointerData().get()));
    context_->ExecuteStrategy(cont.GetPointerData(), s21::kRotate, s21::kZ,
                              val);
    cont.verts4vecs();
  }
  void UnExecute(shared_ptr_data data) override {
    if (!list_data_.empty()) {
      *data.get() = list_data_.back();
      list_data_.pop_back();
    }
  }
  void ClearHistory() override { list_data_.clear(); }

 private:
  User *context_;

};  // class CommandRotateZ

class CommandMoveX : public ViwerCommand {
 public:
  CommandMoveX(User *context) : context_(context) {}
  void Execute(ViwerController &cont, const double val) override {
    if (list_data_.size() == kMaxOldDataSize) list_data_.pop_front();
    list_data_.push_back(*(cont.GetPointerData().get()));
    context_->ExecuteStrategy(cont.GetPointerData(), s21::kMove, s21::kX, val);
    cont.verts4vecs();
  }
  void UnExecute(shared_ptr_data data) override {
    if (!list_data_.empty()) {
      *data.get() = list_data_.back();
      list_data_.pop_back();
    }
  }
  void ClearHistory() override { list_data_.clear(); }

 private:
  User *context_;

};  // class CommandMoveX

class CommandMoveY : public ViwerCommand {
 public:
  CommandMoveY(User *context) : context_(context) {}
  void Execute(ViwerController &cont, const double val) override {
    if (list_data_.size() == kMaxOldDataSize) list_data_.pop_front();
    list_data_.push_back(*(cont.GetPointerData().get()));
    context_->ExecuteStrategy(cont.GetPointerData(), s21::kMove, s21::kY, val);
    cont.verts4vecs();
  }
  void UnExecute(shared_ptr_data data) override {
    if (!list_data_.empty()) {
      *data.get() = list_data_.back();
      list_data_.pop_back();
    }
  }
  void ClearHistory() override { list_data_.clear(); }

 private:
  User *context_;

};  // class CommandMoveY

class CommandMoveZ : public ViwerCommand {
 public:
  CommandMoveZ(User *context) : context_(context) {}
  void Execute(ViwerController &cont, const double val) override {
    if (list_data_.size() == kMaxOldDataSize) list_data_.pop_front();
    list_data_.push_back(*(cont.GetPointerData().get()));
    context_->ExecuteStrategy(cont.GetPointerData(), s21::kMove, s21::kZ, val);
    cont.verts4vecs();
  }
  void UnExecute(shared_ptr_data data) override {
    if (!list_data_.empty()) {
      *data.get() = list_data_.back();
      list_data_.pop_back();
    }
  }
  void ClearHistory() override { list_data_.clear(); }

 private:
  User *context_;

};  // class CommandMoveZ

class CommandScale : public ViwerCommand {
 public:
  CommandScale(User *context) : context_(context) {}
  void Execute(ViwerController &cont, const double val) override {
    if (list_data_.size() == kMaxOldDataSize) list_data_.pop_front();
    list_data_.push_back(*(cont.GetPointerData().get()));
    context_->ExecuteStrategy(cont.GetPointerData(), s21::kScale, s21::kX, val);
    cont.verts4vecs();
  }
  void UnExecute(shared_ptr_data data) override {
    if (!list_data_.empty()) {
      *data.get() = list_data_.back();
      list_data_.pop_back();
    }
  }
  void ClearHistory() override { list_data_.clear(); }

 private:
  User *context_;

};  // class CommandMoveZ

class CommandInvoker {
 public:
  CommandInvoker() : command_(nullptr) {}
  ~CommandInvoker() = default;
  void SetCommand(ViwerCommand *command) { command_ = command; }
  void ExecCommand(ViwerController &cont, const double val) {
    if (command_) {
      command_->Execute(cont, val);
    }
  }
  void UndoCommand(shared_ptr_data data) {
    if (command_) {
      command_->UnExecute(data);
    }
  }

  void ClearHistory() {
    if (command_) {
      command_->ClearHistory();
    }
  }

 private:
  ViwerCommand *command_;
};  // class CommandInvoker

}  // namespace s21

#endif  // SRC__BACKEND__VIWER_COMMAND_H