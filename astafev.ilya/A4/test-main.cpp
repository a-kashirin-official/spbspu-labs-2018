#define BOOST_TEST_MAIN

#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"
#include <boost/test/included/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(CompositeShape)
  const double Accuracy = 0.00001;

  BOOST_AUTO_TEST_CASE(Constructor)
  {
    BOOST_CHECK_THROW(astafev::CompositeShape testCompositeShape(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Constructor_Copying)
  {
    astafev::Rectangle rect1({5, 6},3, 4);
    astafev::Rectangle rect2( {9, 1}, 7, 8);
    astafev::Circle circ({12, 13},11);
    astafev::Rectangle rect3({6, 7},4, 1);
    std::shared_ptr<astafev::Shape> rectPtr1 = std::make_shared<astafev::Rectangle>(rect1);
    std::shared_ptr<astafev::Shape> rectPtr2 = std::make_shared<astafev::Rectangle>(rect2);
    std::shared_ptr<astafev::Shape> circPtr = std::make_shared<astafev::Circle>(circ);
    std::shared_ptr<astafev::Shape> rectPtr3 = std::make_shared<astafev::Rectangle>(rect3);
    astafev::CompositeShape testcompositeShape(rectPtr1);
    testcompositeShape.addElement(rectPtr2);
    testcompositeShape.addElement(circPtr);
    testcompositeShape.addElement(rectPtr3);

    astafev::CompositeShape testcompositeShape1(testcompositeShape);
    for (size_t i = 0; i < testcompositeShape.getSize(); ++i) {
      astafev::rectangle_t rectangle = testcompositeShape[i]->getFrameRect();
      astafev::rectangle_t rectangle1 = testcompositeShape1[i]->getFrameRect();
      BOOST_CHECK_EQUAL(rectangle.height, rectangle1.height);
      BOOST_CHECK_EQUAL(rectangle.width, rectangle1.width);
      BOOST_CHECK_EQUAL(rectangle.pos.x, rectangle1.pos.x);
      BOOST_CHECK_EQUAL(rectangle.pos.y, rectangle1.pos.y);
    }
  }

  BOOST_AUTO_TEST_CASE(Constructor_Moving)
  {
    astafev::Rectangle rect1({5, 6},3, 4);
    astafev::Rectangle rect2( {9, 1}, 7, 8);
    astafev::Circle circ({12, 13},11);
    astafev::Rectangle rect3({6, 7},4, 1);
    std::shared_ptr<astafev::Shape> rectPtr1 = std::make_shared<astafev::Rectangle>(rect1);
    std::shared_ptr<astafev::Shape> rectPtr2 = std::make_shared<astafev::Rectangle>(rect2);
    std::shared_ptr<astafev::Shape> circPtr = std::make_shared<astafev::Circle>(circ);
    std::shared_ptr<astafev::Shape> rectPtr3 = std::make_shared<astafev::Rectangle>(rect3);
    astafev::CompositeShape testcompositeShape(rectPtr1);
    testcompositeShape.addElement(rectPtr2);
    testcompositeShape.addElement(circPtr);
    testcompositeShape.addElement(rectPtr3);
    astafev::CompositeShape testcompositeShape1(testcompositeShape);
    astafev::CompositeShape testcompositeShape2(std::move(testcompositeShape));
    for (size_t i = 0; i < testcompositeShape2.getSize(); ++i) {
      astafev::rectangle_t rectangle = testcompositeShape1[i]->getFrameRect();
      astafev::rectangle_t rectangle1 = testcompositeShape2[i]->getFrameRect();
      BOOST_CHECK_EQUAL(rectangle.height, rectangle1.height);
      BOOST_CHECK_EQUAL(rectangle.width, rectangle1.width);
      BOOST_CHECK_EQUAL(rectangle.pos.x, rectangle1.pos.x);
      BOOST_CHECK_EQUAL(rectangle.pos.y, rectangle1.pos.y);
    }
  }

  BOOST_AUTO_TEST_CASE(Assignment_Copy)
  {
    astafev::Rectangle rect1({5, 6},3, 4);
    astafev::Rectangle rect2( {9, 1}, 7, 8);
    astafev::Circle circ({12, 13},11);
    astafev::Rectangle rect3({6, 7},4, 1);
    std::shared_ptr<astafev::Shape> rectPtr1 = std::make_shared<astafev::Rectangle>(rect1);
    std::shared_ptr<astafev::Shape> rectPtr2 = std::make_shared<astafev::Rectangle>(rect2);
    std::shared_ptr<astafev::Shape> circPtr = std::make_shared<astafev::Circle>(circ);
    std::shared_ptr<astafev::Shape> rectPtr3 = std::make_shared<astafev::Rectangle>(rect3);
    astafev::CompositeShape testcompositeShape(rectPtr1);
    testcompositeShape.addElement(rectPtr2);
    testcompositeShape.addElement(circPtr);
    testcompositeShape.addElement(rectPtr3);
    astafev::CompositeShape testcompositeShape1(rectPtr1);
    testcompositeShape1 = testcompositeShape;
    for (size_t i = 0; i < testcompositeShape.getSize(); ++i) {
      astafev::rectangle_t rectangle = testcompositeShape[i]->getFrameRect();
      astafev::rectangle_t rectangle1 = testcompositeShape1[i]->getFrameRect();
      BOOST_CHECK_EQUAL(rectangle.height, rectangle1.height);
      BOOST_CHECK_EQUAL(rectangle.width, rectangle1.width);
      BOOST_CHECK_EQUAL(rectangle.pos.x, rectangle1.pos.x);
      BOOST_CHECK_EQUAL(rectangle.pos.y, rectangle1.pos.y);
    }
  }

  BOOST_AUTO_TEST_CASE(Assignment_Move)
  {
    astafev::Rectangle rect1({5, 6},3, 4);
    astafev::Rectangle rect2( {9, 1}, 7, 8);
    astafev::Circle circ({12, 13},11);
    astafev::Rectangle rect3({6, 7},4, 1);
    std::shared_ptr<astafev::Shape> rectPtr1 = std::make_shared<astafev::Rectangle>(rect1);
    std::shared_ptr<astafev::Shape> rectPtr2 = std::make_shared<astafev::Rectangle>(rect2);
    std::shared_ptr<astafev::Shape> circPtr = std::make_shared<astafev::Circle>(circ);
    std::shared_ptr<astafev::Shape> rectPtr3 = std::make_shared<astafev::Rectangle>(rect3);
    astafev::CompositeShape testcompositeShape(rectPtr1);
    testcompositeShape.addElement(rectPtr2);
    testcompositeShape.addElement(circPtr);
    testcompositeShape.addElement(rectPtr3);
    astafev::CompositeShape testcompositeShape1(testcompositeShape);
    astafev::CompositeShape testcompositeShape2(rectPtr1);
    testcompositeShape2 = std::move(testcompositeShape);
    for (size_t i = 0; i < testcompositeShape2.getSize(); ++i) {
      astafev::rectangle_t rectangle = testcompositeShape1[i]->getFrameRect();
      astafev::rectangle_t rectangle1 = testcompositeShape2[i]->getFrameRect();
      BOOST_CHECK_EQUAL(rectangle.height, rectangle1.height);
      BOOST_CHECK_EQUAL(rectangle.width, rectangle1.width);
      BOOST_CHECK_EQUAL(rectangle.pos.x, rectangle1.pos.x);
      BOOST_CHECK_EQUAL(rectangle.pos.y, rectangle1.pos.y);
    }
  }

  BOOST_AUTO_TEST_CASE(Move_Test)
  {
    astafev::Rectangle rect1({1.5, 1.5},1, 1);
    astafev::Rectangle rect2({2.5, 2.5},1, 1);
    astafev::Rectangle rect3({3.5, 3.5},1, 1);
    std::shared_ptr<astafev::Shape> rectPtr1 = std::make_shared<astafev::Rectangle>(rect1);
    std::shared_ptr<astafev::Shape> rectPtr2 = std::make_shared<astafev::Rectangle>(rect2);
    std::shared_ptr<astafev::Shape> rectPtr3 = std::make_shared<astafev::Rectangle>(rect3);
    astafev::CompositeShape testCompositeShape(rectPtr1);
    testCompositeShape.addElement(rectPtr2);
    testCompositeShape.addElement(rectPtr3);
    testCompositeShape.move({15, 10});
    BOOST_CHECK_CLOSE(testCompositeShape.getFrameRect().pos.x, 15, Accuracy);
    BOOST_CHECK_CLOSE(testCompositeShape.getFrameRect().pos.y, 10, Accuracy);
  }


  BOOST_AUTO_TEST_CASE(Relative_Move_Test_CS)
  {
    astafev::Rectangle rect1({1.5, 1.5},1, 1);
    astafev::Rectangle rect2({2.5, 2.5},1, 1);
    astafev::Rectangle rect3({3.5, 3.5},1, 1);
    std::shared_ptr<astafev::Shape> rectPtr1 = std::make_shared<astafev::Rectangle>(rect1);
    std::shared_ptr<astafev::Shape> rectPtr2 = std::make_shared<astafev::Rectangle>(rect2);
    std::shared_ptr<astafev::Shape> rectPtr3 = std::make_shared<astafev::Rectangle>(rect3);
    astafev::CompositeShape testcompositeShape(rectPtr1);
    testcompositeShape.addElement(rectPtr2);
    testcompositeShape.addElement(rectPtr3);
    testcompositeShape.move(-1, 1);
    BOOST_CHECK_CLOSE(testcompositeShape.getFrameRect().pos.x, 1.5, Accuracy);
    BOOST_CHECK_CLOSE(testcompositeShape.getFrameRect().pos.y, 3.5, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(Area_Test_CS)
  {
    astafev::Rectangle rect1({1.5, 1.5},1, 1);
    astafev::Rectangle rect2({2.5, 2.5},1, 1);
    astafev::Rectangle rect3({3.5, 3.5},1, 1);
    std::shared_ptr<astafev::Shape> rectPtr1 = std::make_shared<astafev::Rectangle>(rect1);
    std::shared_ptr<astafev::Shape> rectPtr2 = std::make_shared<astafev::Rectangle>(rect2);
    std::shared_ptr<astafev::Shape> rectPtr3 = std::make_shared<astafev::Rectangle>(rect3);
    astafev::CompositeShape testcompositeShape(rectPtr1);
    testcompositeShape.addElement(rectPtr2);
    testcompositeShape.addElement(rectPtr3);
    BOOST_REQUIRE_EQUAL(testcompositeShape.getArea(), 3);
  }

  BOOST_AUTO_TEST_CASE(Area_Test_Move_CS)
  {
    astafev::Rectangle rect1({1.5, 1.5},1, 1);
    astafev::Rectangle rect2({2.5, 2.5},1, 1);
    astafev::Rectangle rect3({3.5, 3.5},1, 1);
    std::shared_ptr<astafev::Shape> rectPtr1 = std::make_shared<astafev::Rectangle>(rect1);
    std::shared_ptr<astafev::Shape> rectPtr2 = std::make_shared<astafev::Rectangle>(rect2);
    std::shared_ptr<astafev::Shape> rectPtr3 = std::make_shared<astafev::Rectangle>(rect3);
    astafev::CompositeShape testcompositeShape(rectPtr1);
    testcompositeShape.addElement(rectPtr2);
    testcompositeShape.addElement(rectPtr3);
    testcompositeShape.move(5, 5);
    BOOST_CHECK_EQUAL(testcompositeShape.getArea(), 3);
  }

  BOOST_AUTO_TEST_CASE(Frame_Rect_Test_CS)
  {
    astafev::Rectangle rect1({1.5, 1.5},1, 1);
    astafev::Rectangle rect2({2.5, 2.5},1, 1);
    astafev::Rectangle rect3({3.5, 3.5},1, 1);
    std::shared_ptr<astafev::Shape> rectPtr1 = std::make_shared<astafev::Rectangle>(rect1);
    std::shared_ptr<astafev::Shape> rectPtr2 = std::make_shared<astafev::Rectangle>(rect2);
    std::shared_ptr<astafev::Shape> rectPtr3 = std::make_shared<astafev::Rectangle>(rect3);
    astafev::CompositeShape testcompositeShape(rectPtr1);
    testcompositeShape.addElement(rectPtr2);
    testcompositeShape.addElement(rectPtr3);
    BOOST_CHECK_CLOSE_FRACTION(testcompositeShape.getFrameRect().pos.x, 2.5, Accuracy);
    BOOST_CHECK_CLOSE_FRACTION(testcompositeShape.getFrameRect().pos.y, 2.5, Accuracy);
    BOOST_CHECK_CLOSE_FRACTION(testcompositeShape.getFrameRect().width, 3, Accuracy);
    BOOST_CHECK_CLOSE_FRACTION(testcompositeShape.getFrameRect().height, 3, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(Scale_Test_CS)
  {
    astafev::Rectangle rect1({1.5, 1.5},1, 1);
    astafev::Rectangle rect2({2.5, 2.5},1, 1);
    astafev::Rectangle rect3({3.5, 3.5},1, 1);
    std::shared_ptr<astafev::Shape> rectPtr1 = std::make_shared<astafev::Rectangle>(rect1);
    std::shared_ptr<astafev::Shape> rectPtr2 = std::make_shared<astafev::Rectangle>(rect2);
    std::shared_ptr<astafev::Shape> rectPtr3 = std::make_shared<astafev::Rectangle>(rect3);
    astafev::CompositeShape testcompositeShape(rectPtr1);
    testcompositeShape.addElement(rectPtr2);
    testcompositeShape.addElement(rectPtr3);
    testcompositeShape.scale(4);
    BOOST_CHECK_CLOSE_FRACTION(testcompositeShape.getArea(), 48, Accuracy);
    BOOST_CHECK_CLOSE_FRACTION(testcompositeShape.getFrameRect().pos.x, 2.5, Accuracy);
    BOOST_CHECK_CLOSE_FRACTION(testcompositeShape.getFrameRect().pos.y, 2.5, Accuracy);
    BOOST_CHECK_CLOSE_FRACTION(testcompositeShape.getFrameRect().width, 12, Accuracy);
    BOOST_CHECK_CLOSE_FRACTION(testcompositeShape.getFrameRect().height, 12, Accuracy);

  }


  BOOST_AUTO_TEST_CASE(Remove_Element_Test_CS)
  {
    astafev::Rectangle rect1({1.5, 1.5},1, 1);
    astafev::Rectangle rect2({2.5, 2.5},1, 1);
    astafev::Rectangle rect3({3.5, 3.5},1, 1);
    std::shared_ptr<astafev::Shape> rectPtr1 = std::make_shared<astafev::Rectangle>(rect1);
    std::shared_ptr<astafev::Shape> rectPtr2 = std::make_shared<astafev::Rectangle>(rect2);
    std::shared_ptr<astafev::Shape> rectPtr3 = std::make_shared<astafev::Rectangle>(rect3);
    astafev::CompositeShape testcompositeShape(rectPtr1);
    testcompositeShape.addElement(rectPtr2);
    testcompositeShape.addElement(rectPtr3);
    testcompositeShape.deleteElement(0);
    BOOST_CHECK_CLOSE_FRACTION(testcompositeShape.getFrameRect().pos.x, 3, Accuracy);
    BOOST_CHECK_CLOSE_FRACTION(testcompositeShape.getFrameRect().pos.y, 3, Accuracy);
    BOOST_CHECK_CLOSE_FRACTION(testcompositeShape.getFrameRect().width, 2, Accuracy);
    BOOST_CHECK_CLOSE_FRACTION(testcompositeShape.getFrameRect().height, 2, Accuracy);
  }


  BOOST_AUTO_TEST_CASE(Invalid_Argument_Scale_Test_CS)
  {
    astafev::Circle circ({0, 0},10);
    std::shared_ptr<astafev::Shape> circPtr = std::make_shared<astafev::Circle>(circ);
    astafev::CompositeShape testcompositeShape(circPtr);
    BOOST_CHECK_THROW(testcompositeShape.scale(-1), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Invalid_Argument_RemoveShape_Test_CS)
  {
    astafev::Circle circ({0, 0},10);
    std::shared_ptr<astafev::Shape> circPtr = std::make_shared<astafev::Circle>(circ);
    astafev::CompositeShape testcompositeShape(circPtr);
    BOOST_CHECK_THROW(testcompositeShape.deleteElement(2), std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(Clear_Test_CS)
  {
    astafev::Circle circ1({0, 0},10);
    astafev::Circle circ2({10, 10},20);
    astafev::Circle circ3({20, 20},30);
    std::shared_ptr<astafev::Shape> circPtr1 = std::make_shared<astafev::Circle>(circ1);
    std::shared_ptr<astafev::Shape> circPtr2 = std::make_shared<astafev::Circle>(circ2);
    std::shared_ptr<astafev::Shape> circPtr3 = std::make_shared<astafev::Circle>(circ3);
    astafev::CompositeShape testcompositeShape(circPtr1);
    testcompositeShape.addElement(circPtr2);
    testcompositeShape.addElement(circPtr3);
    testcompositeShape.deleteElement(2);
    BOOST_REQUIRE_EQUAL(testcompositeShape.getSize(), 2);
  }

  BOOST_AUTO_TEST_CASE(Out_Of_Range_Error_Get_Element_Test_CS)
  {
    astafev::Circle circ({0, 0},10);
    std::shared_ptr<astafev::Shape> circPtr = std::make_shared<astafev::Circle>(circ);
    astafev::CompositeShape testcompositeShape(circPtr);
    BOOST_CHECK_THROW(testcompositeShape[2], std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(rotate)
  {
    astafev::Rectangle rect1({5, 6},3, 4);
    astafev::Rectangle rect2({9, 1},7, 8);
    astafev::Circle circ({12, 13},11);
    astafev::Rectangle rect3({6, 7},4, 1);
    std::shared_ptr<astafev::Shape> rectPtr1 = std::make_shared<astafev::Rectangle>(rect1);
    std::shared_ptr<astafev::Shape> rectPtr2 = std::make_shared<astafev::Rectangle>(rect2);
    std::shared_ptr<astafev::Shape> circPtr = std::make_shared<astafev::Circle>(circ);
    std::shared_ptr<astafev::Shape> rectPtr3 = std::make_shared<astafev::Rectangle>(rect3);
    astafev::CompositeShape testcompositeShape(rectPtr1);
    testcompositeShape.addElement(rectPtr2);
    testcompositeShape.addElement(circPtr);
    testcompositeShape.addElement(rectPtr3);

    astafev::CompositeShape testcompositeShape1(testcompositeShape);
    testcompositeShape1.rotate(70);
    BOOST_CHECK_CLOSE(testcompositeShape.getArea(), testcompositeShape1.getArea(), Accuracy);
    for (int i = 0; i < 3; ++i) 
    {
      BOOST_CHECK_CLOSE(testcompositeShape[i]->getArea(), testcompositeShape1[i]->getArea(), Accuracy);
    }

  }

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(MatrixTests)
  const double EPS = 0.00001;

  BOOST_AUTO_TEST_CASE(Constructor1)
  {
    BOOST_CHECK_THROW(astafev::Matrix testMatrix(nullptr), std::invalid_argument);
  }
  BOOST_AUTO_TEST_CASE(Constructor2)
  {
    astafev::Circle testCircle({100.0, 0.0},10.0);
    std::shared_ptr<astafev::Shape> circlePtr = std::make_shared<astafev::Circle>(testCircle);
    astafev::Matrix testMatrix(circlePtr);
    BOOST_CHECK_THROW(testMatrix[-1], std::invalid_argument);
  }


  BOOST_AUTO_TEST_CASE(CopyConstructorTest)
  {
    astafev::Circle testCircleM({-10.0, 0.0},10.0);
    astafev::Rectangle testRectangleM1({20.0, 30.0},20.0, 40.0);
    astafev::Rectangle testRectangleM2({30.0, 0.0},20.0, 40.0);
    std::shared_ptr<astafev::Shape> circlePtrM = std::make_shared<astafev::Circle>(testCircleM);
    std::shared_ptr<astafev::Shape> rectanglePtrM1 = std::make_shared<astafev::Rectangle>(testRectangleM1);
    std::shared_ptr<astafev::Shape> rectanglePtrM2 = std::make_shared<astafev::Rectangle>(testRectangleM2);
    astafev::Matrix testMatrix1(circlePtrM);
    testMatrix1.addElement(rectanglePtrM1);
    testMatrix1.addElement(rectanglePtrM2);
    astafev::Matrix testMatrix2(testMatrix1);
    std::unique_ptr<std::shared_ptr<astafev::Shape>[]> layer0 = testMatrix2[0];
    std::unique_ptr<std::shared_ptr<astafev::Shape>[]> layer1 = testMatrix2[1];
    BOOST_CHECK(layer0[0] == circlePtrM);
    BOOST_CHECK(layer0[1] == rectanglePtrM1);
    BOOST_CHECK(layer1[0] == rectanglePtrM2);
    BOOST_REQUIRE_EQUAL(testMatrix2.getLayerNumber(), 2);
    BOOST_REQUIRE_EQUAL(testMatrix2.getLayerSize(), 2);
  }

  BOOST_AUTO_TEST_CASE(MoveConstructorTest)
  {
    astafev::Circle testCircleM({-10.0, 0.0},10.0);
    astafev::Rectangle testRectangleM1({20.0, 30.0},20.0, 40.0);
    astafev::Rectangle testRectangleM2({30.0, 0.0},20.0, 40.0);
    std::shared_ptr<astafev::Shape> circlePtrM = std::make_shared<astafev::Circle>(testCircleM);
    std::shared_ptr<astafev::Shape> rectanglePtrM1 = std::make_shared<astafev::Rectangle>(testRectangleM1);
    std::shared_ptr<astafev::Shape> rectanglePtrM2 = std::make_shared<astafev::Rectangle>(testRectangleM2);
    astafev::Matrix testMatrix1(circlePtrM);
    testMatrix1.addElement(rectanglePtrM1);
    testMatrix1.addElement(rectanglePtrM2);
    astafev::Matrix testMatrix2(std::move(testMatrix1));
    std::unique_ptr<std::shared_ptr<astafev::Shape>[]> layer0 = testMatrix2[0];
    std::unique_ptr<std::shared_ptr<astafev::Shape>[]> layer1 = testMatrix2[1];
    BOOST_CHECK(layer0[0] == circlePtrM);
    BOOST_CHECK(layer0[1] == rectanglePtrM1);
    BOOST_CHECK(layer1[0] == rectanglePtrM2);
    BOOST_REQUIRE_EQUAL(testMatrix1.getLayerNumber(), 0);
    BOOST_REQUIRE_EQUAL(testMatrix1.getLayerSize(), 0);
    BOOST_REQUIRE_EQUAL(testMatrix2.getLayerNumber(), 2);
    BOOST_REQUIRE_EQUAL(testMatrix2.getLayerSize(), 2);
  }

  BOOST_AUTO_TEST_CASE(CopyOperatorTest)
  {
    astafev::Circle testCircleM2({40.0, 30.0},20.0);
    astafev::Circle testCircleM1({-10.0, 0.0},10.0);
    astafev::Rectangle testRectangleM1({20.0, 30.0},20.0, 40.0);
    astafev::Rectangle testRectangleM2({30.0, 0.0},20.0, 40.0);
    std::shared_ptr<astafev::Shape> circlePtrM1 = std::make_shared<astafev::Circle>(testCircleM1);
    std::shared_ptr<astafev::Shape> circlePtrM2 = std::make_shared<astafev::Circle>(testCircleM2);
    std::shared_ptr<astafev::Shape> rectanglePtrM1 = std::make_shared<astafev::Rectangle>(testRectangleM1);
    std::shared_ptr<astafev::Shape> rectanglePtrM2 = std::make_shared<astafev::Rectangle>(testRectangleM2);
    astafev::Matrix testMatrix1(circlePtrM1);
    testMatrix1.addElement(rectanglePtrM1);
    testMatrix1.addElement(rectanglePtrM2);
    astafev::Matrix testMatrix2(circlePtrM2);
    testMatrix2 = testMatrix1;
    std::unique_ptr<std::shared_ptr<astafev::Shape>[]> layer0 = testMatrix2[0];
    std::unique_ptr<std::shared_ptr<astafev::Shape>[]> layer1 = testMatrix2[1];
    BOOST_CHECK(layer0[0] == circlePtrM1);
    BOOST_CHECK(layer0[1] == rectanglePtrM1);
    BOOST_CHECK(layer1[0] == rectanglePtrM2);
    BOOST_REQUIRE_EQUAL(testMatrix2.getLayerNumber(), 2);
    BOOST_REQUIRE_EQUAL(testMatrix2.getLayerSize(), 2);
  }

  BOOST_AUTO_TEST_CASE(MoveOperatorTest)
  {
    astafev::Circle testCircleM2({40.0, 30.0},20.0);
    astafev::Circle testCircleM1({-10.0, 0.0},10.0);
    astafev::Rectangle testRectangleM1({20.0, 30.0},20.0, 40.0);
    astafev::Rectangle testRectangleM2({30.0, 0.0},20.0, 40.0);
    std::shared_ptr<astafev::Shape> circlePtrM1 = std::make_shared<astafev::Circle>(testCircleM1);
    std::shared_ptr<astafev::Shape> circlePtrM2 = std::make_shared<astafev::Circle>(testCircleM2);
    std::shared_ptr<astafev::Shape> rectanglePtrM1 = std::make_shared<astafev::Rectangle>(testRectangleM1);
    std::shared_ptr<astafev::Shape> rectanglePtrM2 = std::make_shared<astafev::Rectangle>(testRectangleM2);
    astafev::Matrix testMatrix1(circlePtrM1);
    testMatrix1.addElement(rectanglePtrM1);
    testMatrix1.addElement(rectanglePtrM2);
    astafev::Matrix testMatrix2(circlePtrM2);
    testMatrix2 = std::move(testMatrix1);
    std::unique_ptr<std::shared_ptr<astafev::Shape>[]> layer0 = testMatrix2[0];
    std::unique_ptr<std::shared_ptr<astafev::Shape>[]> layer1 = testMatrix2[1];
    BOOST_CHECK(layer0[0] == circlePtrM1);
    BOOST_CHECK(layer0[1] == rectanglePtrM1);
    BOOST_CHECK(layer1[0] == rectanglePtrM2);
    BOOST_REQUIRE_EQUAL(testMatrix1.getLayerNumber(), 0);
    BOOST_REQUIRE_EQUAL(testMatrix1.getLayerSize(), 0);
    BOOST_REQUIRE_EQUAL(testMatrix2.getLayerNumber(), 2);
    BOOST_REQUIRE_EQUAL(testMatrix2.getLayerSize(), 2);
  }

  BOOST_AUTO_TEST_CASE(MatrixGetFramerectTest)
  {
    astafev::Circle testCircleM2({40.0, 30.0},20.0);
    astafev::Circle testCircleM1({-10.0, 0.0},10.0);
    astafev::Rectangle testRectangleM1({20.0, 30.0},20.0, 40.0);
    astafev::Rectangle testRectangleM2({30.0, 0.0},20.0, 40.0);
    std::shared_ptr<astafev::Shape> circlePtr1 = std::make_shared<astafev::Circle>(testCircleM1);
    std::shared_ptr<astafev::Shape> circlePtr2 = std::make_shared<astafev::Circle>(testCircleM2);
    std::shared_ptr<astafev::Shape> rectanglePtr1 = std::make_shared<astafev::Rectangle>(testRectangleM1);
    std::shared_ptr<astafev::Shape> rectanglePtr2 = std::make_shared<astafev::Rectangle>(testRectangleM2);
    astafev::Matrix testMatrix(circlePtr1);
    testMatrix.addElement(rectanglePtr1);
    testMatrix.addElement(rectanglePtr2);
    testMatrix.addElement(circlePtr2);
    std::unique_ptr<std::shared_ptr<astafev::Shape>[]> layer0 = testMatrix[0];
    std::unique_ptr<std::shared_ptr<astafev::Shape>[]> layer1 = testMatrix[1];
    std::unique_ptr<std::shared_ptr<astafev::Shape>[]> layer2 = testMatrix[2];
    BOOST_CHECK(layer0[0] == circlePtr1);
    BOOST_CHECK(layer0[1] == rectanglePtr1);
    BOOST_CHECK(layer1[0] == rectanglePtr2);
    BOOST_CHECK(layer1[1] == nullptr);
    BOOST_CHECK(layer2[0] == circlePtr2);
    BOOST_CHECK(layer2[1] == nullptr);
    BOOST_CHECK_CLOSE_FRACTION(layer0[0]->getFrameRect().pos.x, -10.0, EPS);
    BOOST_CHECK_CLOSE_FRACTION(layer0[1]->getFrameRect().pos.x, 20.0, EPS);
    BOOST_CHECK_CLOSE_FRACTION(layer1[0]->getFrameRect().pos.x, 30.0, EPS);
    BOOST_CHECK_CLOSE_FRACTION(layer2[0]->getFrameRect().pos.x, 40.0, EPS);
    BOOST_CHECK_CLOSE_FRACTION(layer0[0]->getFrameRect().pos.y, 0.0, EPS);
    BOOST_CHECK_CLOSE_FRACTION(layer0[1]->getFrameRect().pos.y, 30.0, EPS);
    BOOST_CHECK_CLOSE_FRACTION(layer1[0]->getFrameRect().pos.y, 0.0, EPS);
    BOOST_CHECK_CLOSE_FRACTION(layer2[0]->getFrameRect().pos.y, 30.0, EPS);
  }

  BOOST_AUTO_TEST_CASE(addCs)
  {
    astafev::Circle testCircleM2({40.0, 30.0},20.0);
    astafev::Circle testCircleM1({-10.0, 0.0},10.0);
    astafev::Rectangle testRectangleM1({20.0, 30.0},20.0, 40.0);
    astafev::Rectangle testRectangleM2({30.0, 0.0},20.0, 40.0);
    std::shared_ptr<astafev::Shape> circlePtr1 = std::make_shared<astafev::Circle>(testCircleM1);
    std::shared_ptr<astafev::Shape> circlePtr2 = std::make_shared<astafev::Circle>(testCircleM2);
    std::shared_ptr<astafev::Shape> rectanglePtr1 = std::make_shared<astafev::Rectangle>(testRectangleM1);
    std::shared_ptr<astafev::Shape> rectanglePtr2 = std::make_shared<astafev::Rectangle>(testRectangleM2);
    astafev::CompositeShape testCompasiteShape(rectanglePtr1);
    testCompasiteShape.addElement(rectanglePtr2);
    testCompasiteShape.addElement(circlePtr2);

    size_t size = testCompasiteShape.getSize();
    std::shared_ptr<astafev::CompositeShape> array = std::make_shared<astafev::CompositeShape>(testCompasiteShape);
    astafev::Matrix testMatrix(circlePtr1);
    testMatrix.addElement(array, size);

    std::unique_ptr<std::shared_ptr<astafev::Shape>[]> layer0 = testMatrix[0];
    std::unique_ptr<std::shared_ptr<astafev::Shape>[]> layer1 = testMatrix[1];
    std::unique_ptr<std::shared_ptr<astafev::Shape>[]> layer2 = testMatrix[2];
    BOOST_CHECK(layer0[0] == circlePtr1);
    BOOST_CHECK(layer0[1] == rectanglePtr1);
    BOOST_CHECK(layer1[0] == rectanglePtr2);
    BOOST_CHECK(layer1[1] == nullptr);
    BOOST_CHECK(layer2[0] == circlePtr2);
    BOOST_CHECK(layer2[1] == nullptr);
  }

BOOST_AUTO_TEST_SUITE_END()

