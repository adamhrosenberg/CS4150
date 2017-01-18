#include <stdlib.h>
#include <iostream>
#include <queue>
#include <set>
#include <sstream>
#include <map>



/**
Adam Rosenberg
In this problem the input describe a DAG, and gives a source and end node. 
Each node has a cost associated with it, and the algorithm here is to find the 
cheapest route from A to B.
**/
using namespace std;



class Node{
public:
    string cityname;
    int i;
    int weight;
    bool operator()(Node* lhs,Node* rhs)
    {
        return lhs->weight >= rhs->weight;
    }
};
struct AdjList{
    map<string,set<Node*> > list;
    map<string,Node*> citymap;
    int n;
};


int shortest(AdjList* map,string _src, string _dest){
    Node* src = map->citymap[_src];
    Node* dest = map->citymap[_dest];
    priority_queue<Node*,vector<Node*>, Node> pq;
    int dist[map->n];
    for(int i = 0; i < map->n; i++){
        dist[i] = 2147483647;
    }
    pq.push(src);
    dist[src->i] = 0;
    while(!pq.empty()){
        Node* currentCity = pq.top();
        pq.pop();
        set<Node*> currentList = map->list[currentCity->cityname];
        set<Node*>::iterator iter;
        for(iter = currentList.begin(); iter != currentList.end(); iter++){
            int nextIndex = (*iter)->i;
            int nextWeight = (*iter)->weight;
            int nextD = dist[currentCity->i]+ nextWeight;
            if(dist[nextIndex] > nextD){
                dist[nextIndex] = nextD;
                pq.push(*iter);
            }
        }
    }
    return dist[dest->i];
}

int main (int argc, char** argv){
    AdjList* roadMap = new AdjList;
    string n;
    getline(cin,n);
    roadMap->n = stoi(n);
    for(int i = 0; i < stoi(n); i ++){
        set<Node*> list;
        Node* node = new Node;
        string name;
        getline(cin, name);
        stringstream ss(name);
        int weight = 0;
        int flag = 0;
        for(int index = 0; index < 2; index++){
            string name;
            if(flag == 0){
                ss >> name;
                node->cityname = name;
                flag = 1;
            }else if(flag == 1){
                ss >> weight;
                node->weight = weight;
                flag = 0;
            }
        }
        roadMap->citymap[node->cityname] = node;
        roadMap->list[node->cityname] = list;
        node->i = i;



    }

    string highways;
    getline(cin,highways);
    int numHighways = stoi(highways);
    for(int i = 0; i < numHighways; i ++){
        string currentCity;
        getline(cin,currentCity);
        stringstream ss(currentCity);
        string src, dest;
        for(unsigned int j = 0; j < 2; j++){
            if(j == 1){
                ss >> dest;
            }
            else{
                ss >> src;
            }
        }
        roadMap->list[src].insert(roadMap->citymap[dest]);
    }




    int t = 0;
    string currentTrip;
    getline(cin,currentTrip);
    t = stoi(currentTrip);
    for(int i = 0; i < t; i++){
        string src, dest;
        string trip;
        getline(cin,trip);
        stringstream str(trip);
        for(int j = 0; j < 2; j++){
            if(j == 0){
                str >> src;
            } else{
                str >> dest;
            }
        }
        int tollTotal = shortest(roadMap,src,dest);
        if(tollTotal == 2147483647){
            cout << "NO" << endl;
        }else{
            cout << tollTotal << endl;
        }
    }
    return 0;
}
