//
// Created by 宋飞龙 on 2018-11-29.
//

#include "raycolor.h"

Eigen::Vector3d raycolor(const Ray & r, Object * world)
{
  Hit rec;
  if (world->intersect(r,1.0,std::numeric_limits<double>::infinity(),rec)) {
    Eigen::Vector3d target = rec.p + rec.n + random_in_unit_sphere();
    return 0.5 * raycolor(Ray(rec.p, target - rec.p), world);
  } else {
    Eigen::Vector3d unit_direction = r.direction.normalized();
    double t = 0.5 *(unit_direction(1) + 1.0);
    return (1.0-t)*Eigen::Vector3d(1.0,1.0,1.0) + t*Eigen::Vector3d(0.5,0.7,1.0);
  }
}

