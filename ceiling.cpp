/**
Adam Rosenberg


Advanced Ceiling Manufacturers (ACM) is analyzing the properties of its new series of Incredibly Collapse-Proof Ceilings (ICPCs). An ICPC consists of nn layers of material, each with a different value of collapse resistance (measured as a positive integer). The analysis ACM wants to run will take the collapse-resistance values of the layers, store them in a binary search tree, and check whether the shape of this tree in any way correlates with the quality of the whole construction. Because, well, why should it not?

To be precise, ACM takes the collapse-resistance values for the layers, ordered from the top layer to the bottom layer, and inserts them one-by-one into a tree. The rules for inserting a value vv are:

If the tree is empty, make vv the root of the tree.
If the tree is not empty, compare vv with the root of the tree. If vv is smaller, insert vv into the left subtree of the root, otherwise insert vv into the right subtree.
ACM has a set of ceiling prototypes it wants to analyze by trying to collapse them. It wants to take each group of ceiling prototypes that have trees of the same shape and analyze them together.

For example, assume ACM is considering five ceiling prototypes with three layers each, as described by Sample Input 1 and shown in Figure 1. Notice that the first prototype’s top layer has collapse-resistance value 2, the middle layer has value 7, and the bottom layer has value 1. The second prototype has layers with collapse-resistance values of 3, 1, and 4 – and yet these two prototypes induce the same tree shape, so ACM will analyze them together.

Given a set of prototypes, your task is to determine how many different tree shapes they induce.

Input
The first line of the input contains two integers nn (1≤n≤501≤n≤50), which is the number of ceiling prototypes to analyze, and kk (1≤k≤201≤k≤20), which is the number of layers in each of the prototypes.

The next nn lines describe the ceiling prototypes. Each of these lines contains kk distinct integers (between 11 and 106106, inclusive), which are the collapse-resistance values of the layers in a ceiling prototype, ordered from top to bottom.

Output
Display the number of different tree shapes.
**/


#include <vector>
#include <sstream>
#include <iostream>
#include <set>



using namespace std;


class node{
public:
    int data;
    node* leftchild;
    node* rightchild;
    int hasbeenchecked;
public:
    node(int data){
        this->data = data;
        leftchild = 0;
        rightchild = 0;
        hasbeenchecked=0;
    }
};

node* insert(int data, node* root){
	if(root == NULL){
		root = new node(data);
        root->data = data;
		return root;
	}
	else{
        node* current = root;
        do{
            if (data > current->data) {

                if (current->rightchild == NULL) {
                    current->rightchild = new node(data);
                    current->rightchild->data = data;
//                    current->rightchild->rightchild = 0;
//                    current->rightchild->leftchild = 0;
                    current = NULL;
                } else {
                    current = current->rightchild;
                }
                } else if (data < current->data) {
                    if (current->leftchild == NULL) {
                        current->leftchild = new node(data);
                        current->leftchild->data = data;
//                        current->leftchild->rightchild = 0;
//                        current->leftchild->leftchild = 0;
                        current = NULL;
                    } else {
                        current = current->leftchild;
                    }
                }
        }while(current!=NULL);
		return root;
	}
}

int uniqueshape(struct node* first, struct node* second){

    if(first == NULL || second == NULL)
        return((first == NULL) & (second==NULL));

    return (uniqueshape(first->rightchild, second->rightchild) && uniqueshape(first->leftchild, second->leftchild));
}



int main(int argc, char* argv[]){

    vector<node*> forest; //group of trees
    int currentlevel = 0;
    int height;
	string first;
	getline(cin,first);
	stringstream ss(first);
    if(ss.good())
        ss >> first;
    height = stoi(first);



	for(int i = 0; i < height; i++){
        node* rootptr = 0;
		string indexline;
		int val = 0;

		getline(cin,indexline);
		stringstream ss(indexline);

		while(ss >> val){
            rootptr = insert(val, rootptr);
		}

		forest.push_back(rootptr);
	}



    int equaltrees = 0;
    for(int outer = 0; outer < forest.size()-1; outer++){
        for(int inner = forest.size()-1; inner > outer;  inner--){

            if(!forest.at(inner)->hasbeenchecked){
                if(uniqueshape(forest.at(outer), forest.at(inner))){
                    forest.at(inner)->hasbeenchecked = 1;
//                    cout << "tree at " << outer << " equals tree at " << inner << endl;
                    equaltrees++;
                }
            }
        }
    }

    for(const auto& i: forest){

    }

    int sum=0;
    for(int i = 0; i < forest.size(); i++){
        sum += i;
    }

//    cout << "equal trees, sum, forest.size() " << equaltrees << " " << sum << " " << forest.size() << endl;
    if(equaltrees == sum){
        cout<<"1" << endl;
    }
    else{
        cout << forest.size() - equaltrees << endl;
    }



	return 0;
}


