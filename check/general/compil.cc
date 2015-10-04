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

#include <sstream>
#include <iostream>
#include <boost/test/unit_test.hpp>
#include "nauths/mml/mml.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

BOOST_AUTO_TEST_SUITE(compil)

BOOST_AUTO_TEST_CASE(decl)
{
  mml::Circle<mml::Num>   nc;
  mml::Circle<mml::Real>  rc;
  mml::Point<mml::Num>    np;
  mml::Point<mml::Real>   rp;
  mml::Line<mml::Num>     nl;
  mml::Line<mml::Real>    rl;
  mml::Polygon<mml::Num>  nq;
  mml::Polygon<mml::Real> rq;
  mml::Rect<mml::Num>     nr;
  mml::Rect<mml::Real>    rr;
  mml::Shape<mml::Num>    ns;
  mml::Shape<mml::Real>   rs;

  std::stringstream s;
  s << "nc: " << nc << std::endl
    << "rc: " << rc << std::endl
    << "np: " << np << std::endl
    << "rp: " << rp << std::endl
    << "nl: " << nl << std::endl
    << "rl: " << rl << std::endl
    << "nq: " << nq << std::endl
    << "rq: " << rq << std::endl
    << "nr: " << nr << std::endl
    << "rr: " << rr << std::endl
    << "ns: " << ns << std::endl
    << "rs: " << rs << std::endl;

  BOOST_REQUIRE(true);
}

BOOST_AUTO_TEST_SUITE_END()
