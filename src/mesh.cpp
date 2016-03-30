#include "mesh.h"
#include <iostream>

void MESH::load(ifstream& meshfile)
{
  meshfile >> dim >> nodes_num >> elem_num;

  nodes.resize(nodes_num);
  elements.resize(elem_num);

  double x, y, z;
  int id_node, id_elem;
  int i, j;

  for (i = 0; i < nodes_num; i++) {
    meshfile >> id_node >> x >> y;
    if (dim > 2) {
      meshfile >> z;
    }
    nodes[id_node - 1] = new NODE(id_node, dim, x , y, z);
  }

  for (i = 0; i < elem_num; i++) {
    meshfile >> id_elem;
    elements[id_elem - 1] = new ELEMENT(id_elem, 4);
    for (j = 0; j < 4; j++) {
      meshfile >> id_node;
      elements[id_elem - 1]->add_node(nodes[id_node - 1], j);
    }
  }
}

MESH::~MESH()
{
  for (int inode = 0; inode < nodes_num; inode++) {
    delete nodes[inode];  
  }

  for (int ielem = 0; ielem < elem_num; ielem++) {
    delete elements[ielem];  
  }
}

void MESH::print(ofstream& outfile)
{
  outfile << "MESH nodes num: " << nodes_num << ", elem num: " << elem_num << ", dim: " << dim << endl;
  for (int ielem = 0; ielem < elem_num; ielem++) {
    elements[ielem]->print(outfile);  
  }

}

