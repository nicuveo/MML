//
// misc.hh for mml
// Made by nicuveo <crucuny@gmail.com>
//

#ifndef MML_MISC_HH_
# define MML_MISC_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <boost/utility/enable_if.hpp>
# include <boost/preprocessor.hpp>
# include <boost/foreach.hpp>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Macros

# define mml_foreach BOOST_FOREACH

# define MML_ENABLE_IF(C, T) typename boost::enable_if<C, T>::type
# define MML_COMMA() BOOST_PP_COMMA()



#endif /* !MML_MISC_HH_ */
