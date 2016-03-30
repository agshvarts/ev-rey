#ifndef _ELEMENT_H_
#define _ELEMENT_H_

#include <fstream>
#include <vector>
#include "node.h"

using namespace std;

class ELEMENT
{
private:
  int id;
  int nodes_num;
  vector<NODE*> nodes;
  vector<vector<double> > Jacobian_2D(double gpx, double gpy);

public:
  ELEMENT(int id, int nodes_num);

  NODE* get_node(int i) { return nodes[i]; };

  vector<vector<double> > tangent_2D;
  //el_tang;

  void add_node(NODE* node, int ind);
  void print(ofstream &outfile);
  void fill();
  //void tangent_2D() { return el_tang; };
};

#endif //_ELEMENT_H_
