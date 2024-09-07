#include "viwer_model.h"

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace s21 {

void ViwerModel::setValue(std::string file_name) {
  std::ifstream file(file_name);
  if (!file.is_open()) throw std::invalid_argument("file unfind");
  std::string current_line;
  while (std::getline(file, current_line)) {
    current_line += ' ';
    if (current_line.size() > 6 && current_line[0] == 'v' &&
        current_line[1] == ' ') {
      for (auto it = (current_line.begin() + 2); it != current_line.end();
           ++it) {
        if (isdigit(*it) || *it == '-') {
          std::string digit;
          while (isdigit(*it) || *it == '.' || *it == '-') {
            digit.push_back(*it);
            it++;
          }
          data->vertexes.push_back(std::stod(digit));
        }
      }
    } else if (current_line.size() > 4 && current_line[0] == 'f' &&
               current_line[1] == ' ') {
      int first = 0, first_count = 0;
      for (auto it = (current_line.begin() + 2); it != current_line.end();
           ++it) {
        if (isdigit(*it)) {
          if (first) first_count++;
          std::string digit;
          while (isdigit(*it)) {
            digit.push_back(*it);
            it++;
          }
          data->vectors.push_back(std::stoi(digit));
          while (*it != ' ') {
            it++;
          }
          if (first_count) data->vectors.push_back(data->vectors.back());
          if (first == 0) first = std::stoi(digit);
        }
      }
      data->vectors.push_back(first);
    }
  }
  file.close();
  if (data->vertexes.size() < 4) error++;
  data->vectors.shrink_to_fit();
  data->vertexes.shrink_to_fit();
}

void ViwerModel::verts4vecs() {
  data->vecs.clear();
  int vect = 0;
  for (long unsigned int i = 0; i < data->vectors.size(); i++) {
    int vr = data->vectors[vect];
    data->vecs.push_back(data->vertexes[vr * 3 - 3]);
    data->vecs.push_back(data->vertexes[vr * 3 - 2]);
    data->vecs.push_back(data->vertexes[vr * 3 - 1]);
    vect++;
  }
}

void ViwerModel::resetData() {
  data->vecs.clear();
  data->vertexes.clear();
  data->vectors.clear();
  data->x_max = data->x_min = data->y_max = data->y_min = data->z_max =
      data->z_min = 0;
      error = 0;
}

int ViwerModel::getError() { return error; }
}  // namespace s21
