//
// Created by Ege Tan on 21.10.2024.
//
#include "stack.h"

using namespace std;

//place the queen function is implemented in order to create a safe placement
//this function increment all the squares that a queen threaten.
void place_the_queen(int row, int col, vector<vector<int>>& safeMatrix, int size)
{
    // Increment the count for all cells to the right of the queen's position in the same row
    for (int i = col + 1; i < size; ++i)
    {
        safeMatrix[row][i]++;
    }
    // Increment the count for all cells to the left of the queen's position in the same row
    for (int i = col - 1; i >= 0; --i)
    {
        safeMatrix[row][i]++;
    }
    // Increment the count for all cells below the queen's position in the same column
    for (int i = row + 1; i < size; ++i)
    {
        safeMatrix[i][col]++;
    }
    // Increment the count for all cells above the queen's position in the same column
    for (int i = row - 1; i >= 0; --i)
    {
        safeMatrix[i][col]++;
    }
    // Increment the count for all cells in the upper-left diagonal from the queen's position
    for (int i = 1; row - i >= 0 && col - i >= 0; ++i)
    {
        safeMatrix[row - i][col - i]++;
    }
    // Increment the count for all cells in the bottom-right diagonal from the queen's position
    for (int i = 1; row + i < size && col + i < size; ++i)
    {
        safeMatrix[row + i][col + i]++;
    }
    // Increment the count for all cells in the upper-right diagonal from the queen's position
    for (int i = 1; row - i >= 0 && col + i < size; ++i)
    {
        safeMatrix[row - i][col + i]++;
    }
    // Increment the count for all cells in the bottom-left diagonal from the queen's position
    for (int i = 1; row + i < size && col - i >= 0; ++i)
    {
        safeMatrix[row + i][col - i]++;
    }
}
//place the queen function is implemented in order to create a safe placement
//this function decrement all the squares that a queen threaten.
void remove_the_queen(int row, int col, vector<vector<int>>& safeMatrix, int size)
{
    // Decrement the count for all cells to the right of the queen's position in the same row
    for (int i = col + 1; i < size; ++i)
    {
        safeMatrix[row][i]--;
    }
    // Decrement the count for all cells to the left of the queen's position in the same row
    for (int i = col - 1; i >= 0; --i)
    {
        safeMatrix[row][i]--;
    }
    // Decrement the count for all cells below the queen's position in the same column
    for (int i = row + 1; i < size; ++i)
    {
        safeMatrix[i][col]--;
    }
    // Decrement the count for all cells above the queen's position in the same column
    for (int i = row - 1; i >= 0; --i)
    {
        safeMatrix[i][col]--;
    }
    // Decrement the count for all cells in the upper-left diagonal from the queen's position
    for (int i = 1; row - i >= 0 && col - i >= 0; ++i)
    {
        safeMatrix[row - i][col - i]--;
    }
    // Decrement the count for all cells in the bottom-right diagonal from the queen's position
    for (int i = 1; row + i < size && col + i < size; ++i)
    {
        safeMatrix[row + i][col + i]--;
    }
    // Decrement the count for all cells in the upper-right diagonal from the queen's position
    for (int i = 1; row - i >= 0 && col + i < size; ++i)
    {
        safeMatrix[row - i][col + i]--;
    }
    // Decrement the count for all cells in the bottom-left diagonal from the queen's position
    for (int i = 1; row + i < size && col - i >= 0; ++i)
    {
        safeMatrix[row + i][col - i]--;
    }
    // Reset the queen's position to 0, indicating it is now unoccupied
    safeMatrix[row][col] = 0;
}
//this function checks wheter a square is safe or not
bool is_safe(int row, int col, const vector<vector<int>>& safeMatrix)
{
    return safeMatrix[row][col] == 0;
}
//if a solution is found by main function , here it is appended to the another
//matrix that holds all the solutions (required for filestream)
void save_solution(const vector<int>& soln, vector<vector<int>>& totalSolution)
{
    totalSolution.push_back(soln);
}
//this function is a helper function for file output , it proivdes a specific format
string print_list(const vector<int>& vec)
{
    string res = "[";
    for (int i = 0; i < vec.size(); ++i)
    {
        res += to_string(vec[i]);
        if (i != vec.size()-1)
        {
            res+= ", ";
        }
    }
    res += "]";
    return res;
}

int main()
{
    int size_input{0};
    cout << "Enter the value of N for the N-Queens problem: ";
    cin >> size_input;
    if (0<size_input && size_input<14)//while input is between 0 and 14
    {
        //vector for hollding all the solutions
        vector<vector<int>> totalSolution;
        int row {0}, col {0};

        //holding for 1 solution
        vector<int> soln(size_input, -1);
        //board
        vector<vector<int>> board(size_input, vector<int>(size_input, 0));
        //stack that includes row-col pair for keeping the place of queens
        stack<pair<int, int>> mystack(size_input);
        //output file stream
        ofstream outputFile(to_string(size_input) + "queens_solutions.txt");
        while (true)
        {
            //for checking wheter a queen is placed or not
            bool placed = false;
            //iterating between each columns
            while (col < size_input)
            {
                //if a safe square is found
                if (is_safe(row, col, board))
                {
                    soln[row] = col;
                    //place the queen to that square
                    place_the_queen(row, col, board, size_input);
                    //push the coordinates of the queen to the stack
                    mystack.push({row, col});
                    //go to next row
                    row ++;
                    col = 0;
                    //make placed variable true
                    placed = true;
                    break;
                }
                col ++;
            }
            //placement is happened
            if (placed)
            {
                //starting for backtrack process
                if (row == size_input)
                {
                    //first save solution to the vector
                    save_solution(soln, totalSolution);
                    int prevRow = mystack.top().first;
                    int prevCol = mystack.top().second;
                    //take last position of queen from the stack and pop it
                    //for backtracking
                    mystack.pop();
                    row = prevRow;
                    col = prevCol + 1;
                    remove_the_queen(row, soln[row], board, size_input);
                    soln[row] = -1;
                }
            }
            else
            {
                if (mystack.empty()) // if every scenario is tried (end of the program)
                {
                    outputFile << "Total solutions for N="<<size_input<<": "<< totalSolution.size()<< endl << endl;
                    for (int i = 0; i < totalSolution.size(); ++i)
                    {
                        outputFile << "Solution " << i+1 << ": "<< print_list(totalSolution[i])<<endl;
                    }
                    outputFile.close();
                    cout << "Solutions have been saved to '" << size_input << "queens_solutions.txt'" << endl;
                    break;
                }
                //if a solution is not found yet
                int prevRow = mystack.top().first;
                int prevCol = mystack.top().second;
                mystack.pop();
                row = prevRow;
                col = prevCol + 1;
                remove_the_queen(row, soln[row], board, size_input);
                soln[row] = -1;
            }
        }
        //cout << "Enter the value of N for the N-Queens problem: ";
        //cin >> size_input;
    }
    else{cout << "Invalid input. Please enter a positive integer" <<endl;}
    return 0;
}
