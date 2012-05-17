//
// ostream.hh for mml
// Made by nicuveo <crucuny@gmail.com>
//

#ifndef MML_OSTREAM_HH_
# define MML_OSTREAM_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <ostream>
# include "mml/shapes.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local macros

# define MMLM_decl(_1, _2, S)                                        \
  template <typename T>                                              \
  std::ostream& operator<<(std::ostream&, const MMLM_Name(S)<T>&);   \



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace mml
{

  namespace il
  {

    template <typename T>
    std::ostream& operator<<(std::ostream& ostr, const Shape<T>& p);

    BOOST_PP_SEQ_FOR_EACH(MMLM_decl, _, MMLM_SHAPES)

  }

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local macros undef

# undef MMLM_decl



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "mml/io/ostream.hxx"



#endif /* !MML_OSTREAM_HH_ */
