#include<iostream>
#include<fstream>
#include<string>
#include<math.h>
using namespace std;
#define nx 200 
// #define delta_t 0.0025
#define total_time_Steps 400000

int main(){
    // Defining variables
    int A = 1;
    double delta_t = 0.0025;
    double delta_x = 1;
    double M = 1;  //mobility
    double kappa =1; 
    double composition[nx];
    double new_composition[nx];

    // Opening a file to write output
    ofstream file("Initial composition.txt");
    //Initial condition 
    for(int i=0;i<nx;i++){
        if(i>=((nx*9)/20) && i<(nx*11)/20 ) composition[i]=1; //updated boundary condition 90-110 = 1 else 0.2 
        else composition[i]=0.2;
        file <<composition[i]<<" ";
    }
    file<<"\n";
    file.close();

    // Finite difference method
    for(int t=1;t<=total_time_Steps;t++){
        for(int i=0;i<nx;i++){
            int left,left_minus,right,right_plus;
            //Boundary Condition
            if(i==nx-1){
                right = 0;
                right_plus=1;
                left=i-1;
                left_minus=i-2;
            }
            else if(i==nx-2){
                right = i+1;
                right_plus=0;
                left=i-1;
                left_minus=i-2;
            }
            else if(i==0){
                right = i+1;
                right_plus=i+2;
                left=nx-1;
                left_minus=nx-2;
            }
            else if(i==1){
                right = i+1;
                right_plus=i+2;
                left=0;
                left_minus=nx-1;
            }
            else{
                right = i+1;
                right_plus=i+2;
                left=i-1;
                left_minus=i-2;
            }

            // Storing the updated values in new array
            double g1c = A*(24*composition[i]-12);
            double g2c = A*(2+(12*composition[i]*composition[i])-(12*composition[i]));
            double term1 = g1c*pow((composition[right]-composition[left])/(2*delta_x),2);
            double term2 = g2c*((composition[right]+composition[left]-2*composition[i])/pow(delta_x,2));
            double term3= (2*kappa)*((composition[left_minus]-(4*composition[left])+(6*composition[i])-(4*composition[right])+composition[right_plus])/(pow(delta_x,4)));
            new_composition[i] = composition[i] + (M*delta_t)*(term1+term2-term3);
        }
        //Updating original array after one iteration 
        for(int i=0;i<nx;i++){
            composition[i]=new_composition[i];
        }

        // Storing the solution in a file
        if(t%40000==0){
            string filename = "Solution at t= " + to_string(int(t*delta_t)) + ".txt";
            ofstream file(filename);
            for(int i=0;i<nx;i++){
                file<<composition[i]<<" ";
            }
            file<<"\n";
        }
    }
    file.close() ;
    cout<<"Finish";
    return 0;
}
