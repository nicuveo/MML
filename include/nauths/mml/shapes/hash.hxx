//
// Copyright Antoine Leblanc 2010 - 2013
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef MML_HASH_HXX_
# define MML_HASH_HXX_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "nauths/mml/shapes/hash.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local code

namespace mml
{

  namespace local
  {


    MML_SHAPE_UNION_VISITOR(HashSwitch, std::size_t, return mml::il::hash_value(x));


    template <typename T, typename U>
    inline std::size_t
    hash_pair(T const& t, U const& u, std::size_t seed = 0)
    {
      boost::hash_combine(seed, t);
      boost::hash_combine(seed, u);
      return seed;
    }


  }

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

namespace mml
{

  namespace il
  {


    template <typename T>
    inline std::size_t
    hash_value(const il::Shape<T>& s)
    {
      return s.apply(local::HashSwitch());
    }

    template <typename T>
    inline std::size_t
    hash_value(const il::Point<T>& p)
    {
      return local::hash_pair(p.x(), p.y());
    }

    template <typename T>
    inline std::size_t
    hash_value(const il::Line<T>& l)
    {
      return local::hash_pair(l[0], l[1]);
    }

    template <typename T>
    inline std::size_t
    hash_value(const il::Rect<T>& r)
    {
      return local::hash_pair(r.min(), r.max());
    }

    template <typename T>
    inline std::size_t
    hash_value(const il::Circle<T>& c)
    {
      return local::hash_pair(c.center(), c.radius());
    }

    template <typename T>
    inline std::size_t
    hash_value(const il::Polygon<T>& p)
    {
      return boost::hash_value(p.points_data());
    }

    template <typename T>
    inline std::size_t
    hash_value(const il::Empty<T>&)
    {
      assert(false);
      return 0;
    }


  }

}



#endif /* !MML_HASH_HXX_ */
