//
// Created by 宋飞龙 on 2018-11-29.
//

#ifndef RAYTRACING_RAY_H
#define RAYTRACING_RAY_H

#include "vec3.h"

class Ray {
 public:
  vec3 origin;
  vec3 direction;

  Ray() {}

  Ray(const vec3 & origin, const vec3 & direction) {
    this->origin = origin;
    this->direction = direction;
  }

  vec3 point_at_t(double t) const {
    return origin + t * direction;
  }
};

#endif //RAYTRACING_RAY_H
