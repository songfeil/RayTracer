//
// Created by 宋飞龙 on 2018-11-30.
//

#ifndef RAYTRACING_TEXTURE_H
#define RAYTRACING_TEXTURE_H

#include <Eigen/Core>

class Texture {
 public:
  virtual Eigen::Vector3d value(double u, double v, const Eigen::Vector3d & p) const = 0;
};

class constantTexture : public Texture {
 public:
  Eigen::Vector3d color;

  constantTexture() {}

  constantTexture(const Eigen::Vector3d & c) : color(c) {}

  virtual Eigen::Vector3d value(double u, double v, const Eigen::Vector3d & p) const {
    return color;
  }
};

class checkerBoardTexture : public Texture {
 public:
  Texture * col0;
  Texture * col1;

  checkerBoardTexture() {}

  checkerBoardTexture(Texture * t0, Texture * t1) : col0(t0), col1(t1) {}

  virtual Eigen::Vector3d value(double u, double v, const Eigen::Vector3d & p) const {
    double sines = sin(10*p.x())*sin(10*p.y())*sin(10*p.z());
    if(sines < 0)
      return col0->value(u,v,p);
    else
      return col1->value(u,v,p);
  }

};

#endif //RAYTRACING_TEXTURE_H
