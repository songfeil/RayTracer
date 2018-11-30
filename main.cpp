#include <vector>
#include <iostream>
#include "write_ppm.h"
#include <Eigen/Core>
#include "Object.h"
#include "ObjectList.h"
#include "Sphere.h"
#include <limits>
#include <Camera.h>
#include "raycolor.h"


int main(int argc, char * argv[])
{

  int width =  640;
  int height = 360;
  int numSample = 10;

  std::vector<unsigned char> rgb_image(3*width*height);

  Camera cam;

  Object * list[2];

  Eigen::Vector3d pos0(0, 0, -1);
  list[0] = new Sphere(pos0, 0.5, nullptr);
  Eigen::Vector3d pos1(0, -100.5, -1);
  list[1] = new Sphere(pos1, 100, nullptr);

  Object * world = new ObjectList(list, 2);

  for(int j=0;j<height;j++)
  {
    if (j % 10 == 0) {
      std::cout << "Rendering height " << (double) j * 100 / height << std::endl;
    }
    for(int i=0;i<width;i++)
    {
      Eigen::Vector3d rgb = Eigen::Vector3d(0, 0, 0);
      for (int s=0; s<numSample; s++) {
        double u = double(i) / double(width);
        double v = double(j) / double(height);

        Ray r = cam.get_ray(u, v);

        Eigen::Vector3d p = r.point_at_t(2.0);
        rgb += raycolor(r, world);
      }

      rgb /= numSample;

      rgb = Eigen::Vector3d(sqrt(rgb[0]),sqrt(rgb[1]),sqrt(rgb[2]));


      auto clamp = [](double s){ return std::max(std::min(s,1.0),0.0);};
      rgb_image[0+3*(i+width*j)] = 255.0*clamp(rgb(0));
      rgb_image[1+3*(i+width*j)] = 255.0*clamp(rgb(1));
      rgb_image[2+3*(i+width*j)] = 255.0*clamp(rgb(2));
    }
  }

  write_ppm("rgb.ppm",rgb_image,width,height,3);
}
