#ifndef puzzle_h
#define puzzle_h
#include <iostream>

using namespace std;

int Solved_Puzzle[3][3] = {1,2,3,4,5,6,7,8,0};

template <int rows, int cols>
//This function is used to diplay the puzzle as a 3x3 matrix.
void Display_Puzzle(int (&puzzle)[rows][cols]){
    cout << endl;
    for(int i = 0; i < 3; ++i){
        cout << "{ ";
        for(int j = 0; j < 3; ++j){
            cout << puzzle[i][j];
            cout << " ";
        }
        cout << "}";
        cout << endl;
    }
    cout << endl;
}

//This function is used to make moves within the puzzle using WASD.
template <int rows, int cols>
void Move_Puzzle(int (&puzzle)[rows][cols], char move, int &n, int &m){
    if(move == 'w'){ //up
        if(n != 0){
            puzzle[n][m] = puzzle[n-1][m];
            puzzle[n-1][m] = 0;
            n = n-1;
        }
    }
    else if(move == 'a'){ //left
        if(m != 0){
            puzzle[n][m] = puzzle[n][m-1];
            puzzle[n][m-1] = 0;
            m = m-1;
        }
    }
    else if(move == 's'){ //down
        if(n != 2){
            puzzle[n][m] = puzzle[n+1][m];
            puzzle[n+1][m] = 0;
            n = n+1;
        }
    }
    else if(move == 'd'){ //right
        if(m != 2){
            puzzle[n][m] = puzzle[n][m+1];
            puzzle[n][m+1] = 0;
            m = m+1;
        }
    }
}

//Used to assign puzzles to each other
template <int rows, int cols>
void AssignPuzzle(int (&puzzle)[rows][cols], int (&puzzle2)[rows][cols]){
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            puzzle[i][j] = puzzle2[i][j];
        }
    }
}

//Checks to see if the puzzle is solved
template <int rows, int cols>
bool SolvedState(int (&puzzle)[rows][cols]){
    bool solved = false;
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            if(puzzle[i][j] != Solved_Puzzle[i][j])
                return solved = false;
        }
    }
    return solved = true;
}

template <int rows, int cols>
int GetHn(int (&puzzle)[rows][cols]){
    int hn = 0;
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            if(puzzle[i][j] != Solved_Puzzle[i][j])
                ++hn;
        }
    }
    return hn;
}

#endif /* Puzzle_h */


//if(n != 2 || parent->prev != 'U'){
//    AssignPuzzle(temp, parent->GameState); //temp = puzzle
//    Move_Puzzle(temp, 's', n,m);
//    node* down = newNode(temp,n,m);
//    parent->down = down;
//    //Display_Puzzle(down->GameState);
//    n = parent->n;
//    m = parent->m;
//    down->hn = GetHn(down->GameState);
//    down->prev = 'D';
//    Q.push_back(parent->down);
//    Puzzles.push_back(parent->down);
//    //cout << down->hn << endl;
//}
//
//if(m != 2 || parent->prev != 'L'){
//    AssignPuzzle(temp, parent->GameState); //temp = puzzle
//    Move_Puzzle(temp, 'd', n,m);
//    node* right = newNode(temp,n,m);
//    parent->right = right;
//   //Display_Puzzle(right->GameState);
//    right->hn = GetHn(right->GameState);
//    right->prev = 'R';
//    Q.push_back(parent->right);
//    Puzzles.push_back(parent->right);
//    //cout << right->hn << endl;
//}
//}
