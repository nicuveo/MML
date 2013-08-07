//
// color_map.hh for tools
// Made by nicuveo <crucuny@gmail.com>
//

#ifndef TOOLS_COLOR_MAP_HH_
# define TOOLS_COLOR_MAP_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <map>
# include "img/color.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace tools
{

  // ColorMap ABC
  //   maps and interpolates values to colours
  //   used the same way as a std::map, except for the get method
  //   color interpolation function is cutsomisable
  //
  //   trivial example (with rgb interpolation):
  //                map[10]  = Color::rgbf(1.0, 0.0, 0.0);
  //                map[30]  = Color::rgbf(0.0, 1.0, 0.0);
  //     assert(map.get(20) == Color::rgbf(0.5, 0.5, 0.0));
  //
  //   undeflorwing / overflowing values are handled in derived classes

  template <typename K = int, typename V = Color, typename F = V (*)(const V&, const V&, float)>
  class ColorMap : public std::map<K, V>
  {
    public:
      typedef K Key;
      typedef V Value;
      typedef F Fun;

      ColorMap(const Fun& f = mix_rgb);

      Value get(Key key) const;

      const Key& min() const;
      const Key& max() const;
      const Value& min_value() const;
      const Value& max_value() const;

    private:
      virtual Value underflow() const = 0;
      virtual Value overflow() const = 0;

      Fun f_;
  };


  // ClampColorMap
  //   values are clamped to the [min, max] ranged

  template <typename K = int, typename V = Color, typename F = V (*)(const V&, const V&, float)>
  class ClampColorMap : public ColorMap<K, V, F>
  {
    public:
      typedef ColorMap<K, V, F> SuperType;
      typedef typename SuperType::Fun Fun;
      typedef typename SuperType::Value Value;

      ClampColorMap(const Fun& f = mix_rgb);

    private:
      virtual Value underflow() const;
      virtual Value overflow() const;

  };


  // StrictColorMap
  //   (over|under)flowing values generate a domain error

  class ColorMapDomainError : public std::domain_error
  {
    public:
      ColorMapDomainError();
  };

  template <typename K = int, typename V = Color, typename F = V (*)(const V&, const V&, float)>
  class StrictColorMap : public ColorMap<K, V, F>
  {
    public:
      typedef ColorMap<K, V, F> SuperType;
      typedef typename SuperType::Fun Fun;
      typedef typename SuperType::Value Value;

      StrictColorMap(const Fun& f = mix_rgb);

    private:
      virtual Value underflow() const;
      virtual Value overflow() const;

  };


  // DefaultColorMap
  //   (over|under)flowing values are mapped to a default color

  template <typename K = int, typename V = Color, typename F = V (*)(const V&, const V&, float)>
  class DefaultColorMap : public ColorMap<K, V, F>
  {
    public:
      typedef ColorMap<K, V, F> SuperType;
      typedef typename SuperType::Fun Fun;
      typedef typename SuperType::Value Value;

      DefaultColorMap(const Fun& f = mix_rgb);
      DefaultColorMap(const Value& def, const Fun& f = mix_rgb);
      DefaultColorMap(const Value& ufdef, const Value& ofdef, const Fun& f = mix_rgb);

      const Value& underflow_color() const;
      const Value& overflow_color() const;
      Value& underflow_color();
      Value& overflow_color();

    private:
      virtual Value underflow() const;
      virtual Value overflow() const;

      Color uf_;
      Color of_;
  };

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH

# include "img/color_map.hxx"



#endif /* !TOOLS_COLOR_MAP_HH_ */
