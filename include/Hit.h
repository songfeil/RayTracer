//
// Created by 宋飞龙 on 2018-11-29.
//

#ifndef RAYTRACING_HIT_H
#define RAYTRACING_HIT_H

#include <Eigen/Core>

class Material;
class Object;

class Hit {
 public:
  double t;
  Eigen::Vector3d p;
  Eigen::Vector3d n;
  const Object * obj_ptr;
  Material * mat_ptr;
};

#endif //RAYTRACING_HIT_H
