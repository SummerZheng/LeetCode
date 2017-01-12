#include<iostream>
#include<vector>
#include"print.h"

using namespace std;

const int sz = 9;

bool findCell2fill(const vector<vector<char>>& board, int& i, int& j) {
  for (i = 0; i != sz; ++i) {
    for (j = 0; j != sz; ++j) {
      if (board[i][j] == '.')
        return true;
    } 
  }
  return false;
}

bool validRow(const vector<vector<char>>& board, int i, char numChar) {
  for (int col = 0; col != sz; ++col) {
    if (board[i][col] == numChar)
      return false;
  }
  return true;
}

bool validCol(const vector<vector<char>>& board, int j, char numChar) {
  for (int row = 0; row != sz; ++row) {
    if (board[row][j] == numChar)
      return false;
  }
  return true;
}

bool validCell(const vector<vector<char>>& board, int i, int j, char numChar) {
  int ri = i/3*3, cj = j/3*3;
  for (int r = ri; r != ri + 3; ++r) {
    for (int c = cj; c != cj + 3; ++c) {
      if (board[r][c] == numChar)
        return false;
    }
  }
  return true;
}

bool validfill(const vector<vector<char>>& board, int i, int j, char num) {
  if (validRow(board, i, num) && validCol(board, j, num) && validCell(board, i, j, num))
    return true;
  return false;
}

bool solveSudoku_util(vector<vector<char>>& board) {
  int i = 0, j = 0;
  if (findCell2fill(board, i, j)) {
    for (int num = 1; num <= sz; ++num) {
      char numChar = '0' + num;
      if (validfill(board, i, j, numChar)) {
        board[i][j] = numChar;
        if (solveSudoku_util(board)) 
          return true;
        board[i][j] = '.';
      }
    }
    return false;
  }
  return true;
}

void solveSudoku(vector<vector<char>>& board) {
  solveSudoku_util(board);
}

int main() {
  vector<vector<char>> myBoard{
      {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
      {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
      {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
      {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
      {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
      {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
      {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
      {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
      {'.', '.', '.', '.', '8', '.', '.', '7', '9'},
      };
  solveSudoku(myBoard);
  print(myBoard);
  return 0;
}
