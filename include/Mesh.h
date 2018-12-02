//
// Created by 宋飞龙 on 2018-11-30.
//

#ifndef RAYTRACING_MESH_H
#define RAYTRACING_MESH_H

#include "Object.h"
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <igl/readOBJ.h>
#include <igl/AABB.h>
#include <igl/Hit.h>
#include <string>
#include <iostream>

double triangleArea(const Eigen::Vector3d & p0, const Eigen::Vector3d & p1, const Eigen::Vector3d & p2) {
  return 0.5 * (p1 - p0).cross(p2 - p0).norm();
}

class TriangleMesh : public Object{
 public:
  Eigen::MatrixXd V;
  Eigen::MatrixXi F;
  igl::AABB<Eigen::MatrixXd, 3> tree;

  Material * mat_ptr;
  Eigen::MatrixXd UV;
  Eigen::MatrixXi UF;
  Eigen::MatrixXd NV;
  Eigen::MatrixXi NF;

//  Material * normalTexture;
//  bool normalMapping;

  TriangleMesh(const std::string OBJFileName, Material * material) {
    bool res = igl::readOBJ(OBJFileName, V, UV, NV, F, UF, NF);
    if (!res) {
      exit(2);
    }

    std::cout << "Vertices " << V.rows() << " Faces " << F.rows() << std::endl;

    initTree();
    mat_ptr = material;
  }

  TriangleMesh(const Eigen::MatrixXd & V, const Eigen::MatrixXi & F) {
    this->V = V;
    this->F = F;
    mat_ptr = new lambertian(Eigen::Vector3d(0.8, 0.8, 0.8));
//    normalTexture = nullptr;
//    normalMapping = false;
    initTree();
  }

  void initTree() {
    tree.deinit();
    tree.init(V, F);
  }

  virtual bool intersect(const Ray & ray, double min_t, double max_t, Hit & hit) const {
    igl::Hit iglhit;

    bool result = tree.intersect_ray(V, F, ray.origin.transpose(), ray.direction.transpose(), iglhit);

    if (result && iglhit.t <= max_t && iglhit.t >= min_t) {
      hit.t = (double) iglhit.t;
      hit.p = ray.point_at_t(hit.t);
      hit.mat_ptr = this->mat_ptr;
      hit.obj_ptr = this;
      hit.fid = iglhit.id;

      // Calculate normal
      Eigen::RowVector3i face = F.row(iglhit.id);
      Eigen::RowVector3d edge0 = V.row(face(1)) - V.row(face(0));
      Eigen::RowVector3d edge1 = V.row(face(2)) - V.row(face(0));
      hit.n = edge0.cross(edge1).normalized();

//      std::cout << "Mesh hit" << std::endl;

      return true;
    } else {
      return false;
    }
  }

  virtual void getUV(const Hit * h, double & u, double & v) const {
    Eigen::Vector3d pos = h->p;
    Eigen::Vector3i face = F.row(h->fid);

    double pab = triangleArea(pos, V.row(face(0)).transpose(), V.row(face(1)).transpose());
    double pac = triangleArea(pos, V.row(face(0)).transpose(), V.row(face(2)).transpose());
    double pbc = triangleArea(pos, V.row(face(1)).transpose(), V.row(face(2)).transpose());
    double area = pab + pac + pbc;

    Eigen::Vector3d bary(pbc / area, pac / area, pab / area);

    Eigen::Vector3i tf = UF.row(h->fid);
    Eigen::Vector2d t0 = UV.row(tf(0));
    Eigen::Vector2d t1 = UV.row(tf(1));
    Eigen::Vector2d t2 = UV.row(tf(2));

    Eigen::Vector2d uv = bary(0) * t0 + bary(1) * t1 + bary(2) * t2;
    u = uv(0);
    v = uv(1);
  }

  void uniform_scale(const double s) {
    V = s * V;
    initTree();
  }

  void translate(const Eigen::Vector3d & t) {
    for (int i = 0; i < V.rows(); i++) {
      V.row(i) = t.transpose() + V.row(i);
    }
    initTree();
  }

  void rotate(const Eigen::Matrix3d & r) {
    for (int i = 0; i < V.rows(); i++) {
      V.row(i) = V.row(i) * r;
    }
    initTree();
  }

};

#endif //RAYTRACING_MESH_H
