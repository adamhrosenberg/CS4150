#include <algorithm>
#include <iostream>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

/**
Adam Rosenberg
Oliver is a manager of a bank near KTH and wants to close soon. There are many people standing in the queue wanting to put cash into their accounts after they heard that the bank increased the interest rates by 42%42% (from 0.01%0.01% per year to 0.0142%0.0142% per year).
However, there are too many people and only one counter is open which can serve one person per minute. Greedy as Oliver is, he would like to select some people in the queue, so that the total amount of cash stored by these people is as big as possible and that money then can work for the bank overnight.

There is a problem, though. Some people don’t have the time to wait until the bank closes because they have to run somewhere else, so they have to be served before a certain time, after which they just leave. Oliver also turned off the infrared door sensor outside the bank, so that no more people can enter, because it’s already too crowded in the hall.

Task
Help Oliver calculate how much cash he can get from the people currently standing in the queue before the bank closes by serving at most one person per minute.

Input
The first line of input contains two integers NN (1≤N≤10000)(1≤N≤10000) and TT (1≤T≤47)(1≤T≤47), the number of people in the queue and the time in minutes until Oliver closes the bank. Then follow NN lines, each with 2 integers cici and titi, denoting the amount of cash in Swedish crowns person ii has and the time in minutes from now after which person ii leaves if not served. Note that it takes one minute to serve a person and you must begin serving a person at time titi at the latest. You can assume that 1≤ci≤1000001≤ci≤100000 and 0≤ti<T0≤ti<T.

Output
Output one line with the maximum amount of money you can get from the people in the queue before the bank closes.

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