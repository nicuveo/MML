//
// Copyright Antoine Leblanc 2010 - 2013
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef MML_SHAPE_MACROS_HH_
# define MML_SHAPE_MACROS_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <boost/preprocessor.hpp>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Macros

# define MMLM_NAME(S)  BOOST_PP_TUPLE_ELEM(4, 0, S)
# define MMLM_Name(S)  BOOST_PP_TUPLE_ELEM(4, 1, S)
# define MMLM_name(S)  BOOST_PP_TUPLE_ELEM(4, 2, S)
# define MMLM_VALUE(S) BOOST_PP_TUPLE_ELEM(4, 3, S)

# define MMLM_SHAPES                                              \
  ((POINT,   Point,   point,   1))                                \
  ((LINE,    Line,    line,    2))                                \
  ((RECT,    Rect,    rect,    3))                                \
  ((CIRCLE,  Circle,  circle,  5))                                \
  ((POLYGON, Polygon, polygon, 7))                                \


# define MMLM_ALL_SHAPES                                          \
  ((EMPTY,   Empty,   empty,   0))                                \
  MMLM_SHAPES                                                     \

# define MMLM_CASE(_, data, shape)                                \
  case BOOST_PP_TUPLE_ELEM(2, 0, data)::MMLM_NAME(shape):         \
    BOOST_PP_TUPLE_ELEM(2, 1, data);                              \



#endif /* !MML_SHAPE_MACROS_HH_ */
