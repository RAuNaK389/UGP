#include<iostream>
#include<fstream>
#include<string>
using namespace std;
# define nx 100 
void back_substitution(float matrix[nx][2] ,float new_composition[nx] , float d[nx] ){
    for(int i=nx-1;i>=0;i--){
        if (i==nx-1) new_composition[i] = d[i]/matrix[i][0];
        else if(i==0){
            new_composition[i] = (d[i] -((new_composition[i+1]*matrix[i][1])+(new_composition[nx-1]*matrix[0][1])))/matrix[i][0];
        }
        else {
            new_composition[i] = (d[i] - (new_composition[i+1]*matrix[i][1]))/matrix[i][0];
        }
    }
}

int main(){
    // defining variables
    float delta_t = 0.25;
    float delta_x = 1;
    float D=1;
    int total_time_steps=4000;
    float composition[nx];
    float new_composition[nx]; 
    float lambda= (D*delta_t)/(2*delta_x*delta_x);
    float matrix[nx][2];
    float d[nx];
    float a_i,b_i,c_i,c_i_prime;
    
    // initial composition
    ofstream file("Initial composition.txt");
    for(int i=0;i<nx;i++){
        if(i>nx/4 && i<3*(nx/4)) composition[i]=1;
        else composition[i]=0;
        file<<composition[i]<<" ";
    }
    file<<"\n";
    file.close();

    /* Solving with implicit method will give a tridiagonal matrix AX=d.
    So we will convert the tridiagonal matrix to an upper triangular matrix using Gauss eleminitation method
    And then solve the system of linear equations using back-substitution. */
    for (int t=1;t<=total_time_steps;t++){
        for(int i=0;i<nx;i++){
            // Boundary condition
            int left = (i==0)?(nx-1):i-1;
            int right = (i==nx-1)?0:i+1;

            // d_vector represent the right hand side of the equation AX=d. 
            d[i]=(lambda*composition[right])+((1-(2*lambda))*composition[i]) + (lambda*composition[left]);

            /* As after converting the tridiagonal matrix to an upper triangular matrix each row will contain only two 
            non-zero values will be present in so we will we using a 2D array "matrix" with dimension (nx,2) to store the 
            U matrix for efficient space complexity.
            matrix[i][0] will represent diagonal elements .*/
            a_i = 1+(2*lambda);
            b_i = -lambda;
            c_i = -lambda;

            if(i==0){
                matrix[i][0]= a_i;
                matrix[i][1]=b_i;
            }
            else{
                c_i_prime = c_i/matrix[i-1][0];
                matrix[i][0] = a_i - (c_i_prime * matrix[i-1][1]);
                matrix[i][1] = b_i;
                d[i]= d[i] -(c_i_prime*d[i-1]);
            }   
        }
        float c = -lambda;
        for(int k=0;k<nx-1;k++){
            d[nx-1] = d[nx-1] - ((c/matrix[k][0])*d[k]);
            if(k==nx-2 || k==0) matrix[nx-1][0] = matrix[nx-1][0] - ((c/matrix[k][0])*matrix[k][1]);
            c = 0-((c/matrix[k][0])*matrix[k][1]);
        }
        
        back_substitution(matrix,new_composition,d);
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