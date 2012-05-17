//
// perlin.hh for mml
// Made by nicuveo <crucuny@gmail.com>
//

#ifndef MML_PERLIN_HH_
# define MML_PERLIN_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <vector>
# include <cassert>
# include "mml/lib/template.hh"
# include "mml/shapes.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Predeclarations

namespace mml
{

  namespace il
  {

    template <typename T, typename U>
    class PerlinNoise;

    template <typename T, typename U>
    class PerlinNoiseSum;

  }

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace mml
{

  // Trait type

  template <typename T = Real, typename U = T>
  struct perlin
  {
    public:
      typedef T ValueType;
      typedef U CoeffType;
      typedef TOOLS_TPL_PRM(U) CoeffPrm;
      typedef il::PerlinNoise<T, U> Noise;
      typedef il::PerlinNoiseSum<T, U> NoiseSum;
      typedef std::pair<Noise, U> WeightedNoise;
      typedef std::vector<WeightedNoise> WeightedNoiseList;


      // Helpers

      template <typename F>
      static NoiseSum harmonic_sum_f(PrmNum b, PrmNum n, F const& kf);
      static NoiseSum harmonic_sum(PrmNum b, PrmNum n, CoeffPrm km);
  };


  namespace il
  {

    // PerlinNoise

    template <typename T, typename U>
    class PerlinNoise
    {
      public:
        typedef T ValueType;
        typedef U CoeffType;
        typedef TOOLS_TPL_PRM(ValueType) ValuePrm;
        typedef TOOLS_TPL_PRM(CoeffType) CoeffPrm;
        typedef Point<ValueType> ValuePoint;
        typedef Point<ValueType> ValueVector;
        typedef Point<CoeffType> CoeffPoint;
        typedef Point<CoeffType> CoeffVector;
        typedef std::vector<ValueVector> ValueGrid;

        PerlinNoise(Num size = 1);

        ValueType operator()(CoeffPrm x, CoeffPrm y) const;
        ValueType operator()(const CoeffPoint& p) const;

      private:
        const ValueVector& grad(PrmNum x, PrmNum y) const;
        ValueType noise(PrmNum bx, PrmNum by, CoeffPrm kx, CoeffPrm ky) const;

        Num size_;
        ValueGrid g_;
    };


    // PerlinNoiseSum

    template <typename T, typename U>
    class PerlinNoiseSum : public perlin<T, U>::WeightedNoiseList
    {
      public:
        typedef T ValueType;
        typedef U CoeffType;
        typedef TOOLS_TPL_PRM(ValueType) ValuePrm;
        typedef TOOLS_TPL_PRM(CoeffType) CoeffPrm;
        typedef Point<ValueType> ValuePoint;
        typedef Point<CoeffType> CoeffPoint;
        typedef typename perlin<T, U>::WeightedNoise WeightedNoise;
        typedef typename perlin<T, U>::WeightedNoiseList WeightedNoiseList;

        PerlinNoiseSum();
        PerlinNoiseSum(const WeightedNoiseList&);

        PerlinNoiseSum& operator=(const WeightedNoiseList&);

        ValueType operator()(CoeffPrm x, CoeffPrm y) const;
        ValueType operator()(const CoeffPoint& p) const;
    };

  }

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "mml/tools/perlin.hxx"



#endif /* !MML_PERLIN_HH_ */
