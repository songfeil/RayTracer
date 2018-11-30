//
// Created by 宋飞龙 on 2018-11-29.
//

#ifndef RAYTRACING_RAY_H
#define RAYTRACING_RAY_H

#include <Eigen/Core>

class Ray {
 public:
  Eigen::Vector3d origin;
  Eigen::Vector3d direction;

  Ray() {}

  Ray(const Eigen::Vector3d & origin, const Eigen::Vector3d & direction) {
    this->origin = origin;
    this->direction = direction;
  }

  Eigen::Vector3d point_at_t(double t) const {
    return origin + t * direction;
  }
};

#endif //RAYTRACING_RAY_H
