//
// test.cc for mml
// Made by nicuveo <crucuny@gmail.com>
//



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

#include <iostream>

#define BOOST_TEST_MODULE Compil
#include <boost/test/included/unit_test.hpp>

#include "includes.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

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

  std::cout << "nc: " << nc << std::endl
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
