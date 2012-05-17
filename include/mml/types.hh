//
// types.hh for mml
// Made by nicuveo <crucuny@gmail.com>
//

#ifndef MML_TYPES_HH_
# define MML_TYPES_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <cmath>
# include "mml/lib/real.hh"
# include "mml/lib/template.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Macros

# ifndef MML_NUM
#  define MML_NUM int
# endif

# ifndef MML_REAL
#  define MML_REAL double
# endif



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Internal types

namespace mml
{

  namespace il
  {

    template <typename T> class Shape;
    template <typename T> class Point;
    template <typename T> class Line;
    template <typename T> class Rect;
    template <typename T> class Circle;
    template <typename T> class Polygon;
    template <typename T> class Empty;

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
    return Num(x < 0 ? std::ceil(x - 0.5) : std::floor(x + 0.5));
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



#endif /* !MML_TYPES_HH_ */
