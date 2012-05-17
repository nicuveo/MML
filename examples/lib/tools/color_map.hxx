//
// color_map.hxx for tools
// Made by nicuveo <crucuny@gmail.com>
//

#ifndef TOOLS_COLOR_MAP_HXX_
# define TOOLS_COLOR_MAP_HXX_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "color_map.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

namespace tools
{


  template <typename K, typename V, typename F>
  ColorMap<K, V, F>::ColorMap(const F& f)
    : f_(f)
  {
  }

  template <typename K, typename V, typename F>
  V
  ColorMap<K, V, F>::get(K key) const
  {
    typename std::map<K, V>::const_iterator it1 = this->lower_bound(key);
    typename std::map<K, V>::const_iterator it2;

    if (key == it1->first or it1 == this->begin())
      return it1->second;

    it2 = it1--;
    float k = (float(key - it1->first) / float(it2->first - it1->first));

    return f_(it1->second, it2->second, k > 1.f ? 1.f : k);
  }


}



#endif /* !TOOLS_COLOR_MAP_HXX_ */
