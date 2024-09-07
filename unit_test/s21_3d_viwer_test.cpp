#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <exception>

#include "./../src/backend/affine_strategy/viwer_affine_strategy.h"
#include "./../src/backend/model/viwer_model.h"

const std::string ktest_path = "./../objFiles";

TEST(OpenFile, NO_THROW) {
  s21::ViwerModel Model;
  EXPECT_NO_THROW(Model.setValue(ktest_path + "/cube.obj"));
}

TEST(OpenFile, THROW) {
  s21::ViwerModel Model;
  ASSERT_NO_THROW(Model.setValue(ktest_path));
}

TEST(Moving, MovingX) {
  s21::User User;
  s21::AffineStrategy Strategy;
  s21::ViwerModel Model;
  Model.setValue(ktest_path + "/testMoving.obj");
  User.SetStrategy(&Strategy);
  User.ExecuteStrategy(Model.getData(), s21::Mode::kMove, s21::Axis::kX, 1);
  Model.verts4vecs();
  std::string str = "1 0 0 1 0 0 ";
  std::string result;
  Model.printInStr(result);
  EXPECT_EQ(str, result);
}

TEST(Moving, MovingY) {
  s21::User User;
  s21::AffineStrategy Strategy;
  s21::ViwerModel Model;
  Model.setValue(ktest_path + "/testMoving.obj");
  User.SetStrategy(&Strategy);
  User.ExecuteStrategy(Model.getData(), s21::Mode::kMove, s21::Axis::kY, 1);
  Model.verts4vecs();
  std::string str = "0 1 0 0 1 0 ";
  std::string result;
  Model.printInStr(result);
  EXPECT_EQ(str, result);
}

TEST(Moving, MovingZ) {
  s21::User User;
  s21::AffineStrategy Strategy;
  s21::ViwerModel Model;
  Model.setValue(ktest_path + "/testMoving.obj");
  User.SetStrategy(&Strategy);
  User.ExecuteStrategy(Model.getData(), s21::Mode::kMove, s21::Axis::kZ, 1);
  Model.verts4vecs();
  std::string str = "0 0 1 0 0 1 ";
  std::string result;
  Model.printInStr(result);
  EXPECT_EQ(str, result);
}

TEST(Rotate, RotateX) {
  s21::User User;
  s21::AffineStrategy Strategy;
  s21::ViwerModel Model;
  Model.setValue(ktest_path + "/testRotate.obj");
  User.SetStrategy(&Strategy);
  User.ExecuteStrategy(Model.getData(), s21::Mode::kRotate, s21::Axis::kX, 360);
  Model.verts4vecs();
  std::string str =
      "0 0 0 1 0 0 1 0 0 1 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 1 0 0 0 0 0 "
      "0 0 0 0 -1 0 0 -1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 -1 0 0 -1 0 0 "
      "0 0 0 0 0 1 -1 0 1 -1 0 1 0 0 1 0 0 0 0 0 0 0 0 0 -1 0 0 -1 0 1 -1 0 1 "
      "-1 0 0 0 0 1 0 0 1 0 0 1 0 0 1 -1 0 1 -1 0 1 0 0 1 0 0 1 -1 0 1 -1 0 1 "
      "0 0 1 0 0 1 0 0 0 0 0 1 0 0 1 0 0 1 0 0 1 0 0 0 0 0 0 0 0 1 0 0 1 0 0 0 "
      "0 0 0 0 0 0 0 0 ";
  std::string result;
  Model.printInStr(result);
  EXPECT_EQ(str, result);
}

TEST(Rotate, RotateY) {
  s21::User User;
  s21::AffineStrategy Strategy;
  s21::ViwerModel Model;
  Model.setValue(ktest_path + "/testRotate.obj");
  User.SetStrategy(&Strategy);
  User.ExecuteStrategy(Model.getData(), s21::Mode::kRotate, s21::Axis::kY, 360);
  Model.verts4vecs();
  std::string str =
      "0 0 0 0 1 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 1 0 0 1 0 0 1 0 0 0 0 "
      "0 0 0 0 1 0 0 1 0 0 1 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 1 0 0 0 0 "
      "0 1 0 -1 1 0 -1 1 0 0 1 0 0 1 0 0 1 0 0 1 0 0 1 0 0 1 0 -1 1 0 -1 1 0 0 "
      "1 0 0 0 0 0 1 0 0 1 0 -1 1 0 -1 1 0 0 0 0 0 0 0 -1 1 0 -1 1 0 -1 0 0 -1 "
      "0 0 0 0 0 0 0 0 0 0 0 0 0 0 -1 0 0 -1 0 0 0 0 0 0 0 0 -1 0 0 -1 0 0 0 0 "
      "0 0 0 0 0 0 0 ";
  std::string result;
  Model.printInStr(result);
  EXPECT_EQ(str, result);
}

TEST(Rotate, RotateZ) {
  s21::User User;
  s21::AffineStrategy Strategy;
  s21::ViwerModel Model;
  Model.setValue(ktest_path + "/testRotate.obj");
  User.SetStrategy(&Strategy);
  User.ExecuteStrategy(Model.getData(), s21::Mode::kRotate, s21::Axis::kZ, 360);
  Model.verts4vecs();
  std::string str =
      "0 0 0 -1 0 0 -1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 -1 0 0 -1 0 0 0 "
      "0 0 0 0 0 0 0 1 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 1 0 0 1 0 0 1 0 "
      "0 0 0 0 0 -1 0 1 -1 0 1 -1 0 0 -1 0 0 0 0 0 0 0 0 0 0 1 0 0 1 -1 0 1 -1 "
      "0 1 0 0 0 0 0 0 -1 0 0 -1 0 0 -1 0 1 -1 0 1 0 0 0 0 0 0 -1 0 1 -1 0 1 0 "
      "0 1 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 1 0 0 0 0 0 0 0 0 1 0 0 1 0 "
      "0 1 0 0 1 0 0 0 ";
  std::string result;
  Model.printInStr(result);
  EXPECT_EQ(str, result);
}

TEST(Scale, Scale) {
  s21::User User;
  s21::AffineStrategy Strategy;
  s21::ViwerModel Model;
  Model.setValue(ktest_path + "/testRotate.obj");
  User.SetStrategy(&Strategy);
  User.ExecuteStrategy(Model.getData(), s21::Mode::kScale, s21::Axis::kX, 360);
  Model.verts4vecs();
  std::string str =
      "0 0 0 720 720 0 720 720 0 720 0 0 720 0 0 0 0 0 0 0 0 0 720 0 0 720 0 "
      "720 720 0 720 720 0 0 0 0 0 0 0 0 720 720 0 720 720 0 720 0 0 720 0 0 0 "
      "0 0 0 0 0 0 720 0 0 720 0 720 720 0 720 720 0 0 0 0 720 0 720 720 720 "
      "720 720 720 720 720 0 720 720 0 0 720 0 0 720 0 0 720 720 0 720 720 720 "
      "720 720 720 720 720 0 720 0 720 0 0 720 720 0 720 720 0 720 720 720 720 "
      "720 720 720 0 0 720 0 0 720 720 720 720 720 720 720 0 720 720 0 720 720 "
      "0 0 0 0 0 720 0 0 720 0 0 720 0 720 720 0 720 0 0 0 0 0 0 720 0 720 720 "
      "0 720 0 0 720 0 0 720 0 0 0 ";
  std::string result;
  Model.printInStr(result);

  EXPECT_EQ(str, result);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::InitGoogleMock(&argc, argv);

  return RUN_ALL_TESTS();
}
