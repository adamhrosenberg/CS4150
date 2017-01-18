#include <iostream>
#include <math.h>
#include <vector>
/**
Adam Rosenberg
Greedy algorithm to find the cheapest possible route from a to b in a graph. 
**/
using namespace std;
int main() {
    vector<int> input;

    int n=0, i=0, buffer;
    cin >> n;

    for(; i <= n; i++){
        cin >> buffer;
        input.push_back(buffer);
    }

    vector<int> y;
    vector<int> x;

    for (int i = 0; i < input.size(); i++) {
        y.push_back((pow((400 - input[i]), 2)));
        x.push_back(0);
        for (int j = 0; j < i; j++) {
            int temp = pow((400 - (input[i] - input.at(j))), 2);
            if ((y.at(j) + temp) < y.at(i)) {
                x[i] = j + 1;
                y.at(i) =  (y.at(j) + temp);
            }
        }
    }

    cout << y.at(input.size()-1);

    return 0;
}
