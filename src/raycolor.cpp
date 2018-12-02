//
// Created by 宋飞龙 on 2018-11-29.
//

#include "raycolor.h"

Eigen::Vector3d raycolor(const Ray & r, Object * world, int depth)
{
  Hit rec;
  double min_t = 1e-7;
  if (world->intersect(r, min_t, std::numeric_limits<double>::infinity(), rec)) {
    Ray scattered;
    Eigen::Vector3d attenuation;
    double u, v;
    rec.getUV(u, v);
    Eigen::Vector3d emitted = rec.mat_ptr->emitted(u, v, rec.p);

    if (depth > 0 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
      return emitted + attenuation.cwiseProduct(raycolor(scattered, world, depth - 1));
    } else {
      return emitted;
    }
  } else {
    Eigen::Vector3d unit_direction = r.direction.normalized();
    double t = 0.5 * (unit_direction(1) + 1.0);
    return 1 * ((1.0 - t)*Eigen::Vector3d(1.0, 1.0, 1.0) + t*Eigen::Vector3d(0.5, 0.7, 1.0));
  }
}

