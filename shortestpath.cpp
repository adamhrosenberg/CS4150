// Adam Rosenberg

#include <sstream>
#include <string>
#include <stdio.h>
#include <set>
#include <iostream>
#include <vector>
#include <queue>


using namespace std;

/**
Given a weighted directional cyclic graph, find the cheapest path from a to b, otherwise report impossible. 
**/
struct path{
    int source;
    int destination;
    int weight;
    bool operator<(path p) const {
        return this->weight>p.weight;
    }
};

int main(){
//n = number of nodes
//m = number of edges
//q = number of queuries
//s = starting search index
    int n, m, q, s;

    string streamstring;
    string buffer;
    path currentpath;
    unsigned int src, dest, cost;
    bool flag = false;

    while(true) {
        scanf("%d %d %d %d", &n, &m, &q, &s);
        if(n==0){
            return 0;
        }
        else{
            if(flag){
                cout << endl;
//                flag = true;
            }else{
                flag = true;
            }

        }
        int i;
        vector<vector<path>> edgemap(n);

        for (i = 0; i < m; i++) {
            scanf("%d %d %d", &src, &dest, &cost);
            currentpath.source = src;
            currentpath.destination = dest;
            currentpath.weight = cost;
            edgemap[src].push_back(currentpath);
        }

        src = s;
        vector<int> distances = vector<int>(n, 2147483647);
        priority_queue<path> queue;
        path root;
        root.destination = src;
        root.weight = 0;
        queue.push(root);
        distances.at(src) = 0;

        while (!queue.empty()) {
            path current;
            current = queue.top();
            queue.pop();
            dest = current.destination;
            int j;
            for (j = 0; j < edgemap.at(dest).size(); j++) {
                path pathtocompare = edgemap.at(dest).at(j);
                int currentdistance = pathtocompare.destination;
                if (distances.at(dest) + pathtocompare.weight < distances.at(currentdistance)) {
                    distances.at(currentdistance) = pathtocompare.weight + distances.at(dest);
                    path toadd;
                    toadd.destination = currentdistance;
                    toadd.weight = distances.at(currentdistance);
                    queue.push(toadd);
                }
            }
        }
        int temp;
        for (int k = 0; k < q; k++) {
            scanf("%d", &temp);
            if (distances.at(temp) == 2147483647) {
                cout << "IMPOSSIBLE" << endl;
            } else {
                cout << distances.at(temp) << endl;
            }
        }
    }
    return 0;
}
