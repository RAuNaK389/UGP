#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <random>
#include <vector>
using namespace std;
#define nx 200
#define ny 200
#define n 36

double summation(vector<double> &arr, int i)
{
    double sum = 0;
    for (int j = 0; j < n; j++)
    {
        if (j != i)
            sum += (arr[j] * arr[j]);
    }
    return sum;
}

int main()
{
    double delta_x = 1, delta_y = 1, alpha = 1, beta = 1, gamma = 1, delta_t = 0.1, L = 1, kappa = 1;
    int total_time_steps = 10000;
    // double initial_orientation[ny][nx][n], final_orientation[ny][nx][n];
    vector<vector<vector<double> > > initial_orientation(ny, vector<vector<double> >(nx, vector<double>(n)));
    vector<vector<vector<double> > > final_orientation(ny, vector<vector<double> >(nx, vector<double>(n)));

    // Random number generator
    random_device rd;  // Seed generator
    mt19937 gen(rd()); // Mersenne Twister PRNG

    double min = 0, max = 0 + 0.01; // Define range
    uniform_real_distribution<double> dist(min, max);

    // Initial condition
    for (int i = 0; i < ny; i++)
    {
        for (int j = 0; j < nx; j++)
        {
            for (int k = 0; k < n; k++)
            {
                initial_orientation[i][j][k] = dist(gen);
            }
        }
    }

    // Storing Data
    ofstream outfile("Initial Composition.bin", ios::out | ios::binary);
    vector<double> flat_data;
    flat_data.reserve(ny * nx * n);

    for (int i = 0; i < ny; ++i)
    {
        for (int j = 0; j < nx; ++j)
        {
            for (int k = 0; k < n; ++k)
            {
                flat_data.push_back(initial_orientation[i][j][k]);
            }
        }
    }

    outfile.write(reinterpret_cast<char *>(flat_data.data()), flat_data.size() * sizeof(double));
    outfile.close();
    // outfile.write(reinterpret_cast<char*>(&initial_orientation[0][0][0]), ny * nx * n * sizeof(double));

    // Saving the data for grain boundaries
    ofstream outfile2("Initial Microstructure.bin", ios::out | ios::binary);
    vector<double> flat_data2;
    flat_data2.reserve(ny * nx * n);

    for (int i = 0; i < ny; ++i)
    {
        for (int j = 0; j < nx; ++j)
        {
            flat_data2.push_back(summation(initial_orientation[i][j], -1));
        }
    }

    outfile2.write(reinterpret_cast<char *>(flat_data2.data()), flat_data2.size() * sizeof(double));
    outfile2.close();

    for (int t = 1; t <= total_time_steps; t++)
    {
        for (int i = 0; i < ny; i++)
        {
            for (int j = 0; j < nx; j++)
            {
                // periodic boundary conditions
                int right, left, right_plus, left_minus;
                int top, top_minus, down, down_plus;
                right = (j == nx - 1) ? 0 : j + 1;
                left = (j == 0) ? nx - 1 : j - 1;

                right_plus = (j == nx - 2) ? 0 : ((j == nx - 1) ? 1 : j + 2);
                left_minus = (j == 1) ? nx - 1 : ((j == 0) ? nx - 2 : j - 2);

                top = (i == 0) ? ny - 1 : i - 1;
                down = (i == ny - 1) ? 0 : i + 1;

                top_minus = (i == 1) ? ny - 1 : ((i == 0) ? ny - 2 : i - 2);
                down_plus = (i == ny - 2) ? 0 : ((i == ny - 1) ? 1 : i + 2);

                for (int k = 0; k < n; k++)
                {
                    double term1 = (beta * pow(initial_orientation[i][j][k], 3)) - (alpha * initial_orientation[i][j][k]) + ((2 * gamma * initial_orientation[i][j][k]) * (summation(initial_orientation[i][j], k)));
                    double d2n_dx2 = (0.5 * (initial_orientation[i][right][k] + initial_orientation[i][left][k] - (2 * initial_orientation[i][j][k])) + 0.25 * (initial_orientation[i][right_plus][k] + initial_orientation[i][left_minus][k] - (2 * initial_orientation[i][j][k]))) / (delta_x * delta_x);
                    double d2n_dy2 = (0.5 * (initial_orientation[top][j][k] + initial_orientation[down][j][k] - (2 * initial_orientation[i][j][k])) + 0.25 * (initial_orientation[top_minus][j][k] + initial_orientation[down_plus][j][k] - (2 * initial_orientation[i][j][k]))) / (delta_y * delta_y);
                    double term_2 = (d2n_dx2 + d2n_dy2) * kappa;
                    final_orientation[i][j][k] = initial_orientation[i][j][k] + (delta_t * L * (term_2 - term1));
                }
            }
        }

        // updating the data
        for (int i = 0; i < ny; i++)
        {
            for (int j = 0; j < nx; j++)
            {
                for (int k = 0; k < n; k++)
                {
                    initial_orientation[i][j][k] = final_orientation[i][j][k];
                }
            }
        }

        // storing the result
        if (t % 500 == 0){
            string filename = "Solution at t= " + to_string(int(t * delta_t)) + ".bin";
            ofstream outfile(filename, ios::out | ios::binary);
            vector<double> flat_data;
            flat_data.reserve(ny * nx * n);

            for (int i = 0; i < ny; ++i){
                for (int j = 0; j < nx; ++j){
                    for (int k = 0; k < n; ++k){
                        flat_data.push_back(initial_orientation[i][j][k]);
                    }
                }
            }
            outfile.write(reinterpret_cast<char *>(flat_data.data()), flat_data.size() * sizeof(double));
            outfile.close();
            // Saving the data for grain boundaries
            string filename2 = "Microstructure at t= " + to_string(int(t * delta_t)) + ".bin";
            ofstream outfile2(filename2, ios::out | ios::binary);
            vector<double> flat_data2;
            flat_data2.reserve(ny * nx * n);

            for (int i = 0; i < ny; ++i){
                for (int j = 0; j < nx; ++j){
                    flat_data2.push_back(summation(initial_orientation[i][j], -1));
                }
            }
            outfile2.write(reinterpret_cast<char *>(flat_data2.data()), flat_data2.size() * sizeof(double));
            outfile2.close();
        }
    }
    cout << "Finish" << endl;
}