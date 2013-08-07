//
// polygon.hh for mml
// Made by nicuveo <crucuny@gmail.com>
//

#ifndef MML_POLYGON_HH_
# define MML_POLYGON_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <vector>
# include <boost/iterator/transform_iterator.hpp>
# include "mml/lib/dual_iterator.hh"
# include "mml/shapes/shape_base.hh"



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

        typedef std::vector<ExactPoint> ExactPoints;
        typedef typename ExactPoints::size_type SizeType;
        typedef typename tools::DualType<ExactPoints>::Type ExactEdge;
        typedef typename ExactPoints::const_iterator PointIterator;
        typedef tools::DualIterator<ExactPoints> EdgeIterator;
        typedef boost::transform_iterator<ExactLine (*)(ExactEdge const&), EdgeIterator> LineIterator;
        typedef std::pair<PointIterator, PointIterator> PointRange;
        typedef std::pair<EdgeIterator, EdgeIterator> EdgeRange;
        typedef std::pair<LineIterator, LineIterator> LineRange;


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

# include "mml/shapes/polygon.hxx"



#endif /* !MML_POLYGON_HH_ */
