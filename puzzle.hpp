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

//Retruns H(n) value with the Missing tile heuristic
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

//Retruns H(n) value with the Manhattan District heuristic
template <int rows, int cols>
int Get_M_Distance(int (&puzzle)[rows][cols]){
    int M_distance = 0;
    int temp = 0;
    
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            if(puzzle[i][j] != Solved_Puzzle[i][j]){
                if(i == 0 && j == 0){ //Checking tile 1
                    for (int x = 0; x < 3; ++x){
                        for (int y = 0; y < 3; ++y){
                            if(puzzle[x][y] == 1){
                                temp = abs(x-i) + abs(y-j);
                                M_distance = M_distance + temp;
                            }
                        }
                    }
                }
                else if(i == 0 && j == 1){ //Checking tile 2
                    for (int x = 0; x < 3; ++x){
                        for (int y = 0; y < 3; ++y){
                            if(puzzle[x][y] == 2){
                                temp = abs(x-i) + abs(y-j);
                                M_distance = M_distance + temp;
                            }
                        }
                    }
                }
                else if(i == 0 && j == 2){ //Checking tile 3
                    for (int x = 0; x < 3; ++x){
                        for (int y = 0; y < 3; ++y){
                            if(puzzle[x][y] == 3){
                                temp = abs(x-i) + abs(y-j);
                                M_distance = M_distance + temp;
                            }
                        }
                    }
                }
                else if(i == 1 && j == 0){ //Checking tile 4
                    for (int x = 0; x < 3; ++x){
                        for (int y = 0; y < 3; ++y){
                            if(puzzle[x][y] == 4){
                                temp = abs(x-i) + abs(y-j);
                                M_distance = M_distance + temp;
                            }
                        }
                    }
                }
                else if(i == 1 && j == 1){ //Checking tile 5
                    for (int x = 0; x < 3; ++x){
                        for (int y = 0; y < 3; ++y){
                            if(puzzle[x][y] == 5){
                                temp = abs(x-i) + abs(y-j);
                                M_distance = M_distance + temp;
                            }
                        }
                    }
                }
                else if(i == 1 && j == 2){ //Checking tile 6
                    for (int x = 0; x < 3; ++x){
                        for (int y = 0; y < 3; ++y){
                            if(puzzle[x][y] == 6){
                                temp = abs(x-i) + abs(y-j);
                                M_distance = M_distance + temp;
                            }
                        }
                    }
                }
                else if(i == 2 && j == 0){ //Checking tile 7
                    for (int x = 0; x < 3; ++x){
                        for (int y = 0; y < 3; ++y){
                            if(puzzle[x][y] == 7){
                                temp = abs(x-i) + abs(y-j);
                                M_distance = M_distance + temp;
                            }
                        }
                    }
                }
                else if(i == 2 && j == 1){ //Checking tile 8
                    for (int x = 0; x < 3; ++x){
                        for (int y = 0; y < 3; ++y){
                            if(puzzle[x][y] == 8){
                                temp = abs(x-i) + abs(y-j);
                                M_distance = M_distance + temp;
                            }
                        }
                    }
                }
                else if(i == 2 && j == 2){ //Checking tile 9
                    for (int x = 0; x < 3; ++x){
                        for (int y = 0; y < 3; ++y){
                            if(puzzle[x][y] == 0){
                                temp = abs(x-i) + abs(y-j);
                                M_distance = M_distance + temp;
                            }
                        }
                    }
                }
            }
        }
    }
    return M_distance;
}


#endif /* Puzzle_h */

