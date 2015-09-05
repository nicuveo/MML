//
// Copyright Antoine Leblanc 2010 - 2015
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef MML_SHAPE_UNION_HH_
# define MML_SHAPE_UNION_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <boost/variant.hpp>
# include <boost/type_traits.hpp>
# include "nauths/mml/shapes/empty.hh"
# include "nauths/mml/shapes/point.hh"
# include "nauths/mml/shapes/line.hh"
# include "nauths/mml/shapes/rect.hh"
# include "nauths/mml/shapes/circle.hh"
# include "nauths/mml/shapes/polygon.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local macros

# define MMLM_type(_1, T, S) MMLM_Name(S)<T>
# define MMLM_trait(_1, NAME, S)                                     \
  template <typename T>                                              \
  struct NAME<mml::il::MMLM_type(_, T, S)>                           \
    : mpl::true_                                                     \
  {                                                                  \
  };                                                                 \



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Macros

# define MML_SHAPE_UNION_VISITOR(name, rt, X)                        \
  MML_SHAPE_UNION_VISITOR_E(name, rt, X, X)                          \

# define MML_SHAPE_UNION_VISITOR_WARG(name, rt, at, X)               \
  MML_SHAPE_UNION_VISITOR_WARG_E(name, rt, at, X, X)                 \

# define MML_SHAPE_UNION_VISITOR_OP(rt, t, X)                        \
  template <typename U>                                              \
  inline rt operator()(t x) const                                    \
  {                                                                  \
    (void) x; /* prevents warnings about unused x */                 \
    X;                                                               \
  }                                                                  \

# define MML_SHAPE_UNION_VISITOR_E(name, rt, X, EX)                  \
  struct name : public boost::static_visitor<rt>                     \
  {                                                                  \
    public:                                                          \
      typedef rt result_type;                                        \
                                                                     \
      MML_SHAPE_UNION_VISITOR_OP(rt, mml::il::Empty<U> const&, EX)   \
      MML_SHAPE_UNION_VISITOR_OP(rt, mml::il::Empty<U>&, EX)         \
      MML_SHAPE_UNION_VISITOR_OP(rt, U const&, X)                    \
      MML_SHAPE_UNION_VISITOR_OP(rt, U&, X)                          \
  }                                                                  \

# define MML_SHAPE_UNION_VISITOR_WARG_E(name, rt, at, X, EX)         \
  struct name : public boost::static_visitor<rt>                     \
  {                                                                  \
    public:                                                          \
      typedef rt result_type;                                        \
                                                                     \
      name(at arg)                                                   \
        : arg_(arg)                                                  \
      {                                                              \
      }                                                              \
                                                                     \
      MML_SHAPE_UNION_VISITOR_OP(rt, mml::il::Empty<U> const&, EX)   \
      MML_SHAPE_UNION_VISITOR_OP(rt, mml::il::Empty<U>&, EX)         \
      MML_SHAPE_UNION_VISITOR_OP(rt, U const&, X)                    \
      MML_SHAPE_UNION_VISITOR_OP(rt, U&, X)                          \
                                                                     \
    private:                                                         \
      at arg_;                                                       \
  }                                                                  \



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace boost
{

  // shape traits
  //   on most platforms, those can't be automatically deduced,
  //   hence the need to explictely declare them.
  //   they enable optimizations for boost::variant
  //   (see online doc)

# ifndef BOOST_HAS_NOTHROW_CONSTRUCTOR
  BOOST_PP_SEQ_FOR_EACH(MMLM_trait, has_nothrow_constructor, MMLM_ALL_SHAPES)
# endif

# ifndef BOOST_HAS_NOTHROW_COPY
  BOOST_PP_SEQ_FOR_EACH(MMLM_trait, has_nothrow_copy, MMLM_ALL_SHAPES)
# endif

}

namespace mml
{

  namespace il
  {

    // shape union

    template <typename T>
    struct ShapeUnion
    {
      public:
        typedef boost::variant<
        BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_TRANSFORM(MMLM_type, T, MMLM_ALL_SHAPES))
        > Type;
    };

  }

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local macros undef

# undef MMLM_type
# undef MMLM_trait



#endif /* !MML_SHAPE_UNION_HH_ */
