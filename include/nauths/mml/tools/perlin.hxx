//
// Copyright Antoine Leblanc 2010 - 2015
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef MML_PERLIN_HXX_
# define MML_PERLIN_HXX_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "nauths/mml/lib/utils.hh"
# include "nauths/mml/tools/perlin.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

namespace mml
{


  // Helpers

  template <typename T, typename U>
  template <typename F>
  typename perlin<T, U>::NoiseSum
  perlin<T, U>::harmonic_sum_f(PrmNum b, PrmNum n, F const& kf)
  {
    NoiseSum res;
    Num f = b;

    assert(gt(n, 0));
    res.reserve(n);

    for (Num i = 0; lt(i, n); ++i, f *= 2)
      res.push_back(WeightedNoise(f, kf(i)));

    return res;
  }

  template <typename T, typename U>
  typename perlin<T, U>::NoiseSum
  perlin<T, U>::harmonic_sum(PrmNum b, PrmNum n, CoeffPrm km)
  {
    NoiseSum res;
    Num f = b;
    U k = 1.;

    assert(gt(n, 0));
    res.reserve(n);

    for (Num i = 0; i < n; ++i, f *= 2, k *= km)
      res.push_back(WeightedNoise(f, k));

    return res;
  }



  namespace il
  {


    // PerlinNoise

    template <typename T, typename U>
    PerlinNoise<T, U>::PerlinNoise(PrmNum size)
      : size_(size)
    {
      assert(gt(size, 0));

      Num n = (size + 1) * (size + 1);
      g_.resize(n);

      for (ValueVector& v : g_)
        v = random_vector<T>().normalized();
    }


    template <typename T, typename U>
    inline typename PerlinNoise<T, U>::ValueType
    PerlinNoise<T, U>::operator()(CoeffPrm x, CoeffPrm y) const
    {
      assert(ge(x, CoeffType(0)) and le(x, CoeffType(1)));
      assert(ge(y, CoeffType(0)) and le(y, CoeffType(1)));

      Num bx = std::min(to<Num>(std::floor(x * size_)), size_ - 1);
      Num by = std::min(to<Num>(std::floor(y * size_)), size_ - 1);

      return clamp(noise(bx, by, x * size_ - bx, y * size_ - by), T(0), T(1));
    }

    template <typename T, typename U>
    inline typename PerlinNoise<T, U>::ValueType
    PerlinNoise<T, U>::operator()(const CoeffPoint& p) const
    {
      return operator()(p.x(), p.y());
    }


    template <typename T, typename U>
    inline const typename PerlinNoise<T, U>::ValueVector&
    PerlinNoise<T, U>::grad(PrmNum x, PrmNum y) const
    {
      assert(ge(x, 0) and le(x, size_));
      assert(ge(y, 0) and le(y, size_));

      return g_[y * (size_ + 1) + x];
    }

    template <typename T, typename U>
    typename PerlinNoise<T, U>::ValueType
    PerlinNoise<T, U>::noise(PrmNum bx, PrmNum by, CoeffPrm kx, CoeffPrm ky) const
    {
      assert(ge(kx, CoeffType(0)) and le(kx, CoeffType(1)));
      assert(ge(ky, CoeffType(0)) and le(ky, CoeffType(1)));

      ValueType r0 = to<ValueType>(grad(bx + 0, by + 0) * CoeffVector(kx - 0., ky - 0.));
      ValueType r1 = to<ValueType>(grad(bx + 1, by + 0) * CoeffVector(kx - 1., ky - 0.));
      ValueType r2 = to<ValueType>(grad(bx + 0, by + 1) * CoeffVector(kx - 0., ky - 1.));
      ValueType r3 = to<ValueType>(grad(bx + 1, by + 1) * CoeffVector(kx - 1., ky - 1.));

      CoeffType x = 3 * std::pow(kx, 2) - 2 * std::pow(kx, 3);
      CoeffType y = 3 * std::pow(ky, 2) - 2 * std::pow(ky, 3);

      assert(ge(x, CoeffType(0)) and le(x, CoeffType(1)));
      assert(ge(y, CoeffType(0)) and le(y, CoeffType(1)));

      r0 += to<ValueType>(x * (r1 - r0));
      r2 += to<ValueType>(x * (r3 - r2));

      return to<ValueType>((1 + r0 + y * (r2 - r0)) / 2);
    }



    // PerlinNoiseSum

    template <typename T, typename U>
    inline PerlinNoiseSum<T, U>::PerlinNoiseSum()
    {
    }

    template <typename T, typename U>
    inline PerlinNoiseSum<T, U>::PerlinNoiseSum(const WeightedNoiseList& l)
    : WeightedNoiseList(l)
    {
    }


    template <typename T, typename U>
    inline PerlinNoiseSum<T, U>&
    PerlinNoiseSum<T, U>::operator=(const WeightedNoiseList& l)
    {
      WeightedNoiseList::operator=(l);
      return *this;
    }


    template <typename T, typename U>
    inline typename PerlinNoiseSum<T, U>::ValueType
    PerlinNoiseSum<T, U>::operator()(CoeffPrm x, CoeffPrm y) const
    {
      ValueType res = 0;
      CoeffType k = 0;

      for (const WeightedNoise& wpn : *this)
      {
        res += to<ValueType>(wpn.second * wpn.first(x, y));
        k += wpn.second;
      }

      return to<ValueType>(res / k);
    }

    template <typename T, typename U>
    inline typename PerlinNoiseSum<T, U>::ValueType
    PerlinNoiseSum<T, U>::operator()(const CoeffPoint& p) const
    {
      return operator()(p.x(), p.y());
    }


  }

}



#endif /* !MML_PERLIN_HXX_ */
