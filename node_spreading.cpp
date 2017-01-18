//Adam Rosenberg

include <iostream>
#include <vector>
#include <list>
#include <sstream>
#include <map>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

/**
Given a graph, where nodes are pushing out messages to each child node, record all of the name names of the nodes in 
lexicographical order efficiently. 
**/

struct Student{
public:
    string name;

    vector<Student*> friends;
    int uid;
//    map<string, Student*> friendsmap;

    Student(string _name){
        name = _name;
    }
};

map<string, Student*> studentmap;
vector<string> studentnames;
int day = 0;
int numberofstudents;

void BFS(string name){

    int maxday = 0;
    set<string>unpopularfriends;
    for(int i = 0; i < numberofstudents; i++){
        unpopularfriends.insert(studentnames.at(i));
    }
    queue<Student*> queue;
    map<int, vector<string>> final;
    Student* current = studentmap[name];
    vector<int> distance(numberofstudents, -1);
    distance.at(current->uid) = 0;
    queue.push(current);
    final[0].push_back(current->name);
    unpopularfriends.erase(current->name);
    while(!queue.empty()){
        Student* curr = queue.front();
        queue.pop();
        for(auto s:curr->friends){
            int friendDist = distance.at(s->uid);
            if(friendDist == -1){
                unpopularfriends.erase(s->name);
                queue.push(s);
                distance.at(s->uid) = distance.at(curr->uid) + 1;
                maxday = distance.at(curr->uid) + 1;
                final[distance.at(s->uid)].push_back(s->name);
            }
        }
    }

    for(int i = 0; i <= maxday ; i++) {
        sort(final[i].begin(), final[i].end());
    }

    for(int i = 0; i <= maxday; i++){
        for(int j = 0; j < final[i].size(); j++){
            cout << final[i].at(j) << " ";
        }
    }

    vector<string> leftofnames;
    for(auto n:unpopularfriends){
        leftofnames.push_back(n);
    }
    sort(leftofnames.begin(), leftofnames.end());
    for(int i = 0; i < leftofnames.size(); i++){
        cout << leftofnames.at(i) << " ";
    }

    cout << endl;
}


int main() {



    string buffer;
    getline(cin, buffer);
    numberofstudents = stoi(buffer);

    for(int i = 0; i<numberofstudents; i++){
        string name;
        getline(cin, name);
        Student* current = new Student(name);
        current->uid = i;
        studentmap[name] = current;
        studentnames.push_back(name);
    }

    int numberoffriendships;
    getline(cin, buffer);
    numberoffriendships = stoi(buffer);

    for(int i = 0; i < numberoffriendships; i++){
        getline(cin, buffer);
        stringstream ss(buffer);
        bool flag = true;
        string src;
        string dest;
        while(ss.good()){
            if(flag){
                ss>>src;
                flag = !flag;
            }else{
                ss>>dest;
            }
        }
        Student* destpointer = studentmap[dest];
        Student* sourcepointer = studentmap[src];
        destpointer->friends.push_back(sourcepointer);
        sourcepointer->friends.push_back(destpointer);


    }

    int numberofrumors;
    getline(cin, buffer);
    numberofrumors = stoi(buffer);
    for(int i = 0; i < numberofrumors; i++){
        getline(cin, buffer);
        BFS(buffer);
    }


//    for(auto s : studentmap)
//        cout<< s.second->name << endl;


    return 0;
}
