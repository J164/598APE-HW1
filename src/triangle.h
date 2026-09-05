#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__
#include "plane.h"

class Triangle : public Plane{
public:
   double thirdX;
   Vector a, edge1, edge2;
   Triangle(const Vector& c, const Vector& b, const Vector& a, Texture* t);
   double getIntersection(const Ray& ray);
   bool getLightIntersection(const Ray& ray, double* fill);
};

#endif
