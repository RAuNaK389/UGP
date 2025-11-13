#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <random>
#include <vector>
#include <random>

using namespace std;
#define nx 200
#define delta_t 0.025
#define total_time_steps 40000
#define n 2

// Utility Functions

double summation(vector<double> arr, int i)
{
    double sum = 0;
    if (i == -1)
    {
        for (int j = 0; j < n; j++)
        {
            sum += (pow(arr[j], 4) / 4 - pow(arr[j], 2) / 2);
        }
    }
    else if (i == -2)
    {
        for (int j = 0; j < n - 1; j++)
        {
            for (int k = j + 1; k < n; k++)
            {
                sum += (arr[j] * arr[j] * arr[k] * arr[k]);
            }
        }
    }
    else
    {
        for (int j = 0; j < n; j++)
        {
            if (j != i)
                sum += (arr[j] * arr[j]);
        }
    }

    return sum;
}

int main()
{
    double delta_x = 1, K = 1, A = 1, L = 1, M = 1, kappa = 1, E = 1;
    // double initial_orientation[nx][n], new_orientation[nx][n], new_composition[nx], composition[nx];
    vector<double> composition(nx), new_composition(nx);
    vector<vector<double>> initial_orientation(nx, vector<double>(n));
    vector<vector<double>> new_orientation(nx, vector<double>(n));

    //////////////////////////////////////////////////////////////////////////////////////////

    // Initial Composition profile

    ofstream file("Initial composition.txt");

    // Initial condition

    for (int i = 0; i < nx; i++)
    {
        composition[i]=1;

        // if (i < nx / 2)
        // {
        //     composition[i] = 1;
        // }
        // else
        // {
        //     composition[i] = 0;
        // }
        file << composition[i] << " ";
    }

    file << "\n";
    file.close();

    //////////////////////////////////////////////////////////////////////////////////////

    // Initial order parameter
    for (int i = 0; i < nx; i++)
    {
        // initial_orientation[i][0] = 1;
        // initial_orientation[i][1] = 0;
        if (i < nx / 2)
        {
            initial_orientation[i][0] = 1;
            initial_orientation[i][1] = 0;
        }
        else
        {
            initial_orientation[i][0] = 0;
            initial_orientation[i][1] = 1;
        }
    }

    // Storing Data
    ofstream outfile("Initial order-parm.bin", ios::out | ios::binary);
    vector<double> flat_data;
    flat_data.reserve(nx * n);

    for (int j = 0; j < nx; ++j)
    {
        for (int k = 0; k < n; ++k)
        {
            flat_data.push_back(initial_orientation[j][k]);
        }
    }

    outfile.write(reinterpret_cast<char *>(flat_data.data()), flat_data.size() * sizeof(double));
    outfile.close();
    ////////////////////////////////////////////////////////////////////////////////////

    // Finite Difference
    for (int t = 1; t <= total_time_steps; t++)
    {
        for (int i = 0; i < nx; i++)
        {
            // Boundary Conditions
            int left, right, left_minus, right_plus;
            left = (i == 0) ? nx - 1 : i - 1;
            right = (i == nx - 1) ? 0 : i + 1;
            left_minus = (i == 0) ? nx - 2 : (i == 1 ? nx - 1 : i - 2);
            right_plus = (i == nx - 1) ? 1 : (i == nx - 2 ? 0 : i + 2);

            // Solving CH eqn
            double dc_dx, d2c_dx2, d4c_dx4, m_c, dm_dc, d2m_dc2, d3m_dc3, dh_dx, d2h_dx2, f1c, f2c, f3c, h_n;
            f1c = A * ((2 * composition[i]) + (4 * composition[i] * composition[i] * composition[i]) - (6 * composition[i] * composition[i]));
            f3c = A * ((24 * composition[i]) - 12);
            f2c = A * (2 + (12 * composition[i] * composition[i]) - (12 * composition[i]));
            dc_dx = (composition[right] - composition[left]) / (2 * delta_x);
            d2c_dx2 = (composition[right] + composition[left] - 2 * composition[i]) / (delta_x * delta_x);
            d4c_dx4 = (composition[left_minus] - (4 * composition[left]) + (6 * composition[i]) - (4 * composition[right]) + composition[right_plus]) / (pow(delta_x, 4));
            h_n = 0.25 + summation(initial_orientation[i], -1) + 2 * E * summation(initial_orientation[i], -2);
            double n1_term = ((pow(initial_orientation[i][0], 3)) - (initial_orientation[i][0]) + ((2 * E * initial_orientation[i][0] * summation(initial_orientation[i], 0))));
            double dn1_dx = (initial_orientation[right][0] - initial_orientation[left][0]) / (2 * delta_x);
            double d2n1_dx2 = (initial_orientation[right][0] + initial_orientation[left][0] - (2 * initial_orientation[i][0])) / (delta_x * delta_x);
            dh_dx = n1_term * dn1_dx;
            d2h_dx2 = n1_term * d2n1_dx2 + (dn1_dx * dn1_dx * (2 * E * summation(initial_orientation[i], 0) + 3 * pow(initial_orientation[i][0], 3) - 1));
            // m_c = 1 + (0.5 * composition[i] * composition[i]) - (2.5 * composition[i] * composition[i] * (1 - composition[i]) * (1 - composition[i]));
            // dm_dc = composition[i] - (2.5 * f1c);
            // d2m_dc2 = 1 - (2.5 * f2c);
            // d3m_dc3 = -(2.5 * f3c);
             double c = composition[i];
             m_c = 1 + 0.5 * c * c - 2.5 * c * c * pow(1 - c, 2);
             dm_dc = c - 5 * c * pow(1 - c, 2) + 5 * c * c * (1 - c);
             d2m_dc2 = 1 - 5 * ((1 - c) * (1 - c) - 2 * c * (1 - c)) + 10 * c * (1 - c) - 5 * c * c;
             d3m_dc3 = 20 - 60 * c;

            double exp = M * ((f2c * d2c_dx2) + (f3c * dc_dx * dc_dx) + (d2h_dx2 * dm_dc) + (dh_dx * d2m_dc2 * dc_dx) + (d2m_dc2 * dc_dx * dh_dx) + (d3m_dc3 * dc_dx * dc_dx * h_n) + (d2m_dc2 * d2c_dx2 * h_n) - (2 * kappa * d4c_dx4));
            new_composition[i] = composition[i] + delta_t * exp;
            // new_composition[i]=min(1.0, max(0.0, new_composition[i]));

            // Solving for Order-Parameter
            for (int k = 0; k < n; k++)
            {
                double term1 = (pow(initial_orientation[i][k], 3)) - (initial_orientation[i][k]) + ((2 * initial_orientation[i][k]) * (summation(initial_orientation[i], k)));
                double d2n_dx2 = (initial_orientation[right][k] + initial_orientation[left][k] - (2 * initial_orientation[i][k])) / (delta_x * delta_x);
                new_orientation[i][k] = initial_orientation[i][k] + (delta_t * L * (2 * K * d2n_dx2 - m_c * term1));
                // new_orientation[i][k] = min(1.0, max(0.0, new_orientation[i][k]));
            }
        }
        // Updating values

        for (int i = 0; i < nx; i++)
        {
            for (int k = 0; k < n; k++)
            {
                initial_orientation[i][k] = new_orientation[i][k];
            }
        }
        for (int i = 0; i < nx; i++)
        {
            composition[i] = new_composition[i];
        }

        // Storing the solution in a file
        if (t % 4000 == 0)
        {
            string filename = "Composition at t= " + to_string(int(t * delta_t)) + ".txt";
            ofstream file(filename);
            for (int i = 0; i < nx; i++)
            {
                file << composition[i] << " ";
            }
            file << "\n";
            file.close();

            // for order=param
            string f_name = "Order-param at t= " + to_string(int(t * delta_t)) + ".bin";
            ofstream outfile(f_name, ios::out | ios::binary);
            vector<double> flat_data_1;
            flat_data_1.reserve(nx * n);

            for (int i = 0; i < nx; ++i)
            {
                for (int k = 0; k < n; ++k)
                {
                    flat_data_1.push_back(initial_orientation[i][k]);
                }
            }

            outfile.write(reinterpret_cast<char *>(flat_data_1.data()), flat_data_1.size() * sizeof(double));
            outfile.close();
        }
    }
    cout << "Finish" << endl;
    ;
    return 0;
}
