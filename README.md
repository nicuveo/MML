*MML*: a Minimalistic Maths Library
===================================

The *MML* was born as the collection of various maths tools that
I needed at some point in some of my projects. It is now a rather
unfieed library that focuses on fundamental 2D shapes.

It is a "headers only" library, as it relies on templates / macros
to decide what types to use for value storage and for intermediate
computations, and what relational operations to use on them.


Shapes
------

The *MML* expose a variadic `Shape` structure, implemented with
`boost variant`. Each shape can be one of those fundamental shapes:
  * a `Point` / `Vector`;
  * a `Line` segment;
  * a `Rect` (which is really an *AABB*);
  * a `Circle`;
  * a generic `Polygon` (a basic list of points).

```c++
#include <nauths/mml/mml.hh>

typedef mml::shapes<int>::Point  Point;
typedef mml::shapes<int>::Rect   Rect;
typedef mml::shapes<int>::Circle Circle;
typedef mml::shapes<int>::Shape  Shape;

void test()
{
  Shape circle = Circle(Point(10, 10), 10);
  Shape box = Rect(Point(0, 0), Point(20, 20));
  Rect circle_bbox = circle.bounding_rect();

  assert(circle_bbox == box);

  std::cout << "circle area: " << circle.area() << std::endl
            << "box area:    " << box.area()    << std::endl;
}
```



Algorithms
----------

Some high-level algorithms that work on shapes include *inclusion test*
and *overlapping tests*. One can even use a given optional macro to
define relational operators on shapes based on the inclusion notion.

```c++
#define MML_OPERATORS // enables < and > relations
#define MML_MACROS    // enables _contains_ and _is_in_ alias

#include <nauths/mml/mml.hh>

typedef mml::shapes<int>::Shape Shape;

void test(Shape const& s1, Shape const& s2)
{
  assert(mml::contains(s1, s2) == (s1 > s2));
  assert(mml::contains(s1, s2) == (s1 _contains_ s2));
  assert(mml::is_in(s1, s2) == (s1 < s2));
  assert(mml::is_in(s1, s2) == (s1 _is_in_ s2));
}
```



Tools
-----------

The *MML* implements several other tools, such as a basic Perlin Noise
generator and a regular / semi-regular tiling generator. For more
information, please see the full documentation in the
[Wiki](https://github.com/nicuveo/MML/wiki).
