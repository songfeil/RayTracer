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

class imageTexture : public Texture {
 public:
  imageTexture() {}

  imageTexture(unsigned char *pixels, int width, int height) : data(pixels), nx(width), ny(height) {}

  virtual Eigen::Vector3d value(double u, double v, const Eigen::Vector3d & p) const {
    int i = (1 - u) * nx;
    int j = (1 - v) * ny - 0.001;
    if (i < 0) i = 0;
    if (j < 0) j = 0;
    if (i > nx-1) i = nx-1;
    if (j > ny-1) j = ny-1;
    double r = int(data[3*i + 3*nx*j]  ) / 255.0;
    double g = int(data[3*i + 3*nx*j+1]) / 255.0;
    double b = int(data[3*i + 3*nx*j+2]) / 255.0;
    return Eigen::Vector3d(r, g, b);
  }

  unsigned char *data;
  int nx, ny;
};

#endif //RAYTRACING_TEXTURE_H
