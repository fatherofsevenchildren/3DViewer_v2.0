#ifndef GLWIDGET_H
#define GLWIDGET_H

#define GL_SILENCE_DEPRECATION

#include <QColor>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QtGui>
#include <QtOpenGL>

/*extern "C" {
#include "../../back/parser.h"
}*/

#include "../../backend/viwer_facade/viwer_facade.h"

// namespace s21 {
class GLWidget : public QOpenGLFunctions, public QOpenGLWidget {
 public:
  QColor backColor, lineColor, pointColor;

  GLWidget();
  void SetData(std::shared_ptr<s21::ObjectData> input_data);
  explicit GLWidget(QWidget *parent = 0);
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void draw_lines();
  void draw_points();
  void change();
  void set_projection(bool projection);
  float x = 0, y = 0, z = 0;
  bool lines = 1, points = 0, point_type = 1, projection = 1, dashed = 0;
  int point_sz = 1, line_sz = 1;

 private:
  std::shared_ptr<s21::ObjectData> data_;
  float xRot, yRot, zRot;
  QPoint mPos;
  void mousePressEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;
};
//} // namespace s21
#endif  // GLWIDGET_H
