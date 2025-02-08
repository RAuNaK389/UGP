#include<iostream>
#include<fstream>
#include<string>
using namespace std;
#define nx 100 
int main(){
    // Defining variables
    int D = 1; // Diffusivity
    int delta_x = 1;
    float delta_t = 0.25;
    int total_time_Steps = 4000;
    double composition[nx];
    double new_composition[nx];

    // Opening a file to write output
    ofstream file("Initial composition.txt");
    //Initial condition 
    for(int i=0;i<nx;i++){
        if(i>=(nx/4) && i<(3*nx)/4 ) composition[i]=1;
        else composition[i]=0;
        file <<composition[i]<<" ";
    }
    file<<"\n";
    file.close();

    // Finite difference method
    for(int t=1;t<=total_time_Steps;t++){
        for(int i=0;i<nx;i++){
            //Periodic boundary condition
            // if(i==0){
            // composition[i] = composition[i] + (((D*delta_t)/(delta_x*delta_x))*(composition[99]-(2*composition[i])+composition[i+1])) ;
            // }
            // else if(i==99) {
            // composition[i] = composition[i] + (((D*delta_t)/(delta_x*delta_x))*(composition[i-1]-(2*composition[i])+composition[0])) ;
            // }
            // else{
            // composition[i] = composition[i] + (((D*delta_t)/(delta_x*delta_x))*(composition[i-1]-(2*composition[i])+composition[i+1])) ;
            // }
            int left,right;
            if (i==0){
                left=nx-1;
                right=i+1;
            }
            else if(i==nx-1){
                left = i-1;
                right=0;
            }
            else {
                left=i-1;
                right=i+1;
            }
            // Storing the updated values in new array
            new_composition[i] = composition[i]+ (((D*delta_t)/(delta_x*delta_x))*(composition[left]-(2*composition[i])+composition[right])) ;
        }
        //Updating original array after one iteration 
        for(int i=0;i<nx;i++){
            composition[i]=new_composition[i];
        }

        // Storing the solution in a file
        if(t%400==0){
            string filename = "Solution at t= " + to_string(int(t*delta_t)) + ".txt";
            ofstream file(filename);
            for(int i=0;i<100;i++){
                file<<composition[i]<<" ";
            }
            file<<"\n";
        }
    }
    file.close() ;
    cout<<"Finish";
    return 0;
}
