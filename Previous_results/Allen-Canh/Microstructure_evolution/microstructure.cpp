#include <iostream>
#include <fstream>
#include <vector>
#include<string>
using namespace std;

int main() {
    const int ny = 200, nx = 200, n = 36;
    const int total_size = ny * nx * n;

    // Step 1: Read into flat vector
    vector<double> flat_data(total_size);

    ifstream infile("Initial Composition.bin", ios::in | ios::binary);
    if (!infile) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    infile.read(reinterpret_cast<char*>(flat_data.data()), total_size * sizeof(double));
    infile.close();

    // Step 2: Convert flat_data back to 3D vector
    vector<vector<vector<double>>> initial_orientation(ny, vector<vector<double>>(nx, vector<double>(n)));

    for (int i = 0; i < ny; ++i) {
        for (int j = 0; j < nx; ++j) {
            for (int k = 0; k < n; ++k) {
                int idx = i * nx * n + j * n + k;
                initial_orientation[i][j][k] = flat_data[idx];
            }
        }
    }

    

    return 0;
}
