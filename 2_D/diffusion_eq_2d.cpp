#include<iostream>
#include<fstream>
#include<string>
using namespace std;
#define nx 100
#define ny 100
int main(){
    // defining variables
    int total_time_steps = 4000;
    int delta_x = 1;
    int delta_y = 1;
    int D = 1; // Diffusivity
    double delta_t = 0.25;
    double composition[ny][nx];
    double new_composition[ny][nx];

    // initialising composition and saving in a file 
    ofstream solution("Initial Composition.txt");
    for(int i=0;i<ny;i++){
        for(int j=0;j<nx;j++){
            if((j>=(nx/4) && j< (3*nx)/4 ) && (i>=(ny/4) && i< (3*ny)/4)) composition[i][j]=1;
            else composition[i][j]=0;
            solution<<composition[i][j]<<" ";
        }
        solution<<"\n";
    }
    solution.close();

    // Solving diffusion equation
    for (int t=1;t<=total_time_steps;t++){
        for(int i=0;i<ny;i++){
            // boundary condition on y 
            int left_y,right_y;
                if(i==0 ){
                    left_y = ny-1;
                    right_y =i+1;
                }
                else if(i==ny-1){
                    left_y = i-1;
                    right_y=0;
                }
                else{
                    left_y = i-1;
                    right_y = i+1;
                }

            for(int j=0;j<nx;j++){
                // boundary condition on x 
                int left_x,right_x;
                if(j==0 ){
                    left_x = nx-1;
                    right_x=j+1;
                }
                else if(j==nx-1){
                    left_x = j-1;
                    right_x=0;
                }
                else{
                    left_x = j-1;
                    right_x = j+1;
                }

                // applying FDM
                double x_term = ((D*delta_t)/(delta_x*delta_x))*(composition[right_x][j]-(2*composition[i][j])+composition[left_x][j]) ;
                double y_term = ((D*delta_t)/(delta_y*delta_y))*(composition[i][right_y]-(2*composition[i][j])+composition[i][left_y]) ; 
                new_composition[i][j] = composition[i][j] + x_term + y_term ;

        }
    }

    //Updating Composition 
    for(int i=0;i<ny;i++){
        for(int j=0;j<nx;j++){
            composition[i][j]=new_composition[i][j];
        }
    }
    
    // Saving the solution in a file 
    if(t%400 == 0 ){
        string filename = "solution at t= " + to_string(int(t*delta_t)) + ".txt";
        ofstream solution(filename);
        for(int i=0;i<ny;i++){
        for(int j=0;j<nx;j++){
            solution<<composition[i][j]<<" ";
        }
        solution<<"\n";
    }
    solution.close();
    }
    }
    cout<<"Finish";
    return 0;
}