// example on insertion
#include <iostream>     // std::cout
#include <fstream>
#include "problem.h"

using namespace std;

int main (int argc, char* argv[]) 
{
  cout << "Hello, Reynolds!" << endl;

  int dim, nodes_num, elem_num;
  double id, x, y, z;
  NODE* node;

  if (argc < 4)
  {
    cout << "2 input files (mesh and bc) and 1 output must be specified!" << endl;
    return 1;
  }

	ifstream meshfile(argv[1]);
  ifstream bc_dir_file(argv[2]);
  ofstream sol_file(argv[3]);

	if (!meshfile.is_open()){ 
    cout << "Error opening file" << endl; 
    return 1; 
  };	

  if (!bc_dir_file.is_open()){ 
    cout << "Error opening file" << endl; 
    return 1; 
  };

  /*MESH mesh;
  mesh.create_from_file(meshfile);
  mesh.print(outfile);*/
  
  PROBLEM prob;

  prob.load_mesh(meshfile);
  prob.load_bc_dir(bc_dir_file);

  prob.fill_global_tang();
  prob.fill_rhs();

  prob.solve();
  prob.print_sol(sol_file);

  meshfile.close();
  bc_dir_file.close();
  sol_file.close();

    



    return 0;
}
