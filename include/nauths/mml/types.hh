//
// Copyright Antoine Leblanc 2010 - 2014
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef MML_TYPES_HH_
# define MML_TYPES_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <cmath>
# include "nauths/mml/lib/real.hh"
# include "nauths/mml/lib/template.hh"
# include "nauths/mml/shapes/shape_macros.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Macros

# ifndef MML_NUM
#  define MML_NUM int
# endif

# ifndef MML_REAL
#  define MML_REAL double
# endif



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local macros

# define MMLM_decl(_1, _2, S)                                        \
  template <typename T>                                              \
  class MMLM_Name(S);                                                \



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Internal types

namespace mml
{

  namespace il
  {

    template <typename T>
    class Shape;

    BOOST_PP_SEQ_FOR_EACH(MMLM_decl, _, MMLM_ALL_SHAPES)

  }

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace mml
{

  // Numeric types

  typedef MML_NUM  Num;
  typedef MML_REAL Real;

  typedef TOOLS_PRM(Num) PrmNum;
  typedef TOOLS_REF(Num) RefNum;
  typedef TOOLS_PRM(Real) PrmReal;
  typedef TOOLS_REF(Real) RefReal;

  template <typename T, typename F> inline T to(F const& x) { return static_cast<T>(x); }

  template <typename T> inline bool eq(T const& x, T const& y) { return x == y; }
  template <typename T> inline bool ne(T const& x, T const& y) { return x != y; }
  template <typename T> inline bool lt(T const& x, T const& y) { return x <  y; }
  template <typename T> inline bool le(T const& x, T const& y) { return x <= y; }
  template <typename T> inline bool gt(T const& x, T const& y) { return x >  y; }
  template <typename T> inline bool ge(T const& x, T const& y) { return x >= y; }


  // Rounding

# ifndef MML_NO_ROUNDING

  template <> inline Num to<Num, Real>(Real const& x)
  {
    return Num(std::floor(0.5 + x));
  }

# endif


  // Approximation

# ifndef MML_NO_APPROX

#  ifndef MML_THRESHOLD
#   define MML_THRESHOLD -6 // epsilon = 1E-6
#  endif

  template <> inline bool eq(Real const& x, Real const& y) { return eq<tools::Real<Real, MML_THRESHOLD> >(x, y); }
  template <> inline bool ne(Real const& x, Real const& y) { return ne<tools::Real<Real, MML_THRESHOLD> >(x, y); }
  template <> inline bool lt(Real const& x, Real const& y) { return lt<tools::Real<Real, MML_THRESHOLD> >(x, y); }
  template <> inline bool le(Real const& x, Real const& y) { return le<tools::Real<Real, MML_THRESHOLD> >(x, y); }
  template <> inline bool gt(Real const& x, Real const& y) { return gt<tools::Real<Real, MML_THRESHOLD> >(x, y); }
  template <> inline bool ge(Real const& x, Real const& y) { return ge<tools::Real<Real, MML_THRESHOLD> >(x, y); }

# endif


  // Shape trait

  template <typename T>
  struct shapes
  {
    public:
      typedef il::Shape<T>   Shape;
      typedef il::Point<T>   Point;
      typedef il::Point<T>   Vector;
      typedef il::Line<T>    Line;
      typedef il::Rect<T>    Rect;
      typedef il::Circle<T>  Circle;
      typedef il::Polygon<T> Polygon;
  };


  // Shape types

  using il::Shape;
  using il::Point;
  using il::Line;
  using il::Rect;
  using il::Circle;
  using il::Polygon;

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local macros undef

# undef MMLM_decl



#endif /* !MML_TYPES_HH_ */
