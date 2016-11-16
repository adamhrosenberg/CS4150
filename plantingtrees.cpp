#include <iostream>
#include <string.h>
#include <vector>
#include <sstream>
#include <algorithm>

/**
Adam Rosenberg


Farmer Jon has recently bought nn tree seedlings that he wants to plant in his yard. It takes 11 day for Jon to plant a seedling1, and for each tree Jon knows exactly in how many days after planting it grows to full maturity. Jon would also like to throw a party for his farmer friends, but in order to impress them he would like to organize the party only after all the trees have grown. More precisely, the party can be organized at earliest on the next day after the last tree has grown up.

Help Jon to find out when is the earliest day when the party can take place. Jon can choose the order of planting the trees as he likes, so he wants to plant the trees in such a way that the party will be as soon as possible.

Input
The input consists of two lines. The first line contains a single integer NN (1≤N≤1000001≤N≤100000) denoting the number of seedlings. Then a line with NN integers titi follows (1≤ti≤10000001≤ti≤1000000), where titi denotes the number of days it takes for the iith tree to grow.

Output
You program should output exactly one line containing one integer, denoting the earliest day when the party can be organized. The days are numbered 1,2,3,…1,2,3,… beginning from the current moment.

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