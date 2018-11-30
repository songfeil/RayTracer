//
// Created by 宋飞龙 on 2018-11-30.
//

#ifndef RAYTRACING_RANDOM_SCENE_H
#define RAYTRACING_RANDOM_SCENE_H

#include <Eigen/Core>
#include "Object.h"
#include "ObjectList.h"
#include "Sphere.h"


Object *random_scene() {
  int n = 500;
  Object **list = new Object*[n+1];
  list[0] =  new Sphere(Eigen::Vector3d(0,-700,0), 700, new lambertian(Eigen::Vector3d(0.5, 0.5, 0.5)));
  int i = 1;
  for (int a = -11; a < 11; a++) {
    for (int b = -11; b < 11; b++) {
      float choose_mat = drand48();
      Eigen::Vector3d center(a+0.9*drand48(),0.2,b+0.9*drand48());
      if ((center - Eigen::Vector3d(4,0.2,0)).norm() > 0.9) {
        if (choose_mat < 0.8) {  // diffuse
          list[i++] = new Sphere(center, 0.2, new lambertian(Eigen::Vector3d(drand48()*drand48(), drand48()*drand48(), drand48()*drand48())));
        }
        else if (choose_mat < 0.95) { // metal
          list[i++] = new Sphere(center, 0.2,
                                 new metal(Eigen::Vector3d(0.5*(1 + drand48()), 0.5*(1 + drand48()), 0.5*(1 + drand48())),  0.5*drand48()));
        }
        else {  // glass
          list[i++] = new Sphere(center, 0.2, new dielectric(1.5));
        }
      }
    }
  }

  list[i++] = new Sphere(Eigen::Vector3d(0, 1, 0), 1.0, new dielectric(2.5));
  list[i++] = new Sphere(Eigen::Vector3d(-4, 1, 0), 1.0, new lambertian(Eigen::Vector3d(0.4, 0.2, 0.1)));
  list[i++] = new Sphere(Eigen::Vector3d(4, 1, 0), 1.0, new metal(Eigen::Vector3d(1, 1, 1), 0.0));

  return new ObjectList(list,i);
}

#endif //RAYTRACING_RANDOM_SCENE_H
