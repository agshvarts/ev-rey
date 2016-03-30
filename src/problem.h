#ifndef _PROBLEM_H_
#define _PROBLEM_H_

#include <Eigen/Sparse>
#include <Eigen/SparseCholesky>

#include "mesh.h"
#include <fstream>

#include <vector>

//http://eigen.tuxfamily.org/index.php?title=Main_Page

using namespace Eigen;
using namespace std;

/*typedef Eigen::SparseMatrix<double> SpapseMat; */
/*typedef Eigen::SparseVector<double> SpVec; */
  
class PROBLEM {

  private:
    int dof_num;
    int bc_dir_num;

    //map <int, double> bc_dir_map;
    vector<int> bc_dir;

    MESH mesh;

    SparseMatrix<double> global_tang;
    VectorXd rhs;

    VectorXd sol;

    SparseVector<double> sol_dir;

    void apply_bc_dir();

  public:
    void fill_global_tang();
    void fill_rhs();
    void load_bc_dir(ifstream& bc_file);

    void load_mesh(ifstream& mesh_file);
    void print_mesh(ofstream& out_file);

    void print_sol(ofstream& out_file);

    void solve();

};

#endif //_PROBLEM_H_
