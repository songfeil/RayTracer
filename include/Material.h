//
// Created by 宋飞龙 on 2018-11-29.
//

#ifndef RAYTRACING_MATERIAL_H
#define RAYTRACING_MATERIAL_H

#include "Ray.h"
#include "randomFunc.h"
#include "Hit.h"
#include <Eigen/Core>

class Material {
 public:
  virtual bool scatter(const Ray & r_in, const Hit & rec, Eigen::Vector3d & attenuation, Ray & scattered) const = 0;
};

class lambertian : public Material {
 public:
  lambertian(const Eigen::Vector3d & a) : albedo(a) {}
  virtual bool scatter(const Ray & r_in, const Hit & rec, Eigen::Vector3d & attenuation, Ray & scattered) const {
    Eigen::Vector3d target = rec.p + rec.n + random_in_unit_sphere();
    scattered = Ray(rec.p, target-rec.p);
    attenuation = albedo;
    return true;
  }
  Eigen::Vector3d albedo;    // 反射率
};

#endif //RAYTRACING_MATERIAL_H
