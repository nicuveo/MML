//
// Copyright Antoine Leblanc 2010 - 2015
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
# include <nauths/npl/real.hh>
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

# define MMLM_decl1(_1, _2, S)                                       \
  template <typename T>                                              \
  class MMLM_Name(S);                                                \

# define MMLM_decl2(_1, _2, S)                                       \
  typedef il::MMLM_Name(S)<T>  MMLM_Name(S);                         \

# define MMLM_decl3(_1, _2, S)                                       \
  using il::MMLM_Name(S);                                            \



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Internal types

namespace mml
{

  namespace il
  {

    template <typename T>
    class Shape;

    BOOST_PP_SEQ_FOR_EACH(MMLM_decl1, _, MMLM_ALL_SHAPES)

  }

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace mml
{

  // Numeric types

  typedef MML_NUM  Num;
  typedef MML_REAL Real;

  typedef MML_PRM(Num) PrmNum;
  typedef MML_REF(Num) RefNum;
  typedef MML_PRM(Real) PrmReal;
  typedef MML_REF(Real) RefReal;

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

  template <> inline bool eq(Real const& x, Real const& y) { return eq<npl::Real<Real, MML_THRESHOLD> >(x, y); }
  template <> inline bool ne(Real const& x, Real const& y) { return ne<npl::Real<Real, MML_THRESHOLD> >(x, y); }
  template <> inline bool lt(Real const& x, Real const& y) { return lt<npl::Real<Real, MML_THRESHOLD> >(x, y); }
  template <> inline bool le(Real const& x, Real const& y) { return le<npl::Real<Real, MML_THRESHOLD> >(x, y); }
  template <> inline bool gt(Real const& x, Real const& y) { return gt<npl::Real<Real, MML_THRESHOLD> >(x, y); }
  template <> inline bool ge(Real const& x, Real const& y) { return ge<npl::Real<Real, MML_THRESHOLD> >(x, y); }

# endif


  // Shape trait

  template <typename T>
  struct shapes
  {
    public:
      typedef il::Shape<T>   Shape;
      typedef il::Point<T>   Vector;

      BOOST_PP_SEQ_FOR_EACH(MMLM_decl2, _, MMLM_ALL_SHAPES)
  };


  // Shape types

  using il::Shape;

  BOOST_PP_SEQ_FOR_EACH(MMLM_decl3, _, MMLM_ALL_SHAPES)

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local macros undef

# undef MMLM_decl1
# undef MMLM_decl2
# undef MMLM_decl3



#endif /* !MML_TYPES_HH_ */
