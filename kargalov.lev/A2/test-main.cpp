#define BOOST_TEST_MODULE main
#define BOOST_TEST_DYN_LINK

#include <stdexcept>
#include <boost/test/included/unit_test.hpp>

#include "circle.hpp"
#include "rectangle.hpp"

using namespace kargalov;

const double EPSILON = 0.0000001;

BOOST_AUTO_TEST_SUITE(RectangleSuite)

const point_t center = {1, 34};
const double width = 245;
const double height = 12;
Rectangle testrect({width, height, center});
const double areaBefore = testrect.getArea();


BOOST_AUTO_TEST_CASE(testMoving)
{
    testrect.move({100, 23});
    BOOST_CHECK_CLOSE_FRACTION(testrect.getFrameRect().width, width, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testrect.getFrameRect().height, height, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testrect.getArea(), areaBefore, EPSILON);

    testrect.move(45, 11);
    BOOST_CHECK_CLOSE_FRACTION(testrect.getFrameRect().width, width, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testrect.getFrameRect().height, height, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testrect.getArea(), areaBefore, EPSILON);
}

BOOST_AUTO_TEST_CASE(testArea){
    testrect.scale(102);
    BOOST_CHECK_CLOSE_FRACTION(testrect.getArea(), areaBefore * 102 * 102, EPSILON);
}

BOOST_AUTO_TEST_CASE(testIncorrectParametrs){
    BOOST_CHECK_THROW( testrect.scale(-1.0), std::invalid_argument );
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CircleSuite)

const point_t center = {1, 34};
const double radius = 245;
Circle testcirc(center, radius);
const double areaBefore = testcirc.getArea();


BOOST_AUTO_TEST_CASE(testMoving)
{
    testcirc.move({100, 23});
    BOOST_CHECK_CLOSE_FRACTION(testcirc.getFrameRect().width, radius * 2, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testcirc.getArea(), areaBefore, EPSILON);

    testcirc.move(45, 11);
    BOOST_CHECK_CLOSE_FRACTION(testcirc.getFrameRect().width, radius * 2, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testcirc.getArea(), areaBefore, EPSILON);
}

BOOST_AUTO_TEST_CASE(testArea){
    testcirc.scale(102);
    BOOST_CHECK_CLOSE_FRACTION(testcirc.getArea(), areaBefore * 102 * 102, EPSILON);
}

BOOST_AUTO_TEST_CASE(testIncorrectParametrs){
    BOOST_CHECK_THROW( testcirc.scale(-1.0), std::invalid_argument );
}
BOOST_AUTO_TEST_SUITE_END()
