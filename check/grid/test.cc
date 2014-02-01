//
// Copyright Antoine Leblanc 2010 - 2013
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <nauths/mml/mml.hh>

#define BOOST_TEST_MODULE Grid
#include <boost/test/included/unit_test.hpp>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local code

namespace
{

  typedef mml::Shape<mml::Num> Shape;
  typedef mml::Point<mml::Num> Point;
  typedef mml::Point<mml::Num> Vector;
  typedef mml::Polygon<mml::Num> Polygon;

  class Object
  {
    public:
      Object(const Shape& s)
        : id(sid++), shape(s)
      {
      }

      const unsigned id;
      const Shape shape;

    private:
      static unsigned sid;
  };

  unsigned Object::sid = 0;

  inline const Shape& shape(Object* const& o)
  {
    return o->shape;
  }

  typedef mml::Grid<Object*, mml::Num> Grid;

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

BOOST_AUTO_TEST_CASE(EMPTY)
{
  Grid g(&shape, Point(0, 0), 10, 100, 100);

  std::pair<float, float> s(0.f, 0.f);
  BOOST_REQUIRE_MESSAGE(g.stats() == s, "wat");
}

BOOST_AUTO_TEST_CASE(BASIC_TEST)
{
  Grid g(&shape, Point(0, 0), 10, 100, 100);
  Polygon p(Shape::tetragon(Point(  0,  50), Point( 50, 100),
                            Point(100,  50), Point( 50,   0)));

  g.insert(new Object(p));

  for (int y = 0; y <= 1000; ++y)
    for (int x = 0; x <= 1000; ++x)
    {
      bool b1 = g.find(Point(x, y)) != 0;
      bool b2 = mml::contains(p, Point(x, y));

      BOOST_REQUIRE_MESSAGE(b1 == b2, Point(x, y) << " => "
                            << std::boolalpha << b1 << ", "
                            << std::boolalpha << b2);
    }
}
