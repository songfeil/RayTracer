#ifndef CAMERA_H
#define CAMERA_H

#include "Object.h"
#include "Ray.h"
#include <Eigen/Core>
#include <Eigen/Geometry>

class Camera {
public:
  Eigen::Vector3d origin;
  Eigen::Vector3d u, v, w;
  Eigen::Vector3d horizontal;
  Eigen::Vector3d vertical;
  Eigen::Vector3d lower_left_corner;
  double len_radius;
  double theta;
  double half_height;
  double half_width;

  Camera() {
    Eigen::Vector3d lookfrom = Eigen::Vector3d(6, 1, 1.5);
    Eigen::Vector3d lookat = Eigen::Vector3d(0, 0, 0);
    Eigen::Vector3d vup = Eigen::Vector3d(0, 1, 0);
    double vfov = 45;
    double aspect = 1.7777777;
    double aperture = 0.1;
    double focus_dist = (lookfrom - lookat).norm();

    len_radius = aperture/2;
    theta = vfov*M_PI/180;
    half_height = tan(theta/2);
    half_width = aspect * half_height;
    origin = lookfrom;

    w = (lookfrom - lookat).normalized();
    u = vup.cross(w).normalized();
    v = u.cross(w).normalized();

    lower_left_corner = origin - half_width*focus_dist*u - half_height*focus_dist*v - focus_dist*w;
    horizontal = 2*half_width*focus_dist*u;
    vertical = 2*half_height*focus_dist*v;
  }

  Camera(Eigen::Vector3d lookfrom, Eigen::Vector3d lookat, Eigen::Vector3d vup, double vfov, double aspect, double aperture, double focus_dist)
  {
    len_radius = aperture/2;
    theta = vfov*M_PI/180;
    half_height = tan(theta/2);
    half_width = aspect * half_height;
    origin = lookfrom;

    w = (lookfrom - lookat).normalized();
    u = vup.cross(w).normalized();
    v = u.cross(w).normalized();

    lower_left_corner = origin - half_width*focus_dist*u - half_height*focus_dist*v - focus_dist*w;
    horizontal = 2*half_width*focus_dist*u;
    vertical = 2*half_height*focus_dist*v;
  }

  void update(Eigen::Vector3d lookfrom, Eigen::Vector3d lookat, Eigen::Vector3d vup, double vfov, double aspect, double aperture, double focus_dist)
  {
    len_radius = aperture/2;
    theta = vfov*M_PI/180;
    half_height = tan(theta/2);
    half_width = aspect * half_height;
    origin = lookfrom;

    w = (lookfrom - lookat).normalized();
    u = vup.cross(w).normalized();
    v = u.cross(w).normalized();

    lower_left_corner = origin - half_width*focus_dist*u - half_height*focus_dist*v - focus_dist*w;
    horizontal = 2*half_width*focus_dist*u;
    vertical = 2*half_height*focus_dist*v;
  }

  Ray get_ray(double s,double t)
  {
    Ray ray;

    Eigen::Vector3d rd = len_radius * random_in_unit_disk();
    Eigen::Vector3d offset = u * rd.x() +v*rd.y();

    ray.origin = origin + offset;
    ray.direction = (lower_left_corner + s*horizontal + t*vertical - origin - offset).normalized();

    return ray;
  }

  Eigen::Vector3d random_in_unit_disk()
  {
    Eigen::Vector3d p;
    do{
      p = 2.0*Eigen::Vector3d(drand48(),drand48(),0)-Eigen::Vector3d(1,1,0);
    }while (p.dot(p)>=1.0);
    return p;
  }
};

#endif
