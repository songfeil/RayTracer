//
// Created by 宋飞龙 on 2018-11-29.
//

#ifndef RAYTRACING_RAYCOLOR_H
#define RAYTRACING_RAYCOLOR_H

#include <Eigen/Core>
#include <Eigen/Geometry>
#include "Ray.h"
#include "Object.h"

Eigen::Vector3d raycolor(const Ray & r, Object * world, int depth);

#endif //RAYTRACING_RAYCOLOR_H
