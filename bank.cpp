#include <algorithm>
#include <iostream>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

/**
Adam Rosenberg
The problem here is that there a queue of people in line, the objective is to find the maximum amount of money 
you can profit from the people in the queue before the establishment closes. 
**/

struct person{ int amount, duration;};
struct couple{ int first, second;};
bool peopleop(const person &a, const person &b)
{
        return a.amount >= b.amount;
}

void orderpeople(vector<int>& peoples, person p)
{
	for(int i = p.duration; i >= 0; i--){
		if(peoples[i] == 0){
		peoples[i] = p.amount;
		break;
		}
	}    
}

couple parseacouple(){
	couple scope;
	int first, second;
	scanf("%d%d", &first, &second);
	scope.first = first;
	scope.second = second;
	return scope;
}
int main(int argc, const char * argv[]) {
        vector<person> peoples;
      	int first;
	int second;
	int numberofpeople;
	int total = 0;
    	couple coup = parseacouple();
	numberofpeople  = coup.first;
	second = coup.second;    
	vector<int> line(second);

	
    for(int i = 0; i < numberofpeople ; i++){
        couple coup = parseacouple();
        person p;
	p.amount = coup.first;
	p.duration = coup.second;
        peoples.push_back(p);
    }
    
    	sort(peoples.begin(), peoples.end(), peopleop);
    
   	for(int i = 0; i < peoples.size(); i++)
		orderpeople(line,peoples[i]);
	
    
        for(int i = 0; i < line.size(); i++)
        	total += line[i];
   	 
    
    cout << total;

    
    return 0;
}
