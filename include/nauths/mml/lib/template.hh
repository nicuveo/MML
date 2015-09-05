//
// Copyright Antoine Leblanc 2010 - 2015
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef MML_TEMPLATE_HH_
# define MML_TEMPLATE_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <boost/call_traits.hpp>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Macro helpers

# define MML_PRM(T)              boost::call_traits<T>::param_type
# define MML_TPL_PRM(T) typename boost::call_traits<T>::param_type

# define MML_REF(T)              boost::call_traits<T>::reference
# define MML_TPL_REF(T) typename boost::call_traits<T>::reference



#endif /* !MML_TEMPLATE_HH_ */
