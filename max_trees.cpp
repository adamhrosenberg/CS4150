#include <iostream>
#include <string.h>
#include <vector>
#include <sstream>
#include <algorithm>

/**
Adam Rosenberg
Greedy algorithm to schedule the planting of trees to maximize profit. 
**/
using namespace std;

bool greaterThan (int i,int j) { return (i>j); }

int main() {
    int numberOfTrees;
    string days = "";
    cin >> numberOfTrees;
    cin.ignore(256, '\n');
    getline(cin, days);
    stringstream stream(days);
    string num;
    vector<int> trees;

    while (stream >> num)
        trees.push_back(stoi(num));

    sort(trees.begin(), trees.end(), greaterThan);

    int max = 0;
    for(int i = 1; i <= numberOfTrees; i++){
        int x = trees.at(i-1);
        if(x+i > max){
            max = trees.at(i-1) + i;
        }
    }

    max++;
    cout << max << endl;

    return 0;
}
