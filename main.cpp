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
#define BOY1 0
#define BOY2 1
#define GIRL 2

void hillClimbing(double* Lands, double runtime, int DataSize, double totalLands) {
     double idealboy1 = totalLands / 5 * 2;
    double idealboy2 = totalLands / 5 * 2;
    double idealgirl = totalLands / 5;
    double ideal[3] = { idealboy1, idealboy2, idealgirl };
    cout << fixed << setprecision(4);
    cout << "total lands =>" << totalLands << endl;
    cout << "Ideal for boy 1 => " << idealboy1 << endl;
    cout << "Ideal for boy 2 => " << idealboy2 << endl;
    cout << "Ideal for girl => " << idealgirl << endl;
    cout << endl;

    auto start_time = high_resolution_clock::now();

    int* CurrentDistribution = new int[DataSize];
    int* bestDistribution = new int[DataSize];

    double* sum = new double[3]{ 0, 0, 0 };
    double* bestsum = new double[3]{ 0, 0, 0 };

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