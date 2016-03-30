#ifndef _MESH_H_
#define _MESH_H_

#include "node.h"
#include "element.h"

#include <fstream> 
#include <vector>

using namespace std;

class MESH 
{
  private:
  
  int dim;
  int nodes_num;
  int elem_num; 

  vector<NODE*> nodes;
  vector<ELEMENT*> elements;  

  public:

  NODE* get_node(int i) {return nodes[i]; };
  int get_nodes_num() { return nodes_num; };
  int get_elem_num() { return elem_num; };

  ELEMENT* get_element(int i) { return elements[i]; };
  
  void load(ifstream& meshfile);
  ~MESH();
  void print(ofstream& outfile);
};

#endif //_MESH_H_
