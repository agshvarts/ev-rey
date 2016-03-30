#include "node.h"
#include <iostream>
 
using namespace std;

NODE::NODE(int id, int dim, double x, double y, double z)
{ 
  this->id = id;
  this->dim = dim;  

  this->x = x;
  this->y = y;
  if (dim > 2) {
    this->z = z;
    this->gap = z;
  } 
  else {
    this->z = 0.0;
    this->gap = -y;
  }
}

void NODE::print(ofstream &outfile)
{
  outfile << "NODE id: " << id << ", dim: " << dim << endl;
  outfile << "  x: " << x << endl; 
  outfile << "  y: " << y << endl;
  if (dim > 2) {
    outfile << "  z: " << z << endl;
  }
}


