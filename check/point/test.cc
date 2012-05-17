//
// test.cc for mml
// Made by nicuveo <crucuny@gmail.com>
//



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

#include <cstdlib>
#include <iostream>
#include <mml/mml.hh>

#define BOOST_TEST_MODULE Point
#include <boost/test/included/unit_test.hpp>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local code

namespace
{

  int next()
  {
    return sqrt(rand()) / 5;
  }

  typedef mml::Point<mml::Num> Point;

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

BOOST_AUTO_TEST_CASE(t0)
{
  srand(time(0));

  int x = next() - next();
  int y = next() - next();

  Point p0;
  Point p1(x, y);
  Point p2(p1);

  BOOST_REQUIRE_EQUAL(p0, Point());
  BOOST_REQUIRE_EQUAL(p0, Point(0, 0));
  BOOST_REQUIRE_EQUAL(p0.x(), 0);
  BOOST_REQUIRE_EQUAL(p0.y(), 0);
  BOOST_REQUIRE_EQUAL(p0.rx(), 0);
  BOOST_REQUIRE_EQUAL(p0.ry(), 0);
  BOOST_REQUIRE_EQUAL(p0[0], 0);
  BOOST_REQUIRE_EQUAL(p0[1], 0);

  BOOST_REQUIRE_EQUAL(p1, Point(x, y));
  BOOST_REQUIRE_EQUAL(p1.x(), x);
  BOOST_REQUIRE_EQUAL(p1.y(), y);
  BOOST_REQUIRE_EQUAL(p1.rx(), x);
  BOOST_REQUIRE_EQUAL(p1.ry(), y);
  BOOST_REQUIRE_EQUAL(p1[0], x);
  BOOST_REQUIRE_EQUAL(p1[1], y);

  BOOST_REQUIRE_EQUAL(p2, p1);
  BOOST_REQUIRE_EQUAL(p2.x(), p1.x());
  BOOST_REQUIRE_EQUAL(p2.y(), p1.y());
  BOOST_REQUIRE_EQUAL(p2.rx(), p1.x());
  BOOST_REQUIRE_EQUAL(p2.ry(), p1.y());
  BOOST_REQUIRE_EQUAL(p2[0], p1.x());
  BOOST_REQUIRE_EQUAL(p2[1], p1.y());
}

BOOST_AUTO_TEST_CASE(t1)
{
  srand(time(0));

  int x = next() - next();
  int y = next() - next();

  Point p0;
  Point p1(x, y);
  Point p2(p1);

  BOOST_REQUIRE_EQUAL(p0.length(), 0);
  BOOST_REQUIRE_EQUAL(p0.sqr_length(), 0);
  BOOST_REQUIRE_EQUAL(p1.length(), sqrt(x * x + y * y));
  BOOST_REQUIRE_EQUAL(p1.sqr_length(), x * x + y * y);
  BOOST_REQUIRE_EQUAL(p2.length(), p1.length());
  BOOST_REQUIRE_EQUAL(p2.sqr_length(), p1.sqr_length());
}

BOOST_AUTO_TEST_CASE(t2)
{
  srand(time(0));

  int x = next() - next();
  int y = next() - next();

  Point p0;
  Point p1(x, y);
  Point p2(p1);

  BOOST_REQUIRE_EQUAL(p0 * 4, p0);
  BOOST_REQUIRE_EQUAL(p0 / 4, p0);
  BOOST_REQUIRE_EQUAL(p0 % 4, p0);
  BOOST_REQUIRE_EQUAL(p0 + p0, p0);
  BOOST_REQUIRE_EQUAL(p0 - p0, p0);
  BOOST_REQUIRE_EQUAL(p0 * p0, 0);
  BOOST_REQUIRE_EQUAL(p0.normal(), p0);

  BOOST_REQUIRE_EQUAL(p1 * 4, Point(x * 4, y * 4));
  BOOST_REQUIRE_EQUAL(p1 / 4, Point(x / 4, y / 4));
  BOOST_REQUIRE_EQUAL(p1 % 4, Point(x % 4, y % 4));
  BOOST_REQUIRE_EQUAL(p1 + p0, p1);
  BOOST_REQUIRE_EQUAL(p1 - p0, p1);
  BOOST_REQUIRE_EQUAL(p1 * p0, 0);
  BOOST_REQUIRE_EQUAL(p1 * p1, x * x + y * y);
  BOOST_REQUIRE_EQUAL(p1.normal(), Point(-y, x));
}

BOOST_AUTO_TEST_CASE(t3)
{
  srand(time(0));

  int x = next() - next();
  int y = next() - next();

  Point p(x, y);

#define C_TEST_TYPE(TYPE, MIN, MAX)             \
  {                                             \
    typedef TYPE T;                             \
    for (T i = T(MIN); i < T(MAX); i += T(1))   \
      BOOST_REQUIRE_EQUAL(p * i, i * p);        \
  }                                             \

  C_TEST_TYPE(signed char,     -10, 10);
  C_TEST_TYPE(unsigned char,     0, 10);
  C_TEST_TYPE(signed short,    -10, 10);
  C_TEST_TYPE(unsigned short,    0, 10);
  C_TEST_TYPE(signed int,      -10, 10);
  C_TEST_TYPE(unsigned int,      0, 10);
  C_TEST_TYPE(signed long,     -10, 10);
  C_TEST_TYPE(unsigned long,     0, 10);
  C_TEST_TYPE(float,           -10, 10);
  C_TEST_TYPE(double,          -10, 10);
}
