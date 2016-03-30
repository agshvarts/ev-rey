#include "problem.h"
#include <iostream>

using namespace std;

void PROBLEM::load_mesh(ifstream& mesh_file)
{
  mesh.load(mesh_file);

  dof_num = mesh.get_nodes_num();

}

void PROBLEM::load_bc_dir(ifstream& bc_file)
{
  bc_file >> bc_dir_num;

  bc_dir.resize(bc_dir_num);

  int i, id_node;
  double val;
  
  sol_dir.resize(dof_num);
  sol_dir.reserve(bc_dir_num);

  for (i = 0; i < bc_dir_num; i++)
  {
    bc_file >> id_node >> val;
    //cout << "id: " << id_node << ", val: " << val << endl;
    //bc_dir_map.insert(pair<int, double>(id_node, val));
    bc_dir[i] = id_node;
    sol_dir.coeffRef(id_node - 1) = val;
  }

  /*cout << "BC DIR IND: " << endl;*/
  /*cout << bc_dir << endl;*/

  /*cout << "BC DIR VAL: " << endl;
  cout << sol_dir << endl; 
  cout << "FINISH" << endl;*/

}

void PROBLEM::apply_bc_dir()
{
  SparseVector<double> mult = global_tang * sol_dir;
  rhs = rhs - VectorXd(mult);

  int id;
  double val;

  for (int i = 0; i < bc_dir_num; i++) 
  {
    id = bc_dir[i];
    val = sol_dir.coeff(id - 1);
    
    for (int j = 0; j < dof_num; j++)
    {
      global_tang.coeffRef(id - 1, j) = 0.0;
      global_tang.coeffRef(j, id - 1) = 0.0;
    }
    global_tang.coeffRef(id - 1, id - 1) = 1.0;
    rhs[id - 1] = val;
  }
  
  //cout << "RHS: " << endl;
  //cout << rhs << endl;

 // cout << "K: " << endl;
  //cout << global_tang << endl;


}


void PROBLEM::print_mesh(ofstream& out_file)
{
  mesh.print(out_file);
}

void PROBLEM::fill_global_tang()
{
  global_tang.resize(dof_num, dof_num);
  global_tang.reserve(5 * dof_num);  
  
  int i_gl, j_gl, i, j;

  ELEMENT* elem;
   
  for (int i_elem = 0; i_elem < mesh.get_elem_num(); i_elem++)
  {
    elem = mesh.get_element(i_elem);
    elem->fill();

    for (i = 0; i < 4; i++) 
    {
      i_gl = elem->get_node(i)->id - 1;

      for (j = 0; j < 4; j++) 
      { 
        j_gl = elem->get_node(j)->id - 1;

        global_tang.coeffRef(i_gl, j_gl) += elem->tangent_2D[i][j];
     
      }
    }
    //out_file << "GLOBAL TANG: " << endl;
    //out_file << global_tang << endl;
  }
  
  //cout << "GLOBAL TANG: " << endl;
  //cout << global_tang << endl;
  //global_tang.coeffRef(i, j) += 1.0;


  // i
}

void PROBLEM::fill_rhs()
{
  /*rhs.resize(dof_num); */
  /*fill(rhs.begin(), rhs.end(), 0.0);*/
  rhs = VectorXd::Zero(dof_num);
}

void PROBLEM::solve()
{
  apply_bc_dir();

  SimplicialLDLT<SparseMatrix<double> > solver;

  solver.compute(global_tang);
  sol = solver.solve(rhs);


  /*cout << "SOLUTION: " << endl;
  cout << sol << endl;

  cout << "TEST: " << endl;
  cout << global_tang * sol << endl;*/
   
}


void PROBLEM::print_sol(ofstream& sol_file)
{
  int id;
  for (int i = 0; i < mesh.get_nodes_num(); i++) {
    id = mesh.get_node(i)->id;
    sol_file << id << " " << sol[id - 1] << endl;
  }    
}

