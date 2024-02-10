#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <cmath>
#include <random>
#include <iomanip>

using namespace std;
using namespace std::chrono;

#define Filepath "\\dataset\\"

void hillClimbing(double* Lands, double runtime, int DataSize, double totalLands) {
}

int main()
{
    string filename = "1";
    double runtime = 5;

    ifstream file(Filepath + filename + ".txt");
    if (!file)
    {
        cout << "Cannot open file: " << filename << endl;
        return 1;
    }
    int DataSize = 0;
    double totalLands = 0;
    double number;

    while (file >> number)
    {
        DataSize++;
        totalLands += number;
    }

    cout << endl
         << "Dataset " << filename << " with " << DataSize << " records " << endl
         << endl;

    double *Lands = new double[DataSize];

    file.clear();
    file.seekg(0, ios::beg);

    for (int i = 0; i < DataSize; i++)
    {
        file >> Lands[i];
    }
    file.close();
    hillClimbing(Lands, runtime, DataSize, totalLands);
    delete[] Lands;

    return 0;
}