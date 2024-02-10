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

void printDistribution(double* Lands, int* distribution, int DataSize) {
    cout << "\nNote: boy1 => 0  **** boy2 => 1  **** girl => 2\n";
    cout << "\nOptimal Distribution:\n\n";
    for (int i = 0; i < DataSize; i++) {
        cout << i << " = " << Lands[i] << " => " << distribution[i] << "  \n";
    }
}

double RandomFunction(double sum[3], double *Lands, int *distributionResult, int DataSize, double totalLands)
{
    mt19937 generator(chrono::high_resolution_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> distribution(0, 2);
    for (int i = 0; i < DataSize; i++)
    {
        int randomindex = distribution(generator);
        sum[randomindex] += Lands[i];
        distributionResult[i] = randomindex;
    }
    return abs(sum[BOY1] - 0.4 * totalLands) + abs(sum[BOY2] - 0.4 * totalLands) + abs(sum[GIRL] - 0.2 * totalLands);
}

void hillClimbing(double *Lands, double runtime, int DataSize, double totalLands)
{
    double idealboy1 = totalLands / 5 * 2;
    double idealboy2 = totalLands / 5 * 2;
    double idealgirl = totalLands / 5;
    double ideal[3] = {idealboy1, idealboy2, idealgirl};
    cout << fixed << setprecision(4);
    cout << "total lands =>" << totalLands << endl;
    cout << "Ideal for boy 1 => " << idealboy1 << endl;
    cout << "Ideal for boy 2 => " << idealboy2 << endl;
    cout << "Ideal for girl => " << idealgirl << endl;
    cout << endl;

    auto start_time = high_resolution_clock::now();

    int *CurrentDistribution = new int[DataSize];
    int *bestDistribution = new int[DataSize];

    double *sum = new double[3]{0, 0, 0};
    double *bestsum = new double[3]{0, 0, 0};
    double currentDiff = RandomFunction(sum, Lands, CurrentDistribution, DataSize, totalLands);
    cout << currentDiff << endl;
    double bestDiff = currentDiff;
    double localmin = currentDiff;
    double minbestDiff = currentDiff;

    while (true)
    {
        for (int j = 0; j < DataSize; j++)
        {

            int originalValue = CurrentDistribution[j];

            if (sum[originalValue] > ideal[originalValue])
            {

                for (int newValue = 0; newValue <= 2; newValue++)
                {

                    if (newValue == originalValue)
                        continue;

                    if (sum[newValue] < ideal[newValue])
                    {
                        sum[newValue] += Lands[j];
                        sum[originalValue] -= Lands[j];

                        double neighborDiff = abs(sum[BOY1] - 0.4 * totalLands) + abs(sum[BOY2] - 0.4 * totalLands) + abs(sum[GIRL] - 0.2 * totalLands);

                        if (neighborDiff <= bestDiff)
                        {
                            bestDiff = neighborDiff;
                            CurrentDistribution[j] = newValue;
                        }
                        else
                        {
                            sum[newValue] -= Lands[j];
                            sum[originalValue] += Lands[j];
                        }
                    }
                }
            }
        }

         if (bestDiff == localmin) {
            if (bestDiff <= minbestDiff) {
                minbestDiff = bestDiff;
                bestDistribution = CurrentDistribution;
                bestsum[0] = sum[0];
                bestsum[1] = sum[1];
                bestsum[2] = sum[2];
            }
            sum[0] = 0;
            sum[1] = 0;
            sum[2] = 0;
            currentDiff = RandomFunction(sum, Lands, CurrentDistribution, DataSize, totalLands);
            bestDiff = currentDiff;
            localmin = currentDiff;
        }
        else {
            localmin = bestDiff;
        }

        auto end_time = high_resolution_clock::now();
        auto elapsed_time = duration_cast<duration<double>>(end_time - start_time).count();

        if (elapsed_time >= runtime)
            break;
    }

    cout << "Optimal F: " << minbestDiff << endl;
    //printDistribution(Lands, bestDistribution, DataSize);
    cout << fixed << setprecision(4); 
    cout << "sum boy1 => " << bestsum[0]<< " , sum boy2 => " << bestsum[1] << " , sum girl => " << bestsum[2] << std::endl;

    delete[] CurrentDistribution;
    delete[] sum;
   // delete[] bestDistribution;
    //delete[] bestsum;
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