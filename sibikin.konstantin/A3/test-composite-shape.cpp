#include <boost/test/unit_test.hpp>
#include <iostream>
#include "composite-shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"

const double EPS = 0.001;

BOOST_AUTO_TEST_SUITE(Comp_Test)

  struct PolyFixture
  {
    sibikin::Circle circle;
    sibikin::Rectangle rect;

    PolyFixture() :
      circle({5.0, 5.0}, 4.0),
      rect({5.0, 5.0}, 2.0, 3.0)
    {
    }

    ~PolyFixture() = default;
  };

  BOOST_FIXTURE_TEST_CASE(Comp_Move_By_Test, PolyFixture)
  {
    sibikin::CompositeShape comp;
    comp.addShape(&rect);
    comp.addShape(&circle);

    const double areaBeforeMove = comp.getArea();
    const sibikin::rectangle_t frameBeforeMove = comp.getFrameRect();
    comp.move(2, 3.5);
    BOOST_CHECK_CLOSE(comp.getArea(), areaBeforeMove, EPS);
    BOOST_CHECK_EQUAL(comp.getFrameRect().height, frameBeforeMove.height);
    BOOST_CHECK_EQUAL(comp.getFrameRect().width, frameBeforeMove.width);
  }

  BOOST_FIXTURE_TEST_CASE(Comp_Move_To_Test, PolyFixture)
  {
    sibikin::CompositeShape comp;
    comp.addShape(&rect);
    comp.addShape(&circle);

    const double areaBeforeMove = comp.getArea();

    comp.move({7.0, 8.0});
    BOOST_CHECK_CLOSE(comp.getArea(), areaBeforeMove, EPS);
  }

  BOOST_FIXTURE_TEST_CASE(Comp_Add_Rect_With_Rect_Test, PolyFixture)
  {
    sibikin::CompositeShape comp;
    comp.addShape(&rect);
    sibikin::Rectangle rect2( {2.0, 3.0} , 3.0, 4.0);
    comp.addShape(&rect2);
    BOOST_CHECK_CLOSE(comp.getArea(), rect.getArea() + rect2.getArea(), EPS);
  }

  BOOST_FIXTURE_TEST_CASE(Comp_Add_Circle_With_Circle_Test, PolyFixture)
  {
    sibikin::CompositeShape comp;
    comp.addShape(&circle);
    sibikin::Circle circle2( {2.0, 3.0}, 3.0);
    comp.addShape(&circle2);
    BOOST_CHECK_CLOSE(comp.getArea(), circle.getArea() + circle2.getArea(), EPS);
  }

  BOOST_FIXTURE_TEST_CASE(Comp_Add_Rect_With_Circle_Test, PolyFixture)
  {
    sibikin::CompositeShape comp;
    comp.addShape(&rect);
    comp.addShape(&circle);

    BOOST_CHECK_CLOSE(rect.getArea() + circle.getArea(), comp.getArea(), EPS);
  }

  BOOST_FIXTURE_TEST_CASE(Comp_DeleteShape_Test, PolyFixture)
  {
    sibikin::CompositeShape comp;
    comp.addShape(&rect);
    comp.addShape(&circle);

    comp.deleteShape(1);
    BOOST_CHECK_EQUAL(comp.getSize(), 1);
    BOOST_CHECK_CLOSE(comp.getArea(), circle.getArea(),EPS);
  }

  BOOST_FIXTURE_TEST_CASE(Comp_Scale_Test, PolyFixture)
  {
    sibikin::CompositeShape comp;
    comp.addShape(&rect);
    comp.addShape(&circle);

    const double areaBeforeScale = comp.getArea();

    comp.scale(2.0);
    BOOST_CHECK_CLOSE(comp.getArea(), areaBeforeScale * 4, EPS);
    BOOST_CHECK_CLOSE(comp.getArea(), rect.getArea() + circle.getArea(), EPS);

    comp.scale(0.5);
    BOOST_CHECK_CLOSE(comp.getArea(), areaBeforeScale, EPS);
    BOOST_CHECK_CLOSE(comp.getArea(), rect.getArea() + circle.getArea(), EPS);

  }
  BOOST_FIXTURE_TEST_CASE(Comp_Scale_Invalid_Argument, PolyFixture)
  {
    sibikin::CompositeShape comp;
    comp.addShape(&rect);
    comp.addShape(&circle);

    BOOST_CHECK_THROW(comp.scale(-5), std::invalid_argument);
  }

  BOOST_FIXTURE_TEST_CASE(Comp_GetSize_Test, PolyFixture)
  {
    sibikin::CompositeShape comp;
    comp.addShape(&rect);
    comp.addShape(&circle);
    const size_t realSize = 2;

    BOOST_CHECK_EQUAL(realSize, comp.getSize());
  }

  BOOST_FIXTURE_TEST_CASE(Comp_Frame_Test, PolyFixture)
  {
    sibikin::CompositeShape comp;
    //comp.addShape(&rect);
    comp.addShape(&circle);

    BOOST_CHECK_CLOSE(comp.getFrameRect().width, 8.0, EPS);
    BOOST_CHECK_CLOSE(comp.getFrameRect().height, 8.0, EPS);
    BOOST_CHECK_CLOSE(comp.getPos().x, 5.0, EPS);
    BOOST_CHECK_CLOSE(comp.getPos().y, 5.0, EPS);
  }

  BOOST_FIXTURE_TEST_CASE(Comp_Copy_Contructor_Test, PolyFixture)
  {
    sibikin::CompositeShape comp1;
    comp1.addShape(&circle);
    comp1.addShape(&rect);
    sibikin::CompositeShape comp2(comp1);

    BOOST_CHECK_EQUAL(comp1.getSize(), comp2.getSize());
    BOOST_CHECK_CLOSE(comp1.getPos().x, comp2.getPos().x, EPS);
    BOOST_CHECK_CLOSE(comp1.getPos().y, comp2.getPos().y, EPS);
    BOOST_CHECK_CLOSE(comp1.getArea(), comp2.getArea(), EPS);

  }

  BOOST_FIXTURE_TEST_CASE(Comp_Move_Contructor_Test, PolyFixture)
  {
    sibikin::CompositeShape comp1;
    comp1.addShape(&circle);
    comp1.addShape(&rect);
    const double area = comp1.getArea();
    const sibikin::point_t pos = comp1.getPos();
    sibikin::CompositeShape comp2(std::move(comp1));

    BOOST_CHECK_EQUAL(comp2.getSize(), size_t(2));
    BOOST_CHECK_EQUAL(comp2.getPos().x, pos.x);
    BOOST_CHECK_EQUAL(comp2.getPos().y, pos.y);
    BOOST_CHECK_EQUAL(comp2.getArea(), area);

    BOOST_CHECK_EQUAL(comp1.getSize(), size_t(0));
    BOOST_CHECK_CLOSE(comp1.getArea(), 0, EPS);
    BOOST_CHECK_CLOSE(comp1.getPos().x, 0, EPS);
    BOOST_CHECK_CLOSE(comp1.getPos().y, 0, EPS);
  }

  BOOST_FIXTURE_TEST_CASE(Comp_Operator_Brackets_Test, PolyFixture)
  {
    sibikin::CompositeShape comp1;
    comp1.addShape(&rect);
    sibikin::rectangle_t rectFrame = rect.getFrameRect(),
                         compFrame = comp1[0].getFrameRect();
    BOOST_CHECK_CLOSE(comp1[0].getArea(), rect.getArea(), EPS);
    BOOST_CHECK_CLOSE(compFrame.pos.x, rectFrame.pos.x, EPS);
    BOOST_CHECK_CLOSE(compFrame.pos.y, rectFrame.pos.y, EPS);
    BOOST_CHECK_CLOSE(compFrame.width, rectFrame.width, EPS);
    BOOST_CHECK_CLOSE(compFrame.height, rectFrame.height, EPS);
  }

  BOOST_FIXTURE_TEST_CASE(Comp_Copy_Operator_Test, PolyFixture)
  {
    sibikin::CompositeShape comp1;
    comp1.addShape(&circle);
    comp1.addShape(&rect);
    sibikin::CompositeShape comp2(&circle);
    comp2 = comp1;

    BOOST_CHECK_EQUAL(comp1.getSize(), comp2.getSize());
    BOOST_CHECK_CLOSE(comp1.getPos().x, comp2.getPos().x, EPS);
    BOOST_CHECK_CLOSE(comp1.getPos().y, comp2.getPos().y, EPS);
    BOOST_CHECK_CLOSE(comp1.getArea(), comp2.getArea(), EPS);
  }

  BOOST_FIXTURE_TEST_CASE(Comp_Move_Operator_Test, PolyFixture)
  {
    sibikin::CompositeShape comp1;
    comp1.addShape(&circle);
    comp1.addShape(&rect);
    const double area = comp1.getArea();
    const sibikin::point_t pos = comp1.getPos();
    sibikin::CompositeShape comp2(&rect);
    comp2 = std::move(comp1);

    BOOST_CHECK_EQUAL(comp2.getSize(), size_t(2));
    BOOST_CHECK_EQUAL(comp2.getPos().x, pos.x);
    BOOST_CHECK_EQUAL(comp2.getPos().y, pos.y);
    BOOST_CHECK_EQUAL(comp2.getArea(), area);

    BOOST_CHECK_EQUAL(comp1.getSize(), size_t(0));
    BOOST_CHECK_CLOSE(comp1.getArea(), 0, EPS);
    BOOST_CHECK_CLOSE(comp1.getPos().x, 0, EPS);
    BOOST_CHECK_CLOSE(comp1.getPos().y, 0, EPS);
  }

  BOOST_FIXTURE_TEST_CASE(CompositeShape_rotation_Test, PolyFixture)
  {
    sibikin::CompositeShape comp;
    comp.addShape(&circle);
    comp.addShape(&rect);

    comp.rotate(90.0);
    BOOST_CHECK_CLOSE(comp[0].getFrameRect().pos.x, 5.0, EPS);
    BOOST_CHECK_CLOSE(comp[0].getFrameRect().pos.y, 5.0, EPS);
    BOOST_CHECK_CLOSE(comp[1].getFrameRect().pos.x, 5.0, EPS);
    BOOST_CHECK_CLOSE(comp[1].getFrameRect().pos.y, 5.0, EPS);

    comp.rotate(-90.0);
    BOOST_CHECK_CLOSE(comp.getFrameRect().pos.x, 5.0, EPS);
    BOOST_CHECK_CLOSE(comp.getFrameRect().pos.y, 5.0, EPS);

    BOOST_CHECK_CLOSE(comp[0].getFrameRect().pos.x, 5.0, EPS);
    BOOST_CHECK_CLOSE(comp[0].getFrameRect().pos.y, 5.0, EPS);
    BOOST_CHECK_CLOSE(comp[1].getFrameRect().pos.x, 5.0, EPS);
    BOOST_CHECK_CLOSE(comp[1].getFrameRect().pos.y, 5.0, EPS);

    comp.rotate(180.0);
    BOOST_CHECK_CLOSE(comp[0].getFrameRect().pos.x, 5.0, EPS);
    BOOST_CHECK_CLOSE(comp[0].getFrameRect().pos.y, 5.0, EPS);
    BOOST_CHECK_CLOSE(comp[1].getFrameRect().pos.x, 5.0, EPS);
    BOOST_CHECK_CLOSE(comp[1].getFrameRect().pos.y, 5.0, EPS);
  }


BOOST_AUTO_TEST_SUITE_END()
