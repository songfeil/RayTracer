//
// Created by 宋飞龙 on 2018-11-29.
//

#ifndef RAYTRACING_OBJECT_H
#define RAYTRACING_OBJECT_H

#include "Material.h"
#include "Hit.h"
#include "Ray.h"

class Object {
 public:
  virtual bool intersect(const Ray & ray, double min_t, double max_t, Hit & hit) const = 0;
};

#endif //RAYTRACING_OBJECT_H