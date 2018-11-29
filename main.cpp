#include <Eigen/Core>
#include <vector>
#include <iostream>
#include "write_ppm.h"


int main(int argc, char * argv[])
{

  double min_t = 1.0;

  int width =  640;
  int height = 360;
  int numSample = 1;

  std::vector<unsigned char> rgb_image(3*width*height);

//  // For each pixel (i,j)
//  for(unsigned i=0; i<height; ++i)
//  {
//    if (i % 1 == 0) {
//      std::cout << "Calculating " << (double)i * 100 / height << "%" << std::endl;
//    }
//
//    for(unsigned j=0; j<width; ++j)
//    {
//      // Set background color
//      Eigen::Vector3d rgb(0,0,0);
//
//      // Anti-aliasing
//      for (unsigned s=0; s<numSample; s++) {
//        double u = (double(i)+random(0,100)/100.0f) / height;
//        double v = (double(j)+random(0,100)/100.0f) / width;
//
//        // Compute viewing ray
//        Ray ray = cam.get_ray(v, u);
//
//        // Shoot ray and collect color
//        Eigen::Vector3d color(0, 0, 0);
//        raycolor(ray,min_t,objects,lights,0,color);
//        rgb += color / (double)numSample;
//      }
//
//      // Write double precision color into image
//      auto clamp = [](double s){ return std::max(std::min(s,1.0),0.0);};
//      rgb_image[0+3*(j+width*i)] = 255.0*clamp(rgb(0));
//      rgb_image[1+3*(j+width*i)] = 255.0*clamp(rgb(1));
//      rgb_image[2+3*(j+width*i)] = 255.0*clamp(rgb(2));
//
//    }
//  }

  write_ppm("rgb.ppm",rgb_image,width,height,3);
}
