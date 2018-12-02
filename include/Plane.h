//
// Created by 宋飞龙 on 2018-12-02.
//

#ifndef RAYTRACING_PLANE_H
#define RAYTRACING_PLANE_H

#include "Object.h"
#include <Eigen/Core>

class Plane : public Object {
 public:
  Eigen::Vector3d p;
  Eigen::Vector3d n;
  Material * mat_ptr;

  Plane(const Eigen::Vector3d & pos, const Eigen::Vector3d & normal, Material * m) : p(pos), n(normal), mat_ptr(m) {}

  virtual bool intersect(const Ray & ray, double min_t, double max_t, Hit & hit) const {
    // Check if parallel
    double d = this->n.dot(ray.direction);
    if (abs(d) < 1e-8) {
      return false;
    }

    // Calculate t
    double tmp_t = (this->n.dot(this->p - ray.origin)) / d;

    // Check t valid
    if (tmp_t > min_t) {
      hit.t = tmp_t;
      hit.n = this->n.normalized();
      hit.mat_ptr = this->mat_ptr;
      hit.p = ray.point_at_t(tmp_t);
      hit.obj_ptr = this;
      return true;
    } else {
      return false;
    }
  }

};

#endif //RAYTRACING_PLANE_H
