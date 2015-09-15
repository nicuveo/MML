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



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Custom shapes

#define MMLM_EXTRA_SHAPES \
  ((DIAMOND, Diamond, diamond, 11))

#include "diamond.hh"
#include "nauths/mml/mml.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

BOOST_AUTO_TEST_SUITE(extra)

BOOST_AUTO_TEST_CASE(extra_00)
{
  typedef mml::Diamond<int> Diamond;
  typedef mml::Point<int> Point;
  typedef mml::Shape<int> Shape;

  Diamond d0;
  Diamond d1(4, 3);
  Diamond d2(Point(10, 10), 4, 3);
  Shape s0 = d0;
  Shape s1 = d1;
  Shape s2 = d2;

  BOOST_REQUIRE(not s0.valid());
  BOOST_REQUIRE(    s1.valid());
  BOOST_REQUIRE(    s2.valid());
}

BOOST_AUTO_TEST_SUITE_END()
