#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

#define BOOST_TEST_MODULE testMain
#include <boost/test/included/unit_test.hpp>

// Delta epsilon
const double Epsilon = 0.0000001;

// Testing Rectangle class
BOOST_AUTO_TEST_SUITE(testSuiteCircle)

// Cover for the test rect object
struct CircleFixture
{
  // Test rect object
  hvatov::Circle circle;

  // Test rect init
  CircleFixture() :
    circle({ 30, 30 }, 10)
  {

  }

  // Test rect destructor
  ~CircleFixture() = default;
};

BOOST_FIXTURE_TEST_CASE(testCircleMove1, CircleFixture)
{
  // Check at the beginning
  BOOST_CHECK_CLOSE(circle.getPosition().x, 30, Epsilon);
  BOOST_CHECK_CLOSE(circle.getPosition().y, 30, Epsilon);
  BOOST_CHECK_CLOSE(circle.getRadius(), 10, Epsilon);
  BOOST_CHECK_CLOSE(circle.getArea(), M_PI * 10 * 10, Epsilon);

  // Move and check again
  circle.move({ 300, 300 });
  BOOST_CHECK_CLOSE(circle.getPosition().x, 300, Epsilon);
  BOOST_CHECK_CLOSE(circle.getPosition().y, 300, Epsilon);
  BOOST_CHECK_CLOSE(circle.getRadius(), 10, Epsilon);
  BOOST_CHECK_CLOSE(circle.getArea(), M_PI * 10 * 10, Epsilon);
}

BOOST_FIXTURE_TEST_CASE(testCircleMove2, CircleFixture)
{
  // Check at the beginning
  BOOST_CHECK_CLOSE(circle.getPosition().x, 30, Epsilon);
  BOOST_CHECK_CLOSE(circle.getPosition().y, 30, Epsilon);
  BOOST_CHECK_CLOSE(circle.getRadius(), 10, Epsilon);
  BOOST_CHECK_CLOSE(circle.getArea(), M_PI * 10 * 10, Epsilon);

  // Move and check again
  circle.move(270, 270);
  BOOST_CHECK_CLOSE(circle.getPosition().x, 300, Epsilon);
  BOOST_CHECK_CLOSE(circle.getPosition().y, 300, Epsilon);
  BOOST_CHECK_CLOSE(circle.getRadius(), 10, Epsilon);
  BOOST_CHECK_CLOSE(circle.getArea(), M_PI * 10 * 10, Epsilon);
}

BOOST_FIXTURE_TEST_CASE(testCircleArea, CircleFixture)
{
  // Scale object 10 times and check its area
  circle.scale(10);
  BOOST_CHECK_CLOSE(circle.getArea(), M_PI * 10 * 10 * 10 * 10, Epsilon);
  // Scale object 5 times and check its area
  circle.scale(5);
  BOOST_CHECK_CLOSE(circle.getArea(), M_PI * 5 * 5 * 10 * 10 * 10 * 10, Epsilon);
}

BOOST_FIXTURE_TEST_CASE(testCircleThrowScale, CircleFixture)
{
  // Check if throws exceptions in scale method
  BOOST_CHECK_THROW(circle.scale(-5), std::invalid_argument);
}

BOOST_FIXTURE_TEST_CASE(testCircleThrowConstructor, CircleFixture)
{
  // Check if throws exceptions in constructor
  BOOST_CHECK_THROW(hvatov::Circle(10, 10, -10), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()

// Testing Rect class
BOOST_AUTO_TEST_SUITE(testSuiteRectangle)

// Cover for the test rect object
struct RectFixture
{
  // Test rect object
  hvatov::Rectangle rect;

  // Test rect init
  RectFixture() :
    rect({ 30, 30 }, 10, 10)
  {

  }

  // Test rect destructor
  ~RectFixture() = default;
};

BOOST_FIXTURE_TEST_CASE(testRectangleMove1, RectFixture)
{
  // Check at the beginning
  BOOST_CHECK_CLOSE(rect.getPosition().x, 30, Epsilon);
  BOOST_CHECK_CLOSE(rect.getPosition().y, 30, Epsilon);
  BOOST_CHECK_CLOSE(rect.getWidth(), 10, Epsilon);
  BOOST_CHECK_CLOSE(rect.getHeight(), 10, Epsilon);
  BOOST_CHECK_CLOSE(rect.getArea(), 10 * 10, Epsilon);

  // Move and check again
  rect.move({ 300, 300 });
  BOOST_CHECK_CLOSE(rect.getPosition().x, 300, Epsilon);
  BOOST_CHECK_CLOSE(rect.getPosition().y, 300, Epsilon);
  BOOST_CHECK_CLOSE(rect.getWidth(), 10, Epsilon);
  BOOST_CHECK_CLOSE(rect.getHeight(), 10, Epsilon);
  BOOST_CHECK_CLOSE(rect.getArea(), 10 * 10, Epsilon);
}

BOOST_FIXTURE_TEST_CASE(testRectangleMove2, RectFixture)
{
  // Check at the beginning
  BOOST_CHECK_CLOSE(rect.getPosition().x, 30, Epsilon);
  BOOST_CHECK_CLOSE(rect.getPosition().y, 30, Epsilon);
  BOOST_CHECK_CLOSE(rect.getWidth(), 10, Epsilon);
  BOOST_CHECK_CLOSE(rect.getHeight(), 10, Epsilon);
  BOOST_CHECK_CLOSE(rect.getArea(), 10 * 10, Epsilon);

  // Move and check again
  rect.move(270, 270);
  BOOST_CHECK_CLOSE(rect.getPosition().x, 300, Epsilon);
  BOOST_CHECK_CLOSE(rect.getPosition().y, 300, Epsilon);
  BOOST_CHECK_CLOSE(rect.getWidth(), 10, Epsilon);
  BOOST_CHECK_CLOSE(rect.getHeight(), 10, Epsilon);
  BOOST_CHECK_CLOSE(rect.getArea(), 10 * 10, Epsilon);
}

BOOST_FIXTURE_TEST_CASE(testRectangleArea, RectFixture)
{
  // Scale object 10 times and check its area
  rect.scale(10);
  BOOST_CHECK_CLOSE(rect.getArea(), 10 * 10 * 10 * 10, Epsilon);
  // Scale object 5 times and check its area
  rect.scale(5);
  BOOST_CHECK_CLOSE(rect.getArea(), 5 * 5 * 10 * 10 * 10 * 10, Epsilon);
}

BOOST_FIXTURE_TEST_CASE(testRectangleThrowScale, RectFixture)
{
  // Check if throws exceptions in scale method
  BOOST_CHECK_THROW(rect.scale(-5), std::invalid_argument);
}

BOOST_FIXTURE_TEST_CASE(testRectangleThrowConstructor, RectFixture)
{
  // Check if throws exceptions in constructor
  BOOST_CHECK_THROW(hvatov::Rectangle(10, 10, -10, -10), std::invalid_argument);
}

BOOST_FIXTURE_TEST_CASE(testRectangleRotate, RectFixture)
{
  // rotate object 90 degress
  rect.rotate(90);
  // Check area
  BOOST_CHECK_CLOSE(rect.getArea(), 10 * 10, Epsilon);
  // Check other params
  BOOST_CHECK_CLOSE(rect.getHeight(), 10, Epsilon);
  BOOST_CHECK_CLOSE(rect.getWidth(), 10, Epsilon);
  // Check frame rectangle
  hvatov::rectangle_t r = rect.getFrameRect();
  BOOST_CHECK_CLOSE(r.width, 10, Epsilon);
  BOOST_CHECK_CLOSE(r.height, 10, Epsilon);
  BOOST_CHECK_CLOSE(r.pos.x, 30, Epsilon);
  BOOST_CHECK_CLOSE(r.pos.y, 30, Epsilon);
}

BOOST_AUTO_TEST_SUITE_END()

// Testing Circle class
BOOST_AUTO_TEST_SUITE(testSuiteContainer)

// Cover for the test container object
struct FixtureCompShape
{
  // Test rect object
  hvatov::CompositeShape container;

  // Test rect init
  FixtureCompShape() :
    container()
  {

  }

  // Test rect destructor
  ~FixtureCompShape() = default;
};

BOOST_FIXTURE_TEST_CASE(testContainerAssignment, FixtureCompShape)
{
  // Init buffer variable
  hvatov::CompositeShape cmp;
  cmp.addElement(std::shared_ptr< hvatov::Shape >(new hvatov::Rectangle(10, 10, 10, 10)));
  cmp.addElement(std::shared_ptr< hvatov::Shape >(new hvatov::Circle(10, 10, 10)));

  // Init testing object
  container = cmp;

  // Check if elements are equal
  BOOST_CHECK_EQUAL(container[0], cmp[0]);
  BOOST_CHECK_EQUAL(container[1], cmp[1]);
}

BOOST_FIXTURE_TEST_CASE(testContainerCopyConstructor, FixtureCompShape)
{
  // Init buffer variable
  container.addElement(std::shared_ptr< hvatov::Shape >(new hvatov::Rectangle(10, 10, 10, 10)));
  container.addElement(std::shared_ptr< hvatov::Shape >(new hvatov::Circle(10, 10, 10)));

  // Init testing object
  hvatov::CompositeShape cmp(container);

  // Check if elements are equal
  BOOST_CHECK_EQUAL(container[0], cmp[0]);
  BOOST_CHECK_EQUAL(container[1], cmp[1]);
}

BOOST_FIXTURE_TEST_CASE(testContainerMoveConstructor, FixtureCompShape)
{
  // Init buffer variable
  std::shared_ptr< hvatov::Shape > ptr1(new hvatov::Rectangle(10, 10, 10, 10));
  std::shared_ptr< hvatov::Shape > ptr2(new hvatov::Circle(10, 10, 10));

  container.addElement(ptr1);
  container.addElement(ptr2);

  // Init testing object
  hvatov::CompositeShape cmp(std::move(container));

  // Check if elements are equal
  BOOST_CHECK_EQUAL(cmp[0], ptr1);
  BOOST_CHECK_EQUAL(cmp[1], ptr2);
  BOOST_CHECK_EQUAL(cmp.getSize(), 2);

  BOOST_CHECK_EQUAL(container.getSize(), 0);
}

BOOST_FIXTURE_TEST_CASE(testContainerRotate, FixtureCompShape)
{
  // Init testing object
  container.addElement(std::shared_ptr< hvatov::Shape >(new hvatov::Rectangle(15, 15, 10, 20)));
  container.addElement(std::shared_ptr< hvatov::Shape >(new hvatov::Rectangle(25, 15, 10, 20)));

  // rotate 45 degrees
  container.rotate(45);

  // Check 
  BOOST_CHECK_CLOSE(container[0]->getArea(), 10 * 20, Epsilon);
  BOOST_CHECK_CLOSE(container[1]->getArea(), 10 * 20, Epsilon);
  // Check frame rectangle
  hvatov::rectangle_t r = container.getFrameRect();
  BOOST_CHECK_CLOSE(r.pos.x, 20, Epsilon);
  BOOST_CHECK_CLOSE(r.pos.y, 15, Epsilon);
  BOOST_CHECK_CLOSE(container.getArea(), 10 * 20 * 2, Epsilon);
}

BOOST_FIXTURE_TEST_CASE(testContainerAdd, FixtureCompShape)
{
  // Init buffer variable
  hvatov::CompositeShape cmp;
  cmp.addElement(std::shared_ptr< hvatov::Shape >(new hvatov::Rectangle(10, 10, 10, 10)));
  cmp.addElement(std::shared_ptr< hvatov::Shape >(new hvatov::Circle(10, 10, 10)));

  // Init testing object
  container.addElement(std::shared_ptr< hvatov::Shape >(new hvatov::Circle(30, 30, 30)));

  // Add containers
  container = container + cmp;

  // Check if there are 3 elements
  BOOST_CHECK_EQUAL(container.getSize(), 3);
}

BOOST_FIXTURE_TEST_CASE(testContainerIndex, FixtureCompShape)
{
  std::shared_ptr< hvatov::Shape > ptr(new hvatov::Rectangle(10, 10, 10, 10));
  // Init testing object
  container.addElement(ptr);

  // Check if elements are equal
  BOOST_CHECK_EQUAL(container[0], ptr);

  // Check if throws an exception if index is invalid
  BOOST_CHECK_THROW(container[10], std::invalid_argument);
}

BOOST_FIXTURE_TEST_CASE(testContainerArea, FixtureCompShape)
{
  // Init testing object
  container.addElement(std::shared_ptr< hvatov::Shape >(new hvatov::Circle(30, 30, 30)));
  container.addElement(std::shared_ptr< hvatov::Shape >(new hvatov::Rectangle(30, 30, 30, 30)));

  // Check 
  BOOST_CHECK_CLOSE(container.getArea(), M_PI * 30 * 30 + 900, Epsilon);
}

BOOST_FIXTURE_TEST_CASE(testContainerAreaMove, FixtureCompShape)
{
  // Init testing object
  container.addElement(std::shared_ptr< hvatov::Shape >(new hvatov::Circle(30, 30, 30)));
  container.addElement(std::shared_ptr< hvatov::Shape >(new hvatov::Rectangle(30, 30, 30, 30)));

  // Check 
  BOOST_CHECK_CLOSE(container.getArea(), M_PI * 30 * 30 + 900, Epsilon);

  // Move to point
  container.move({ 100, 100 });
  // Check 
  BOOST_CHECK_CLOSE(container.getArea(), M_PI * 30 * 30 + 900, Epsilon);

  // Move relatively
  container.move(100, 100);
  // Check 
  BOOST_CHECK_CLOSE(container.getArea(), M_PI * 30 * 30 + 900, Epsilon);
}

BOOST_FIXTURE_TEST_CASE(testContainerScale, FixtureCompShape)
{
  // Init testing object
  container.addElement(std::shared_ptr< hvatov::Shape >(new hvatov::Circle(30, 30, 30)));
  container.addElement(std::shared_ptr< hvatov::Shape >(new hvatov::Rectangle(30, 30, 30, 30)));

  // Scale
  container.scale(10);

  // Check area
  BOOST_CHECK_CLOSE(container[0]->getArea(), M_PI * 30 * 30 * 10 * 10, Epsilon);
  BOOST_CHECK_CLOSE(container[1]->getArea(), 30 * 30 * 10 * 10, Epsilon);

  // Check frame rectangle
  BOOST_CHECK_CLOSE(container[0]->getFrameRect().width, 10 * 30 * 2, Epsilon);
  BOOST_CHECK_CLOSE(container[0]->getFrameRect().height, 10 * 30 * 2, Epsilon);
  BOOST_CHECK_CLOSE(container[1]->getFrameRect().width, 10 * 30, Epsilon);
  BOOST_CHECK_CLOSE(container[1]->getFrameRect().height, 10 * 30, Epsilon);
}

BOOST_FIXTURE_TEST_CASE(testContainerScaleMove, FixtureCompShape)
{
  // Init testing object
  container.addElement(std::shared_ptr< hvatov::Shape >(new hvatov::Circle(30, 30, 30)));
  container.addElement(std::shared_ptr< hvatov::Shape >(new hvatov::Rectangle(30, 30, 30, 30)));

  container.scale(10);

  // Check 
  BOOST_CHECK_CLOSE(container[0]->getArea(), M_PI * 30 * 30 * 10 * 10, Epsilon);
  BOOST_CHECK_CLOSE(container[1]->getArea(), 30 * 30 * 10 * 10, Epsilon);

  // Move to point
  container.move({ 100, 100 });
  // Check 
  BOOST_CHECK_CLOSE(container[0]->getArea(), M_PI * 30 * 30 * 10 * 10, Epsilon);
  BOOST_CHECK_CLOSE(container[1]->getArea(), 30 * 30 * 10 * 10, Epsilon);

  // Move relatively
  container.move(100, 100);
  // Check 
  BOOST_CHECK_CLOSE(container[0]->getArea(), M_PI * 30 * 30 * 10 * 10, Epsilon);
  BOOST_CHECK_CLOSE(container[1]->getArea(), 30 * 30 * 10 * 10, Epsilon);
}

BOOST_FIXTURE_TEST_CASE(testContainerMove, FixtureCompShape)
{
  // Init testing object
  container.addElement(std::shared_ptr< hvatov::Shape >(new hvatov::Circle(30, 30, 30)));
  container.addElement(std::shared_ptr< hvatov::Shape >(new hvatov::Rectangle(30, 30, 30, 30)));

  container.move({ 100, 100 });

  // Check 
  BOOST_CHECK_CLOSE(container[0]->getPosition().x, 100, Epsilon);
  BOOST_CHECK_CLOSE(container[0]->getPosition().y, 100, Epsilon);
  BOOST_CHECK_CLOSE(container[1]->getPosition().x, 100, Epsilon);
  BOOST_CHECK_CLOSE(container[1]->getPosition().y, 100, Epsilon);

  container.move(100, 100);

  // Check 
  BOOST_CHECK_CLOSE(container[0]->getPosition().x, 200, Epsilon);
  BOOST_CHECK_CLOSE(container[0]->getPosition().y, 200, Epsilon);
  BOOST_CHECK_CLOSE(container[1]->getPosition().x, 200, Epsilon);
  BOOST_CHECK_CLOSE(container[1]->getPosition().y, 200, Epsilon);
}

BOOST_FIXTURE_TEST_CASE(testContainerAddElement, FixtureCompShape)
{
  std::shared_ptr< hvatov::Shape > ptr(new hvatov::Rectangle(10, 10, 10, 10));
  // Init testing object
  container.addElement(ptr);

  // Check 
  BOOST_CHECK_EQUAL(container[0], ptr);
}

BOOST_FIXTURE_TEST_CASE(testContainerAddNull, FixtureCompShape)
{
  std::shared_ptr< hvatov::Shape > ptr = nullptr;

  // Check 
  BOOST_CHECK_THROW(container.addElement(ptr), std::invalid_argument);
}

BOOST_FIXTURE_TEST_CASE(testContainerDelete, FixtureCompShape)
{
  std::shared_ptr< hvatov::Shape > ptr1(new hvatov::Rectangle(10, 10, 10, 10));
  std::shared_ptr< hvatov::Shape > ptr2(new hvatov::Rectangle(10, 10, 20, 20));

  container.addElement(ptr1);
  container.addElement(ptr2);
  container.deleteElement(0);

  // Check 
  BOOST_CHECK_EQUAL(container.getSize(), 1);
  BOOST_CHECK_CLOSE(container[0]->getFrameRect().height, 20, Epsilon);
  BOOST_CHECK_CLOSE(container[0]->getFrameRect().width, 20, Epsilon);
}

BOOST_FIXTURE_TEST_CASE(testContainerDeleteIndex, FixtureCompShape)
{
  std::shared_ptr< hvatov::Shape > ptr1(new hvatov::Rectangle(10, 10, 10, 10));
  std::shared_ptr< hvatov::Shape > ptr2(new hvatov::Rectangle(10, 10, 20, 20));

  container.addElement(ptr1);
  container.addElement(ptr2);
  BOOST_CHECK_THROW(container.deleteElement(10), std::invalid_argument);
}

BOOST_FIXTURE_TEST_CASE(testContainerSize, FixtureCompShape)
{
  std::shared_ptr< hvatov::Shape > ptr1(new hvatov::Rectangle(10, 10, 10, 10));
  std::shared_ptr< hvatov::Shape > ptr2(new hvatov::Rectangle(10, 10, 20, 20));

  container.addElement(ptr1);
  container.addElement(ptr2);
  BOOST_CHECK_EQUAL(container.getSize(), 2);
}

BOOST_FIXTURE_TEST_CASE(testContainerClear, FixtureCompShape)
{
  std::shared_ptr< hvatov::Shape > ptr1(new hvatov::Rectangle(10, 10, 10, 10));
  std::shared_ptr< hvatov::Shape > ptr2(new hvatov::Rectangle(10, 10, 20, 20));

  container.addElement(ptr1);
  container.addElement(ptr2);

  container.clear();

  BOOST_CHECK_EQUAL(container.getSize(), 0);
}

BOOST_AUTO_TEST_SUITE_END()

