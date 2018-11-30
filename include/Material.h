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
  Eigen::Vector3d albedo;
};

static Eigen::Vector3d reflect(const Eigen::Vector3d & v, const Eigen::Vector3d & n) {
  return v - 2 * v.dot(n) * n;
}

class metal : public Material {
 public:
  metal(const Eigen::Vector3d & a, float f) : albedo(a) { if (f < 1) fuzz = f; else fuzz = 1; }
  virtual bool scatter(const Ray & r_in, const Hit & rec, Eigen::Vector3d & attenuation, Ray & scattered) const  {
    Eigen::Vector3d reflected = reflect(r_in.direction.normalized(), rec.n);
    scattered = Ray(rec.p, reflected + fuzz*random_in_unit_sphere());
    attenuation = albedo;
    return (scattered.direction.dot(rec.n) > 0);
  }
  Eigen::Vector3d albedo;
  double fuzz;
};

static bool refract(const Eigen::Vector3d & v, const Eigen::Vector3d & n, double ni_over_nt, Eigen::Vector3d & refracted) {
  Eigen::Vector3d uv = v.normalized();
  float dt = uv.dot(n);
  float discriminant = 1.0 - ni_over_nt*ni_over_nt*(1-dt*dt);
  if (discriminant > 0) {
    refracted = ni_over_nt*(uv - n*dt) - n*sqrt(discriminant);
    return true;
  }
  else
    return false;
}

static double schlick(double cosine, double ref_idx) {
  double r0 = (1-ref_idx) / (1+ref_idx);
  r0 = r0*r0;
  return r0 + (1-r0)*pow((1 - cosine),5);
}

class dielectric : public Material {
 public:
  dielectric(float ri) : ref_idx(ri) {}
  virtual bool scatter(const Ray & r_in, const Hit & rec, Eigen::Vector3d & attenuation, Ray & scattered) const  {
    Eigen::Vector3d outward_normal;
    Eigen::Vector3d reflected = reflect(r_in.direction, rec.n);
    double ni_over_nt;
    attenuation = Eigen::Vector3d(1.0, 1.0, 1.0);
    Eigen::Vector3d refracted;
    double reflect_prob;
    double cosine;
    if (r_in.direction.dot(rec.n) > 0) {
      outward_normal = -rec.n;
      ni_over_nt = ref_idx;
      //         cosine = ref_idx * dot(r_in.direction(), rec.normal) / r_in.direction().length();
      cosine = r_in.direction.dot(rec.n) / r_in.direction.norm();
      cosine = sqrt(1 - ref_idx*ref_idx*(1-cosine*cosine));
    }
    else {
      outward_normal = rec.n;
      ni_over_nt = 1.0 / ref_idx;
      cosine = -r_in.direction.dot(rec.n) / r_in.direction.norm();
    }
    if (refract(r_in.direction, outward_normal, ni_over_nt, refracted))
      reflect_prob = schlick(cosine, ref_idx);
    else
      reflect_prob = 1.0;

    // 随机数小与反射系数，设为反射光线，反之为折射光线
    if (drand48() < reflect_prob)
      scattered = Ray(rec.p, reflected);
    else
      scattered = Ray(rec.p, refracted);
    return true;
  }

  double ref_idx;
};

#endif //RAYTRACING_MATERIAL_H
