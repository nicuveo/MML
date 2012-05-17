//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

#include <cstdlib>
#include <iostream>
#include <mml/mml.hh>

#define BOOST_TEST_MODULE Rect
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

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

BOOST_AUTO_TEST_CASE(t0)
{
  srand(time(0));

  int x0 = next();
  int x1 = next();
  int y0 = next();
  int y1 = next();

  if (x1 < x0)
    std::swap(x0, x1);
  if (y1 < y0)
    std::swap(y0, y1);

  Rect r0;
  Rect r1(x0, y0, x1, y1);
  Rect r2(r1);

  BOOST_REQUIRE_EQUAL(r0, Rect());
  BOOST_REQUIRE_EQUAL(r0, Rect(0, 0, 0, 0));
  BOOST_REQUIRE_EQUAL(r0, Rect(Point(0, 0), Point(0, 0)));
  BOOST_REQUIRE_EQUAL(r0.min(), Point(0, 0));
  BOOST_REQUIRE_EQUAL(r0.max(), Point(0, 0));
  BOOST_REQUIRE_EQUAL(r0.x_min(), 0);
  BOOST_REQUIRE_EQUAL(r0.y_min(), 0);
  BOOST_REQUIRE_EQUAL(r0.x_max(), 0);
  BOOST_REQUIRE_EQUAL(r0.y_max(), 0);

  BOOST_REQUIRE_EQUAL(r1, Rect(x0, y0, x1, y1));
  BOOST_REQUIRE_EQUAL(r1, Rect(Point(x0, y0), Point(x1, y1)));
  BOOST_REQUIRE_EQUAL(r1.min(), Point(x0, y0));
  BOOST_REQUIRE_EQUAL(r1.max(), Point(x1, y1));
  BOOST_REQUIRE_EQUAL(r1.x_min(), x0);
  BOOST_REQUIRE_EQUAL(r1.y_min(), y0);
  BOOST_REQUIRE_EQUAL(r1.x_max(), x1);
  BOOST_REQUIRE_EQUAL(r1.y_max(), y1);

  BOOST_REQUIRE_EQUAL(r2, Rect(r1));
  BOOST_REQUIRE_EQUAL(r2, Rect(x0, y0, x1, y1));
  BOOST_REQUIRE_EQUAL(r2, Rect(Point(x0, y0), Point(x1, y1)));
  BOOST_REQUIRE_EQUAL(r2.min(), Point(x0, y0));
  BOOST_REQUIRE_EQUAL(r2.max(), Point(x1, y1));
  BOOST_REQUIRE_EQUAL(r2.x_min(), x0);
  BOOST_REQUIRE_EQUAL(r2.y_min(), y0);
  BOOST_REQUIRE_EQUAL(r2.x_max(), x1);
  BOOST_REQUIRE_EQUAL(r2.y_max(), y1);
}

BOOST_AUTO_TEST_CASE(t1)
{
  srand(time(0));

  int x0 = next();
  int x1 = next();
  int y0 = next();
  int y1 = next();

  if (x1 < x0)
    std::swap(x0, x1);
  if (y1 < y0)
    std::swap(y0, y1);

  Rect r0;
  Rect r1(x0, y0, x1, y1);
  Rect r2(r1);

  BOOST_REQUIRE_EQUAL(r0.bounding_rect(), r0);
  BOOST_REQUIRE_EQUAL(r1.bounding_rect(), r1);
  BOOST_REQUIRE_EQUAL(r2.bounding_rect(), r2);

  BOOST_REQUIRE_EQUAL(r0.delta(), Vector(0, 0));
  BOOST_REQUIRE_EQUAL(r1.delta(), Vector(x1 - x0, y1 - y0));
  BOOST_REQUIRE_EQUAL(r2.delta(), Vector(x1 - x0, y1 - y0));

  BOOST_REQUIRE_EQUAL(r0.center(), Point(0, 0));
  BOOST_REQUIRE_EQUAL(r1.center(), Point((x0 + x1) / 2, (y0 + y1) / 2));
  BOOST_REQUIRE_EQUAL(r2.center(), Point((x0 + x1) / 2, (y0 + y1) / 2));
}

BOOST_AUTO_TEST_CASE(t2)
{
  srand(time(0));

  int x0 = next();
  int x1 = next();
  int y0 = next();
  int y1 = next();

  if (x1 < x0)
    std::swap(x0, x1);
  if (y1 < y0)
    std::swap(y0, y1);

  Rect r0;
  Rect r1(x0, y0, x1, y1);
  Rect r2(r1);

  BOOST_REQUIRE_EQUAL(r0.area(), r0.width() * r0.height());
  BOOST_REQUIRE_EQUAL(r1.area(), r1.width() * r1.height());
  BOOST_REQUIRE_EQUAL(r2.area(), r2.width() * r2.height());
  BOOST_REQUIRE_EQUAL(r0.area(), 0);
  BOOST_REQUIRE_EQUAL(r1.area(), (x1 - x0) * (y1 - y0));
  BOOST_REQUIRE_EQUAL(r2.area(), (x1 - x0) * (y1 - y0));

  BOOST_REQUIRE_EQUAL(r0.perimeter(), 2 * (r0.width() + r0.height()));
  BOOST_REQUIRE_EQUAL(r1.perimeter(), 2 * (r1.width() + r1.height()));
  BOOST_REQUIRE_EQUAL(r2.perimeter(), 2 * (r2.width() + r2.height()));
  BOOST_REQUIRE_EQUAL(r0.perimeter(), 0);
  BOOST_REQUIRE_EQUAL(r1.perimeter(), 2 * (x1 - x0) + 2 * (y1 - y0));
  BOOST_REQUIRE_EQUAL(r2.perimeter(), 2 * (x1 - x0) + 2 * (y1 - y0));
}
