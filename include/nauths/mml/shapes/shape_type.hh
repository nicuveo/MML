//
// Copyright Antoine Leblanc 2010 - 2013
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef MML_SHAPE_TYPE_HH_
# define MML_SHAPE_TYPE_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "nauths/mml/shapes/shape_macros.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local macros

# define MMLM_type(_1, _2, S) MMLM_NAME(S) = MMLM_VALUE(S)
# define MMLM_dual_type(_1, SXS)                                      \
  BOOST_PP_CAT(BOOST_PP_CAT(MMLM_NAME(BOOST_PP_SEQ_ELEM(0, SXS)), _), \
                            MMLM_NAME(BOOST_PP_SEQ_ELEM(1, SXS)))     \
    = MMLM_VALUE(BOOST_PP_SEQ_ELEM(0, SXS)) *                         \
      MMLM_VALUE(BOOST_PP_SEQ_ELEM(1, SXS)),                          \



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace mml
{

  namespace shape
  {

    enum Type
    {
      BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_TRANSFORM(MMLM_type, _, MMLM_ALL_SHAPES))
    };

    enum DualType
    {
      BOOST_PP_SEQ_FOR_EACH_PRODUCT(MMLM_dual_type, (MMLM_SHAPES)(MMLM_SHAPES))
      ERRONEOUS = 0
    };

  }

  typedef shape::Type ShapeType;
  typedef shape::DualType ShapeDualType;


}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local macros undef

# undef MMLM_type
# undef MMLM_dual_type



#endif /* !MML_SHAPE_TYPE_HH_ */
