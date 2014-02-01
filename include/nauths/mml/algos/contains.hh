//
// Copyright Antoine Leblanc 2010 - 2013
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef MML_CONTAINS_HH_
# define MML_CONTAINS_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "nauths/mml/shapes/shape.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local macros

# define MMLM_cdecl(_1, _2, S)                                          \
  template <typename T1, typename T2>                                   \
  bool contains(const Shape<T1>& s1, const MMLM_Name(S)<T2>& s2);       \
  template <typename T1, typename T2>                                   \
  bool contains(const MMLM_Name(S)<T1>& s1, const Shape<T2>& s2);       \

# define MMLM_ccdecl(_, SXS)                                            \
  template <typename T1, typename T2>                                   \
  bool contains(const MMLM_Name(BOOST_PP_SEQ_ELEM(0, SXS))<T1>& s1,     \
                const MMLM_Name(BOOST_PP_SEQ_ELEM(1, SXS))<T2>& s2);    \



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Macros

# if defined MML_OPERATORS and defined MML_MACROS

#  define _is_in_    <
#  define _contains_ >

# endif



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace mml
{

  // specific cases

  BOOST_PP_SEQ_FOR_EACH_PRODUCT(MMLM_ccdecl, (MMLM_SHAPES)(MMLM_SHAPES))


  // semi-specific cases

  BOOST_PP_SEQ_FOR_EACH(MMLM_cdecl, _, MMLM_SHAPES)


  // general cases

  template <typename T1, typename T2>
  bool contains(const Shape<T1>& s1, const Shape<T2>& s2);

  template <typename T1, typename T2>
  inline MML_ENABLE_IF(boost::mpl::and_<MML_IS_SHAPE(T1) MML_COMMA() MML_IS_SHAPE(T2)>, bool)
  is_in(T1 const& s1, T2 const& s2)
  {
    return contains(s2, s1);
  }


  // optional operators

# if defined MML_OPERATORS

  template <typename T1, typename T2>
  inline MML_ENABLE_IF(boost::mpl::and_<MML_IS_SHAPE(T1) MML_COMMA() MML_IS_SHAPE(T2)>, bool)
  operator<(T1 const& s1, T2 const& s2)
  {
    return is_in(s1, s2);
  }

  template <typename T1, typename T2>
  inline MML_ENABLE_IF(boost::mpl::and_<MML_IS_SHAPE(T1) MML_COMMA() MML_IS_SHAPE(T2)>, bool)
  operator>(T1 const& s1, T2 const& s2)
  {
    return contains(s1, s2);
  }

# endif

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local macros undef

# undef MMLM_cdecl
# undef MMLM_ccdecl



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "nauths/mml/algos/contains.hxx"



#endif /* !MML_CONTAINS_HH_ */
