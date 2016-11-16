#include <stdlib.h>
#include <iostream>
#include <queue>
#include <set>
#include <sstream>
#include <map>



/**
Adam Rosenberg
I am traveling next month to the beautiful country of Dagonia, where I am going to rent a car. As I have been making my plans, I have learned four interesting facts about the Dagonian highway system:

The highways lead from city to city; they do not intersect anywhere else.
Each highway is for travel in one direction only.
The highway system is acyclic; once you drive away from a city, there is no way to legally drive back.
Every city charges a toll, payable when you enter the city via a highway.
There are a number of driving trips I would like to take while in Dagonia, and for each I need to determine whether the trip is possible and, if so, the minimum amount I will need to pay in tolls.

For example, Figure 1 is a map of the mining district of Dagistan. If I want to drive from Sourceville to SinkCity, the minimum toll will be $25 ($15 for entering Weston and $10 for entering SinkCity). If I want to drive from Easton to Easton, the minimum toll is $0 (since I am already there). If I want to drive from SinkCity to Weston, I’m out of luck.

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