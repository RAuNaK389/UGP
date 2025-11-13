#include<iostream>
#include<string.h>
#include<fstream>
#include<math.h>
using namespace std;
#define nx 200
int main(){
    //  defining variables
    double delta_x = 1, delta_t = 0.025 , K = 1 , A =1 , L=1 ;
    int total_time_steps = 40000;
    double initial_orientation[nx] , new_orientation[nx];

    // Opening a file to write output
    ofstream file("Initial composition.txt");
    //Initial condition 
    for(int i=0;i<nx;i++){
        if(i<nx/2) initial_orientation[i]=1;
        else initial_orientation[i]=0;
        file<<initial_orientation[i]<<" ";
    }
    file<<"\n";
    file.close();

    //Finite difference 
    for(int t=1;t<=total_time_steps;t++){
        for(int i=0;i<nx;i++){
            //Boundary Conditions
            int left,right;
            left = (i==0)?nx-1:i-1;
            right = (i==nx-1)?0:i+1;
            double df_dn = A*(2*initial_orientation[i]+(4*pow(initial_orientation[i],3))-6*pow(initial_orientation[i],2));
            double d2n_dx2 =( (2*K)*(initial_orientation[left]-2*initial_orientation[i]+initial_orientation[right]))/(delta_x*delta_x);
            new_orientation[i] = initial_orientation[i]+(delta_t*L*(d2n_dx2-df_dn));
        }
        //Updating the orientation factor 
        for(int i=0 ; i<nx;i++){
            initial_orientation[i]=new_orientation[i];
        }

        // Storing the solution in a file
        if(t%4000==0){
            string filename = "Solution at t= " + to_string(int(t*delta_t)) + ".txt";
            ofstream file(filename);
            for(int i=0;i<nx;i++){
                file<<initial_orientation[i]<<" ";
            }
            file<<"\n";
            file.close();
        }
    }
    cout<<"finish"<<endl;
    return 0;
}