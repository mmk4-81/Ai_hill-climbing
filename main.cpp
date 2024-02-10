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


int main(){
    string filename = "1";
    double runtime = 5;

    ifstream file(Filepath + filename + ".txt");
    if (!file) {
        cout << "Cannot open file: " << filename << endl;
        return 1;
    }
    
    return 0;
}