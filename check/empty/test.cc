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
#include <nauths/mml/mml.hh>

#define BOOST_TEST_MODULE Empty
#include <boost/test/included/unit_test.hpp>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local code

namespace
{

  typedef mml::Shape<mml::Num> Shape;
  typedef mml::Point<mml::Num> Point;
  typedef mml::Rect<mml::Num> Rect;

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

BOOST_AUTO_TEST_CASE(Empty_00)
{
  Shape s;

  BOOST_REQUIRE_EQUAL(s.type(), mml::shape::EMPTY);
  BOOST_REQUIRE_EQUAL(s.empty(), true);

  BOOST_REQUIRE_EQUAL(s.perimeter(), 0);
  BOOST_REQUIRE_EQUAL(s.area(), 0);

  BOOST_REQUIRE_EQUAL(s.bounding_rect(), Rect(0, 0, 0, 0));
}
