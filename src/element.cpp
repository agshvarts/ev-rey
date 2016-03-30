#include "element.h"
#include <iostream>
#include <cmath>
// ------------------------------------------------------
inline double shape_4(int i, double xi, double eta) {
  switch (i) { // xi, eta in [0,1]
    case 0 : return (1.0-xi)*(1.0-eta)/4.0;
    case 1 : return (1.0+xi)*(1.0-eta)/4.0;
    case 2 : return (1.0+xi)*(1.0+eta)/4.0;
    case 3 : return (1.0-xi)*(1.0+eta)/4.0;
    default: return 0;
  }
}

inline double shape_4_dxi(int i, double eta) {
  switch (i) { // xi, eta in [0,1]
    case 0 : return -(1.0-eta)/4.0;
    case 1 : return (1.0-eta)/4.0;
    case 2 : return (1.0+eta)/4.0;
    case 3 : return -(1.0+eta)/4.0;
    default: return 0.0;
  }
}

inline double shape_4_deta(int i, double xi) {
  switch (i) { // xi, eta in [0,1]
    case 0 : return -(1.0-xi)/4.0;
    case 1 : return -(1.0+xi)/4.0;
    case 2 : return (1.0+xi)/4.0;
    case 3 : return (1.0-xi)/4.0;
    default: return 0.0;
  }
}

inline double cube(double x)
{
  return x * x * x;
}

vector<vector<double> > ELEMENT::Jacobian_2D(double gpe, double gpn) {
    vector<vector<double> > Jac;
    Jac.resize(2);
    for (int i = 0; i < 2; i++) {
        Jac[i].resize(2);
     }
    //Jac_inv.resize(5);
    Jac[0][0] =  0.0; Jac[0][1] =  0.0;
    Jac[1][0] =  0.0; Jac[1][1] =  0.0;
	for (int n = 0; n < 4; n++) {
		Jac[0][0] +=  shape_4_dxi(n, gpn)*nodes[n]-> x; // 00
		Jac[0][1] +=  shape_4_dxi(n, gpn)*nodes[n]-> y; // 01
		Jac[1][0] +=  shape_4_deta(n, gpe)*nodes[n]-> x; // 10
		Jac[1][1] +=  shape_4_deta(n, gpe)*nodes[n]-> y; // 11
	}
	/*cout << "---------" << endl;
    for (int i = 0; i < 2; i++) {
            cout << Jac[i][0] << "  " << Jac[i][1] << endl;
    }
    cout << "---------" << endl;*/
    return Jac;
}

inline double Jac_det(vector<vector<double> > Jac) {
    double detJac;
    detJac = Jac[0][0]*Jac[1][1]-Jac[1][0]*Jac[0][1];
    return detJac;
}


ELEMENT::ELEMENT(int id, int nodes_num)
{
  this->id = id;
  this->nodes_num = nodes_num;
  this->nodes.resize(nodes_num);
}

void ELEMENT::add_node(NODE* node, int ind)
{
  nodes[ind] = node;
}

void ELEMENT::print(ofstream &outfile)
{
  outfile << "-------------------------------------------------------------" << endl;
  outfile << "ELEMENT id: " << id << ", nodes num: " << nodes.size() << endl;
  for (int i = 0; i < nodes.size(); i++) {
    nodes[i]->print(outfile);
  }
}

void ELEMENT::fill(){
    vector<vector<double> > Kel;
    vector<vector<double> > Jac;
    vector<vector<double> > gp;

    double detJac;
    double d1, d2, d3;
	// ---------- Building the tangent element matrix ------------
    // --- Gauss points
    gp.resize(4);
    for (int i = 0; i < 4; i++) {
        gp[i].resize(2);
     }
    gp[0][0] = -1.0/sqrt(3.0); gp[0][1] = -1.0/sqrt(3.0);
    gp[1][0] =  1.0/sqrt(3.0); gp[1][1] = -1.0/sqrt(3.0);
    gp[2][0] =  1.0/sqrt(3.0); gp[2][1] =  1.0/sqrt(3.0);
    gp[3][0] = -1.0/sqrt(3.0); gp[3][1] =  1.0/sqrt(3.0);
    // ------- RESIZE VECTORS
    Kel.resize(4);
    for (int i = 0; i < 4; i++) {
        Kel[i].resize(4);
     }
    for (int i = 0; i < 4; i++) {
      for (int j = i; j < 4; j++) {
            Kel[i][j] = 0.0;
            Kel[j][i] = Kel[i][j];
        }
    }

 	for (int n = 0; n < 4; n++) { // --- start numerical integration on derivative interaction
		// ---- evaluating JACOBIAN at each Gauss point
		Jac = Jacobian_2D(gp[n][0],gp[n][1]);
		detJac = Jac_det(Jac); 
		//cout << detJac << endl;
        d3 = 0.0;
        for (int l = 0; l < 4; l++) {
            d3 += shape_4(l, gp[n][0], gp[n][1]) * nodes[l]->gap ;
        }
        // ---- iterating among natural functions
		for (int i = 0; i < 4; i++) {
		  for (int j = i; j < 4; j++) {
                // Evaluate gap contribute

				//d1 = 0.0;
				d1 = (shape_4_dxi(i, gp[n][1])*Jac[1][1] + shape_4_deta(i, gp[n][0])*(-Jac[0][1]))/detJac*
            		 (shape_4_dxi(j, gp[n][1])*Jac[1][1] + shape_4_deta(j, gp[n][0])*(-Jac[0][1]))/detJac;
 		   	//d2 = 0.0;
				d2 = (shape_4_dxi(i, gp[n][1])*(-Jac[1][0]) + shape_4_deta(i, gp[n][0])*Jac[0][0])/detJac*
            		 (shape_4_dxi(j, gp[n][1])*(-Jac[1][0]) + shape_4_deta(j, gp[n][0])*Jac[0][0])/detJac;
    			// integration for each i,j
				Kel[i][j] += (d1+d2) * cube(d3) * detJac;
				Kel[j][i] = Kel[i][j];
			}
			//cout << "tangent el " << i << ": " << Kel[i][0] << " - " << Kel[i][1] << " - " << Kel[i][2] << " - " << Kel[i][3] << endl;
        }

	}

   //

    //cout << "------ end building element matrix" << endl;
    //cout << "-------------------------------------" << endl;*/

    tangent_2D = Kel;
}
