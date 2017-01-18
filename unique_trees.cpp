/**
Adam Rosenberg
Input is a variety of binary search trees, and the output is the number of unique shapes of trees.
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


