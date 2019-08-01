//Gurjit Kaur
//Nqueens solved using Stacks
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

bool issafe(vector< vector<string> > board, int row, int col) {
    int i,j;
    int n = board.size();
    for (i=0;i<row;i++) {
    if (board[i][col] == "Q") {
        return false;
    }
    }
    for (i=row, j=col; i>=0 && j>=0; i--, j--) 
        if (board[i][j] == "Q")
            return false;

    for (i=row, j=col; j<n && i>=0; i--, j++)
        if (board[i][j] == "Q")
            return false;
return true;
}
//vector of vector is how you make the matrix. because otherwise you simply have an 1D vector
bool solveNQueen(vector< vector<string> > board, stack< vector < vector <string> > > &s, int row, int column, int n) {
   //Base case
     if (row==n) //row/column
   {
      s.push(board); //print out the whole board
       return false; // this is where our recursion is ending
   }

   //recursive case
   //assume that bottom will get solved by recursion
   for (int column = 0; column < n; column++) //checks each column
   {
       //check if i,j is safe
   if(issafe(board,row,column)) {
       //place the queen
       board[row][column] = "Q";
   bool every_placed = solveNQueen(board, s, row+1,column, n); //checks every row in our board and recursively finding all our solutions
       if (every_placed == true) {     
           return true;
       }
       board[row][column] = ".";
   }
   }
return false; //now you are at the end of the column, moves back to the previous row
}

void print(stack < vector < vector <string> > > s){
    //now we have a stack containing all our posible solutions. we iterate through our stack and we display all our answers
    while(!s.empty())
    {
    vector < vector <string> > board = s.top();
    for (int row = 0; row < board.size(); row++) {
          for (int column = 0; column<board.size(); column++) {
              if (board[row][column] == "Q") {
                  cout << "Q ";
              }
              else {
                  cout << "_ ";
              }
          }
          cout << endl;
      }
    s.pop();
    cout << endl;
}   
}


int main() {
cout << "How many queens are we working with?" << endl;
int n;
cin >> n;
vector < vector <string> > board(n, vector<string>(n,"."));
stack < vector < vector <string> > > s; //stack of all the sol’ns
solveNQueen(board,s,0,0,n);
print(s);
}
