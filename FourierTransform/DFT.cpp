#include <iostream>
#include <complex>
#include <cmath>
#include <vector>

using namespace std;
const double PI = acos(-1);
typedef complex<double> cd;

vector<cd> DFT(vector<cd>& input){
    int size;
    vector<cd> output;

    size = input.size();
    int i, j;
    cd cm;
    cd sum;
    for(i = 0; i < size; i++){
        sum = (0, 0);
        for(j = 0; j < size; j++){
            cm = (cos(-2*PI*i*j/size), sin(-2*PI*i*j/size));
            sum += input[j] * cm;
        }
        output.push_back(sum);
    }

    return output;
}

// cos(2PIft) + isin(2PIft) = e^i2PIft