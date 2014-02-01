//
// Copyright Antoine Leblanc 2010 - 2013
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef MML_CONSTANTS_HH_
# define MML_CONSTANTS_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <limits>
# include <boost/math/constants/constants.hpp>
# include "nauths/mml/types.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace mml
{

  inline Real pi()
  {
    return boost::math::constants::pi<Real>();
  }

  inline Real tau()
  {
    return 2 * boost::math::constants::pi<Real>();
  }

  inline Real root_2()
  {
    return 1.41421356237;
  }

  inline Real root_2_div_2()
  {
    return 0.707106781187;
  }

  inline Real root_3()
  {
    return 1.73205080757;
  }

  inline Real root_3_div_2()
  {
    return 0.866025403784;
  }

  inline Real root_3_div_3()
  {
    return 0.57735026919;
  }

  inline Real root_3_div_4()
  {
    return 0.433012701892;
  }

  inline Real infinity()
  {
    return std::numeric_limits<Real>::infinity();
  }

}



#endif /* !MML_CONSTANTS_HH_ */
