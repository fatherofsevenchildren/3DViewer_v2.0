#ifndef SRC__BACKEND__VIWER_MODEL_H
#define SRC__BACKEND__VIWER_MODEL_H


#include "../data/data.h"

namespace s21 {

class ViwerModel {
 public:
  ViwerModel() : data(std::make_shared<ObjectData>()) {}
  ~ViwerModel() { resetData(); }
  void resetData();
  void setValue(std::string file_name);
  void verts4vecs();
  std::shared_ptr<ObjectData>& getData() { return data; }
  int getError();

  void printInStr(std::string& str) {
    for (auto it = (data->vecs.begin()); it != data->vecs.end(); ++it) {
      std::string ch = std::to_string((int)*it);
      str.append(ch);
      str.push_back(' ');
    }
  }

 private:
  int error = 0;
  std::shared_ptr<ObjectData> data;
};

}  // namespace s21

#endif  // SRC__BACKEND__VIWER_MODEL_H