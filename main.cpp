#include <Eigen/Core>
#include <vector>
#include <iostream>
#include "write_ppm.h"
#include "vec3.h"
#include "Object.h"
#include "ObjectList.h"
#include "Sphere.h"
#include <limits>
#include <random>

#define random(a,b) (rand()%(b-a+1)+a)

vec3 color(const Ray & r, Object * world)
{
  Hit rec;
  if(world->intersect(r,0.0,std::numeric_limits<double>::infinity(),rec))
    return 0.5*vec3(rec.n(0)+1,rec.n(1)+1,rec.n(2)+1);
  else
  {
    vec3 unit_direction = r.direction.normalized();
    double t = 0.5 *(unit_direction(1) + 1.0);
    return (1.0-t)*vec3(1.0,1.0,1.0) + t*vec3(0.5,0.7,1.0);
  }
}



int main(int argc, char * argv[])
{

  double min_t = 1.0;

  int width =  640;
  int height = 360;
  int numSample = 10;

  std::vector<unsigned char> rgb_image(3*width*height);

  Eigen::Vector3d lower_left_corner(-2.0,-1.0,-1.0);
  Eigen::Vector3d horizontal(4.0,0.0,0.0);
  Eigen::Vector3d vertical(0.0,2.0,0.0);
  Eigen::Vector3d origin(0.0,0.0,0.0);

  Object * list[2];

  Eigen::Vector3d pos0(0, 0, -1);
  list[0] = new Sphere(pos0, 0.5, nullptr);
  Eigen::Vector3d pos1(0, -100.5, -1);
  list[1] = new Sphere(pos1, 100, nullptr);

  Object * world = new ObjectList(list, 2);

  for(int j=0;j<height;j++)
  {
    for(int i=0;i<width;i++)
    {
      vec3 rgb = Eigen::Vector3d(0, 0, 0);
      for (int s=0; s<numSample; s++) {
        double u = double(i) / double(width);
        double v = double(j) / double(height);

        Ray r(origin, lower_left_corner + u * horizontal + v * vertical);

        vec3 p = r.point_at_t(2.0);
        rgb += color(r, world);
      }

      rgb /= numSample;

      auto clamp = [](double s){ return std::max(std::min(s,1.0),0.0);};
      rgb_image[0+3*(i+width*(height-j))] = 255.0*clamp(rgb(0));
      rgb_image[1+3*(i+width*(height-j))] = 255.0*clamp(rgb(1));
      rgb_image[2+3*(i+width*(height-j))] = 255.0*clamp(rgb(2));
    }
  }

  write_ppm("rgb.ppm",rgb_image,width,height,3);
}
