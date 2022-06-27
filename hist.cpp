#include <iostream>
#include <fstream>
#include <string>
#include <math.h>



using namespace std;

int h[1000000];
double g[1000000];
double L_x = 0;
double L_y = 0;
double distance_x = 0.0;
double distance_y = 0.0;
double dist = 0;
double x[10000];
double y[10000];
double VVcp;
int N_y;
int N_x;
int N;
int ilosc_cykli;
int nstep;
int k = 0;
int r = 0;
int nk = 0;
double dr = 0;
double rho = 0;
double pi = 3.14159265354;
double cons = 0;
double r_lo = 0;
double r_hi = 0;
double h_id = 0;

string trash;
ifstream file;
ofstream output;
int main(){
	file.open("..\\program_version_3\\input.txt");
	file >> trash;
	file >> VVcp;
	file >> trash;
	file >> N_y;
	file >> trash;
	file >> N_x;
	file >> trash;
	file >> trash;
	file >> trash;
	file >> trash;
	file >> ilosc_cykli;
	file >> trash;
	file.close();
	L_x = N_x*sqrt(VVcp);
	L_y = N_y*sqrt(3*VVcp)*0.5;
	N = N_x * N_y;
	rho = 1.0*N/(L_x*L_y);
	cons = pi * rho;
	dr = 0.005;
	r = 3;
	nstep = ilosc_cykli/2000 +1;
	nk = r/dr;

	for (int i = 0 ; i<nk ; i++){
		h[i] = 0;
		g[i] = 0;
	}

	
    for ( int number = ilosc_cykli/2000 ; number <= ilosc_cykli/1000 ; number++){
    	file.open("..\\program_version_3\\data\\data" + to_string(number) + ".txt");
		for (int i=0 ; i<N ; i++){
			file >> x[i];
			file >> y[i];
			file >> trash;
		}
		file.close();
		for (int i = 0 ; i<N ; i++){
			for (int j = 0 ; j<i ; j++){

				distance_x = x[i] - x[j];
				if (distance_x < -0.5*L_x){
					distance_x += L_x;
				}
				else if (distance_x > 0.5*L_x){
					distance_x -= L_x;
				}

				distance_y = y[i] - y[j];
				if (distance_y < -0.5*L_y){
					distance_y += L_y;
				}
				else if (distance_y > 0.5*L_y){
					distance_y -= L_y;
				}


				
				dist = sqrt(pow(distance_x , 2) + pow(distance_y, 2));
				k = lrint(dist/dr);
				if (k < nk){
					h[k] += 2;
				}

			}
		}
    }

	for (k = 0 ; k < nk ; k++){

		g[k] = 1.0*h[k]/(N*nstep);
		r_lo = k*dr;
		r_hi = r_lo + dr;
		h_id = cons * ( r_hi*r_hi - r_lo*r_lo );
		g[k] = g[k]/h_id;

	}
	output.open("histogram.txt");
	for (int i = 0 ; i <nk ; i++){

		output << dr/2 + i*dr<< " " << g[i] << endl;

	}
	output.close();

}
