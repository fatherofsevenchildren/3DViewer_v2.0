#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QColorDialog>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QSettings>
#include <QTextEdit>
#include <QtCore>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

//#include "../../backend/data/data.h"
#include "../../backend/viwer_facade/viwer_facade.h"
// namespace s21 {

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void DefaultStart();
  void InitSlots();

  void ButtonOpenClicked();
  void VerticesColorButton_clicked();
  void BackgroundColorButton_clicked();
  void VectorsColorButton_clicked();

  void PointTypeClicked();
  void PointSizeSpinBoxChanged(double arg);

  void CheckBoxPointClicked();
  void CheckBoxLineClicked();

  void LineWidhtSpinBoxChanged(double arg);
  void LineDashedClicked(bool checked);

  void ProjectionTypeClicked();

  void MoveXRight();
  void MoveXLeft();

  void MoveYUp();
  void MoveYDown();

  void MoveZOut();
  void MoveZIn();

  void RotateXRight();
  void RotateXLeft();
  void RotateYRight();
  void RotateYLeft();
  void RotateZRight();
  void RotateZLeft();

  void ModeScale(double val);

  void Undo();

 private:
  Ui::MainWindow *ui;
  s21::ViwerFacade facade_;
  QColor color_line_ = Qt::black, color_point_ = Qt::red, color_bg_ = Qt::white;
  std::string last_file_, empty_;

  void interface(bool a);
  void HelpOpenFile();

  void SaveSetts();
  void LoadSetts();
  void UiLoadSetter();
  void UiPointsSetts();
  void UiLineSetts();
  void InitWindow();
};

//}
#endif  // MAINWINDOW_H
