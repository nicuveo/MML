//
// utils.hh for mml
// Made by nicuveo <crucuny@gmail.com>
//

#ifndef MML_UTILS_HH_
# define MML_UTILS_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <cmath>
# include <boost/mpl/logical.hpp>
# include "mml/lib/misc.hh"
# include "mml/lib/template.hh"
# include "mml/lib/operators.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace mml
{

  // clamp

  template <typename T>
  inline T
  clamp(T const& x, T const& min, T const& max)
  {
    return lt(x, min) ? min : (gt(x, max) ? max : x);
  }

  template <typename T>
  inline Point<T>
  clamp(const Point<T>& p, const Point<T>& min, const Point<T>& max)
  {
    return Point<T>(
      clamp(p.x(), min.x(), max.x()),
      clamp(p.y(), min.y(), max.y()));
  }

  template <typename T>
  inline Point<T>
  clamp(const Point<T>& p, const Rect<T>& r)
  {
    return clamp(p, r.min(), r.max());
  }


  // random

  template <typename T>
  inline Point<T> // Vector
  random_vector()
  {
    return Point<T>(
      -RAND_MAX / 2 + rand(),
      -RAND_MAX / 2 + rand());
  }


  // type-aware modulo

  template <typename T1, typename T2>
  inline MML_ENABLE_IF(MML_HAS(MML_MOD, T1, T2), MML_RESULT(MML_MOD, T1, T2))
  mml_mod(T1 const& t1, T2 const& t2)
  {
    return t1 % t2;
  }

  template <typename T1, typename T2>
  inline MML_ENABLE_IF(MML_HASNT(MML_MOD, T1, T2), BOOST_TYPEOF_TPL(std::fmod(T1(), T2())))
  mml_mod(T1 const& t1, T2 const& t2)
  {
    return std::fmod(t1, t2);
  }

}



#endif /* !MML_UTILS_HH_ */
