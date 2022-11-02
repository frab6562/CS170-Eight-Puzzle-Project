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
    
    node* left; //node of parent that is left move.
    node* up;  //node of parent that is up move.
    node* down; //node of parent that is down move.
    node* right; //node of parent that is right move.
};
vector<node*> Q;
vector<node*> P;

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


// I could not get this function to work :(
//If given more time this function will check for duplicates in the tree, however it keeps having memory leaks.
//template <int rows, int cols>
//bool CheckDuplicate(int (&puzzle)[rows][cols], vector<node*> P){
//    bool duplicate;
//    int comp[3][3];
//    if(P.size() == 0)
//        return false;
//    for(int x = 0; x < P.size(); ++x){
//    //    AssignPuzzle(comp,P.at(x)->GameState);
//        for (int i = 0; i < 3; ++i){
//            for (int j = 0; j < 3; ++j){
//                if(puzzle[i][j] != comp[i][j])
//                    return duplicate = false;
//            }
//        }
//    }
//    return duplicate = true;
//}

//This Function expands a node to all possible moves a puzzle can go to. It also stores all the relevavnt information of a node and also pushes a node to the back of the queue.
int nodes_Expanded = 0;
void Expand_Node(node* &parent){
    node* temp = newNode(parent->GameState, parent->n, parent->m);
    if(temp->m != 0 && parent->prev != 'R'){
        AssignPuzzle(temp->GameState, parent->GameState); //temp = puzzle
        Move_Puzzle(temp->GameState, 'a',temp->n,temp->m);
        node* left = newNode(temp->GameState,temp->n,temp->m);
        parent->left = left;
        //Display_Puzzle(left->GameState);
        temp->n = parent->n;
        temp->m = parent->m;
        left->hn = GetHn(left->GameState);
        left->prev = 'L';
        left->depth = parent->depth + 1;
        Q.push_back(parent->left);
        ++nodes_Expanded;
        left->fn = left->hn + left->depth;
    }
    
    
    if(temp->n != 0 && parent->prev != 'D'){
        AssignPuzzle(temp->GameState, parent->GameState); //temp = puzzle
        Move_Puzzle(temp->GameState, 'w', temp->n,temp->m);
        node* up = newNode(temp->GameState,temp->n,temp->m);
        parent->up = up;
        //Display_Puzzle(up->GameState);
        temp->n = parent->n;
        temp->m = parent->m;
        up->hn = GetHn(up->GameState);
        up->prev = 'U';
        Q.push_back(parent->up);
        up->depth = parent->depth + 1;
        ++nodes_Expanded;
        up->fn = up->hn + up->depth;
    }
    
    if(temp->n != 2 && parent->prev != 'U'){
        AssignPuzzle(temp->GameState, parent->GameState); //temp = puzzle
        Move_Puzzle(temp->GameState, 's', temp->n,temp->m);
        node* down = newNode(temp->GameState,temp->n,temp->m);
        parent->down = down;
        //Display_Puzzle(down->GameState);
        temp->n = parent->n;
        temp->m = parent->m;
        down->hn = GetHn(down->GameState);
        down->prev = 'D';
        down->depth = parent->depth + 1;
        Q.push_back(parent->down);
        ++nodes_Expanded;
        down->fn = down->hn + down->depth;
    }
    
    if(temp->m != 2 && parent->prev != 'L'){
        AssignPuzzle(temp->GameState, parent->GameState); //temp = puzzle
        Move_Puzzle(temp->GameState, 'd',temp->n,temp->m);
        node* right = newNode(temp->GameState,temp->n,temp->m);
        parent->right = right;
        right->hn = GetHn(right->GameState);
        right->prev = 'R';
        right->depth = parent->depth + 1;
        Q.push_back(parent->right);
        ++nodes_Expanded;
        right->fn = right->hn + right->depth;
    }
}


//Sorts the Queue in order from greatest to least hn value.
void sortQueue_hn(){
    node* tempi;
    node* tempj;
    for(int i = 0; i < Q.size(); ++i){
        for(int j = i; j < Q.size(); ++j){
            if(Q.at(i)->hn < Q.at(j)->hn){
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

//Used to test the code as I was building it
void DisplayQ(){
    for(int i = 0; i < Q.size(); ++i){
        cout << Q.at(i)->hn << " ";
    }
    cout << endl;
}

//Used to test the code as I was building it
void DisplayFN(){
    for(int i = 0; i < Q.size(); ++i){
        cout << Q.at(i)->fn << " ";
    }
    cout << endl;
}

void Uniform_Search(node* parent){
    bool solved = false;
    Expand_Node(parent);
    sortQueue_hn();
    node* Front = Q.at(Q.size()-1);
    cout << "The best state to expand with h(n) = " << Front->hn << " is..." << endl;
    Display_Puzzle(Front->GameState);
    solved = SolvedState(Front-> GameState);
    while(!solved){
        if(Q.empty()){
            cout << "Failure" << endl;
            return;
        }
        //DisplayQ();
        Front = Q.at(Q.size()-1);
        Q.pop_back();
       // DisplayQ();
        Expand_Node(Front);
        sortQueue_hn();
       // DisplayQ();
        Front = Q.at(Q.size()-1);
        cout << "The best state to expand with h(n) = " << Front->hn << " is..." << endl;
        Display_Puzzle(Front->GameState);
        solved = SolvedState(Front-> GameState);
    }
    cout << "Goal State!" << endl;
    cout << "\nSolution depth was: " << Front->depth << endl;
    cout << "Number of Nodes Expanded: " << nodes_Expanded << endl;
    
}


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
        //DisplayFN();
        Front = Q.at(Q.size()-1);
        Q.pop_back();
        //DisplayFN();
        Expand_Node(Front);
        sortQueue_fn();
        //DisplayFN();
        Front = Q.at(Q.size()-1);
        cout << "The best state to expand with g(n) = " << Front->depth << " and h(n) = " << Front->hn << " is..." << endl;
        Display_Puzzle(Front->GameState);
        solved = SolvedState(Front-> GameState);
    }
    cout << "Goal State!" << endl;
    cout << "\nSolution depth was: " << Front->depth << endl;
    cout << "Number of Nodes Expanded: " << nodes_Expanded << endl;
    
}

#endif /* algorithm_h */
