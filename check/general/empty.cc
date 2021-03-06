//
// Copyright Antoine Leblanc 2010 - 2015
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
#include <boost/test/unit_test.hpp>
#include "nauths/mml/mml.hh"



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

BOOST_AUTO_TEST_SUITE(empty)

BOOST_AUTO_TEST_CASE(Empty_00)
{
  Shape s;

  BOOST_REQUIRE_EQUAL(s.type(), mml::shape::EMPTY);
  BOOST_REQUIRE_EQUAL(s.empty(), true);

  BOOST_REQUIRE_EQUAL(s.perimeter(), 0);
  BOOST_REQUIRE_EQUAL(s.area(), 0);

  BOOST_REQUIRE_EQUAL(s.bounding_rect(), Rect(0, 0, 0, 0));
}

BOOST_AUTO_TEST_SUITE_END()
