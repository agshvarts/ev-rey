#ifndef _NODE_H_
#define _NODE_H_

#include <fstream>

using namespace std; 

class NODE
{
//private:
public:   
  int dim;
      
  double gap;
  
  int id;
  double x, y, z;
//public:
  NODE(int id, int dim, double x, double y, double z);
  void print(ofstream &outfile);
};

#endif //_NODE_H_
