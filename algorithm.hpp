#ifndef algorithm_h
#define algorithm_h
#include <iostream>
#include <vector>
#include "puzzle.hpp"

using namespace std;

class node{
public:
    int GameState[3][3];
    int n; //Row of 0
    int m; //Column of 0
    int hn = 10; //hn is h(n)
    char prev = 'e'; //Previous move of puzzle to prevent loops.
    int depth = 0; //Depth of node, is also g(n)
    int fn = 10;   //g(n) + h(n)
    int fn_MD = 10; //Manhattan District f(n)
    int hn_MD = 10; //Manhattan District h(n)
    
    node* left; //node of parent that is left move.
    node* up;  //node of parent that is up move.
    node* down; //node of parent that is down move.
    node* right; //node of parent that is right move.
};
vector<node*> Q;
vector<vector<int>> Puzzles;

//Creates a new node that is null pointers.
node* newNode(int data[3][3], int n, int m){
    node* root = new node();
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            root->GameState[i][j] = data[i][j];
        }
    }
    root->left = nullptr;
    root->right = nullptr;
    root->up = nullptr;
    root->down = nullptr;
    root->n = n;
    root-> m = m;
    return root;
}

//Checks a node to see if it has a duplicate puzzle.
bool CheckDuplicate(node* parent){
    if(Puzzles.size() == 0)
        return false;
    
    vector<int> temp(9);
    int y = 0;
    
    for(int j = 0; j < 3; ++j){
        for(int k = 0; k < 3; ++k){
            temp.at(y) = parent->GameState[j][k];
            ++y;
        }
    }
    
    for(int x = 0; x < Puzzles.size(); ++x){
        int counter = 0;
        for (int i = 0; i < 9; ++i){
            if(Puzzles.at(x).at(i) == temp.at(i))
                ++counter;
            if(counter == 9)
                return true;
        }
    }
    return false;
}

//Adds a node's Puzzle to a list of puzzle to check them later.
void AddPuzzle(node* parent){
    vector<int> temp(9);
    int i = 0;
        for(int j = 0; j < 3; ++j){
            for(int k = 0; k < 3; ++k){
                temp.at(i) = parent->GameState[j][k];
                ++i;
            }
        }
    Puzzles.push_back(temp);
}

//Stores max size of Queue
int Q_Msize = 0;
void getQ_Max_Size(){
    double Q_Size = Q.size();
    if(Q_Size > Q_Msize)
        Q_Msize = Q_Size;
}

//This Function expands a node to all possible moves a puzzle can go to. It also stores all the relevavnt information of a node and also pushes a node to the back of the queue.
int nodes_Expanded = 0;
void Expand_Node(node* &parent){
    node* temp = newNode(parent->GameState, parent->n, parent->m);
    ++nodes_Expanded;
    
    if(temp->m != 0 && parent->prev != 'R'){
        AssignPuzzle(temp->GameState, parent->GameState); //temp = puzzle
        Move_Puzzle(temp->GameState, 'a',temp->n,temp->m);
        if(!CheckDuplicate(temp)){
            node* left = newNode(temp->GameState,temp->n,temp->m);
            parent->left = left;
            temp->n = parent->n;
            temp->m = parent->m;
            left->hn = GetHn(left->GameState);
            left->hn_MD = Get_M_Distance(left->GameState);
            left->prev = 'L';
            left->depth = parent->depth + 1;
            Q.push_back(parent->left);
            left->fn = left->hn + left->depth;
            left->fn_MD = left->hn_MD + left->depth;
            AddPuzzle(left);
        }
        else{
            temp->n = parent->n;
            temp->m = parent->m;
        }
    }
    
    
    if(temp->n != 0 && parent->prev != 'D'){
        AssignPuzzle(temp->GameState, parent->GameState); //temp = puzzle
        Move_Puzzle(temp->GameState, 'w', temp->n,temp->m);
        if(!CheckDuplicate(temp)){
            node* up = newNode(temp->GameState,temp->n,temp->m);
            parent->up = up;
            temp->n = parent->n;
            temp->m = parent->m;
            up->hn = GetHn(up->GameState);
            up->hn_MD = Get_M_Distance(up->GameState);
            up->prev = 'U';
            Q.push_back(parent->up);
            up->depth = parent->depth + 1;
            up->fn = up->hn + up->depth;
            up->fn_MD = up->hn_MD + up->depth;
            AddPuzzle(up);
        }
        else{
            temp->n = parent->n;
            temp->m = parent->m;
        }
        
    }
    
    if(temp->n != 2 && parent->prev != 'U'){
        AssignPuzzle(temp->GameState, parent->GameState); //temp = puzzle
        Move_Puzzle(temp->GameState, 's', temp->n,temp->m);
        if(!CheckDuplicate(temp)){
            node* down = newNode(temp->GameState,temp->n,temp->m);
            parent->down = down;
            temp->n = parent->n;
            temp->m = parent->m;
            down->hn = GetHn(down->GameState);
            down->hn_MD = Get_M_Distance(down->GameState);
            down->prev = 'D';
            down->depth = parent->depth + 1;
            Q.push_back(parent->down);
            down->fn = down->hn + down->depth;
            down->fn_MD = down->hn_MD + down->depth;
            AddPuzzle(down);
        }
        else{
            temp->n = parent->n;
            temp->m = parent->m;
        }
    }
    
    if(temp->m != 2 && parent->prev != 'L'){
        AssignPuzzle(temp->GameState, parent->GameState); //temp = puzzle
        Move_Puzzle(temp->GameState, 'd',temp->n,temp->m);
        node* right = newNode(temp->GameState,temp->n,temp->m);
        if(!CheckDuplicate(temp)){
            parent->right = right;
            right->hn = GetHn(right->GameState);
            right->hn_MD = Get_M_Distance(right->GameState);
            right->prev = 'R';
            right->depth = parent->depth + 1;
            Q.push_back(parent->right);
            right->fn = right->hn + right->depth;
            right->fn_MD = right->hn_MD + right->depth;
            AddPuzzle(right);
        }
        else{
            temp->n = parent->n;
            temp->m = parent->m;
        }
    }
    getQ_Max_Size();
}


//Sorts the Queue in order from greatest to least depth value.
void sortQueue_gn(){
    node* tempi;
    node* tempj;
    for(int i = 0; i < Q.size(); ++i){
        for(int j = i; j < Q.size(); ++j){
            if(Q.at(i)->depth < Q.at(j)->depth){
                tempi = Q.at(i);
                tempj = Q.at(j);
                Q.at(i) = tempj;
                Q.at(j) = tempi;
            }
        }
    }
}

//Sorts the Queue in order from greatest to least hn value.
void sortQueue_Manhattan(){
    node* tempi;
    node* tempj;
    for(int i = 0; i < Q.size(); ++i){
        for(int j = i; j < Q.size(); ++j){
            if(Q.at(i)->fn_MD < Q.at(j)->fn_MD){
                tempi = Q.at(i);
                tempj = Q.at(j);
                Q.at(i) = tempj;
                Q.at(j) = tempi;
            }
        }
    }
}

//Sort the queue in order from greatest to smalled f(n) values of each node.
void sortQueue_fn(){
    node* tempi;
    node* tempj;
    for(int i = 0; i < Q.size(); ++i){
        for(int j = i; j < Q.size(); ++j){
            if(Q.at(i)->fn < Q.at(j)->fn){
                tempi = Q.at(i);
                tempj = Q.at(j);
                Q.at(i) = tempj;
                Q.at(j) = tempi;
            }
        }
    }
    
}

//This is the unifrom search algoithm used to solve a puzzle. This search does not take into account g(n). I didn't explicilty write it but this function does not even look at g(n) because it is hardcoded to 0.
void Uniform_Search(node* parent){
    bool solved = false;
    Expand_Node(parent);
    node* Front = Q.at(Q.size()-1);
    cout << "The best state to expand with h(n) = 1 is..." << endl;
    Display_Puzzle(Front->GameState);
    solved = SolvedState(Front-> GameState);
    while(!solved){
        if(Q.empty()){
            cout << "Failure" << endl;
            return;
        }
        Front = Q.at(Q.size()-1);
        Q.pop_back();
        Expand_Node(Front);
        sortQueue_gn();
        Front = Q.at(Q.size()-1);
        cout << "The best state to expand with h(n) = 1 is..." << endl;
        Display_Puzzle(Front->GameState);
        solved = SolvedState(Front-> GameState);
    }
    cout << "Goal State!" << endl;
    cout << "\nSolution depth was: " << Front->depth << endl;
    cout << "Number of Nodes Expanded: " << nodes_Expanded << endl;
    cout << "Max Queue size: " << Q_Msize << endl;
}

//This search does look at h(n) and g(n) together
void A_Star_Search(node* parent){
    bool solved = false;
    Expand_Node(parent);
    sortQueue_fn();
    node* Front = Q.at(Q.size()-1);
    cout << "The best state to expand with g(n) = " << Front->depth << " and h(n) = " << Front->hn << " is..." << endl;
    Display_Puzzle(Front->GameState);
    solved = SolvedState(Front-> GameState);
    while(!solved){
        if(Q.empty()){
            cout << "Failure" << endl;
            return;
        }
        Front = Q.at(Q.size()-1);
        Q.pop_back();
        Expand_Node(Front);
        sortQueue_fn();
        Front = Q.at(Q.size()-1);
        cout << "The best state to expand with g(n) = " << Front->depth << " and h(n) = " << Front->hn << " is..." << endl;
        Display_Puzzle(Front->GameState);
        solved = SolvedState(Front-> GameState);
    }
    cout << "Goal State!" << endl;
    cout << "\nSolution depth was: " << Front->depth << endl;
    cout << "Number of Nodes Expanded: " << nodes_Expanded << endl;
    cout << "Max Queue size: " << Q_Msize << endl;
}


//This search uses the Manhattan District heuristic as h(n) and the depth of the node as g(n). 
void A_Star_Search_Manhattan(node* parent){
    bool solved = false;
    Expand_Node(parent);
    sortQueue_Manhattan();
    node* Front = Q.at(Q.size()-1);
    cout << "The best state to expand with g(n) = " << Front->depth << " and h(n) = " << Front->hn << " is..." << endl;
    Display_Puzzle(Front->GameState);
    solved = SolvedState(Front-> GameState);
    while(!solved){
        if(Q.empty()){
            cout << "Failure" << endl;
            return;
        }
        Front = Q.at(Q.size()-1);
        Q.pop_back();
        Expand_Node(Front);
        sortQueue_Manhattan();
        Front = Q.at(Q.size()-1);
        cout << "The best state to expand with g(n) = " << Front->depth << " and h(n) = " << Front->hn_MD << " is..." << endl;
        Display_Puzzle(Front->GameState);
        solved = SolvedState(Front-> GameState);
    }
    cout << "Goal State!" << endl;
    cout << "\nSolution depth was: " << Front->depth << endl;
    cout << "Number of Nodes Expanded: " << nodes_Expanded << endl;
    cout << "Max Queue size: " << Q_Msize << endl;
    
}

#endif /* algorithm_h */
