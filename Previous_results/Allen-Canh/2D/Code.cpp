#include<iostream>
#include<fstream>
#include<math.h>
#include<string>
using namespace std;
#define nx 200 
#define ny 200
int main (){
    double delta_t=0.025 , delta_x = 1 , delta_y=1 , L = 1 , K =1 , A=1;
    double initial_orientation[ny][nx] , new_orientation[ny][nx];
    int total_time_steps=8000;

    // Opening a file to write output
    ofstream file("Initial composition.txt");
    //Initial condition 
    for(int j=0;j<ny;j++){
        for(int i=0;i<nx;i++){
            if(pow(i-(nx/2) , 2)+pow(j-(ny/2),2)<=(20*20)) initial_orientation[j][i]=1;
            else initial_orientation[j][i]=0;
            file<<initial_orientation[j][i]<<" ";
        }
        file<<endl;
    }
    file.close();

    //Finite Difference
    for(int t=1;t<=total_time_steps;t++){
        for(int j=0;j<ny;j++){
            for(int i=0;i<nx;i++){
                //Boundary conditions
                int left,right,up,down;
                left = (i==0)?nx-1:i-1;
                right = (i==nx-1)?0:i+1;
                up = (j==0)?ny-1:j-1;
                down = (j==ny-1)?0:j+1;

                double df_dn = A*((2*initial_orientation[j][i])+(4*pow(initial_orientation[j][i],3))-(6*pow(initial_orientation[j][i],2)));
                double d2n_dx2 =( initial_orientation[j][left]-(2*initial_orientation[j][i])+initial_orientation[j][right])/(delta_x*delta_x);
               double dn2_dy2 = ( initial_orientation[up][i]-(2*initial_orientation[j][i])+initial_orientation[down][i])/(delta_y*delta_y);
               new_orientation[j][i]=initial_orientation[j][i]+(delta_t*L)*((2*K*(d2n_dx2+dn2_dy2)) - df_dn) ;
            }
        }

        // Update 
        for(int j=0;j<ny;j++){
            for(int i=0;i<nx;i++){
                initial_orientation[j][i]=new_orientation[j][i];
                
            }
        }

        //store 
        if(t%800==0){
            string filename = "Solution at t= " + to_string(int(t*delta_t)) + ".txt";
            ofstream file(filename);
            for(int j=0;j<ny;j++){
                for(int i=0;i<nx;i++){
                    file<<initial_orientation[j][i]<<" ";
                }
                file<<"\n";
            }
            file.close();
        }

    }
cout<<"finish"<<endl;

}