//
// color_map.hh for tools
// Made by nicuveo <crucuny@gmail.com>
//

#ifndef TOOLS_COLOR_MAP_HH_
# define TOOLS_COLOR_MAP_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <map>
# include "color.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace tools
{

  template <typename K = int, typename V = Color,
            typename F = V (*)(const V&, const V&, float)>
  class ColorMap : public std::map<K, V>
  {
    public:
      ColorMap(const F& f);

      V get(K key) const;

    private:
      F f_;
  };

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH

# include "color_map.hxx"



#endif /* !TOOLS_COLOR_MAP_HH_ */
