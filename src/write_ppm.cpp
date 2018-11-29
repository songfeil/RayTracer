#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
  assert(
          (num_channels == 3 || num_channels ==1 ) &&
          ".ppm only supports RGB or grayscale images");
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  std::ofstream outfile;
  outfile.open(filename, std::ios::out);

  std::string mode;
  if (num_channels == 1) {
    mode = "P2";
  } else if (num_channels == 3) {
    mode = "P3";
  } else {
    return false;
  }

  // Header
  outfile << mode << std::endl;
  outfile << width << " " << height << " " << "255" << std::endl;

  // Data
  for (auto iter = data.cbegin(); iter != data.cend(); iter++) {
    outfile << (int) (*iter) << std::endl;
  }

  outfile.close();

  return true;
  ////////////////////////////////////////////////////////////////////////////
}
