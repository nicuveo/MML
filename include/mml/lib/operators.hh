//
// operators.hh for mml
// Made by nicuveo <crucuny@gmail.com>
//

#ifndef MML_OPERATORS_HH_
# define MML_OPERATORS_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <boost/typeof/typeof.hpp>
# include <boost/preprocessor.hpp>
# include <boost/type_traits.hpp>
# include <boost/mpl/logical.hpp>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Operators

# define MML_ADD (plus,              + )
# define MML_SUB (minus,             - )
# define MML_MUL (multiplies,        * )
# define MML_DIV (divides,           / )
# define MML_MOD (modulus,           % )

# define MML_OPS (MML_ADD) (MML_SUB) (MML_MUL) (MML_DIV) (MML_MOD)



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local macros

# define MML_OP_TRAIT(R, DATA, X)                                   \
  template <typename T1, typename T2, bool HO = true>               \
  struct BOOST_PP_CAT(mml_, MML_NAME(X))                            \
  {                                                                 \
    public:                                                         \
      typedef BOOST_TYPEOF_TPL(T1() MML_OPER(X) T2()) type;         \
  };                                                                \
  template <typename T1, typename T2>                               \
  struct BOOST_PP_CAT(mml_, MML_NAME(X))<T1, T2, false>             \
  {                                                                 \
  };                                                                \



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Macros

# define MML_NAME(X) BOOST_PP_TUPLE_ELEM(2, 0, X)
# define MML_OPER(X) BOOST_PP_TUPLE_ELEM(2, 1, X)
# define MML_MTNM(X) BOOST_PP_CAT(::mml::mml_, MML_NAME(X))
# define MML_BTNM(X) BOOST_PP_CAT(::boost::has_, MML_NAME(X))

# define MML_HAS(X, T1, T2)    MML_BTNM(X)<T1, T2>
# define MML_HASNT(X, T1, T2)  boost::mpl::not_<MML_HAS(X, T1, T2)>

# define MML_RESULT(X, T1, T2) typename MML_MTNM(X)<T1, T2, MML_HAS(X, T1, T2)::value>::type



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace mml
{

  BOOST_PP_SEQ_FOR_EACH(MML_OP_TRAIT, _, MML_OPS)

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local macros undef

# undef MML_OP_TRAIT



#endif /* !MML_OPERATORS_HH_ */
