#include <iostream>
#include <vector>
#include "puzzle.hpp"
#include "algorithm.hpp"

using namespace std;

int main() {
    bool defaul = false;
    bool custom  = false;
    int choice;
    //n and m are used to keep track of where the '0' is in the puzzle. Either n(row) 0-2 or m(Column) 0-2.
    int n = 1;
    int m = 1;
    //This stores the value of the Default puzzle
    int Default_Puzzle[9] = {1,6,7,5,0,3,4,8,2};
    int puzzle[3][3];
    node* root;
    
    //Intro asking if default or cusstom puzzle.
    cout << "Welcome to 8-Puzzle Solver\nType 1 to use defualt puzzle or 2 to input your own" << endl;
    cin >> choice;
    if(choice == 1)
        defaul = true;
    if(choice == 2)
        custom = true;
    
    
    //Deciding what to do if either 1 or 2 is chosen.
    //Default Puzzle
    if(defaul){
        int x = 0;
        cout << "Default Puzzle" << endl;
        for (int i = 0; i < 3; ++i){
            for (int j = 0; j < 3; ++j){
                puzzle[i][j] = Default_Puzzle[x];
                ++x;
            }
        }
        root = newNode(puzzle,n,m);
        Display_Puzzle(root->GameState);
    }
    //Costum Puzzle
    else{
        bool hasZero = false;
        int x;
        cout << "Enter your Puzzle" << endl;
        for(int i = 0; i < 3; ++i){
            cout << "Input 3 numbers for row " << i+1 << " with a space in between then hit enter" << endl;
            for(int j = 0; j < 3; ++j){
                cin >> x;
                puzzle[i][j] = x;
                if(x == 0){
                    hasZero = true;
                    n = i;
                    m = j;
                }
            }
        }
        root = newNode(puzzle,n,m);
        Display_Puzzle(root->GameState);
        //Checks if puzzle has a 0, if not it terminates program.
        if(!hasZero){
            cout << "!!ERROR: Puzzle does not contain a 0!!" << endl;
            return 0;
        }
    }
    
    //Ask User which algoithm they want to run...
    int decision = 0;
    cout << "Chose an Algorithm. (1) for Unifrom Search, (2) for A* misplaced tile Search, (3) for A* Manhattan Search" << endl;
    cin >> decision;
    if(decision == 1){
        Uniform_Search(root);
    }
    else if(decision == 2){
        A_Star_Search(root);
    }
    else{
        A_Star_Search_Manhattan(root);
    }
    
    return 0;
}

