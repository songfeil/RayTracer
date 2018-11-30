//
// Created by 宋飞龙 on 2018-11-29.
//

#ifndef RAYTRACING_RANDOMFUNC_H
#define RAYTRACING_RANDOMFUNC_H

#include <random>
#include <Eigen/Core>

#define RANDOM(a,b) (rand()%(b-a+1)+a)

static Eigen::Vector3d random_in_unit_sphere()
{
  double ran0 = RANDOM(-1, 1);
  double ran1 = RANDOM(-1, 1);
  double ran2 = RANDOM(-1, 1);

  Eigen::Vector3d p(ran0, ran1, ran2);

  return p.normalized();
}

#endif //RAYTRACING_RANDOMFUNC_H
