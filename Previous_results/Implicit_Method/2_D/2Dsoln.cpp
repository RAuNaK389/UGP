#include<iostream>
#include<fstream>
#include<string>
using namespace std;
# define nx 100 
# define ny 100
# define D 1
# define delta_x 1
# define delta_y 1
#define delta_t 0.25

void initial_composition(float composition[ny][nx]){
    // initialising composition and saving in a file 
    ofstream solution("Initial Composition.txt");
    for(int i=0;i<ny;i++){
        for(int j=0;j<nx;j++){
            if( (j>=(nx/4) && j< (3*nx)/4 )) composition[i][j]=1;
            else composition[i][j]=0;
            solution<<composition[i][j]<<" ";
        }
        solution<<"\n";
    }
    solution.close();
}

void back_substitution(float matrix[ny][2], float temp[],float d[]){
    for(int j=ny-1;j>=0;j--){
        if (j==ny-1) temp[j] = d[j]/matrix[j][0];
        else if(j==0){
            temp[j] = (d[j] -((temp[j+1]*matrix[j][1])+(temp[ny-1]*matrix[0][1])))/matrix[j][0];
        }
        else {
            temp[j] = (d[j] - (temp[j+1]*matrix[j][1]))/matrix[j][0];
        }
    }
}

void update(float composition[ny][nx],float new_composition[ny][nx]){
    for(int i=0;i<ny;i++){
        for(int j=0;j<nx;j++){
            composition[i][j]=new_composition[i][j];
        }
    }
}

void store(float composition[ny][nx],int t){
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

int main(){
    // defining variables
    float composition[ny][nx] , new_composition[ny][nx];
    int total_time_steps = 4000;
    float lambda_y = (D*delta_t)/(2*delta_y*delta_y);
    float lambda_x = (D*delta_t)/(2*delta_x*delta_x);
    float d1[ny];
    float M1[ny][2];
    float a_i,b_i,c_i;
    float temp[ny];

    //Initial composition 
    initial_composition(composition);

    // Using Alternate Direction Implicit Method
    for(int t=1;t<=total_time_steps;t++){
        // Evaluate in y direction
        for(int i=0;i<nx;i++){
            int right=(i==nx-1)?0:i+1;
            int left=(i==0)?nx-1:i-1;
            for(int j=0;j<ny;j++){
                d1[j] = (lambda_x*composition[j][left]) + ((1-2*lambda_x)*composition[j][i]) + (lambda_x*composition[j][right]);
                a_i = 1+(2*lambda_y);
                b_i= -lambda_y;
                if(j==0){
                    M1[j][0] = a_i;
                    M1[j][1]=b_i;
                }
                else {
                    c_i = (b_i/M1[j-1][0]);
                    M1[j][0] = a_i - (b_i*c_i);
                    M1[j][1] = b_i;
                    d1[j]= d1[j]- (c_i*d1[j-1]);
                }
                if(j==ny-1){
                    float c= -lambda_y;
                    for(int k=0;k<ny-1;k++){
                    d1[ny-1] = d1[ny-1] - ((c/M1[k][0])*d1[k]);
                    if(k==ny-2 || k==0) M1[ny-1][0] = M1[ny-1][0] - ((c/M1[k][0])*M1[k][1]);
                    c = 0-((c/M1[k][0])*M1[k][1]);
                    }
                }
            }
            back_substitution(M1,temp,d1);
            for(int j=0;j<ny;j++) new_composition[j][i]=temp[j];
        }
        //update composition at t+delta_t/2
        update(composition,new_composition);

        //Evalute in x direction
        for(int j=0;j<ny;j++){
            int top = (j==0)?ny-1:j-1;
            int bottom = (j==ny-1)?0:j+1;
            for(int i=0;i<nx;i++){
                d1[i] = (lambda_y*composition[bottom][i]) + ((1-2*lambda_y)*composition[j][i]) + (lambda_y*composition[top][i]);
                a_i = 1+(2*lambda_x);
                b_i= -lambda_x;
                if(i==0){
                    M1[i][0] = a_i;
                    M1[i][1]=b_i;
                }
                else {
                    c_i = (b_i/M1[i-1][0]);
                    M1[i][0] = a_i - (b_i*c_i);
                    M1[i][1] = b_i;
                    d1[i]= d1[i]- (c_i*d1[i-1]);
                }
                if(i==nx-1){
                    float c= -lambda_x;
                    for(int k=0;k<nx-1;k++){
                    d1[nx-1] = d1[nx-1] - ((c/M1[k][0])*d1[k]);
                    if(k==nx-2 || k==0) M1[nx-1][0] = M1[nx-1][0] - ((c/M1[k][0])*M1[k][1]);
                    c = 0-((c/M1[k][0])*M1[k][1]);
                    }
                }
            }
            back_substitution(M1,temp,d1);
            for(int i=0;i<nx;i++) new_composition[j][i]=temp[i];
        }

        //update composition at t+delta_t
        update(composition,new_composition);
        
        // storing yhe solution
        if(t%400==0) store(composition,t);
    }
    cout<<"Finish";
    return 0;

}


