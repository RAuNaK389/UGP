#include<iostream>
#include<fstream>
#include<string>
using namespace std;
# define nx 100 
// Defining Diffusitivity function 
float diffusivity(float c){
    float p = 0.5;
    float q = 0.5;
    float D = p + (q*c*c);
    return D;
}

int main(){
    // defining variables
    float delta_t = 0.25;
    float delta_x = 1;
    int total_time_steps=4000;
    float composition[nx];
    float new_composition[nx]; 
    
    // initial composition
    ofstream file("Initial composition.txt");
    for(int i=0;i<nx;i++){
        if(i>nx/4 && i<3*(nx/4)) composition[i]=1;
        else composition[i]=0;
        file<<composition[i]<<" ";
    }
    file<<"\n";
    file.close();

    // Finite Difference method
    for (int t=1;t<=total_time_steps;t++){
        for(int i=0;i<nx;i++){
            // Boundary condition
            int left;
            int right;
            if(i==0){
                right=i+1;
                left=nx-1;
            }
            else if(i==nx-1){
                left=i-1;
                right=0;
            }
            else{
                left=i-1;
                right=i+1;
            }
            // Solving the diffusion equation
            float D1=diffusivity((composition[i]+composition[right])/2);
            float D2 = diffusivity((composition[left]+composition[i])/2);
            new_composition[i]=composition[i]+ ((delta_t/(delta_x*delta_x)) * ( D1*(composition[right]-composition[i]) - D2*(composition[i]-composition[left]))) ;

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
            file.close() ;
        }
    }
    cout<<"Finish";
    return 0;

}