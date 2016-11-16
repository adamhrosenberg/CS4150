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


At the Benjamin Franklin School in Broken Fork Saskatchewan, the spreading of rumors is strictly regulated.

On Day 0, a student wishing to spread a rumor must notify the school office. No spreading of the rumor may occur that day.

On Day 1, the student must tell all of his or her friends the rumor before the end of the day. (Leaving out any friends causes hurt feelings, so this rule is strictly enforced.) No further spreading of the rumor is allowed that day.

On Day 2, each student who learned of the rumor the previous day must pass the rumor along to every friend who has not yet heard the rumor. No further spreading of the rumor is allowed that day.

The rumor must continue spreading in this fashion until the day comes that no more spreading of the rumor is possible under the rules. On that day, the school principal reads the rumor over the intercom, which guarantees that all students have heard the rumor.

Following the intercom announcement, the principal must file a report with the school board. In the report, the principal must list the student who started the rumor, followed by the students (in lexicographic order) who first learned of the rumor on Day 1, and so on, ending with the students (in lexicographic order) who first learned of the rumor over the intercom.

For example, suppose the student body consists of Cam, Art, Edy, Bea, and Dan, where Bea and Edy are friends, Dan and Bea are friends, and Art and Dan are friends.

On Day 0, Dan notifies the office of his plan to start a rumor about the school lunches.
On Day 1, Dan spreads the rumor to his two friends, Bea and Art.
On Day 2, Bea tells her friend Edy. Bea’s other friend (Dan) already knows the rumor, as does Art’s only friend (also Dan).
On Day 3, the rules don’t permit anyone else to be told the rumor, since Edy’s only friend (Bea) already knows. The principal reads the rumor over the intercom and invites everyone to lunch at McDonalds. Cam, who is new to the school and has no friends, finally learns what everyone else has been whispering about.
After lunch, the principal fires the lunchroom staff and files the rumor report, listing the students in this order: Dan, Art, Bea, Edy, Cam.

Your job is to help the principal prepare rumor reports.




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