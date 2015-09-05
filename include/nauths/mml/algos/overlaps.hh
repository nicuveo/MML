//
// Copyright Antoine Leblanc 2010 - 2015
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef MML_OVERLAPS_HH_
# define MML_OVERLAPS_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "nauths/mml/shapes/shape.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local macros

# define MMLM_none(_1, _2)

# define MMLM_awdecl(_, SXS)                                            \
  MMLM_awwdecl(BOOST_PP_SEQ_ELEM(0, SXS), BOOST_PP_SEQ_ELEM(1, SXS))    \

# define MMLM_awwdecl(S1, S2)                                           \
  BOOST_PP_IF(BOOST_PP_LESS_EQUAL(MMLM_VALUE(S1),                       \
                                  MMLM_VALUE(S2)),                      \
              MMLM_awrdecl, MMLM_none)(S1, S2)                          \

# define MMLM_awrdecl(S1, S2)                                           \
  template <typename T1, typename T2>                                   \
  bool does_overlap(const MMLM_Name(S1)<T1>& s1,                        \
                    const MMLM_Name(S2)<T2>& s2);                       \

# define MMLM_odecl(_1, _2, S)                                          \
  template <typename T1, typename T2>                                   \
  bool overlaps(const Shape<T1>& s1, const MMLM_Name(S)<T2>& s2);       \
  template <typename T1, typename T2>                                   \
  bool overlaps(const MMLM_Name(S)<T1>& s1, const Shape<T2>& s2);       \

# define MMLM_oodecl(_, SXS)                                            \
  template <typename T1, typename T2>                                   \
  bool overlaps(const MMLM_Name(BOOST_PP_SEQ_ELEM(0, SXS))<T1>& s1,     \
                const MMLM_Name(BOOST_PP_SEQ_ELEM(1, SXS))<T2>& s2);    \



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace mml
{

  namespace il
  {

    // actual work

    BOOST_PP_SEQ_FOR_EACH_PRODUCT(MMLM_awdecl, (MMLM_SHAPES)(MMLM_SHAPES))

  }


  // specific cases

  BOOST_PP_SEQ_FOR_EACH_PRODUCT(MMLM_oodecl, (MMLM_SHAPES)(MMLM_SHAPES))


  // semi-specific cases

  BOOST_PP_SEQ_FOR_EACH(MMLM_odecl, _, MMLM_SHAPES)


  // general cases

  template <typename T1, typename T2>
  bool overlaps(const Shape<T1>& s1, const Shape<T2>& s2);

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local macros undef

# undef MMLM_none
# undef MMLM_awdecl
# undef MMLM_awwdecl
# undef MMLM_awrdecl
# undef MMLM_odecl
# undef MMLM_oodecl



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "nauths/mml/algos/overlaps.hxx"



#endif /* !MML_OVERLAPS_HH_ */
