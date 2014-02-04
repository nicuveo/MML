//
// Copyright Antoine Leblanc 2010 - 2014
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef MML_HASH_HH_
# define MML_HASH_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <boost/functional/hash.hpp>
# include "nauths/mml/types.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace mml
{

  namespace il
  {

    template <typename T> std::size_t hash_value(const il::Shape<T>&);
    template <typename T> std::size_t hash_value(const il::Point<T>&);
    template <typename T> std::size_t hash_value(const il::Line<T>&);
    template <typename T> std::size_t hash_value(const il::Rect<T>&);
    template <typename T> std::size_t hash_value(const il::Circle<T>&);
    template <typename T> std::size_t hash_value(const il::Polygon<T>&);
    template <typename T> std::size_t hash_value(const il::Empty<T>&);

  }

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "nauths/mml/shapes/hash.hxx"



#endif /* !MML_HASH_HH_ */
