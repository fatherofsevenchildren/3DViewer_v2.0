#include "mainwindow.h"

// using namespace s21;

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  DefaultStart();
}

MainWindow::~MainWindow() {
  SaveSetts();
  delete ui;
}

void MainWindow::interface(bool a) { ui->tabWidget->setEnabled(a); }

void MainWindow::DefaultStart() {
  ui->widget->SetData(facade_.GetData());
  UiLoadSetter();
  InitSlots();
  try {
    facade_.LoadObject(last_file_);
    interface(true);
  } catch (std::invalid_argument &e) {
    HelpOpenFile();
  }
}

void MainWindow::ButtonOpenClicked() {
  std::string file =
      QFileDialog::getOpenFileName(this, "choose file",
                                   QCoreApplication::applicationDirPath(),
                                   "Text Files (*.obj)")
          .toStdString();
  if (!file.empty()) {
    facade_.LoadObject(file);
    interface(true);
    ui->label->setText(QString::fromStdString(file));
    ui->vectors->setText(
        "Vectors " +
        QString::number(facade_.GetData().get()->vectors.size() / 2));
    ui->vertex->setText(
        "Vertexes " +
        QString::number(facade_.GetData().get()->vertexes.size()));
  } else {
    HelpOpenFile();
    ui->label->setText("Error: invalid file");
  }

  ui->widget->update();
}

void MainWindow::HelpOpenFile() {
  QMessageBox::StandardButton my = QMessageBox::question(
      this, "Unable to read file", "Do u want try open other file?",
      QMessageBox::Yes | QMessageBox::No);
  if (my == QMessageBox::No) {
    interface(false);  // QCoreApplication::quit();
  } else {
    ButtonOpenClicked();
  }
}

void MainWindow::BackgroundColorButton_clicked() {
  QColor qcolor = QColorDialog::getColor(Qt::white, this);
  ui->widget->backColor = qcolor;
  ui->widget->update();
}
void MainWindow::VerticesColorButton_clicked() {
  QColor qcolor = QColorDialog::getColor(Qt::white, this);
  ui->widget->pointColor = qcolor;
  ui->widget->update();
}
void MainWindow::VectorsColorButton_clicked() {
  QColor qcolor = QColorDialog::getColor(Qt::white, this);
  ui->widget->lineColor = qcolor;
  ui->widget->update();
}

void MainWindow::CheckBoxLineClicked() {
  ui->widget->lines = ui->checkBox_ln->isChecked();
  ui->widget->update();
}
void MainWindow::LineDashedClicked(bool checked) {
  ui->widget->dashed = (checked) ? 1 : 0;
  ui->widget->update();
}
void MainWindow::LineWidhtSpinBoxChanged(double arg) {
  ui->widget->line_sz = arg;
  ui->widget->update();
}

void MainWindow::CheckBoxPointClicked() {
  ui->widget->points = ui->checkBox_pn->isChecked();
  ui->widget->update();
}
void MainWindow::PointTypeClicked() {
  ui->widget->point_type = ui->radio_sphere->isChecked();
  ui->widget->update();
}
void MainWindow::PointSizeSpinBoxChanged(double arg) {
  ui->widget->point_sz = arg;
  ui->widget->update();
}

void MainWindow::ProjectionTypeClicked() {
  if (ui->rb_central->isChecked()) {
    ui->widget->projection = true;
  } else if (ui->rb_parallel->isChecked()) {
    ui->widget->projection = false;
  }
  ui->widget->update();
}

void MainWindow::MoveXRight() {
  facade_.Move(s21::kX, 0.2);
  ui->widget->update();
}
void MainWindow::MoveXLeft() {
  facade_.Move(s21::kX, -0.2);
  ui->widget->update();
}
void MainWindow::MoveYUp() {
  facade_.Move(s21::kY, 0.2);
  ui->widget->update();
}
void MainWindow::MoveYDown() {
  facade_.Move(s21::kY, -0.2);
  ui->widget->update();
}
void MainWindow::MoveZOut() {
  facade_.Move(s21::kZ, -0.2);
  ui->widget->update();
}
void MainWindow::MoveZIn() {
  facade_.Move(s21::kZ, 0.2);
  ui->widget->update();
}

void MainWindow::RotateXRight() {
  facade_.Rotate(s21::kX, 1);
  ui->widget->update();
}
void MainWindow::RotateXLeft() {
  facade_.Rotate(s21::kX, -1);
  ui->widget->update();
}

void MainWindow::RotateYRight() {
  facade_.Rotate(s21::kY, 1);
  ui->widget->update();
}
void MainWindow::RotateYLeft() {
  facade_.Rotate(s21::kY, -1);
  ui->widget->update();
}
void MainWindow::RotateZRight() {
  facade_.Rotate(s21::kZ, 1);
  ui->widget->update();
}
void MainWindow::RotateZLeft() {
  facade_.Rotate(s21::kZ, -1);
  ui->widget->update();
}

void MainWindow::ModeScale(double val) {
  facade_.Scale(val);
  ui->widget->update();
}

void MainWindow::Undo() {
  facade_.UndoCommand();
  ui->widget->update();
}

void MainWindow::SaveSetts() {
  QSettings settings(
      QCoreApplication::applicationDirPath() + "/3d_settings.conf",
      QSettings::NativeFormat);
  settings.setValue("Colors/bg", ui->widget->backColor.name(QColor::HexArgb));
  settings.setValue("Colors/ln", ui->widget->lineColor.name(QColor::HexArgb));
  settings.setValue("Colors/pn", ui->widget->pointColor.name(QColor::HexArgb));
  settings.setValue("Size/point", ui->widget->point_sz);
  settings.setValue("Size/line", ui->widget->line_sz);
  settings.setValue("Proj/proj", ui->widget->projection);
  settings.setValue("Types/pn", ui->widget->point_type);
  settings.setValue("Types/ln", ui->widget->dashed);
  settings.setValue("Exist/pn", ui->widget->points);
  settings.setValue("Exist/ln", ui->widget->lines);
  settings.setValue("Last_file", ui->label->text());
}

void MainWindow::LoadSetts() {
  QSettings settings(
      QCoreApplication::applicationDirPath() + "/3d_settings.conf",
      QSettings::NativeFormat);
  ui->widget->backColor = settings.value("Colors/bg", color_bg_).toString();
  ui->widget->lineColor = settings.value("Colors/ln", color_line_).toString();
  ui->widget->pointColor = settings.value("Colors/pn", color_point_).toString();
  ui->widget->line_sz = settings.value("Size/line", 1).toInt();
  ui->widget->point_sz = settings.value("Size/point", 1).toInt();
  ui->widget->projection = settings.value("Proj/proj", 1).toInt();
  ui->widget->point_type = settings.value("Types/pn", 0).toInt();
  ui->widget->dashed = settings.value("Types/ln", 0).toInt();
  ui->widget->points = settings.value("Exist/pn", 0).toInt();
  ui->widget->lines = settings.value("Exist/ln", 1).toInt();
//  last_file_ = settings.value("Last_file", QString::fromStdString(empty_))
//                   .toString()
//                   .toStdString();
}

void MainWindow::UiLoadSetter() {
  LoadSetts();
  ui->label->setText(QString::fromStdString(last_file_));
  if (ui->widget->projection) {
    ui->rb_central->setChecked(1);
  } else {
    ui->rb_parallel->setChecked(1);
  }

  UiPointsSetts();
  UiLineSetts();
}

void MainWindow::UiPointsSetts() {
  ui->pnSizeSpinBox->setValue(ui->widget->point_sz);

  if (!ui->widget->point_type) {
    ui->radio_cube->setChecked(1);
  } else {
    ui->radio_sphere->setChecked(1);
  }
  if (ui->widget->points) {
    ui->checkBox_pn->setChecked(1);
  } else {
    ui->checkBox_ln->setChecked(0);
  }
}

void MainWindow::UiLineSetts() {
  ui->lnWidthSpinBox->setValue(ui->widget->line_sz);

  if (ui->widget->lines) {
    ui->checkBox_ln->setChecked(1);
  } else {
    ui->checkBox_ln->setChecked(0);
  }
  if (ui->widget->dashed) {
    ui->checkBox_ln_2->setChecked(1);
  } else {
    ui->checkBox_ln_2->setChecked(0);
  }
}

void MainWindow::InitWindow() {
  LoadSetts();
  UiLoadSetter();
}

void MainWindow::InitSlots() {
  connect(ui->loadModelFileButton, SIGNAL(clicked()), this,
          SLOT(ButtonOpenClicked()));
  connect(ui->changeBGColorButton, SIGNAL(clicked()), this,
          SLOT(BackgroundColorButton_clicked()));
  connect(ui->verticesColorButton, SIGNAL(clicked()), this,
          SLOT(VerticesColorButton_clicked()));
  connect(ui->verticesColorButton, SIGNAL(clicked()), this,
          SLOT(VectorsColorButton_clicked()));

  connect(ui->radio_sphere, SIGNAL(clicked()), this, SLOT(PointTypeClicked()));
  connect(ui->radio_cube, SIGNAL(clicked()), this, SLOT(PointTypeClicked()));
  connect(ui->pnSizeSpinBox, SIGNAL(valueChanged(double)), this,
          SLOT(PointSizeSpinBoxChanged(double)));
  connect(ui->checkBox_pn, SIGNAL(clicked()), this,
          SLOT(CheckBoxPointClicked()));

  connect(ui->lnWidthSpinBox, SIGNAL(valueChanged(double)), this,
          SLOT(LineWidhtSpinBoxChanged(double)));
  connect(ui->checkBox_ln_2, SIGNAL(clicked(bool)), this,
          SLOT(LineDashedClicked(bool)));
  connect(ui->checkBox_ln, SIGNAL(clicked()), this,
          SLOT(CheckBoxLineClicked()));

  connect(ui->rb_central, SIGNAL(clicked()), this,
          SLOT(ProjectionTypeClicked()));
  connect(ui->rb_parallel, SIGNAL(clicked()), this,
          SLOT(ProjectionTypeClicked()));

  connect(ui->moveLeftButton, SIGNAL(clicked()), this, SLOT(MoveXLeft()));
  connect(ui->moveRightButton, SIGNAL(clicked()), this, SLOT(MoveXRight()));
  connect(ui->moveUpButton, SIGNAL(clicked()), this, SLOT(MoveYUp()));
  connect(ui->moveDownButton, SIGNAL(clicked()), this, SLOT(MoveYDown()));
  connect(ui->moveForwardButton, SIGNAL(clicked()), this, SLOT(MoveZIn()));
  connect(ui->moveBackwardButton, SIGNAL(clicked()), this, SLOT(MoveZOut()));

  connect(ui->dSpinBox_scale, SIGNAL(valueChanged(double)), this,
          SLOT(ModeScale(double)));

  connect(ui->rotateUpButton, SIGNAL(clicked()), this, SLOT(RotateXRight()));
  connect(ui->rotateDownButton, SIGNAL(clicked()), this, SLOT(RotateXLeft()));
  connect(ui->rotateRightButton, SIGNAL(clicked()), this, SLOT(RotateYRight()));
  connect(ui->rotateLeftButton, SIGNAL(clicked()), this, SLOT(RotateZLeft()));
  connect(ui->rotateClockwiseButton, SIGNAL(clicked()), this,
          SLOT(RotateZRight()));
  connect(ui->rotateCounterclockwiseButton, SIGNAL(clicked()), this,
          SLOT(RotateZLeft()));

  connect(ui->QuitButton, SIGNAL(clicked()), this, SLOT(Undo()));
  //    connect(ui->moveRightButton, SIGNAL(clicked()), this, SLOT(()));
}
