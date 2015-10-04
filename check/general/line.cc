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
  typedef mml::Line<mml::Num> Line;

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

BOOST_AUTO_TEST_SUITE(line)

BOOST_AUTO_TEST_CASE(Line_0)
{
  Line l0;

  BOOST_REQUIRE(l0.p0() == Point(0, 0));
  BOOST_REQUIRE(l0.p1() == Point(0, 0));
  BOOST_REQUIRE(l0.p0() == l0.p1());
  BOOST_REQUIRE(not l0.valid());


  Line l1(10, 10, 20, 20);

  BOOST_REQUIRE(l1.p0() == Point(10, 10));
  BOOST_REQUIRE(l1.p1() == Point(20, 20));
  BOOST_REQUIRE(l1.p0() != l1.p1());
  BOOST_REQUIRE(l1.valid());


  Line l2(Point(10, 10), Point(20, 20));

  BOOST_REQUIRE(l2.p0() == Point(10, 10));
  BOOST_REQUIRE(l2.p1() == Point(20, 20));
  BOOST_REQUIRE(l2.p0() != l2.p1());
  BOOST_REQUIRE(l2.valid());
}

BOOST_AUTO_TEST_SUITE_END()
