//
// Copyright Antoine Leblanc 2010 - 2015
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef MML_POLYGON_HH_
# define MML_POLYGON_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <vector>
# include <functional>
# include <nauths/npl/dual_iterator.hh>
# include <boost/iterator/transform_iterator.hpp>
# include "nauths/mml/shapes/shape_base.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace mml
{

  namespace il
  {

    template <typename T>
    class Polygon : public TypedShapeBase<Polygon<T>, T, shape::POLYGON>
    {
      public:
        // types

        typedef ShapeBase<Polygon<T>, T> ExactShapeBase;

        typedef typename ExactShapeBase::ValueType    ValueType;
        typedef typename ExactShapeBase::PrmValueType PrmValueType;
        typedef typename ExactShapeBase::RefValueType RefValueType;
        typedef typename ExactShapeBase::ExactVector  ExactVector;
        typedef typename ExactShapeBase::ExactPoint   ExactPoint;
        typedef typename ExactShapeBase::ExactLine    ExactLine;
        typedef typename ExactShapeBase::ExactRect    ExactRect;

        typedef std::vector<ExactPoint>                           ExactPoints;
        typedef typename ExactPoints::size_type                   SizeType;
        typedef typename npl::Dual<ExactPoints>::Type             ExactEdge;
        typedef typename ExactPoints::const_iterator              PointIterator;
        typedef npl::DualIterator<ExactPoints>                    EdgeIterator;
        typedef std::function<ExactLine (ExactEdge const&)>       LineFunc;
        typedef boost::transform_iterator<LineFunc, EdgeIterator> LineIterator;
        typedef npl::Range<PointIterator>                         PointRange;
        typedef npl::Range<EdgeIterator>                          EdgeRange;
        typedef npl::Range<LineIterator>                          LineRange;


        // constructors

        Polygon() throw();
        Polygon(const ExactPoints& points);

        template <typename T2>
        Polygon(const Polygon<T2>&);


        // accessors

        SizeType size() const;

        PointRange points() const;
        EdgeRange edges() const;
        LineRange lines() const;

        const ExactPoints& points_data() const;


        // state

        bool valid() const;


        // geometry

        ExactRect bounding_rect() const;
        ExactPoint center() const;
        Real perimeter() const;
        Real area() const;


        // modifiers

        template <typename F>
        Polygon transform(F const&) const;


        // in-place modifiers

        using ExactShapeBase::move_of;
        using ExactShapeBase::move_to;
        void move_of(const ExactVector&);
        void move_to(const ExactPoint&);
        void scale(PrmReal);


      private:
        // internal conversion

        static ExactLine e_to_l(ExactEdge const&);


        // data

        ExactPoints points_;

        ExactPoint mean_;
        ExactPoint min_;
        ExactPoint max_;
    };


    // comparison operators

    template <typename T1, typename T2>
    bool operator==(const Polygon<T1>& p1, const Polygon<T2>& p2);
    template <typename T1, typename T2>
    bool operator!=(const Polygon<T1>& p1, const Polygon<T2>& p2);

  }

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "nauths/mml/shapes/polygon.hxx"



#endif /* !MML_POLYGON_HH_ */
