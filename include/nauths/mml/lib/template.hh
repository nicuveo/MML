//
// Copyright Antoine Leblanc 2010 - 2014
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef TOOLS_TEMPLATE_HH_
# define TOOLS_TEMPLATE_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <boost/call_traits.hpp>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Macro helpers

# define TOOLS_PRM(T)              boost::call_traits<T>::param_type
# define TOOLS_TPL_PRM(T) typename boost::call_traits<T>::param_type

# define TOOLS_REF(T)              boost::call_traits<T>::reference
# define TOOLS_TPL_REF(T) typename boost::call_traits<T>::reference



#endif /* !TOOLS_TEMPLATE_HH_ */
