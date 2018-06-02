#define BOOST_TEST_MODULE Main

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

using namespace khodyreva;

const double EPSILON = 1e-6;

BOOST_AUTO_TEST_SUITE(Rectangle_Test)

  BOOST_AUTO_TEST_CASE(Moving_To_Point)
  {
    Rectangle rectangle ({19.0, 17.0}, 7.0, 9.0);
    rectangle_t rectangleBeforeMoving = rectangle.getFrameRect();
    double areaBeforeMoving = rectangle.getArea();
    rectangle.move({7.0, 5.0});
    BOOST_REQUIRE_EQUAL(areaBeforeMoving, rectangle.getArea());
    BOOST_REQUIRE_EQUAL(rectangleBeforeMoving.width, rectangle.getFrameRect().width);
    BOOST_REQUIRE_EQUAL(rectangleBeforeMoving.height, rectangle.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(Relative_Moving)
  {
    Rectangle rectangle({19.0, 17.0}, 7.0, 9.0);
    rectangle_t rectangleBeforeMoving = rectangle.getFrameRect();
    double areaBeforeMoving = rectangle.getArea();
    rectangle.move(19.0, -17.0);
    BOOST_REQUIRE_EQUAL(areaBeforeMoving, rectangle.getArea());
    BOOST_REQUIRE_EQUAL(rectangleBeforeMoving.width, rectangle.getFrameRect().width);
    BOOST_REQUIRE_EQUAL(rectangleBeforeMoving.height, rectangle.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(Scaling)
  {
    Rectangle rectangle({19.0, 17.0}, 7.0, 9.0);
    double areaBeforeScaling = rectangle.getArea();
    rectangle.scale(2.0);
    BOOST_CHECK_CLOSE_FRACTION(areaBeforeScaling * 4.0, rectangle.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(Invalid_Constructor)
  {
    BOOST_CHECK_THROW(Rectangle rectangle({19.0, 17.0}, -7.0, 9.0), std::invalid_argument);
    BOOST_CHECK_THROW(Rectangle rectangle({19.0, 17.0}, 7.0, -9.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Invalid_Scale)
  {
    Rectangle rectangle({19.0, 17.0}, 7.0, 9.0);
    BOOST_CHECK_THROW(rectangle.scale(-2.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Circle_Test)

  BOOST_AUTO_TEST_CASE(Moving_To_Point)
  {
    Circle circle ({9.0, 7.0}, 5.0);
    rectangle_t rectangleBeforeMoving = circle.getFrameRect();
    double areaBeforeMoving = circle.getArea();
    circle.move({1.0, 3.0});
    BOOST_REQUIRE_EQUAL(areaBeforeMoving, circle.getArea());
    BOOST_REQUIRE_EQUAL(rectangleBeforeMoving.width, circle.getFrameRect().width);
    BOOST_REQUIRE_EQUAL(rectangleBeforeMoving.height, circle.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(Relative_Moving)
  {
    Circle circle({9.0, 7.0}, 5.0);
    rectangle_t rectangleBeforeMoving = circle.getFrameRect();
    double areaBeforeMoving = circle.getArea();
    circle.move(9.0, -7.0);
    BOOST_REQUIRE_EQUAL(areaBeforeMoving, circle.getArea());
    BOOST_REQUIRE_EQUAL(rectangleBeforeMoving.width, circle.getFrameRect().width);
    BOOST_REQUIRE_EQUAL(rectangleBeforeMoving.height, circle.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(Scaling)
  {
    Circle circle({9.0, 7.0}, 5.0);
    double areaBeforeScaling = circle.getArea();
    circle.scale(2.0);
    BOOST_CHECK_CLOSE_FRACTION(areaBeforeScaling * 4.0, circle.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(Invalid_Constructor)
  {
    BOOST_CHECK_THROW(Circle circle({9.0, 7.0}, -5.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Invalid_Scale)
  {
    Circle circle({9.0, 7.0}, 5.0);
    BOOST_CHECK_THROW(circle.scale(-2.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

//CompositeShape Tests
BOOST_AUTO_TEST_SUITE(CompositeShape_Test)


  BOOST_AUTO_TEST_CASE(Constructor_Test)
  {
    std::shared_ptr<Shape> noShape = nullptr;
    BOOST_CHECK_THROW(CompositeShape cSh(noShape), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Copying_Constructor)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({3.0, 4.0}, 5.0, 7.0));
    CompositeShape cSh(rect1);
    cSh.addShape(std::make_shared<Circle>(Circle({3.0, 5.0}, 9.0)));
    CompositeShape cSh2(cSh);
    for (size_t i = 0; i < cSh.getSize(); ++i)
    {
      const rectangle_t rectangle = cSh[i]->getFrameRect();
      const rectangle_t rectangle2 = cSh2[i]->getFrameRect();
      BOOST_CHECK_EQUAL(rectangle.height, rectangle2.height);
      BOOST_CHECK_EQUAL(rectangle.width, rectangle2.width);
      BOOST_CHECK_EQUAL(rectangle.pos.x, rectangle2.pos.x);
      BOOST_CHECK_EQUAL(rectangle.pos.y, rectangle2.pos.y);
    }
  }

  BOOST_AUTO_TEST_CASE(Copying_Operator)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({3.0, 4.0}, 5.0, 7.0));
    CompositeShape cSh(rect1);
    cSh.addShape(std::make_shared<Circle>(Circle({3.0, 5.0}, 9.0)));
    std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({1.0, 5.0}, 7.0, 5.0));
    CompositeShape cSh2(rect2);
    cSh2.addShape(std::make_shared<Circle>(Circle({6.0, 6.0}, 11.0)));
    cSh = cSh2;
    for (size_t i = 0; i < cSh.getSize(); ++i)
    {
      const rectangle_t rectangle = cSh[i]->getFrameRect();
      const rectangle_t rectangle2 = cSh2[i]->getFrameRect();
      BOOST_CHECK_EQUAL(rectangle.height, rectangle2.height);
      BOOST_CHECK_EQUAL(rectangle.width, rectangle2.width);
      BOOST_CHECK_EQUAL(rectangle.pos.x, rectangle2.pos.x);
      BOOST_CHECK_EQUAL(rectangle.pos.y, rectangle2.pos.y);
    }
  }

  BOOST_AUTO_TEST_CASE(Moving_Constructor)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({3.0, 4.0}, 5.0, 7.0));
    CompositeShape cSh(rect1);
    cSh.addShape(std::make_shared<Circle>(Circle({3.0, 5.0}, 9.0)));
    CompositeShape cSh2(cSh);
    CompositeShape cSh3(std::move(cSh));
    for (size_t i = 0; i < cSh.getSize(); ++i)
    {
      const rectangle_t rectangle2 = cSh2[i]->getFrameRect();
      const rectangle_t rectangle3 = cSh3[i]->getFrameRect();
      BOOST_CHECK_EQUAL(rectangle2.height, rectangle3.height);
      BOOST_CHECK_EQUAL(rectangle2.width, rectangle3.width);
      BOOST_CHECK_EQUAL(rectangle2.pos.x, rectangle3.pos.x);
      BOOST_CHECK_EQUAL(rectangle2.pos.y, rectangle3.pos.y);
    }
  }

  BOOST_AUTO_TEST_CASE(Moving_Operator)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({3.0, 4.0}, 5.0, 7.0));
    CompositeShape cSh(rect1);
    cSh.addShape(std::make_shared<Circle>(Circle({3.0, 5.0}, 9.0)));
    CompositeShape cSh2(cSh);
    std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({1.0, 5.0}, 7.0, 5.0));
    CompositeShape cSh3(rect2);
    cSh3.addShape(std::make_shared<Circle>(Circle({6.0, 6.0}, 11.0)));
    cSh3 = std::move(cSh);
    for (size_t i = 0; i < cSh.getSize(); ++i)
    {
      const rectangle_t rectangle2 = cSh2[i]->getFrameRect();
      const rectangle_t rectangle3 = cSh3[i]->getFrameRect();
      BOOST_CHECK_EQUAL(rectangle2.height, rectangle3.height);
      BOOST_CHECK_EQUAL(rectangle2.width, rectangle3.width);
      BOOST_CHECK_EQUAL(rectangle2.pos.x, rectangle3.pos.x);
      BOOST_CHECK_EQUAL(rectangle2.pos.y, rectangle3.pos.y);
    }
  }

  BOOST_AUTO_TEST_CASE(Index)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({3.0, 4.0}, 5.0, 7.0));
    CompositeShape cSh(rect1);
    cSh.addShape(std::make_shared<Circle>(Circle({3.0, 5.0}, 9.0)));
    BOOST_CHECK_THROW(cSh[3], std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(Move_To_Point)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({3.0, 4.0}, 5.0, 7.0));
    CompositeShape cSh(rect1);
    cSh.addShape(std::make_shared<Circle>(Circle({3.0, 5.0}, 9.0)));
    const rectangle_t rectangleBeforeMoving = cSh.getFrameRect();
    const double areaBeforeMoving = cSh.getArea();
    cSh.move({5.0,7.0});
    BOOST_CHECK_CLOSE(rectangleBeforeMoving.height, cSh.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(rectangleBeforeMoving.width, cSh.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE(areaBeforeMoving, cSh.getArea(), EPSILON);
  }


  BOOST_AUTO_TEST_CASE(Relative_Moving)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({3.0, 4.0}, 5.0, 7.0));
    CompositeShape cSh(rect1);
    cSh.addShape(std::make_shared<Circle>(Circle({3.0, 5.0}, 9.0)));
    const rectangle_t rectangleBeforeMoving = cSh.getFrameRect();
    const double areaBeforeMoving = cSh.getArea();
    cSh.move(5.0,7.0);
    BOOST_CHECK_CLOSE(rectangleBeforeMoving.height, cSh.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(rectangleBeforeMoving.width, cSh.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE(areaBeforeMoving, cSh.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(Scaling)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({3.0, 4.0}, 5.0, 7.0));
    CompositeShape cSh(rect1);
    cSh.addShape(std::make_shared<Circle>(Circle({3.0, 5.0}, 9.0)));
    const rectangle_t rectangleBeforeScaling = cSh.getFrameRect();
    const double areaBeforeScaling = cSh.getArea();
    cSh.scale(2.0);
    BOOST_CHECK_CLOSE(areaBeforeScaling * 4.0, cSh.getArea(), EPSILON);
    BOOST_CHECK_CLOSE(rectangleBeforeScaling.height * 2, cSh.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(rectangleBeforeScaling.width * 2, cSh.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE(rectangleBeforeScaling.pos.x, cSh.getFrameRect().pos.x, EPSILON);
    BOOST_CHECK_CLOSE(rectangleBeforeScaling.pos.y, cSh.getFrameRect().pos.y, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(Invalid_Scale)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({3.0, 4.0}, 5.0, 7.0));
    CompositeShape cSh(rect1);
    cSh.addShape(std::make_shared<Circle>(Circle({3.0, 5.0}, 9.0)));
    BOOST_CHECK_THROW(cSh.scale(-2.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Invalid_Add)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({3.0, 4.0}, 5.0, 7.0));
    CompositeShape cSh(rect1);
    BOOST_CHECK_THROW(cSh.addShape(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Add_Shape)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({3.0, 4.0}, 5.0, 7.0));
    CompositeShape cSh(rect1);
    cSh.addShape(std::make_shared<Circle>(Circle({3.0, 5.0}, 9.0)));
    BOOST_CHECK_EQUAL(cSh.getSize(), 2);
  }

  BOOST_AUTO_TEST_CASE(Invalid_Delete)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({3.0, 4.0}, 5.0, 7.0));
    CompositeShape cSh(rect1);
    cSh.addShape(std::make_shared<Circle>(Circle({3.0, 5.0}, 9.0)));
    BOOST_CHECK_THROW(cSh.deleteShape(5), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Delete_Shape)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({3.0, 4.0}, 5.0, 7.0));
    CompositeShape cSh(rect1);
    cSh.addShape(std::make_shared<Circle>(Circle({3.0, 5.0}, 9.0)));
    cSh.addShape(std::make_shared<Rectangle>(Rectangle({7.0, 8.0}, 5.0, 3.0)));
    cSh.addShape(std::make_shared<Circle>(Circle({2.0, 6.0}, 1.0)));
    cSh.deleteShape(1);
    BOOST_CHECK_EQUAL(cSh.getSize(), 3);
  }

  BOOST_AUTO_TEST_CASE(Get_Area)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({6.0, 1.0}, 9.0, 4.0));
    CompositeShape cSh(rect1);
    cSh.addShape(std::make_shared<Rectangle>(Rectangle({7.0, 8.0}, 5.0, 3.0)));
    cSh.addShape(std::make_shared<Rectangle>(Rectangle({2.0, 6.0}, 10.0, 10.0)));
    BOOST_CHECK_CLOSE(cSh.getArea(), 151.0, EPSILON);
    cSh.scale(2);
    BOOST_CHECK_CLOSE(cSh.getArea(), 604.0, EPSILON);
    cSh.move(2.0, 4.0);
    BOOST_CHECK_CLOSE(cSh.getArea(), 604.0, EPSILON);
    cSh.move({13.0, 21.0});
    BOOST_CHECK_CLOSE(cSh.getArea(), 604.0, EPSILON);
  }



BOOST_AUTO_TEST_SUITE_END()
