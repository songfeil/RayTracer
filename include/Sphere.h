//
// Created by 宋飞龙 on 2018-11-29.
//

#ifndef RAYTRACING_SPHERE_H
#define RAYTRACING_SPHERE_H

#include "Object.h"
#include <Eigen/Core>

class Sphere : public Object {
 public:
  Eigen::Vector3d center;
  double radius;
  Material * mat_ptr;

  Sphere () {}

  Sphere (const Eigen::Vector3d & center, double radius, Material * m) {
    this->center = center;
    this->radius = radius;
    this->mat_ptr = m;
  }

  bool intersect(const Ray & ray, double min_t, double max_t, Hit & hit) const {
    double delta = 0.00001;

    double a = ray.direction.dot(ray.direction);
    double b = 2 * (ray.origin - this->center).dot(ray.direction);
    double c = (ray.origin - this->center).dot(ray.origin - this->center) - this->radius * this->radius;

    if (abs(a) < delta) {
      return false;
    }

    double valid = b * b - 4 * a * c;
    if (valid < 0) {
      return false;
    }

    double t1, t2;
    t1 = ((-b) + sqrt(valid)) / (2 * a);
    t2 = ((-b) - sqrt(valid)) / (2 * a);

    if (t2 < t1) {
      std::swap(t1, t2);
    }

    if (t1 >= min_t && t1 <= max_t) {
      double t = t1;
      hit.t = t;
      hit.n = (ray.origin + (t * ray.direction) - this->center).normalized();
      hit.p = ray.point_at_t(t);
      hit.mat_ptr = this->mat_ptr;
      hit.obj_ptr = this;
      return true;
    } else if (t2 >= min_t && t2 <= max_t) {
      double t = t2;
      hit.t = t;
      hit.n = (ray.origin + (t * ray.direction) - this->center).normalized();
      hit.p = ray.point_at_t(t);
      hit.mat_ptr = this->mat_ptr;
      hit.obj_ptr = this;
      return true;
    } else {
      return false;
    }
  }
};

#endif //RAYTRACING_SPHERE_H
