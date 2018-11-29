//
// Created by 宋飞龙 on 2018-11-29.
//

#ifndef RAYTRACING_HIT_H
#define RAYTRACING_HIT_H

#include "vec3.h"
#include "Material.h"

class Hit {
 public:
  double t;
  vec3 p;
  vec3 n;
  Material * mat_ptr;
};

#endif //RAYTRACING_HIT_H
