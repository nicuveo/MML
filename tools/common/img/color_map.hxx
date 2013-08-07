//
// color_map.hxx for tools
// Made by nicuveo <crucuny@gmail.com>
//

#ifndef TOOLS_COLOR_MAP_HXX_
# define TOOLS_COLOR_MAP_HXX_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "img/color_map.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

namespace tools
{


  // ColorMap ABC

  template <typename K, typename V, typename F>
  ColorMap<K, V, F>::ColorMap(const Fun& f)
    : f_(f)
  {
  }


  template <typename K, typename V, typename F>
  typename ColorMap<K, V, F>::Value
  ColorMap<K, V, F>::get(Key key) const
  {
    typename std::map<K, V>::const_iterator it1 = this->lower_bound(key);
    typename std::map<K, V>::const_iterator it2;

    if (it1 == this->end())
      return overflow();
    if (key == it1->first)
      return it1->second;
    if (it1 == this->begin())
      return underflow();

    it2 = it1--;
    float k = (float(key - it1->first) / float(it2->first - it1->first));

    return f_(it1->second, it2->second, k > 1.f ? 1.f : k);
  }


  template <typename K, typename V, typename F>
  inline const typename ColorMap<K, V, F>::Key&
  ColorMap<K, V, F>::min() const
  {
    return this->begin()->first;
  }

  template <typename K, typename V, typename F>
  inline const typename ColorMap<K, V, F>::Key&
  ColorMap<K, V, F>::max() const
  {
    return this->rbegin()->first;
  }

  template <typename K, typename V, typename F>
  inline const typename ColorMap<K, V, F>::Value&
  ColorMap<K, V, F>::min_value() const
  {
    return this->begin()->second;
  }

  template <typename K, typename V, typename F>
  inline const typename ColorMap<K, V, F>::Value&
  ColorMap<K, V, F>::max_value() const
  {
    return this->rbegin()->second;
  }



  // ClampColorMap

  template <typename K, typename V, typename F>
  ClampColorMap<K, V, F>::ClampColorMap(const Fun& f)
    : SuperType(f)
  {
  }


  template <typename K, typename V, typename F>
  inline typename ClampColorMap<K, V, F>::Value
  ClampColorMap<K, V, F>::underflow() const
  {
    return this->min_value();
  }

  template <typename K, typename V, typename F>
  inline typename ClampColorMap<K, V, F>::Value
  ClampColorMap<K, V, F>::overflow() const
  {
    return this->max_value();
  }



  // StrictColorMap

  inline ColorMapDomainError::ColorMapDomainError()
    : std::domain_error("color map domain error")
  {
  }


  template <typename K, typename V, typename F>
  StrictColorMap<K, V, F>::StrictColorMap(const Fun& f)
    : SuperType(f)
  {
  }


  template <typename K, typename V, typename F>
  inline typename StrictColorMap<K, V, F>::Value
  StrictColorMap<K, V, F>::underflow() const
  {
    throw ColorMapDomainError();
  }

  template <typename K, typename V, typename F>
  inline typename StrictColorMap<K, V, F>::Value
  StrictColorMap<K, V, F>::overflow() const
  {
    throw ColorMapDomainError();
  }



  // DefaultColorMap

  template <typename K, typename V, typename F>
  DefaultColorMap<K, V, F>::DefaultColorMap(const Fun& f)
    : SuperType(f)
  {
  }

  template <typename K, typename V, typename F>
  DefaultColorMap<K, V, F>::DefaultColorMap(const Value& def, const Fun& f)
    : SuperType(f), uf_(def), of_(def)
  {
  }

  template <typename K, typename V, typename F>
  DefaultColorMap<K, V, F>::DefaultColorMap(const Value& ufdef, const Value& ofdef, const Fun& f)
    : SuperType(f), uf_(ufdef), of_(ofdef)
  {
  }


  template <typename K, typename V, typename F>
  inline const typename DefaultColorMap<K, V, F>::Value&
  DefaultColorMap<K, V, F>::underflow_color() const
  {
    return uf_;
  }

  template <typename K, typename V, typename F>
  inline const typename DefaultColorMap<K, V, F>::Value&
  DefaultColorMap<K, V, F>::overflow_color() const
  {
    return of_;
  }

  template <typename K, typename V, typename F>
  typename DefaultColorMap<K, V, F>::Value&
  DefaultColorMap<K, V, F>::underflow_color()
  {
    return uf_;
  }

  template <typename K, typename V, typename F>
  typename DefaultColorMap<K, V, F>::Value&
  DefaultColorMap<K, V, F>::overflow_color()
  {
    return of_;
  }


  template <typename K, typename V, typename F>
  inline typename DefaultColorMap<K, V, F>::Value
  DefaultColorMap<K, V, F>::underflow() const
  {
    return underflow_color();
  }

  template <typename K, typename V, typename F>
  inline typename DefaultColorMap<K, V, F>::Value
  DefaultColorMap<K, V, F>::overflow() const
  {
    return overflow_color();
  }


}



#endif /* !TOOLS_COLOR_MAP_HXX_ */
