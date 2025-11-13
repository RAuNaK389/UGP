#include<iostream>
#include<math.h>
#include<fstream>
#include<string>
using namespace std;
#define nx 200
#define ny 50
//f=A*c*(1-c)^2

int main(){
    // Defining Variables
    long long total_time_Steps = 400000;
    double delta_t = 0.0025, delta_x = 1, delta_y = 1 ;
    double A = 1, M = 1, K =1  ;//kappa
    double composition[ny][nx] , new_composition[ny][nx] ;
     

    // Initial Composition
    ofstream solution("Initial Composition.txt");
    for(int i=0;i<ny;i++){
        for(int j=0;j<nx;j++){
            if( (j>=(nx*9)/20 && j< (nx*11)/20 )) composition[i][j]=1;
            else composition[i][j]=0.2;
            solution<<composition[i][j]<<" ";
        }
        solution<<"\n";
    }
    solution.close(); 

     // Solving using finite difference method 
     for(long long t=1;t<=total_time_Steps;t++){
        for(int i=0;i<ny;i++){

            //Boundary conditions in y 
            int top , down , top_minus , down_plus;
            if(i==ny-1){
                down = 0 , down_plus=1 ; 
                top = i-1 , top_minus = i-2;
            }
            else if(i==ny-2){
                down = i+1 , down_plus=0; 
                top = i-1 , top_minus = i-2;
            }
            else if(i==0){
                down = i+1 , down_plus=i+2;
                top = ny-1 , top_minus = ny-2;
            }
            else if(i==1){
                down = i+1 , down_plus=i+2;
                top = i-1 , top_minus = ny-1;
            }
            else{
                down = i+1 , down_plus=i+2;
                top = i-1 , top_minus = i-2;
            }

            for(int j=0;j<nx;j++){

                //boundary conditions in x 
                int right, left, right_plus, left_minus ;
                if(j==nx-1){
                    right = 0,right_plus=1;
                    left=j-1;left_minus=j-2;
                }
                else if(j==nx-2){
                    right = j+1;right_plus=0;
                    left=j-1;left_minus=j-2;
                }
                else if(j==0){
                    right = j+1;right_plus=j+2;
                    left=nx-1;left_minus=nx-2;
                }
                else if(j==1){
                    right = j+1;right_plus=j+2;
                    left=0;left_minus=nx-1;
                }
                else{
                    right = j+1;right_plus=j+2;
                    left=j-1;left_minus=j-2;
                }
                
                // Storing the updated values in new array
                double f3c = A*(24*composition[i][j]-12); 
                double f2c = A*(2+(12*composition[i][j]*composition[i][j])-(12*composition[i][j]));

                double dc_dx = (composition[i][right] - composition[i][left] )/ (2*delta_x);
                double dc_dy = (composition[top][j] - composition[down][j] )/ (2*delta_y);

                double d2c_dx2 = (composition[i][left] - (2*composition[i][j]) + composition[i][right])/(delta_x*delta_x);
                double d2c_dy2 = (composition[top][j] - (2*composition[i][j]) + composition[down][j])/(delta_y*delta_y);

                double d4c_dx4 = (composition[i][left_minus]-(4*composition[i][left])+(6*composition[i][j])-(4*composition[i][right])+composition[i][right_plus])/(pow(delta_x,4));
                double d4c_dy4 = (composition[top_minus][j]-(4*composition[top][j])+(6*composition[i][j])-(4*composition[down][j])+composition[down_plus][j])/(pow(delta_y,4));

                double d4c_dx2_dy2 = (composition[down][right]-(2*composition[i][right])+composition[top][right]-(2*composition[down][j])+(4*composition[i][j])-(2*composition[top][j])+composition[down][left]-(2*composition[i][left])+composition[top][left])/(delta_x*delta_x*delta_y*delta_y);

                new_composition[i][j]=composition[i][j] + (M*delta_t)*((f2c*(d2c_dx2+d2c_dy2))+(f3c*(pow(dc_dx,2)+pow(dc_dy,2))) - (2*K*(d4c_dx4+d4c_dy4+2*d4c_dx2_dy2)));
            }
        }
        //Updating Composition  after one time step
        for(int i=0;i<ny;i++){
            for(int j=0;j<nx;j++){
                composition[i][j]=new_composition[i][j];
            }
        }

        // Storing data 
        if(t%40000 == 0 ){
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