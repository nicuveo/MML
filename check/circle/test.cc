//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

#include <cstdlib>
#include <iostream>
#include <mml/mml.hh>

#define BOOST_TEST_MODULE Circle
#include <boost/test/included/unit_test.hpp>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local code

namespace
{

  int next()
  {
    return sqrt(rand()) / 5;
  }

  typedef mml::Shape<mml::Num> Shape;
  typedef mml::Point<mml::Num> Point;
  typedef mml::Point<mml::Num> Vector;
  typedef mml::Rect<mml::Num> Rect;
  typedef mml::Circle<mml::Num> Circle;

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

BOOST_AUTO_TEST_CASE(t0)
{
  srand(time(0));

  int x = next();
  int y = next();
  int r = next();

  Circle c0;
  Circle c1(x, y, r);
  Circle c2(c1);

  BOOST_REQUIRE_EQUAL(c0, Circle());
  BOOST_REQUIRE_EQUAL(c0, Circle(0, 0, 0));
  BOOST_REQUIRE_EQUAL(c0, Circle(Point(0, 0), 0));
  BOOST_REQUIRE_EQUAL(c0.center(), Point(0, 0));
  BOOST_REQUIRE_EQUAL(c0.radius(), 0);

  BOOST_REQUIRE_EQUAL(c1, Circle(x, y, r));
  BOOST_REQUIRE_EQUAL(c1, Circle(Point(x, y), r));
  BOOST_REQUIRE_EQUAL(c1.center(), Point(x, y));
  BOOST_REQUIRE_EQUAL(c1.radius(), r);

  BOOST_REQUIRE_EQUAL(c2, Circle(x, y, r));
  BOOST_REQUIRE_EQUAL(c2, Circle(Point(x, y), r));
  BOOST_REQUIRE_EQUAL(c2.center(), Point(x, y));
  BOOST_REQUIRE_EQUAL(c2.radius(), r);
}

BOOST_AUTO_TEST_CASE(t1)
{
  srand(time(0));

  int x = next();
  int y = next();
  int r = next();

  Circle c0;
  Circle c1(x, y, r);
  Circle c2(c1);

  BOOST_REQUIRE_EQUAL(c0.bounding_rect(), Rect(0, 0, 0, 0));
  BOOST_REQUIRE_EQUAL(c1.bounding_rect(), Rect(x - r, y - r, x + r, y + r));
  BOOST_REQUIRE_EQUAL(c2.bounding_rect(), Rect(x - r, y - r, x + r, y + r));
}

BOOST_AUTO_TEST_CASE(t2)
{
  srand(time(0));

  int x = next();
  int y = next();
  int r = next();

  Circle c0;
  Circle c1(x, y, r);
  Circle c2(c1);

  BOOST_REQUIRE_EQUAL(c0.area(), 0);
  BOOST_REQUIRE_EQUAL(c1.area(), c1.radius() * c1.radius() * mml::pi());
  BOOST_REQUIRE_EQUAL(c2.area(), c2.radius() * c2.radius() * mml::pi());
}

BOOST_AUTO_TEST_CASE(t3)
{
  srand(time(0));

  int x = next();
  int y = next();
  int r = next();

  Circle c0;
  Circle c1(x, y, r);
  Circle c2(c1);

  BOOST_REQUIRE_EQUAL(c0.perimeter(), 0);
  BOOST_REQUIRE_EQUAL(c1.perimeter(), 2 * c1.radius() * mml::pi());
  BOOST_REQUIRE_EQUAL(c2.perimeter(), 2 * c2.radius() * mml::pi());
}
